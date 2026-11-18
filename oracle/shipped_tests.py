#!/usr/bin/env python3
"""Run every candidate through the test suite its corpus ships (the Pass column).

Three of the four established corpora release an executable test with each function:

  humaneval   HumanEval-Decompile `c_test` assert mains  (LLM4Decompile `evaluate_func`)
  mbpp        the MBPP C conversion's `test` mains        (SK2Decompile `execute_rate`)
  exebench    ExeBench `real_exe_wrapper` + 10 `real_io_pairs` per function

AnghaBench ships none. The three harnesses are ported in oracle/shipped_tests_driver.py, which
runs INSIDE the image (`--network none`): candidates are never executed on the host. One
container per function scores the reference (`identity`) and every system that has a candidate.

A candidate is first scored by the harness exactly as released (`strict`). The released
harnesses compile with gcc/g++, which reject the vocabulary Ghidra and Hex-Rays emit (`__cdecl`,
`_DWORD`, `undefined4`, ...), so when the verbatim compile fails the candidate is scored once
more behind a block of declarations for that vocabulary (`compat`); the candidate text itself is
not changed. A candidate passes if either attempt passes.

  python3 oracle/shipped_tests.py --jobs 16                    # everything (resumable)
  python3 oracle/shipped_tests.py --groups humaneval --limit 5
  python3 oracle/shipped_tests.py --bundles humaneval_001 --force

Results: results/shipped_tests/<id>/<system>.json. `python3 oracle/tables.py --results` then
prints Pass and Div|P next to the oracle's columns.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import shutil
import subprocess
import sys
import threading
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BUNDLES = ROOT / "data" / "bundles"
CANDIDATES = ROOT / "data" / "candidates"
TESTS = ROOT / "data" / "shipped_tests"                 # <id>.json, one per function
EXEBENCH_INC = TESTS / "_exebench_include"              # nlohmann/ + clib/ (ExeBench's headers)
OUT = ROOT / "results" / "shipped_tests"
DRIVER = Path(__file__).resolve().parent / "shipped_tests_driver.py"
IMAGE = os.environ.get("DDIV_AFL_IMAGE", "ddiv-oracle:22.04")

GROUPS = ("humaneval", "mbpp", "exebench")
SYSTEMS = ["ghidra", "ida", "llm4decompile", "sk2decompile", "idioms", "glm-refine", "degpt",
           "autodecompiler", "nova", "slade", "glm-e2e"]

_print_lock = threading.Lock()


def arms_for(bundle: str, only):
    """`identity` plus every system that produced a candidate for this function."""
    arms = ["identity"] + [s for s in SYSTEMS
                           if (CANDIDATES / bundle / f"{s}.response.c").exists()]
    return [a for a in arms if not only or a in only]


def run_bundle(bundle: str, group: str, pending, args, uid_gid: str):
    out_dir = OUT / bundle
    scratch = OUT / "_scratch" / bundle
    if scratch.exists():
        shutil.rmtree(scratch)
    (scratch / "cand").mkdir(parents=True)

    jobs, meta = [], {}
    for arm in pending:
        src = (BUNDLES / bundle / "target" / "original_function.c" if arm == "identity"
               else CANDIDATES / bundle / f"{arm}.response.c")
        data = src.read_bytes() if src.exists() else b""
        (scratch / "cand" / f"{arm}.c").write_bytes(data)
        meta[arm] = {"sha256": hashlib.sha256(data).hexdigest()[:16], "bytes": len(data)}
        jobs.append({"arm": arm, "candidate_file": f"/job/cand/{arm}.c"})

    test = json.loads((TESTS / f"{bundle}.json").read_text())
    spec: dict = {"kind": group, "jobs": jobs, "compat": True}
    if group == "humaneval":
        spec["c_func"] = test["c_func"]
        spec["c_test"] = test["c_test"]
    elif group == "mbpp":
        spec["func_dep"] = test["func_dep"]
        spec["test"] = test["test"]
        spec["func_name"] = test["func_name"]
    else:  # exebench
        spec["c_deps"] = test["real_deps"] or ""
        spec["cpp_wrapper"] = test["real_exe_wrapper"]
        spec["io_pairs"] = test["real_io_pairs"]
        spec["include_root"] = "/exeinc"
    (scratch / "spec.json").write_text(json.dumps(spec))

    # --pids-limit/--memory only guard against pathological candidates; they do not alter the
    # ported harnesses' behaviour on ordinary code.
    cmd = ["docker", "run", "--rm", "--network", "none", "--user", uid_gid,
           "--label", "ddiv-shipped-tests=1",
           "--pids-limit", "512", "--memory", "8g", "--memory-swap", "8g",
           "-v", f"{scratch.resolve()}:/job",
           "-v", f"{DRIVER.resolve()}:/driver.py:ro"]
    if group == "exebench":
        cmd += ["-v", f"{EXEBENCH_INC.resolve()}:/exeinc:ro"]
    cmd += [args.image, "python3", "/driver.py", "/job/spec.json", "/job/results.json"]
    # an exebench candidate costs one g++ compile of nlohmann/json.hpp plus up to 10 runs of 5 s;
    # x3 for the up-to-two extra compile attempts of a candidate the verbatim harness rejects
    outer_timeout = 3 * (90 + (120 if group == "exebench" else 40) * len(pending))
    try:
        proc = subprocess.run(cmd, capture_output=True, text=True, timeout=outer_timeout)
    except subprocess.TimeoutExpired:
        return bundle, None, f"docker timeout ({outer_timeout}s)"
    results_file = scratch / "results.json"
    if proc.returncode != 0 or not results_file.exists():
        return bundle, None, f"docker rc={proc.returncode}: {(proc.stderr or '')[-300:]}"

    results = json.loads(results_file.read_text())
    out_dir.mkdir(parents=True, exist_ok=True)
    written = {}
    for rec in results:
        arm = rec["arm"]
        sidecar = {"bundle": bundle, "group": group, "system": arm, **meta[arm],
                   "strict": rec.get("strict"), "compat": rec.get("compat"),
                   "renamed": rec.get("renamed"),
                   "error": rec.get("error"), "elapsed": rec.get("elapsed")}
        tmp = out_dir / f".{arm}.json.tmp"
        tmp.write_text(json.dumps(sidecar, indent=1))
        os.replace(tmp, out_dir / f"{arm}.json")
        written[arm] = rec
    if not args.keep_scratch:
        shutil.rmtree(scratch, ignore_errors=True)
    return bundle, written, None


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--groups", default=",".join(GROUPS))
    ap.add_argument("--image", default=IMAGE)
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--arms", default=None, help="comma list (default: identity + all systems)")
    ap.add_argument("--bundles", default=None, help="comma list of function ids")
    ap.add_argument("--bundles-file", default=None,
                    help="only the function ids listed in this file (see oracle/sample.py)")
    ap.add_argument("--limit", type=int, default=0, help="first N functions of each group")
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--keep-scratch", action="store_true")
    args = ap.parse_args()

    groups = [g.strip() for g in args.groups.split(",") if g.strip()]
    for g in groups:
        if g not in GROUPS:
            sys.exit(f"group {g!r} ships no tests (choose from {', '.join(GROUPS)})")
    only_arms = {a.strip() for a in args.arms.split(",")} if args.arms else None
    only_bundles = {b.strip() for b in args.bundles.split(",")} if args.bundles else None
    if args.bundles_file:
        listed = set(Path(args.bundles_file).read_text().split())
        only_bundles = listed if only_bundles is None else (only_bundles & listed)
    uid_gid = f"{os.getuid()}:{os.getgid()}"

    todo, skipped = [], 0
    for group in groups:
        picked = 0
        for bdir in sorted(BUNDLES.glob(f"{group}_*")):
            bundle = bdir.name
            if only_bundles and bundle not in only_bundles:
                continue
            if not (TESTS / f"{bundle}.json").is_file():
                continue
            if args.limit and not only_bundles:
                picked += 1
                if picked > args.limit:
                    break
            pending = [a for a in arms_for(bundle, only_arms)
                       if args.force or not (OUT / bundle / f"{a}.json").exists()]
            if not pending:
                skipped += 1
                continue
            todo.append((bundle, group, pending))
    print(f"[shipped-tests] image={args.image}  {len(todo)} functions / "
          f"{sum(len(t[2]) for t in todo)} candidates pending ({skipped} functions complete)",
          flush=True)

    tally: dict = defaultdict(Counter)
    failures, done = [], 0
    with ThreadPoolExecutor(max_workers=args.jobs) as ex:
        futs = {ex.submit(run_bundle, b, g, p, args, uid_gid): (b, g) for b, g, p in todo}
        for fut in as_completed(futs):
            bundle, group = futs[fut]
            done += 1
            try:
                _, written, err = fut.result()
            except Exception as e:
                written, err = None, f"{type(e).__name__}: {e}"
            if err:
                failures.append((bundle, err))
                with _print_lock:
                    print(f"  [{done}/{len(todo)}] {bundle:<22} INFRA {err}", flush=True)
                continue
            for arm, rec in written.items():
                s, c = rec.get("strict") or {}, rec.get("compat") or {}
                tally[(group, arm)]["n"] += 1
                tally[(group, arm)]["compiled"] += bool(s.get("compiled") or c.get("compiled"))
                tally[(group, arm)]["passed"] += bool(s.get("passed") or c.get("passed"))
            if done % 50 == 0 or done == len(todo):
                with _print_lock:
                    print(f"  [{done}/{len(todo)}] {bundle}", flush=True)

    if tally:
        print("\n[shipped-tests] this run (strict or compat):")
        print(f"  {'group':<10} {'system':<16} {'n':>5} {'compiled':>9} {'passed':>7}")
        for (group, arm), c in sorted(tally.items()):
            print(f"  {group:<10} {arm:<16} {c['n']:>5} {c['compiled']:>9} {c['passed']:>7}")
    if failures:
        print(f"\n[shipped-tests] {len(failures)} functions produced no result (re-run to retry):")
        for bundle, err in failures[:10]:
            print(f"  {bundle}: {err}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
