#!/usr/bin/env python3
"""Container-side runner for the differential-fuzzing oracle (runs INSIDE
`ddiv-oracle`, pure stdlib -- no ddiv deps, no network).

Two modes (selected by config `mode`), so the corpus is fuzzed ONCE per bundle and reused:
  * generate -- build ORIG, verify baseline-repro, fuzz ORIG ONCE with a FIXED seed, freeze the
                deduped corpus (seeds + queue + crashes) to /work/corpus_out + corpus_meta.json.
                `fuzz_ok` is gated on AFL actually launching (fuzzer_stats) -- a launch failure is
                reported, never silently degraded to a seed-only corpus.
  * replay   -- build orig+cand, load the FROZEN corpus (no fuzzing), and adjudicate per-input
                divergence: crash-status / crash-signature / EXIT-CODE / same full variable state.
                It also measures llvm-cov coverage of the target function as the INTACT-confidence.

Fuzzing the SAME frozen corpus for every arm makes model comparison fair + reproducible (the old
one-shot fuzz-per-arm gave each candidate a different, RNG-dependent corpus).

"Same observable behaviour" on a non-crashing input means MORE than identical stdout/stderr:
when the harness emits an ``argv[2]`` exit-memstate dump (the func0 functional harnesses fold
the return value + every output buffer into ``vb_digest`` and dump ALL writable globals), we
compare the two runs' FULL post-call variable state -- by-name, relocation-masked symbol
digests, the sound cross-binary compare ported from ``ddiv.functional``. Harnesses that
don't dump (cve_barebone / github_barebone print their result) fall back to the stdout/stderr
compare. So "the two functions behave identically" is asserted over every variable the harness
can observe, not just what it happened to print.

It writes `/work/out/result.json`. The HOST facility (oracle/difffuzz.py) does the
splice, invokes this in Docker, and may refine crash-pattern divergences via crashparse.

Config (read from /work/config.json):
  { "orig_dir","cand_dir","entry","flags","target_func","fuzz_seconds",
    "seeds_dir","replay_timeout","poc_should_crash" }
Verdict vocabulary: INTACT | DEVIATED | BUILD_FAILED | INFRA  (DECOMPILE_FAILED/SPLICE_FAILED
are decided host-side before we run).
"""
import json, os, re, shutil, signal, stat, subprocess, sys, glob, hashlib, time

WORK = "/work"
OUT = os.path.join(WORK, "out")
CFLAGS = "-fsanitize=address -fno-omit-frame-pointer -g -O1"
AFL_ENV = {
    "AFL_SKIP_CPUFREQ": "1", "AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES": "1",
    "AFL_NO_AFFINITY": "1", "AFL_USE_ASAN": "1",
    # Skip (don't ABORT on) seeds that crash/time-out in the dry run. Some bundles have an
    # input-controlled slow path (e.g. a large parsed loop count) that exceeds AFL's 1000ms
    # dry-run limit on ONE seed -> without this AFL PROGRAM ABORTs -> no fuzzer_stats -> the
    # whole bundle mis-reads as a corpus-gen failure (INFRA). Paired with `-t <ms>+` below.
    "AFL_IGNORE_SEED_PROBLEMS": "1",
    "ASAN_OPTIONS": "abort_on_error=1:detect_leaks=0:symbolize=0",
}
# Replay-run sanitizer options. symbolize=1 (+ UBSan print_stacktrace + llvm-symbolizer in the
# image) gives a SYMBOLIZED stack -> stable FUNCTION-name crash identity, which is what
# crash_signature anchors on (a source line is a coordinate, not identity). This is replay-only;
# the fuzzing env (AFL_ENV) keeps symbolize=0 so fuzz throughput is unaffected.
RUN_ASAN = "abort_on_error=1:detect_leaks=0:symbolize=1:dedup_token_length=3"
RUN_UBSAN = "print_stacktrace=1:halt_on_error=1"
# Fixed AFL RNG seed -> reproducible corpus generation (frozen once per bundle, replayed for
# every arm). Overridable but constant by default so the same bundle yields the same corpus.
AFL_SEED = os.environ.get("DDIV_AFL_SEED", "1337")
DEFAULT_FUZZ_SECONDS = 3600
ORACLE_VERSION = 2
_HARNESS_MARKER = "VB_DIFFFUZZ_OBSERVERS_V2"


def sh(cmd, cwd=None, env=None, timeout=None):
    e = dict(os.environ); e.update(env or {})
    # start_new_session -> the child leads its OWN process group, so a timeout can reap the WHOLE
    # tree. subprocess.run(timeout=)+PIPE kills only the direct child and then blocks in
    # communicate() until every pipe write-end closes -- a fuzz target hung in deep recursion
    # (CWE-674) or a slow parse (tcpdump) inherits that fd and holds it open, so the container runs
    # to the docker kill long past the fuzz's own 608s cap. killpg on timeout is what enforces it.
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


def build(src_dir, entry, flags, out_bin):
    """AFL+ASAN build. Returns (ok, log)."""
    cmd = (f"afl-clang-fast {CFLAGS} {flags} -o {out_bin} {entry} -lm")
    rc, log = sh(cmd, cwd=src_dir, env=AFL_ENV, timeout=300)
    ok = rc == 0 and os.path.exists(os.path.join(src_dir, out_bin))
    return ok, log


