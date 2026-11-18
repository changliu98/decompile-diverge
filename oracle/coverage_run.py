#!/usr/bin/env python3
"""Container-side source-coverage measurement of a bundle's FROZEN differential corpus.

Reads /work/config.json, rebuilds the REFERENCE (original) harness with LLVM source-based
coverage instrumentation, replays every frozen corpus input, and reports region/line/branch
coverage OF THE TARGET FUNCTION. Pure stdlib; result lands in /work/out/coverage.json
(read from the FILE, never from stdout -- nested-docker stdout races empty under load).

Three things this does that the inline `coverage()` in difffuzz_run.py did not:

  * it resolves the target function's OWN file. `harness.c` does `#include "func.c"`, so
    filtering the report on the entry TU hid the target of every functional bundle -- only
    the single-file cve_barebone harnesses ever parsed a number, which is why five of the
    six rows of the paper's reach table had no backing artifact.
  * CONTINUOUS profiling (`%c` + `-runtime-counter-relocation`), so inputs that CRASH still
    contribute their coverage. Counters are otherwise flushed by an atexit hook a crashing
    run never reaches -- and crashes are ~40% of a cve_barebone corpus, including the
    reference PoC itself. Measured worth ~7pp of line coverage on a crash-heavy bundle.
  * it records RAW COUNTS, not just percentages, so a function with no branches is reported
    as undefined (denominator 0) instead of silently averaging in as 0%.

The build is sanitizer-free at -O0 (mirrors difffuzz's CLEAN_CFLAGS): source line/branch
coverage is only meaningful against unoptimized source, and ASAN redzones/aborts would
change which inputs terminate.
"""
import glob
import json
import os
import re
import shutil
import signal
import subprocess

WORK = "/work"
OUT = os.path.join(WORK, "out")

# -O0 so line/branch coverage maps to SOURCE structure; continuous profiling so crashing
# inputs still count. -ffunction-sections mirrors difffuzz's clean build.
COV_CFLAGS = ("-g -O0 -fno-omit-frame-pointer -ffunction-sections "
              "-fprofile-instr-generate -fcoverage-mapping "
              "-mllvm -runtime-counter-relocation")

# name may be bare ("func0") or file-qualified ("harness.c:am_writestring"), then three
# (total, missed, pct) groups: regions, lines, branches.
_ROW = re.compile(r"^(\S+)\s+(\d+)\s+(\d+)\s+([\d.]+)%"
                  r"\s+(\d+)\s+(\d+)\s+([\d.]+)%"
                  r"\s+(\d+)\s+(\d+)\s+([\d.]+)%\s*$")


def sh(cmd, cwd=None, env=None, timeout=None):
    """Run cmd, reaping the whole process group on timeout (a hung target otherwise holds
    the pipe open and rides the container to the outer docker kill)."""
    e = dict(os.environ)
    e.update(env or {})
    p = subprocess.Popen(cmd, cwd=cwd, env=e, shell=isinstance(cmd, str),
                         stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                         start_new_session=True)
    try:
        out, _ = p.communicate(timeout=timeout)
        return p.returncode, out.decode("utf-8", "replace")
    except subprocess.TimeoutExpired:
        try:
            os.killpg(os.getpgid(p.pid), signal.SIGKILL)
        except (ProcessLookupError, PermissionError):
            p.kill()
        try:
            out, _ = p.communicate(timeout=30)
        except subprocess.TimeoutExpired:
            out = b""
        return 124, (out or b"").decode("utf-8", "replace")


def _nonsan(flags):
    """Drop -fsanitize*/-fno-sanitize* (keep -I/-D/...) -- the coverage build is clean."""
    return " ".join(t for t in flags.split()
                    if not t.startswith("-fsanitize") and not t.startswith("-fno-sanitize"))


def _cell(total, missed):
    """A coverage cell that stays honest about an empty denominator."""
    total, missed = int(total), int(missed)
    covered = total - missed
    return {"total": total, "covered": covered,
            "pct": (100.0 * covered / total) if total else None}


def _parse(report, target_func):
    """Pull the target's row out of an llvm-cov `-show-functions` report.

    Returns (record, match_mode). Exact match on the (de-qualified) name is required first;
    a unique substring match is accepted as a fallback in case llvm-cov elides a long name,
    and is flagged so the aggregate can audit it.
    """
    rows = []
    for line in report.splitlines():
        m = _ROW.match(line.strip())
        if not m:
            continue
        name = m.group(1)
        if name == "TOTAL":
            continue
        rows.append((name.rsplit(":", 1)[-1], m))

    def rec(m):
        return {"regions": _cell(m.group(2), m.group(3)),
                "lines": _cell(m.group(5), m.group(6)),
                "branches": _cell(m.group(8), m.group(9))}

    exact = [m for n, m in rows if n == target_func]
    if len(exact) == 1:
        return rec(exact[0]), "exact"
    if len(exact) > 1:                       # same name in >1 file: unresolvable, be explicit
        return None, "ambiguous"
    part = [m for n, m in rows if target_func and target_func in n]
    if len(part) == 1:
        return rec(part[0]), "substring"
    return None, "not_found"


