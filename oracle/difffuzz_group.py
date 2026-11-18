#!/usr/bin/env python3
"""Run the differential-fuzzing oracle over a group x arms, N workers in parallel.

  python oracle/difffuzz_group.py --group cve_barebone --jobs 16
  python oracle/difffuzz_group.py --group cve_barebone --report-only

Each (bundle, arm) is one dockerized eval (ddiv-oracle, --network none, 16g cap).
Resumable: an existing sidecar results/verdicts/<bundle>/<arm>.json is skipped UNLESS its
verdict is INFRA (transient -> retried). `identity` is always run as the per-bundle soundness
gate: if it is not INTACT the harness itself is broken and the bundle is flagged (excluded
from the aggregate).

Scope guard: only self-contained-harness groups (cve_barebone, github_barebone, and the
functional groups). Real-project `cve` bundles are rejected (no self-contained fuzz harness).
"""
from __future__ import annotations

import argparse
import glob
import json
import sys
import traceback
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from oracle.difffuzz import (BUNDLES, CAND_ROOT, CORPUS_ROOT, DIFF_ROOT, ORACLE_VERSION,
                             RECIPE, DiffResult, ensure_corpus, evaluate, write_sidecar)

EVAL_DIRS = [CAND_ROOT]
LLM_ARMS = ["llm4decompile", "autodecompiler", "idioms", "sk2decompile", "nova",
            "slade", "degpt", "glm-e2e", "glm-refine"]
FE_ARMS = ["ghidra", "ida"]
IN_SCOPE = ("cve_barebone", "github_barebone", "humaneval", "mbpp", "exebench", "anghabench")
_REPO = Path(__file__).resolve().parent.parent


def cand_path(bundle_name, arm):
    for d in EVAL_DIRS:
        p = d / bundle_name / f"{arm}.response.c"
        if p.exists():
            return p
    return None


def arms_for(bundle: Path):
    name = bundle.name
    arms = ["identity"]
    for a in LLM_ARMS + FE_ARMS:
        if cand_path(name, a):
            arms.append(a)
    return arms


def sidecar_path(name, arm):
    return DIFF_ROOT / name / f"{arm}.json"


def needs_run(name, arm, force, seconds):
    p = sidecar_path(name, arm)
    if not p.exists():
        return True
    if force:
        return True
    try:
        d = json.loads(p.read_text())
        if d.get("verdict") == "INFRA":            # transient -> always retry
            return True
        if int(d.get("oracle_version", -1)) != ORACLE_VERSION:
            return True
        # The fuzz budget is part of the corpus recipe (ensure_corpus never reuses a corpus grown
        # at a different budget). A sidecar scored at another budget -- notably the retired 60s
        # default -- must be re-scored on the new-budget corpus. Keying resumption on the budget
        # keeps a 60s->600s extension resumable WITHOUT --force, which would instead redo already
        # up-to-date work on every restart of a multi-day run.
        return int(d.get("fuzz_seconds", -1)) != int(seconds)
    except Exception:
        return True


def run_one(bundle: Path, arm: str, seconds: int):
    name = bundle.name
    try:
        if arm == "identity":
            cand = (bundle / "target" / "original_function.c").read_bytes()
        else:
            cp = cand_path(name, arm)
            if cp is None:
                return (name, arm, "NO_CAND")
            cand = cp.read_bytes()
        # Fuzz ORIG ONCE per bundle, freeze, and replay that SAME corpus for every arm (fair +
        # reproducible). A generation/launch failure -> INFRA (retryable), never a silent INTACT.
        corpus_dir, meta = ensure_corpus(bundle, seconds)
        if corpus_dir is None:
            res = DiffResult(verdict="INFRA", bundle=name, arm=arm, fuzz_seconds=seconds,
                             fuzz_ok=bool(meta.get("fuzz_ok")), afl_rc=meta.get("afl_rc"),
                             error="corpus generation failed: " + str(meta.get("error")))
            write_sidecar(res, DIFF_ROOT / name)
            return (name, arm, "INFRA")
        res = evaluate(bundle, cand, arm=arm, seconds=seconds,
                       corpus_dir=corpus_dir, corpus_meta=meta)
        write_sidecar(res, DIFF_ROOT / name)
        return (name, arm, res.verdict)
    except Exception as ex:
        traceback.print_exc()
        return (name, arm, f"EXC:{ex}")


ONLY = None          # optional set of bundle ids (--bundles-file), e.g. a sampled subset


def _bundles(group, limit):
    bs = sorted(Path(p) for p in glob.glob(str(BUNDLES / f"{group}_*"))
                if Path(p).is_dir() and (ONLY is None or Path(p).name in ONLY))
    return bs[:limit] if limit else bs


def enumerate_jobs(group, limit, force, arms_filter, seconds):
    bundles = _bundles(group, limit)
    jobs = []
    for b in bundles:
        arms = arms_for(b)
        if arms_filter:
            arms = [a for a in arms if a in arms_filter or a == "identity"]
        for a in arms:
            if needs_run(b.name, a, force, seconds):
                jobs.append((b, a))
    # ARM-MAJOR order: run every bundle's `identity` first -> each triggers that bundle's ONE
    # corpus generation (48-way parallel, no sibling contention); later arm passes replay the
    # already-frozen corpus from cache. Avoids workers idling on a per-bundle gen lock.
    arm_rank = {"identity": 0}
    for i, a in enumerate(LLM_ARMS + FE_ARMS, start=1):
        arm_rank[a] = i
    jobs.sort(key=lambda ba: (arm_rank.get(ba[1], 99), ba[0].name))
    return bundles, jobs