# Sanitizer-FREE flags for the exit-memstate dump build (mirrors ddiv.functional's
# CLEAN_CFLAGS). Why a SECOND build: ASAN puts a redzone after every global, so vb_dump's bulk
# [.data][.bss] read walks off vb_digest's redzone and traps global-buffer-overflow -- i.e. the
# dump itself "crashes" under ASAN. The dump must therefore come from a clean build; the ASAN
# build stays for crash detection + fuzzing. (This is the two-build split the functional axis uses.)
CLEAN_CFLAGS = "-g -O0 -fno-omit-frame-pointer -ffunction-sections"


def _nonsan(flags):
    """Drop -fsanitize*/-fno-sanitize* tokens (keep -I/-D/etc.) for the sanitizer-free build."""
    return " ".join(t for t in flags.split()
                    if not t.startswith("-fsanitize") and not t.startswith("-fno-sanitize"))


def build_clean(src_dir, entry, flags, out_bin):
    """Sanitizer-free build supplying the memstate dump. Best-effort: on failure the caller
    degrades to the stdout/stderr compare. Bundle sanitizer flags are stripped (no redzones)."""
    cmd = f"clang {CLEAN_CFLAGS} {_nonsan(flags)} -o {out_bin} {entry} -lm"
    rc, log = sh(cmd, cwd=src_dir, timeout=300)
    ok = rc == 0 and os.path.exists(os.path.join(src_dir, out_bin))
    return ok, log


def instrument_generated_harness(src_dir, entry, target_func):
    """Enable DiffFuzz's richer observer protocol in an auto-generated functional harness.

    Bundles are immutable, so this edits only the per-run scratch copy.  The generated harness
    shape is deliberately regular: argument construction lives after the seed cursor setup and
    the call/fold block ends immediately before ``vb_dump``.  We wrap that payload in a two-call
    loop with freshly reconstructed arguments, fold the target's ``errno`` after each call, and
    fold the full zeroed capacity of lone heap-array arguments (the canonical harness otherwise
    observes only their logical prefix).  Both corpus generation and replay call this function,
    so AFL and every arm see exactly the same program.

    Custom CVE harnesses are left untouched: duplicating an arbitrary ownership-sensitive call
    would be unsound.  They still receive the runner-level stdout/stderr + filesystem observers.
    """
    path = os.path.join(src_dir, entry)
    try:
        text = open(path, encoding="utf-8").read()
    except (OSError, UnicodeError):
        return False
    if _HARNESS_MARKER in text:
        return True
    if "auto-generated by ddiv.funcharness" not in text or not target_func:
        return False

    lines = text.splitlines()
    try:
        main_i = next(i for i, line in enumerate(lines) if re.search(r"\bint\s+main\s*\(", line))
        dump_i = next(i for i in range(main_i + 1, len(lines))
                      if "vb_dump(argc>2?argv[2]" in lines[i])
    except StopIteration:
        return False

    call_re = re.compile(r"\b" + re.escape(target_func) + r"\s*\(")
    call_is = [i for i in range(main_i + 1, dump_i) if call_re.search(lines[i])]
    if len(call_is) != 1:
        return False
    call_i = call_is[0]

    # New harnesses set VB_LIT after initializing the cursor; legacy harnesses only have the
    # cursor assignment.  Resetting to the last such setup point reconstructs identical fresh
    # caller arguments for call two while retaining target-owned globals/heap from call one.
    anchors = [i for i in range(main_i + 1, call_i)
               if "VB_CUR=buf; VB_N=nread; VB_I=0;" in lines[i]
               or "if(VB_LIT){ VB_I=VB_LIT_MAGIC_LEN; }" in lines[i]]
    if not anchors:
        return False
    payload_i = anchors[-1] + 1

    payload = lines[payload_i:dump_i]
    rel_call = call_i - payload_i
    call_indent = re.match(r"\s*", payload[rel_call]).group(0)
    payload[rel_call:rel_call + 1] = [
        call_indent + "errno = 0;",
        payload[rel_call],
        call_indent + "int vb_errno_after_call = errno;",
        call_indent + "vb_mix(&vb_errno_after_call, sizeof vb_errno_after_call);",
    ]

    # Lone numeric pointer arguments use a deterministic calloc(VB_ARRCAP) backing store.  Fold
    # all of it, not only the API's logical prefix, so an in-allocation over-write is observable.
    # Paired array+length arguments are already folded over their complete allocation.
    cap_vars = []
    cap_re = re.compile(r"\b(?P<var>a\d+)\s*=\s*\([^)]*\)\s*calloc\(VB_ARRCAP\s*,")
    for line in payload:
        m = cap_re.search(line)
        if m:
            cap_vars.append((m.group("var"), "float" in line or "double" in line))
    heap_fold = []
    for var, floating in cap_vars:
        if floating:
            heap_fold.append(
                f"  for(int _vb_heap_k=0; _vb_heap_k<VB_ARRCAP; ++_vb_heap_k) "
                f"{{ vb_mix_d((double){var}[_vb_heap_k]); }}")
        else:
            heap_fold.append(f"  vb_mix({var}, (unsigned long)VB_ARRCAP * sizeof *{var});")
    payload.extend(heap_fold)

    # Scope each iteration so the generated argument/return declarations may be repeated.  The
    # digest intentionally accumulates call 1 then call 2, making their ordered observations part
    # of one final memstate while target-owned persistent state remains live between calls.
    loop = [
        "  /* " + _HARNESS_MARKER + ": errno + reachable heap outputs + stateful call sequence. */",
        "  const long vb_seed_i = VB_I;",
        "  for(int vb_call_index=0; vb_call_index<2; ++vb_call_index){",
        "    VB_I = vb_seed_i;",
    ]
    loop.extend(("  " + line) if line else line for line in payload)
    loop.append("  }")
    lines[payload_i:dump_i] = loop

    if not any("#include <errno.h>" in line for line in lines):
        include_i = next((i + 1 for i, line in enumerate(lines) if line.startswith("#include")), 0)
        lines.insert(include_i, "#include <errno.h>")
    try:
        with open(path, "w", encoding="utf-8") as fh:
            fh.write("\n".join(lines) + "\n")
    except OSError:
        return False
    return True


