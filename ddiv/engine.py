"""Python build/fuzz/replay engine. Invoked only INSIDE the Docker toolchain.

Based on oracle_aflpp/difffuzz_run_v3.py's two-build split, frozen reference
corpus, isolated execution cwd, and confirmation on BOTH programs. Kept
independent so ddiv can be copied/installed without VanishBench or its dataset.
"""
import hashlib
import json
import os
import platform
import random
import re
import resource
import shutil
import signal
import subprocess
import sys
import time
import traceback
from pathlib import Path

from . import __version__
from .state import (blob, channel_values, crash_signature, differences, elf_layout,
                    filesystem, observations, symbol_states)

WORK = Path("/work")
TOOL = Path(__file__).resolve().parent
TEMP = Path("/tmp/ddiv")
MAX_FILE = 64 * 1024 * 1024


def write_json(path, value):
    path = Path(path)
    tmp = path.with_suffix(path.suffix + ".tmp")
    tmp.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n")
    tmp.replace(path)


def _limits():
    resource.setrlimit(resource.RLIMIT_CORE, (0, 0))
    resource.setrlimit(resource.RLIMIT_FSIZE, (MAX_FILE, MAX_FILE))


def execute(cmd, *, timeout, cwd, env, stdout, stderr=None, executable=None):
    """No shell or pipes; bound output files and kill the process group on exit."""
    with open(stdout, "wb") as out, open(stderr or os.devnull, "wb") as err:
        proc = subprocess.Popen(cmd, executable=executable, cwd=cwd, env=env,
                                stdin=subprocess.DEVNULL, stdout=out,
                                stderr=err if stderr else subprocess.STDOUT,
                                start_new_session=True, preexec_fn=_limits)
        timed_out = False
        try:
            proc.wait(timeout=timeout)
        except subprocess.TimeoutExpired:
            timed_out = True
        finally:
            try:
                os.killpg(proc.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            proc.wait(timeout=5)
    return proc.returncode, timed_out


def base_env():
    # Identical environment for both arms, without passing host credentials.
    return {"PATH": os.environ["PATH"], "LANG": "C", "LC_ALL": "C", "TZ": "UTC",
            "ASAN_SYMBOLIZER_PATH": shutil.which("llvm-symbolizer") or "/usr/bin/llvm-symbolizer",
            "TMPDIR": str(TEMP / "run"), "ASAN_OPTIONS":
            "abort_on_error=1:detect_leaks=0:symbolize=1:allocator_may_return_null=1",
            "UBSAN_OPTIONS": "halt_on_error=1:print_stacktrace=1"}


def build(cfg, result):
    builds, layouts = {}, {}
    for side in ("left", "right"):
        dest = WORK / "build" / side
        dest.mkdir(parents=True)
        source = cfg["programs"][side]["container_path"]
        common = ["-I", str(TOOL / "include"), *cfg["cflags"], "-g", "-O0",
                  "-fno-omit-frame-pointer", "-fno-common", "-fno-pie"]
        # Freeze the source bytes actually compiled (the original mount is read-only).
        frozen_source = dest / "program.c"
        shutil.copyfile(source, frozen_source)
        common += ["-I", cfg["programs"][side]["include_dir"]]
        for flavor in ("clean", "sanitized"):
            compiler = result["toolchain"]["cc"] if flavor == "clean" else "afl-clang-fast"
            flags = common + ([] if flavor == "clean" else
                              ["-fsanitize=address,undefined", "-fno-sanitize-recover=all"])
            obj = dest / (flavor + ".o")
            runtime = dest / (flavor + "-state.o")
            binary = dest / flavor
            commands = [
                [compiler, *flags, "-c", str(frozen_source), "-o", str(obj)],
                [result["toolchain"]["cc"], *flags, *(["-D", "DDIV_CLEAN"] if flavor == "clean" else []),
                 "-c", str(TOOL / "runtime/state.c"), "-o", str(runtime)],
            ]
            extra = []
            if cfg["input_mode"] == "argv":
                extra = [str(TOOL / "runtime/argv.c"), "-Wl,--wrap=main"]
            commands.append([compiler, *flags, str(obj), str(runtime), *extra,
                             *cfg["ldflags"], "-no-pie", "-Wl,--emit-relocs",
                             "-o", str(binary), "-lm"])
            record = {"commands": commands, "ok": True, "logs": []}
            result["builds"][side + "." + flavor] = record
            for index, cmd in enumerate(commands):
                log = dest / (flavor + ".%d.log" % index)
                rc, expired = execute(cmd, timeout=120, cwd=dest, env=base_env(), stdout=log)
                record["logs"].append(str(log.relative_to(WORK)))
                if rc or expired:
                    record.update(ok=False, returncode=rc, timed_out=expired,
                                  error=log.read_text(errors="replace")[-6000:])
                    result.update(status="BUILD_FAILED", error=side + " " + flavor + " build failed")
                    return None, None
            builds[side + "." + flavor] = binary
            if flavor == "clean":
                layouts[side] = elf_layout(binary, obj)
                write_json(dest / "layout.json", layouts[side])
    return builds, layouts


def target_args(cfg, input_path):
    args = list(cfg["args"])
    if cfg["input_mode"] == "file":
        if any("@@" in arg for arg in args):
            return [arg.replace("@@", str(input_path)) for arg in args]
        return [str(input_path), *args]
    return args


def default_seeds(seed):
    rng = random.Random(seed)
    values = [b"", b"0\n", b"1\n", b"-1\n", b"2\n", b"42\n", b"255\n", b"256\n",
              b"2147483647\n", b"-2147483648\n", b"0 0\n", b"1 2\n", b"hello\n",
              b"\0", bytes(32), b"\xff" * 32, bytes(range(32)), b"A" * 128]
    values += [bytes(rng.randrange(256) for _ in range(n)) for n in (4, 8, 16, 32, 64)]
    return values


def generate(cfg, binary):
    seeds = WORK / "seeds"
    seeds.mkdir(exist_ok=True)
    if not cfg["supplied_seeds"]:
        for i, data in enumerate(default_seeds(cfg["seed"])):
            (seeds / ("seed-%04d" % i)).write_bytes(data)
    meta = {"seed": cfg["seed"], "requested_seconds": cfg["seconds"],
            "fuzz_ok": False, "source": "replay" if cfg["replay_only"] else "seeds_only"}
    if cfg["seconds"] > 0 and not cfg["replay_only"]:
        afl_seeds = WORK / "afl-seeds"
        afl_seeds.mkdir()
        # AFL rejects empty seeds; still keep them in the corpus we replay.
        for f in sorted(seeds.iterdir()):
            if f.stat().st_size:
                shutil.copyfile(f, afl_seeds / f.name)
        if not any(afl_seeds.iterdir()):
            (afl_seeds / "bootstrap").write_bytes(b"\0")
        run_dir = TEMP / "run"
        run_dir.mkdir(parents=True, exist_ok=True)
        inp = TEMP / "input"
        env = base_env()
        env.update(AFL_SKIP_CPUFREQ="1", AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES="1",
                   AFL_NO_AFFINITY="1", AFL_IGNORE_SEED_PROBLEMS="1", AFL_NO_UI="1",
                   ASAN_OPTIONS="abort_on_error=1:detect_leaks=0:symbolize=0:allocator_may_return_null=1")
        cmd = ["afl-fuzz", "-i", str(afl_seeds), "-o", str(WORK / "afl"),
               "-m", "none", "-s", str(cfg["seed"]), "-t", str(round(cfg["timeout"] * 1000)) + "+",
               "-V", str(cfg["seconds"]),
               *(["-f", str(inp)] if cfg["input_mode"] == "file" else []), "--", str(binary),
               *target_args(cfg, inp)]
        rc, expired = execute(cmd, timeout=cfg["seconds"] + 30, cwd=run_dir, env=env,
                              stdout=WORK / "afl.log")
        stats_path = WORK / "afl/default/fuzzer_stats"
        stats = {}
        if stats_path.is_file():
            for line in stats_path.read_text().splitlines():
                if ":" in line:
                    key, value = line.split(":", 1)
                    stats[key.strip()] = value.strip()
        ok = bool(stats) and int(stats.get("execs_done", "0")) > 0 and not expired and rc == 0
        meta.update(fuzz_ok=ok, source="afl++" if ok else "seeds_fallback",
                    command=cmd, returncode=rc, timed_out=expired, stats=stats,
                    log="afl.log")
    corpus = WORK / "corpus"
    corpus.mkdir()
    ledger, seen = [], set()
    for root in (seeds, WORK / "afl/default/queue", WORK / "afl/default/crashes",
                 WORK / "afl/default/hangs"):
        if not root.is_dir():
            continue
        for f in sorted(root.iterdir()):
            if not f.is_file() or f.name == "README.txt":
                continue
            data = f.read_bytes()
            sha = hashlib.sha256(data).hexdigest()
            if sha in seen:
                continue
            seen.add(sha)
            name = "%06d" % len(ledger)
            (corpus / name).write_bytes(data)
            ledger.append({"file": "corpus/" + name, "sha256": sha, "size": len(data),
                           "source": str(f.relative_to(WORK))})
    meta.update(size=len(ledger), inputs=ledger,
                sha256=hashlib.sha256("\n".join(x["sha256"] for x in ledger).encode()).hexdigest())
    write_json(WORK / "corpus.json", meta)
    return meta


def run_one(cfg, binary, data, flavor, layout, keep=None):
    run_dir, capture = TEMP / "run", TEMP / "capture"
    for path in (run_dir, capture):
        if path.exists():
            shutil.rmtree(path)
        path.mkdir(parents=True)
    inp = TEMP / "input"
    inp.write_bytes(data)
    env = base_env()
    env["ASAN_OPTIONS"] += ":log_path=" + str(capture / "sanitizer")
    env["UBSAN_OPTIONS"] += ":log_path=" + str(capture / "sanitizer")
    if flavor == "clean":
        env.update(DDIV_STATE_PATH=str(capture / "globals.bin"),
                   DDIV_OBSERVATIONS_PATH=str(capture / "observations.bin"))
    out, err = capture / "stdout", capture / "stderr"
    with inp.open("rb") as feed, out.open("wb") as stdout, err.open("wb") as stderr:
        proc = subprocess.Popen(["program", *target_args(cfg, inp)], executable=str(binary),
                                stdin=feed if cfg["input_mode"] != "file" else subprocess.DEVNULL,
                                stdout=stdout, stderr=stderr, cwd=run_dir, env=env,
                                start_new_session=True, preexec_fn=_limits)
        expired = False
        try:
            proc.wait(timeout=cfg["timeout"])
        except subprocess.TimeoutExpired:
            expired = True
        finally:
            try:
                os.killpg(proc.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            proc.wait(timeout=5)
    diagnostic = b"\n".join(p.read_bytes() for p in sorted(capture.glob("sanitizer.*")))
    # Older sanitizer runtimes occasionally leave the report on stderr.
    diagnostic_text = (diagnostic + b"\n" + err.read_bytes()).decode("utf-8", "replace")
    crash = None if expired else crash_signature(diagnostic_text, proc.returncode)
    status = "timeout" if expired else "crashed" if crash else "exited"
    result = {"status": status, "returncode": proc.returncode, "crash": crash,
              "stdout": blob(out.read_bytes()), "stderr": blob(err.read_bytes()),
              "diagnostic": diagnostic_text[-12000:], "files": filesystem(run_dir)}
    errors, globals_, observed = [], None, {}
    if proc.returncode == -signal.SIGXFSZ:
        errors.append("resource limit: execution exceeded the file/output size limit")
    if flavor == "clean" and status == "exited":
        try:
            globals_ = symbol_states((capture / "globals.bin").read_bytes(), layout)
            opath = capture / "observations.bin"
            observed = observations(opath.read_bytes() if opath.exists() else b"")
        except (OSError, ValueError, UnicodeError) as ex:
            errors.append("post-state capture: " + str(ex))
    if keep:
        shutil.copytree(capture, keep)
        shutil.copytree(run_dir, keep / "files")
    return result, globals_, observed, errors


def run_pair(cfg, builds, layouts, data, keep=None):
    pair = {}
    for side in ("left", "right"):
        post = {"errors": []}
        for flavor in ("sanitized", "clean"):
            path = keep / side / flavor if keep else None
            run, globals_, observed, errors = run_one(
                cfg, builds[side + "." + flavor], data, flavor, layouts[side], path)
            post[flavor] = run
            post["errors"].extend(errors)
            if flavor == "clean":
                post.update(globals=globals_, observations=observed)
        pair[side] = post
    return pair


def confirm(cfg, builds, layouts, data, pair, channels):
    """Port of V3's _stable_both/_dump_stable: four EXTRA runs of each side.

    Confirm each differing channel independently. A random log must not hide a
    stable global difference, and a flaky global must not become a counterexample.
    """
    stable = set(channels)
    values = {side: channel_values(pair[side]) for side in pair}
    for _ in range(cfg["confirmations"]):
        again = run_pair(cfg, builds, layouts, data)
        for side in pair:
            current = channel_values(again[side])
            stable = {key for key in stable if current.get(key) == values[side].get(key)}
        if not stable:
            break
    return sorted(stable)


def compare(cfg, builds, layouts, result):
    meta = result["corpus"]
    counts = {"total": meta["size"], "checked": 0, "equal": 0, "unresolved": 0,
              "truncated": False, "confirmations": cfg["confirmations"]}
    result["comparison"] = counts
    result["unresolved_inputs"] = []
    deadline = time.monotonic() + cfg["replay_seconds"]
    for entry in meta["inputs"]:
        if time.monotonic() >= deadline:
            counts["truncated"] = True
            break
        data = (WORK / entry["file"]).read_bytes()
        pair = run_pair(cfg, builds, layouts, data)
        counts["checked"] += 1
        changed = differences(pair["left"], pair["right"])
        stable = confirm(cfg, builds, layouts, data, pair, changed) if changed else []
        # A confirmed timeout is a difference in completion under the configured
        # budget; it is not a mathematical assertion of nontermination.
        resource_error = any(e.startswith("resource limit:") for p in pair.values() for e in p["errors"])
        # Missing memory capture prevents a global comparison, but it does not
        # erase an independently confirmed stdout/exit/crash difference.
        if stable and not resource_error:
            witness = WORK / "counterexample"
            witness.mkdir()
            (witness / "input").write_bytes(data)
            # Preserve the raw output, diagnostics, dumps, and files from a final
            # replay. Check it too so the stored witness matches the confirmed one.
            final = run_pair(cfg, builds, layouts, data, witness)
            stable = [key for key in stable if all(channel_values(final[s]).get(key) ==
                       channel_values(pair[s]).get(key) for s in pair)]
            if any(e.startswith("resource limit:") for p in final.values() for e in p["errors"]):
                stable = []
            if stable:
                details = {"input_file": "counterexample/input", "input": blob(data),
                           "corpus_input": entry["file"], "channels": stable, **final}
                write_json(witness / "left.json", final["left"])
                write_json(witness / "right.json", final["right"])
                write_json(witness / "difference.json", details)
                result.update(status="DIFFERENT", counterexample=details)
                return
            shutil.rmtree(witness)
        reasons = []
        if changed:
            reasons.append("difference did not reproduce on both programs")
        for side, post in pair.items():
            reasons += [side + ": " + err for err in post["errors"]]
            if any(post[f]["status"] == "timeout" for f in ("sanitized", "clean")):
                reasons.append(side + ": execution timeout")
            crash = post["sanitized"].get("crash")
            if crash and crash["kind"] != "signal" and not crash.get("function"):
                reasons.append(side + ": sanitizer fault location could not be symbolized")
        if reasons:
            counts["unresolved"] += 1
            result["unresolved_inputs"].append({"input": entry["file"], "reasons": reasons})
        else:
            counts["equal"] += 1
        with (WORK / "replay.jsonl").open("a") as log:
            log.write(json.dumps({"input": entry["file"], "differences": changed,
                                  "unresolved": reasons}) + "\n")
    if counts["truncated"] or counts["unresolved"] or not counts["checked"]:
        result["status"] = "INCONCLUSIVE"
    else:
        result["status"] = "NO_DIFFERENCE_FOUND"
    if meta["source"] == "seeds_fallback":
        # Failed fuzzing is visible; a valid seed counterexample still wins above.
        result.update(status="INCONCLUSIVE", error="AFL++ did not finish successfully; see afl.log")


def main():
    if not Path("/.dockerenv").exists() or os.environ.get("DDIV_CONTAINER") != "1":
        raise SystemExit("invoke ddiv's CLI; the engine must run inside its Docker container")
    cfg = json.loads(Path(sys.argv[1]).read_text())
    TEMP.mkdir(parents=True, exist_ok=True)
    (TEMP / "run").mkdir(exist_ok=True)
    result = {"schema_version": 1, "ddiv_version": __version__, "status": "INFRA",
              "config": cfg, "builds": {}, "platform": platform.platform()}
    try:
        afl_version = subprocess.check_output(["afl-clang-fast", "--version"], text=True)
        version = re.search(r"clang version (\d+)", afl_version)
        if not version or not shutil.which("clang-" + version.group(1)):
            raise ValueError("cannot locate the Clang version used by afl-clang-fast")
        cc = shutil.which("clang-" + version.group(1))
        result["toolchain"] = {"cc": cc, "afl_driver": "afl-clang-fast",
                               "symbolizer": shutil.which("llvm-symbolizer")}
        result["compiler"] = subprocess.check_output([cc, "--version"], text=True).splitlines()[0]
        print("Building both programs (sanitized + clean)...", flush=True)
        builds, layouts = build(cfg, result)
        if builds:
            result["global_layouts"] = layouts
            print("Generating and freezing the AFL++ corpus...", flush=True)
            result["corpus"] = generate(cfg, builds["left.sanitized"])
            print("Comparing %d frozen inputs..." % result["corpus"]["size"], flush=True)
            compare(cfg, builds, layouts, result)
    except Exception as ex:
        result.update(status="INFRA", error=str(ex), traceback=traceback.format_exc())
    write_json(WORK / "result.json", result)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