def report(group, limit):
    bundles = _bundles(group, limit)
    broken, per_arm = [], {}
    for b in bundles:
        sc = sidecar_path(b.name, "identity")
        if sc.exists():
            idv = json.loads(sc.read_text()).get("verdict")
            if idv is not None and idv != "INTACT":
                broken.append((b.name, idv))
    broken_set = {n for n, _ in broken}
    for b in bundles:
        if b.name in broken_set:
            continue
        for a in LLM_ARMS + FE_ARMS:
            sc = sidecar_path(b.name, a)
            if not sc.exists():
                continue
            d = json.loads(sc.read_text())
            s = per_arm.setdefault(a, dict(total=0, BUILD_FAILED=0, DECOMPILE_FAILED=0,
                                           SPLICE_FAILED=0, INFRA=0, INTACT=0, DEVIATED=0,
                                           vanish=0))
            s["total"] += 1
            v = d.get("verdict", "INFRA")
            s[v] = s.get(v, 0) + 1
            if v == "DEVIATED" and d.get("vanished"):
                s["vanish"] += 1
    # all-variable channel coverage: how many (non-broken) bundles compared the FULL exit
    # memstate (return+outputs+globals) vs the stdout/stderr fallback -- read off the identity
    # gate. Live => an INTACT there means "identical over all variables", not just same printout.
    mem_live = mem_total = 0
    for b in bundles:
        if b.name in broken_set:
            continue
        sc = sidecar_path(b.name, "identity")
        if not sc.exists():
            continue
        d = json.loads(sc.read_text())
        mem_total += 1
        if d.get("memstate_compared"):
            mem_live += 1
    # corpus provenance: fuzzed (or io-fallback) ONCE per bundle, frozen, replayed for every arm.
    fuzzed, fallback, sizes = 0, 0, []
    for b in bundles:
        mp = CORPUS_ROOT / b.name / "corpus_meta.json"
        if mp.exists():
            try:
                m = json.loads(mp.read_text())
                if not (m.get("corpus_ok") or m.get("fuzz_ok")):   # fuzz_ok = pre-corpus_ok back-compat
                    continue
                sizes.append(int(m.get("corpus_size", 0)))
                if m.get("corpus_source") == "seeds_fallback":
                    fallback += 1
                else:
                    fuzzed += 1
            except Exception:
                pass
    print(f"\n=== difffuzz report: {group}  ({len(bundles)} bundles, "
          f"{len(broken)} identity-broken excluded) ===")
    if fuzzed or fallback:
        extra = f" + {fallback} io-corpus fallback (all-seeds-crash)" if fallback else ""
        print(f"frozen corpus: {fuzzed} fuzzed once & replayed for every arm{extra} "
              f"(mean {sum(sizes)//max(1,len(sizes))} inputs/bundle, fixed AFL seed)")
    if mem_total:
        print(f"all-variable (memstate) channel live on {mem_live}/{mem_total} bundles"
              f"  ({mem_total - mem_live} on stdout/stderr fallback)")
    hdr = f"{'arm':<16}{'built':>7}{'intact':>8}{'deviat':>8}{'vanish':>8}{'bfail':>7}{'dfail':>7}{'infra':>7}"
    print(hdr); print("-" * len(hdr))
    for a in LLM_ARMS + FE_ARMS:
        s = per_arm.get(a)
        if not s:
            continue
        built = s["INTACT"] + s["DEVIATED"]
        print(f"{a:<16}{built:>7}{s['INTACT']:>8}{s['DEVIATED']:>8}{s['vanish']:>8}"
              f"{s['BUILD_FAILED']:>7}{s['DECOMPILE_FAILED']:>7}{s['INFRA']:>7}")
    if broken:
        print(f"\n[!] identity-broken bundles ({len(broken)}): "
              + ", ".join(f"{n}({v})" for n, v in broken[:10])
              + (" ..." if len(broken) > 10 else ""))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--group", required=True)
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--seconds", type=int, default=None,
                    help="AFL budget of the corpus (default: the group's recipe)")
    ap.add_argument("--bundles-file",
                    help="only the function ids listed in this file (see oracle/sample.py)")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--arms", nargs="*", help="restrict to these arms (identity always run)")
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--report-only", action="store_true")
    args = ap.parse_args()

    if args.group not in IN_SCOPE:
        print(f"[refuse] group '{args.group}' is not in scope for the self-contained-harness "
              f"differential oracle. In scope: {IN_SCOPE}")
        sys.exit(2)

    if args.seconds is None:
        args.seconds = RECIPE[args.group][1]
    if args.bundles_file:
        global ONLY
        ONLY = set(Path(args.bundles_file).read_text().split())

    if args.report_only:
        report(args.group, args.limit); return

    bundles, jobs = enumerate_jobs(args.group, args.limit, args.force, args.arms, args.seconds)
    print(f"[difffuzz] group={args.group} bundles={len(bundles)} pending_jobs={len(jobs)} "
          f"jobs={args.jobs} seconds={args.seconds}", flush=True)
    done, counts = 0, {}
    with ThreadPoolExecutor(max_workers=args.jobs) as ex:
        futs = [ex.submit(run_one, b, a, args.seconds) for b, a in jobs]
        for f in as_completed(futs):
            name, arm, verdict = f.result()
            counts[verdict] = counts.get(verdict, 0) + 1
            done += 1
            if done % 25 == 0 or done == len(jobs):
                print(f"  [{done}/{len(jobs)}] {name}/{arm} -> {verdict}   running={counts}",
                      flush=True)
    print(f"[difffuzz] done. verdicts={counts}", flush=True)
    report(args.group, args.limit)


if __name__ == "__main__":
    main()