CRASH_SIG_KEYS = ("ERROR: AddressSanitizer", "runtime error:", "SUMMARY:",
                  "ERROR: libFuzzer", "UndefinedBehaviorSanitizer")


# A source `file:line:col` is a COORDINATE, not a crash identity: comments / reformatting / the
# decompiler re-synthesizing the function all move the coordinate while the same check fails. So the
# fingerprint anchors on (check_kind, symbolized top FUNCTION frames) and never on file:line.
_UBSAN_STRIP = re.compile(r"0x[0-9a-fA-F]+|-?\d+|'[^']*'")
_FRAME = re.compile(r"^\s*#\d+\s+0x[0-9a-fA-F]+\s+in\s+(\S+)")


def _ubsan_kind(msg):
    """Normalized UBSan check_kind: strip operand VALUES / addresses / quoted type names (and any
    embedded numbers) so a commutative reorder ('999999999 * 10' vs '10 * 999999999') or a line/col
    change never alters identity. Keeps the check phrase ('signed integer overflow', ...)."""
    s = _UBSAN_STRIP.sub("", msg).lower()
    return re.sub(r"\s+", " ", s).strip()


def _top_funcs(text, k=3):
    """Top K meaningful FUNCTION names from the symbolized crash stack -- the stable identity
    (a function is identity; a line is a coordinate). Skips libc/sanitizer runtime frames."""
    out = []
    for line in text.splitlines():
        m = _FRAME.match(line)
        if not m:
            continue
        fn = m.group(1)
        if fn in ("_start", "start", "__libc_start_main", "__libc_start_call_main"):
            continue
        if fn.startswith(("__asan", "__ubsan", "__sanitizer", "__interceptor")):
            continue
        out.append(fn)
        if len(out) >= k:
            break
    return out


def crash_signature(text):
    """Coordinate-free crash fingerprint = check_kind (weakness) anchored on the symbolized top
    FUNCTION frames -- NEVER file:line. A line-number change alone must never read as a different
    crash; two same-weakness crashes in the same function are the same crash regardless of how the
    decompiler renumbered the source. Host crashparse further refines via CWE + ASAN dedup."""
    kind = None
    for line in text.splitlines():
        if "AddressSanitizer:" in line:
            kind = "asan:" + line.split("AddressSanitizer:", 1)[1].strip().split(" ")[0]; break
        if "runtime error:" in line:
            kind = "ubsan:" + _ubsan_kind(line.split("runtime error:", 1)[1]); break
    if kind is None:
        kind = "crash"
    # Anchor on the TOP faulting function only (k=1): a faithful candidate can legitimately
    # restructure the call path below it (inline a helper) without changing the crash, so deeper
    # frames are call CONTEXT, not identity -- including them would false-shift on that artifact.
    funcs = _top_funcs(text, k=1)
    return f"{kind}@{funcs[0]}" if funcs else kind


def _filesystem_observation(root):
    """Stable final-state fingerprint for files created below an isolated execution cwd.

    Regular-file contents, symlink targets, empty directories, and special-file kinds are part of
    the observation; mtimes, inode numbers, ownership, and host paths are deliberately excluded.
    """
    out = {}
    for base, dirs, files in os.walk(root, topdown=True, followlinks=False):
        dirs.sort(); files.sort()
        relbase = os.path.relpath(base, root)
        for name in dirs + files:
            path = os.path.join(base, name)
            rel = name if relbase == "." else os.path.join(relbase, name)
            try:
                mode = os.lstat(path).st_mode
                if stat.S_ISREG(mode):
                    with open(path, "rb") as fh:
                        out[rel] = "file:" + hashlib.sha256(fh.read()).hexdigest()
                elif stat.S_ISLNK(mode):
                    out[rel] = "link:" + os.readlink(path)
                elif stat.S_ISDIR(mode):
                    out[rel] = "dir"
                elif stat.S_ISSOCK(mode):
                    out[rel] = "socket"
                elif stat.S_ISFIFO(mode):
                    out[rel] = "fifo"
                else:
                    out[rel] = "special"
            except OSError:
                out[rel] = "unreadable"
    return out


