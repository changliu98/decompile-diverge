"""Host-side Python CLI. C compilation and execution always go through Docker."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import shutil
import signal
import subprocess
import sys
import uuid

from . import __version__


def positive(value):
    number = float(value)
    if not 0 < number < float("inf"):
        raise argparse.ArgumentTypeError("must be a finite positive number")
    return number


def parser():
    p = argparse.ArgumentParser(description="Use AFL++ to find an input that makes two C programs differ.")
    p.add_argument("left", type=Path, help="first C source, with main")
    p.add_argument("right", type=Path, help="second C source, with main")
    p.add_argument("--version", action="version", version="ddiv " + __version__)
    p.add_argument("--seconds", type=int, default=60, help="AFL++ generation budget (default: 60; 0 = seeds only)")
    p.add_argument("--timeout", type=positive, default=1.0, help="seconds per program execution (default: 1)")
    p.add_argument("--replay-seconds", type=positive, default=120.0,
                   help="replay budget; incomplete comparison is INCONCLUSIVE (default: 120)")
    p.add_argument("--seed", type=int, default=1337, help="AFL++ and initial-seed RNG seed (default: 1337)")
    p.add_argument("--input-mode", choices=("stdin", "file", "argv"), default="stdin",
                   help="main reads stdin, an input-file path, or NUL-separated argv (default: stdin)")
    p.add_argument("--arg", action="append", default=[], help="fixed main argument; @@ substitutes file input")
    inputs = p.add_mutually_exclusive_group()
    inputs.add_argument("--seeds", type=Path, help="directory of initial AFL++ inputs")
    inputs.add_argument("--input", type=Path, help="replay this exact input only, without fuzzing")
    p.add_argument("--cflag", action="append", default=[], help="extra compiler flag, e.g. --cflag=-DMODE=1")
    p.add_argument("--ldflag", action="append", default=[], help="extra linker flag, e.g. --ldflag=-lz")
    p.add_argument("--output", type=Path, help="new artifact directory; default: ddiv-results/<unique run>")
    p.add_argument("--image", default=os.environ.get("DDIV_IMAGE", "ddiv:0.1"), help="Docker toolchain image")
    p.add_argument("--memory", default="2g", help="Docker memory limit (default: 2g)")
    p.add_argument("--json", action="store_true", help="print the full JSON result instead of a text report")
    return p


def render(result, output):
    lines = [result["status"]]
    counts = result.get("comparison", {})
    if counts:
        lines.append("Compared %s/%s frozen inputs." % (counts["checked"], counts["total"]))
    if result.get("error"):
        lines.append(result["error"])
    witness = result.get("counterexample")
    if witness:
        lines += ["Input: " + str(output / witness["input_file"]),
                  "  text: " + repr(witness["input"]["text"]),
                  "  hex:  " + witness["input"]["hex"],
                  "Different channels: " + ", ".join(witness["channels"])]
        for side in ("left", "right"):
            post = witness[side]
            lines.append(side + " (" + result["config"]["programs"][side]["path"] + "):")
            for flavor in ("sanitized", "clean"):
                run = post[flavor]
                lines.append("  %s: %s, returncode=%s" % (flavor, run["status"], run["returncode"]))
                if run["crash"]:
                    lines.append("    crash: " + json.dumps(run["crash"], sort_keys=True))
                for stream in ("stdout", "stderr"):
                    if run[stream]["size"]:
                        lines.append("    %s: %r" % (stream, run[stream]["text"]))
            for group in ("globals", "observations"):
                if group not in witness["channels"]:
                    continue
                other = witness["right" if side == "left" else "left"][group] or {}
                for name, value in (post[group] or {}).items():
                    if other.get(name, {}).get("sha256") == value["sha256"]:
                        continue
                    desc = (str(value["signed_le"]) + " (little-endian integer view)"
                            if "signed_le" in value else "hex=" + value["hex"])
                    lines.append("  %s.%s = %s" % (group, name, desc))
            for flavor in ("sanitized", "clean"):
                if flavor + ".files" in witness["channels"]:
                    lines.append("  %s files: %s" % (flavor, json.dumps(post[flavor]["files"], sort_keys=True)))
    elif result["status"] == "NO_DIFFERENCE_FOUND":
        lines.append("No difference on these inputs; this is not a proof of equivalence.")
    lines.append("Report: " + str(output / "result.json"))
    return "\n".join(lines)


def run(args):
    if not shutil.which("docker"):
        raise ValueError("Docker is required for C compilation and execution")
    if args.seconds < 0 or not 0 <= args.seed <= 0xFFFFFFFF:
        raise ValueError("--seconds must be nonnegative and --seed must be in [0, 2^32-1]")
    for flag in args.cflag + args.ldflag:
        if flag.startswith(("-fsanitize", "-fno-sanitize", "-flto", "-fPIE", "-fpie", "-fPIC", "-fpic")) \
                or flag in ("-o", "-c", "-S", "-E", "-pie", "-shared", "-static", "-m32"):
            raise ValueError("ddiv controls build mode, architecture and sanitizers; unsupported flag: " + flag)
    sources = {side: getattr(args, side).expanduser().resolve(strict=True) for side in ("left", "right")}
    if not all(p.is_file() for p in sources.values()):
        raise ValueError("both program inputs must be C source files")
    inputs = []
    if args.input:
        inputs = [args.input.expanduser().resolve(strict=True)]
    if args.seeds:
        seed_dir = args.seeds.expanduser().resolve(strict=True)
        inputs = sorted(p for p in seed_dir.iterdir() if p.is_file())
        if not inputs:
            raise ValueError("the seed directory contains no files")
    if not all(p.is_file() for p in inputs):
        raise ValueError("--input must name a regular file")
    inspect = subprocess.run(["docker", "image", "inspect", args.image, "--format", "{{.Id}}"],
                             capture_output=True, text=True, timeout=30)
    if inspect.returncode:
        raise ValueError("Docker image unavailable: %s. Build it with: docker build -t ddiv:0.1 %s\n%s" %
                         (args.image, Path(__file__).resolve().parent, inspect.stderr.strip()))
    run_id = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ-") + uuid.uuid4().hex[:8]
    output = (args.output or Path("ddiv-results") / run_id).expanduser().resolve()
    output.mkdir(parents=True, exist_ok=False)
    (output / "sources").mkdir()
    (output / "seeds").mkdir()
    tool_root = Path(__file__).resolve().parent
    tool_copy = output / "tool"
    tool_copy.mkdir()
    tool_hashes = {}
    for path in sorted([*tool_root.glob("*.py"), *tool_root.glob("runtime/*.c"),
                        *tool_root.glob("include/*.h")]):
        relative = path.relative_to(tool_root)
        target = tool_copy / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        data = path.read_bytes()
        target.write_bytes(data)
        tool_hashes[str(relative)] = hashlib.sha256(data).hexdigest()
    cfg = {"programs": {}, "seconds": args.seconds, "timeout": args.timeout,
           "replay_seconds": args.replay_seconds, "seed": args.seed, "input_mode": args.input_mode,
           "args": args.arg, "cflags": args.cflag, "ldflags": args.ldflag,
           "confirmations": 4, "replay_only": bool(args.input),
           "supplied_seeds": bool(args.input or args.seeds), "image": args.image,
           "image_id": inspect.stdout.strip(), "memory": args.memory, "tool_sha256": tool_hashes}
    for side, source in sources.items():
        data = source.read_bytes()
        (output / "sources" / (side + ".c")).write_bytes(data)
        cfg["programs"][side] = {"path": str(source), "sha256": hashlib.sha256(data).hexdigest(),
                                 "container_path": "/work/sources/" + side + ".c",
                                 "include_dir": "/src/" + side}
    for i, inp in enumerate(inputs):
        shutil.copyfile(inp, output / "seeds" / ("seed-%06d" % i))
    (output / "config.json").write_text(json.dumps(cfg, indent=2) + "\n")
    container = "ddiv-" + uuid.uuid4().hex
    cmd = ["docker", "run", "--rm", "--init", "--name", container, "--label", "ddiv-run=1",
           "--network", "none", "--read-only", "--cap-drop", "ALL",
           "--security-opt", "no-new-privileges", "--pids-limit", "256", "--cpus", "2",
           "--memory", args.memory, "--memory-swap", args.memory,
           "--user", "%d:%d" % (os.getuid(), os.getgid()),
           "--tmpfs", "/tmp:rw,nosuid,nodev,mode=1777,size=512m",
           "--env", "DDIV_CONTAINER=1", "--env", "PYTHONPATH=/opt",
           "--env", "PYTHONDONTWRITEBYTECODE=1", "--workdir", "/work"]
    mounts = [(output, "/work", False), (tool_copy, "/opt/ddiv", True)]
    mounts += [(source.parent, "/src/" + side, True) for side, source in sources.items()]
    for src, dst, readonly in mounts:
        # --mount, unlike -v, fails if a source disappears instead of silently
        # creating an empty host directory. Reject commas in this Docker syntax.
        if "," in str(src):
            raise ValueError("Docker --mount does not support a comma in this path: " + str(src))
        cmd += ["--mount", "type=bind,src=%s,dst=%s%s" % (src, dst, ",readonly" if readonly else "")]
    cmd += ["--entrypoint", "python3", cfg["image_id"], "-m", "ddiv.engine", "/work/config.json"]
    print("Artifacts: " + str(output), file=sys.stderr, flush=True)
    previous = signal.getsignal(signal.SIGTERM)

    def interrupted(signum, frame):
        raise KeyboardInterrupt

    signal.signal(signal.SIGTERM, interrupted)
    process = None
    try:
        with (output / "docker.log").open("w") as log:
            process = subprocess.Popen(cmd, stdout=log, stderr=subprocess.STDOUT)
            # Bounded builds, fuzzing, and replay, plus one in-flight confirmation.
            limit = 600 + args.seconds + args.replay_seconds + 48 * args.timeout
            process.wait(timeout=limit)
    except (KeyboardInterrupt, subprocess.TimeoutExpired) as ex:
        (output / "result.json").write_text(json.dumps(
            {"status": "INFRA", "config": cfg, "error": "interrupted" if isinstance(ex, KeyboardInterrupt)
             else "container exceeded total time budget"}, indent=2) + "\n")
    finally:
        # Only this invocation's uniquely named container; never sweep/user workers.
        subprocess.run(["docker", "rm", "-f", container], capture_output=True, timeout=20)
        if process is not None:
            process.wait(timeout=20)
        signal.signal(signal.SIGTERM, previous)
    result_path = output / "result.json"
    if not result_path.is_file():
        result_path.write_text(json.dumps({"status": "INFRA", "config": cfg,
            "error": "container produced no result; inspect docker.log",
            "docker_log": (output / "docker.log").read_text(errors="replace")[-6000:]}, indent=2) + "\n")
    result = json.loads(result_path.read_text())
    print(json.dumps(result, indent=2) if args.json else render(result, output))
    return {"NO_DIFFERENCE_FOUND": 0, "DIFFERENT": 1}.get(result["status"], 2)


def main(argv=None):
    args = parser().parse_args(argv)
    try:
        return run(args)
    except (OSError, ValueError, subprocess.SubprocessError) as ex:
        print("ddiv: " + str(ex), file=sys.stderr)
        return 2