def relax_perms():
    """Make everything under /work host-deletable before exiting.

    The container runs as root while the scratch tree belongs to the invoking user, so the
    profraw/report dirs we create land root-owned mode 755 -- and unlinking a file needs write
    permission on its PARENT directory, so the host's cleanup silently no-ops (rmtree runs with
    ignore_errors) and every run leaks its scratch. Left unfixed this leaked 1.1 GB over a full
    run. Best-effort: never let a chmod failure lose the result we just computed.
    """
    for root, dirs, files in os.walk(WORK):
        for name in dirs + files:
            try:
                os.chmod(os.path.join(root, name), 0o777)
            except OSError:
                pass


def main():
    os.makedirs(OUT, exist_ok=True)
    cfg = json.load(open(os.path.join(WORK, "config.json")))
    src = cfg["orig_dir"]
    entry = cfg.get("entry", "harness.c")
    relpath = cfg.get("relpath") or entry
    target = cfg.get("target_func", "")
    flags = _nonsan(cfg.get("flags", "") or "")
    tmo = int(cfg.get("replay_timeout", 10))
    res = {"bundle": cfg.get("bundle", ""), "target_func": target, "relpath": relpath,
           "opt": "-O0", "continuous": True, "ok": False}

    corpus = sorted(f for f in glob.glob(os.path.join(WORK, "corpus", "*"))
                    if os.path.isfile(f))
    res["n_inputs"] = len(corpus)
    if not corpus:
        res["error"] = "empty corpus"
        json.dump(res, open(os.path.join(OUT, "coverage.json"), "w"), indent=1)
        return

    rc, log = sh(f"clang {COV_CFLAGS} {flags} -o cov.bin {entry} -lm", cwd=src, timeout=300)
    cb = os.path.join(src, "cov.bin")
    if rc != 0 or not os.path.exists(cb):
        # -runtime-counter-relocation is the one exotic flag; retry without it rather than
        # lose the bundle (crash inputs then stop contributing -- recorded, not silent).
        rc2, log2 = sh(f"clang {COV_CFLAGS.replace('-mllvm -runtime-counter-relocation', '')} "
                       f"{flags} -o cov.bin {entry} -lm", cwd=src, timeout=300)
        if rc2 != 0 or not os.path.exists(cb):
            res["error"] = "build failed"
            res["build_log"] = (log or "")[-1500:]
            json.dump(res, open(os.path.join(OUT, "coverage.json"), "w"), indent=1)
            return
        res["continuous"] = False

    pf = os.path.join(src, "pf")
    shutil.rmtree(pf, ignore_errors=True)
    os.makedirs(pf, exist_ok=True)
    n_crash = n_timeout = 0
    for i, inp in enumerate(corpus):
        # argv[2] = the memstate dump path the generated harnesses expect; /dev/null keeps
        # the replay shape identical to difffuzz's without writing anything.
        pat = ("%c" if res["continuous"] else "") + f"{i}.profraw"
        r, _ = sh([cb, inp, "/dev/null"], env={"LLVM_PROFILE_FILE": os.path.join(pf, pat)},
                  timeout=tmo)
        if r == 124:
            n_timeout += 1
        elif r < 0 or r >= 128:
            n_crash += 1
    res["n_crashed"], res["n_timeout"] = n_crash, n_timeout

    raws = glob.glob(os.path.join(pf, "*.profraw"))
    if not raws:
        res["error"] = "no profraw"
        json.dump(res, open(os.path.join(OUT, "coverage.json"), "w"), indent=1)
        return
    md = os.path.join(src, "m.profdata")
    rc, mlog = sh(["llvm-profdata-14", "merge", "-sparse", "-o", md] + raws, timeout=600)
    if rc != 0 or not os.path.exists(md):
        res["error"] = "profdata merge failed"
        res["merge_log"] = (mlog or "")[-800:]
        json.dump(res, open(os.path.join(OUT, "coverage.json"), "w"), indent=1)
        return

    # Ask for BOTH the target's own file and the entry TU: llvm-cov qualifies a row with the
    # file it attributes the function to, which is not always the file we spliced into.
    files = [relpath] + ([entry] if entry != relpath else [])
    rc, rep = sh(["llvm-cov-14", "report", cb, f"-instr-profile={md}",
                  "-show-functions"] + files, cwd=src, timeout=300)
    rec, mode = _parse(rep, target)
    res["match"] = mode
    if rec is None:
        res["error"] = f"target row {mode}"
        res["report_tail"] = (rep or "")[-1200:]
    else:
        res.update(rec)
        res["ok"] = True
    json.dump(res, open(os.path.join(OUT, "coverage.json"), "w"), indent=1)


if __name__ == "__main__":
    try:
        main()
    except Exception as ex:
        import traceback
        os.makedirs(OUT, exist_ok=True)
        json.dump({"ok": False, "error": str(ex), "trace": traceback.format_exc()[-1500:]},
                  open(os.path.join(OUT, "coverage.json"), "w"), indent=1)
    finally:
        relax_perms()