def run_one(binary, inp, timeout, dump_path=None, observe_fs=False):
    """Run `binary inp [dump_path]`. When `dump_path` is given it is passed as argv[2] (the
    harness's exit-memstate dump target) and its bytes are read back into `dump` -- None if the
    harness ignores argv[2] (cve_barebone/github_barebone) or the run crashed/failed to write."""
    argv = [binary, inp]
    if dump_path:
        argv.append(dump_path)
        try:
            if os.path.exists(dump_path):
                os.remove(dump_path)                 # never read a previous run's dump
        except OSError:
            pass
    run_dir = os.path.join(WORK, "run_env")
    env = {"ASAN_OPTIONS": RUN_ASAN, "UBSAN_OPTIONS": RUN_UBSAN}
    cwd = None
    if observe_fs:
        # Every invocation starts from the same empty cwd.  This prevents one corpus input (or the
        # original arm) from polluting the next and makes relative file effects comparable.
        shutil.rmtree(run_dir, ignore_errors=True)
        os.makedirs(run_dir)
        env.update({"HOME": run_dir, "TMPDIR": run_dir, "XDG_RUNTIME_DIR": run_dir})
        cwd = run_dir
    rc, out = sh(argv, cwd=cwd, env=env, timeout=timeout)
    crashed = (rc < 0) or (rc >= 128) or any(k in out for k in CRASH_SIG_KEYS)
    sig = crash_signature(out) if crashed else None
    # observable output = stdout+stderr with volatile bits stripped (addresses, pids)
    obs = _norm(out) if not crashed else None
    obs_preview = _norm_text(out)[:500] if not crashed else None
    fs = _filesystem_observation(run_dir) if observe_fs and not crashed else None
    dump = None
    if dump_path and not crashed and os.path.exists(dump_path):
        try:
            with open(dump_path, "rb") as fh:
                dump = fh.read()
        except OSError:
            dump = None
    if observe_fs:
        shutil.rmtree(run_dir, ignore_errors=True)
    return {"rc": rc, "crashed": crashed, "sig": sig, "obs": obs,
            "obs_preview": obs_preview, "fs": fs, "dump": dump, "log": out[-4000:]}


import re
_HEX = re.compile(r"0x[0-9a-fA-F]+")
_NUM = re.compile(r"\b\d{4,}\b")
def _norm_text(s):
    return _HEX.sub("0xADDR", s).strip()


def _norm(s):
    """Hash the complete normalized stream; a difference after byte 2000 must not disappear."""
    return hashlib.sha256(_norm_text(s).encode("utf-8", "replace")).hexdigest()


# --------------------------------------------------------------------------- #
# exit-memstate compare (ALL variable data) -- ported from ddiv.functional,
# pure stdlib (nm + readelf, both present in the image). The func0 functional harness
# dumps [.data][.bss] (return + outputs folded into vb_digest + every module global) to
# argv[2]; we compare orig-vs-cand BY SYMBOL NAME with load-time-address slots masked, so
# the compare is sound across two SEPARATELY-LINKED binaries (their .data/.bss addresses
# and relocations differ purely from the spliced function's code size).
# --------------------------------------------------------------------------- #

def _nm(binary, extra=()):
    try:
        p = subprocess.run(["nm", *extra, binary], stdout=subprocess.PIPE,
                           stderr=subprocess.DEVNULL, timeout=60)
        return p.stdout.decode("utf-8", "replace")
    except (OSError, subprocess.SubprocessError):
        return ""


def relocated_windows(binary):
    """(offset,size) windows in the [.data][.bss] dump that hold LOAD-TIME ADDRESSES (any
    R_X86_64_* dynamic-reloc slot: const-pointer tables, hooks structs, __dso_handle). These
    are PIE-base/layout noise that shift between the two relinked binaries and carry zero func0
    signal, so they are masked on BOTH sides. A genuine heap/stack-address leak into a zero-init
    .bss global has NO static reloc -> not masked -> stays detectable."""
    nm = _nm(binary)
    try:
        rl = subprocess.run(["readelf", "-rW", binary], stdout=subprocess.PIPE,
                            stderr=subprocess.DEVNULL, timeout=60).stdout.decode("utf-8", "replace")
    except (OSError, subprocess.SubprocessError):
        return []
    syms = {}
    for ln in nm.splitlines():
        p = ln.split()
        if len(p) == 3:
            try:
                syms[p[2]] = int(p[0], 16)
            except ValueError:
                pass
    try:
        ds, ed, bs, en = syms["__data_start"], syms["_edata"], syms["__bss_start"], syms["_end"]
    except KeyError:
        return []
    dlen = ed - ds
    wins = []
    for ln in rl.splitlines():
        p = ln.split()
        if len(p) < 3 or not p[2].startswith("R_X86_64"):
            continue
        try:
            off = int(p[0], 16)
        except ValueError:
            continue
        if ds <= off < ed:
            wins.append((off - ds, 8))
        elif bs <= off < en:
            wins.append((dlen + (off - bs), 8))
    return wins


def data_bss_symbol_offsets(binary):
    """{symbol: (dump_offset, size)} for every writable named global (nm d/D/b/B), indexing the
    [__data_start.._edata)+[__bss_start.._end) dump. {} if bounds unreadable -> caller degrades to
    stdout compare. Names give a permutation-invariant, layout-independent by-symbol compare."""
    nm = _nm(binary, ("-S",))
    syms, bounds = {}, {}
    for ln in nm.splitlines():
        p = ln.split()
        try:
            if len(p) == 3 and p[2] in ("__data_start", "_edata", "__bss_start", "_end"):
                bounds[p[2]] = int(p[0], 16)
            elif len(p) == 4 and p[2] in ("d", "D", "b", "B"):
                syms[p[3]] = (int(p[0], 16), int(p[1], 16), p[2].lower())
        except ValueError:
            pass
    try:
        ds, ed, bs, en = (bounds["__data_start"], bounds["_edata"],
                          bounds["__bss_start"], bounds["_end"])
    except KeyError:
        return {}
    dlen = ed - ds
    out = {}
    for name, (addr, size, kind) in syms.items():
        if kind == "d" and ds <= addr < ed:
            out[name] = (addr - ds, size)
        elif kind == "b" and bs <= addr < en:
            out[name] = (dlen + (addr - bs), size)
    return out


def symbol_digests(dump, offsets, windows):
    """{symbol: sha1hex} of each symbol's reloc-masked bytes sliced from `dump`. A symbol whose
    bytes fall past the dump end (truncated I/O-flake write) is omitted."""
    out = {}
    n = len(dump)
    for name, (off, size) in offsets.items():
        if off < 0 or off + size > n:
            continue
        seg = bytearray(dump[off:off + size])
        for woff, wsz in windows:
            lo, hi = max(off, woff), min(off + size, woff + wsz)
            for i in range(lo, hi):
                seg[i - off] = 0
        out[name] = hashlib.sha1(bytes(seg)).hexdigest()
    return out


def corpus_inputs(seeds_dir, afl_out):
    seen, files = set(), []
    dirs = [seeds_dir, os.path.join(afl_out, "default", "queue"),
            os.path.join(afl_out, "default", "crashes")]
    for d in dirs:
        if not os.path.isdir(d):
            continue
        for f in sorted(glob.glob(os.path.join(d, "*"))):
            if not os.path.isfile(f) or os.path.basename(f) in ("README.txt", ".state"):
                continue
            h = hashlib.sha1(open(f, "rb").read()).hexdigest()
            if h in seen:
                continue
            seen.add(h); files.append(f)
    return files


def coverage(src_dir, entry, target_func, corpus):
    """Best-effort llvm-cov of the target function over the corpus. Never fatal."""
    try:
        rc, _ = sh(f"clang -O1 -g -fprofile-instr-generate -fcoverage-mapping "
                   f"-o cov.bin {entry} -lm", cwd=src_dir, timeout=180)
        cb = os.path.join(src_dir, "cov.bin")
        if rc != 0 or not os.path.exists(cb):
            return None
        pf = os.path.join(src_dir, "pf"); os.makedirs(pf, exist_ok=True)
        for i, inp in enumerate(corpus):
            sh([cb, inp], env={"LLVM_PROFILE_FILE": os.path.join(pf, f"{i}.profraw")},
               timeout=10)
        raws = glob.glob(os.path.join(pf, "*.profraw"))
        if not raws:
            return None
        md = os.path.join(src_dir, "m.profdata")
        if sh(["llvm-profdata-14", "merge", "-sparse", *raws, "-o", md])[0] != 0:
            return None
        rc, rep = sh(["llvm-cov-14", "report", cb, f"-instr-profile={md}",
                      "-show-functions", entry], cwd=src_dir)
        for line in rep.splitlines():
            if target_func in line:
                nums = re.findall(r"(\d+\.\d+)%", line)
                if len(nums) >= 3:
                    return {"regions_pct": float(nums[0]), "lines_pct": float(nums[1]),
                            "branches_pct": float(nums[2])}
        return {"raw": rep[-400:]}
    except Exception as ex:
        return {"error": str(ex)}


def _setup_seeds(seeds_dir):
    """Copy the bundle's io/input seeds (or a benign fallback) into /work/seeds. Returns
    (seeds_dir, n). seeds sort so s0000 == io/input/0 (the PoC when present)."""
    seeds = os.path.join(WORK, "seeds"); os.makedirs(seeds, exist_ok=True)
    n = 0
    if seeds_dir and os.path.isdir(seeds_dir):
        for f in sorted(glob.glob(os.path.join(seeds_dir, "*"))):
            if os.path.isfile(f):
                shutil.copy(f, os.path.join(seeds, f"s{n:04d}")); n += 1
    if n == 0:
        for i, b in enumerate([b"1\n", b"0", b"42\n", b"\x00\x01\x02\x03"]):
            open(os.path.join(seeds, f"s{i:04d}"), "wb").write(b); n += 1
    return seeds, n


def do_generate(cfg):
    """CORPUS GENERATION -- run ONCE per bundle, independent of any candidate arm. Build orig,
    verify baseline-repro, fuzz orig ONCE with a FIXED seed, freeze the deduped corpus to
    /work/corpus_out. Writes /work/out/corpus_meta.json with `fuzz_ok` (AFL launched, gated on
    fuzzer_stats), `corpus_source` ("fuzz" | "seeds_fallback"), and `corpus_ok` (a usable corpus
    exists). If AFL can't fuzz (typically: every seed crashes) we FALL BACK to the bundle's curated
    io corpus rather than silently emitting a seed-only INTACT -- the fallback is explicit and only
    used when a real io corpus exists. The host freezes corpus_out + this meta and replays the SAME
    corpus for every arm, so model comparison is fair + reproducible."""
    meta = {"fuzz_ok": False, "corpus_ok": False, "corpus_source": None, "afl_rc": None,
            "afl_seed": AFL_SEED, "corpus_size": 0, "baseline_ok": True,
            "fuzz_seconds": int(cfg.get("fuzz_seconds", DEFAULT_FUZZ_SECONDS)),
            "oracle_version": ORACLE_VERSION}
    mp = os.path.join(OUT, "corpus_meta.json")
    def _emit():
        json.dump(meta, open(mp, "w"), indent=1)
    orig_dir, entry, flags = cfg["orig_dir"], cfg["entry"], cfg.get("flags", "")
    target_func = cfg.get("target_func", "")
    secs = int(cfg.get("fuzz_seconds", DEFAULT_FUZZ_SECONDS)); rt = int(cfg.get("replay_timeout", 10))
    seeds_dir = cfg.get("seeds_dir") or ""

    meta["enhanced_harness"] = instrument_generated_harness(orig_dir, entry, target_func)
    ok_o, log_o = build(orig_dir, entry, flags, "orig_bin")
    if not ok_o:
        meta["error"] = "orig build failed"; meta["build_log"] = log_o[-1500:]; _emit(); return
    orig_bin = os.path.join(orig_dir, "orig_bin")
    seeds, _ = _setup_seeds(seeds_dir)

    # baseline-repro: orig MUST reproduce the reference crash on the PoC (io/input/0) if the
    # bundle baseline crashed; else the whole differential is unsound for this bundle.
    poc = (os.path.join(seeds_dir, "0")
           if seeds_dir and os.path.isfile(os.path.join(seeds_dir, "0")) else None)
    if cfg.get("poc_should_crash") and poc:
        if not run_one(orig_bin, poc, rt)["crashed"]:
            meta["baseline_ok"] = False
            meta["error"] = "baseline no-repro (orig clean on PoC)"; _emit(); return

    if cfg.get("no_fuzz"):
        # Fuzzing disabled -- a pathological reference (e.g. CWE-674 deep recursion whose fuzz
        # target setsid's out of the killable process group and rides the container to its docker
        # kill). Skip AFL and freeze the crafted io corpus directly: still a valid differential
        # replay set (the 25 safe + 25 triggering inputs), so the bundle gets a real verdict
        # instead of sinking to INFRA. Marked corpus_source="no_fuzz_fallback".
        corpus = sorted(f for f in glob.glob(os.path.join(seeds, "*")) if os.path.isfile(f))
        if not corpus:
            meta["error"] = "no_fuzz requested but no io seeds to replay"; _emit(); return
        meta["corpus_source"] = "no_fuzz_fallback"
        cout = os.path.join(WORK, "corpus_out"); shutil.rmtree(cout, ignore_errors=True)
        os.makedirs(cout)
        for i, f in enumerate(corpus):
            try:
                shutil.copy(f, os.path.join(cout, f"c{i:05d}"))
            except OSError:
                pass
        meta["corpus_size"] = len(corpus); meta["corpus_ok"] = True; _emit(); return

    # fuzz ORIG once, FIXED seed -> the frozen corpus reused by every arm.
    afl_out = os.path.join(WORK, "afl_out"); shutil.rmtree(afl_out, ignore_errors=True)
    # -t 5000+ : 5s dry-run tolerance, and the '+' SKIPS still-slower seeds instead of aborting
    # (a single slow seed must not sink corpus generation for the whole bundle).
    fcmd = (f'setarch "$(uname -m)" -R timeout {secs + 8} '
            f'afl-fuzz -m none -s {AFL_SEED} -t 5000+ -i {seeds} -o {afl_out} -V {secs} -- {orig_bin} @@')
    afl_rc, _ = sh(fcmd, env=AFL_ENV, timeout=secs + 60)
    meta["afl_rc"] = afl_rc
    # AFL launched iff it wrote fuzzer_stats.
    meta["fuzz_ok"] = os.path.exists(os.path.join(afl_out, "default", "fuzzer_stats"))
    if meta["fuzz_ok"]:
        corpus = corpus_inputs(seeds, afl_out)          # seeds + AFL queue + AFL crashes
        meta["corpus_source"] = "fuzz"
    else:
        # FALLBACK: AFL can't grow a corpus (the common cause is that EVERY seed crashes, so there
        # is no clean seed to fuzz from -- AFL aborts "need at least one valid input that does not
        # crash"). But the bundle's CURATED io corpus (the crafted 25-safe + 25-triggering
        # differential set) is itself a valid replay set: replaying it on orig vs cand still tells
        # us whether the candidate reproduces vs vanishes/shifts each crash. So fall back to the io
        # seeds directly. This is EXPLICITLY marked (corpus_source="seeds_fallback") so it is never
        # mistaken for a fuzzed result; INFRA only if there is genuinely nothing to replay.
        corpus = sorted(f for f in glob.glob(os.path.join(seeds, "*")) if os.path.isfile(f))
        if not corpus:
            meta["error"] = f"afl did not launch (rc={afl_rc}) and no io seeds to replay"
            _emit(); return
        meta["corpus_source"] = "seeds_fallback"

    cout = os.path.join(WORK, "corpus_out"); shutil.rmtree(cout, ignore_errors=True)
    os.makedirs(cout)
    for i, f in enumerate(corpus):
        try:
            shutil.copy(f, os.path.join(cout, f"c{i:05d}"))
        except OSError:
            pass
    meta["corpus_size"] = len(corpus)
    meta["corpus_ok"] = True
    _emit()


def do_replay(cfg):
    """PER-ARM REPLAY -- reuse the FROZEN corpus (no fuzzing here), build orig+cand, and
    adjudicate each input: crash channels (ASAN), exit-code channel, then full-variable memstate
    (clean build) / stdout. Writes /work/out/result.json."""
    res = {"verdict": None, "build_orig": False, "build_cand": False,
           "oracle_version": ORACLE_VERSION, "external_state_compared": True}
    rp = os.path.join(OUT, "result.json")
    def _emit():
        json.dump(res, open(rp, "w"), indent=1)
    orig_dir, cand_dir = cfg["orig_dir"], cfg["cand_dir"]
    entry, flags = cfg["entry"], cfg.get("flags", "")
    target_func = cfg.get("target_func", "")
    rt = int(cfg.get("replay_timeout", 10))
    frozen = cfg.get("frozen_corpus") or ""

    enhanced_o = instrument_generated_harness(orig_dir, entry, target_func)
    enhanced_c = instrument_generated_harness(cand_dir, entry, target_func)
    res["enhanced_harness"] = bool(enhanced_o and enhanced_c)
    res["multi_call"] = bool(enhanced_o and enhanced_c)

    # 1) ASAN build both (crash detection; the strict build-rate signal).
    ok_o, log_o = build(orig_dir, entry, flags, "orig_bin"); res["build_orig"] = ok_o
    if not ok_o:
        res["verdict"] = "INFRA"; res["error"] = "orig build failed"; res["build_log"] = log_o[-2000:]
        _emit(); return
    ok_c, log_c = build(cand_dir, entry, flags, "cand_bin"); res["build_cand"] = ok_c
    if not ok_c:
        res["verdict"] = "BUILD_FAILED"; res["build_error"] = log_c[-3000:]; _emit(); return
    orig_bin, cand_bin = os.path.join(orig_dir, "orig_bin"), os.path.join(cand_dir, "cand_bin")

    # 1b) sanitizer-free build both -> exit-memstate dump (all-variable compare). Best-effort.
    clean_ok_o, _ = build_clean(orig_dir, entry, flags, "orig_clean")
    clean_ok_c, _ = build_clean(cand_dir, entry, flags, "cand_clean")
    orig_clean = os.path.join(orig_dir, "orig_clean")
    cand_clean = os.path.join(cand_dir, "cand_clean")

    # 2) load the FROZEN corpus (same inputs for every arm -- no per-arm re-fuzzing).
    corpus = sorted(f for f in glob.glob(os.path.join(frozen, "*")) if os.path.isfile(f)) \
        if frozen and os.path.isdir(frozen) else []
    res["corpus_size"] = len(corpus)
    if not corpus:
        res["verdict"] = "INFRA"; res["error"] = "empty/missing frozen corpus"; _emit(); return

    # 3) memstate setup. Dump comes from the CLEAN binaries (no ASAN redzones). memstate_on
    # requires both clean builds, readable bounds, AND a probe that the harness writes a dump.
    dump_o = os.path.join(WORK, "dump_o.bin")
    dump_c = os.path.join(WORK, "dump_c.bin")
    dump_o2 = os.path.join(WORK, "dump_o2.bin")
    o_off = c_off = {}
    o_win = c_win = []
    memstate_on = False
    if clean_ok_o and clean_ok_c:
        o_off, o_win = data_bss_symbol_offsets(orig_clean), relocated_windows(orig_clean)
        c_off, c_win = data_bss_symbol_offsets(cand_clean), relocated_windows(cand_clean)
        if o_off and c_off:
            probe = run_one(orig_clean, corpus[0], rt, os.path.join(WORK, "dump_probe.bin"))
            memstate_on = probe["dump"] is not None

    # 4) differential replay. Priority: crash-status -> crash-signature -> EXIT CODE -> memstate.
    # BOUNDED: a candidate that hangs on many inputs (idioms/sk2 infinite loops are common on real
    # code) would otherwise cost rt per input and blow the container timeout -> a LEAKED, hung
    # container that chokes the box. Cap the replay at `budget` wall-seconds and, once the candidate
    # is known to hang, skip the (expensive) rt*3 re-confirm on later hangs.
    budget = int(cfg.get("replay_budget", 360))    # caps hangs well under the 600s container timeout
    deadline = time.time() + budget
    divs = []
    n_memstate = 0
    hang_confirmed = False
    for inp in corpus:
        if time.time() > deadline:
            res["replay_truncated"] = True             # verdict stands on what we replayed
            break
        # ASAN, NO dump (argv[2] absent -> vb_dump is a no-op).  The isolated cwd observer makes
        # stdout/stderr and relative filesystem effects first-class even when memstate is live.
        o = run_one(orig_bin, inp, rt, observe_fs=True)
        c = run_one(cand_bin, inp, rt, observe_fs=True)
        if o["rc"] == 124:                             # ORIG hangs here -> no valid reference -> skip
            continue
        dtype = None
        extra = {}
        if o["crashed"] != c["crashed"]:
            dtype = "vanished_crash" if o["crashed"] else "introduced_crash"
        elif o["crashed"] and c["crashed"]:
            if o["sig"] != c["sig"]:
                dtype = "shifted_crash"
        elif c["rc"] == 124:
            # CAND hangs while ORIG completed = an introduced non-termination. Confirm the FIRST
            # hang persistently (rt*3: a real infinite loop still times out, a contention-slowed run
            # finishes) so parallel load can't manufacture a hang; once confirmed, later hangs are
            # recorded directly (no re-confirm) to keep a pervasively-hanging candidate bounded.
            if hang_confirmed or run_one(cand_bin, inp, rt * 3)["rc"] == 124:
                hang_confirmed = True
                dtype = "introduced_hang"
                extra = {"compare": "hang"}
        elif o["rc"] in (64, 125, 126, 127):
            # Only when ORIG fails to establish a reference on this input (harness usage / exec
            # failure) is the input non-adjudicable -> skip. A candidate that exec-fails while orig
            # ran fine is NOT skipped: it falls through to exit_code_diff below (o.rc != c.rc).
            pass
        elif o["rc"] != c["rc"]:
            # DIFFERENT (non-crash) exit status = a real behavioural divergence -- including the
            # candidate exec-failing (127/126/125) or usage-erroring (64) while orig ran fine.
            # Previously the rc was recorded but never compared, so this slipped through as INTACT.
            dtype = "exit_code_diff"
            extra = {"compare": "exit_code"}
        else:
            # Same non-crash exit code -> assert identical output, filesystem effects, and full
            # variable state.  Output/fs are peers of memstate, not a fallback: a function may
            # print or write a file while leaving return/output/global memory unchanged.
            compare_channels = []
            if o["obs"] != c["obs"]:
                compare_channels.append("stdout")
                extra.update({"orig_output": o.get("obs_preview"),
                              "cand_output": c.get("obs_preview")})
            if o.get("fs") != c.get("fs"):
                compare_channels.append("filesystem")
                ofs, cfs = o.get("fs") or {}, c.get("fs") or {}
                extra["wrong_paths"] = sorted(
                    p for p in (set(ofs) | set(cfs)) if ofs.get(p) != cfs.get(p))[:12]

            oc = cc = None
            if memstate_on:
                oc = run_one(orig_clean, inp, rt, dump_o)
                cc = run_one(cand_clean, inp, rt, dump_c)
            if oc and cc and oc["dump"] is not None and cc["dump"] is not None \
                    and not oc["crashed"] and not cc["crashed"]:
                n_memstate += 1
                od = symbol_digests(oc["dump"], o_off, o_win)
                cd = symbol_digests(cc["dump"], c_off, c_win)
                wrong = sorted(s for s in (set(od) | set(cd)) if od.get(s) != cd.get(s))
                if wrong:
                    # Guard: trust a memstate diff only if ORIG reproduces it (flaky-global guard).
                    o2 = run_one(orig_clean, inp, rt, dump_o2)
                    if (not o2["crashed"]) and o2["dump"] is not None \
                            and symbol_digests(o2["dump"], o_off, o_win) == od:
                        compare_channels.append("memstate")
                        extra["wrong_syms"] = wrong[:12]
            if compare_channels:
                dtype = "silent_wrong_answer"
                extra["compare"] = "+".join(compare_channels)
        if dtype:
            d = {"input": os.path.basename(inp),
                 "input_hex": open(inp, "rb").read()[:64].hex(),
                 "type": dtype,
                 "orig": {"crashed": o["crashed"], "sig": o["sig"], "rc": o["rc"]},
                 "cand": {"crashed": c["crashed"], "sig": c["sig"], "rc": c["rc"]},
                 "orig_log": o["log"] if o["crashed"] else None,
                 "cand_log": c["log"] if c["crashed"] else None}
            d.update(extra)
            divs.append(d)

    res["memstate_compared"] = memstate_on
    res["memstate_inputs"] = n_memstate
    res["n_divergent"] = len(divs)
    res["divergences"] = divs[:50]
    res["verdict"] = "DEVIATED" if divs else "INTACT"
    # coverage is the INTACT-confidence -- only meaningful (and only worth its cost) for a clean,
    # fully-replayed INTACT. Skip it on DEVIATED or a truncated replay (saves ~100s on exactly the
    # slow/hanging bundles that motivated the budget).
    res["coverage"] = (coverage(orig_dir, entry, target_func, corpus)
                       if (not divs and not res.get("replay_truncated")) else None)
    _emit()


def main():
    os.makedirs(OUT, exist_ok=True)
    cfg = json.load(open(os.path.join(WORK, "config.json")))
    if cfg.get("mode") == "generate":
        do_generate(cfg)
    else:
        do_replay(cfg)


if __name__ == "__main__":
    try:
        main()
    except Exception as ex:
        import traceback
        os.makedirs(OUT, exist_ok=True)
        tb = traceback.format_exc()[-2000:]
        try:
            _mode = json.load(open(os.path.join(WORK, "config.json"))).get("mode", "replay")
        except Exception:
            _mode = "replay"
        if _mode == "generate":
            json.dump({"fuzz_ok": False, "error": str(ex), "trace": tb},
                      open(os.path.join(OUT, "corpus_meta.json"), "w"), indent=1)
        else:
            json.dump({"verdict": "INFRA", "error": str(ex), "trace": tb},
                      open(os.path.join(OUT, "result.json"), "w"), indent=1)
    finally:
        # We run as ROOT in the container; AFL crash files land mode 0600 and the built binaries
        # are root-owned. Make everything host-readable/removable so the host can freeze the
        # corpus AND cleanly rmtree the scratch (else root-owned files leak scratch dirs forever).
        try:
            subprocess.run(["chmod", "-R", "0777", "/work"],
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        except Exception:
            pass
