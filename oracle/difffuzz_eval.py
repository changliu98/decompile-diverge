#!/usr/bin/env python3
"""Differentially fuzz ONE (bundle, arm) and write a sidecar.

  python oracle/difffuzz_eval.py <bundle_dir> --arm llm4decompile
  python oracle/difffuzz_eval.py <bundle_dir> --arm identity        # cand = orig (INTACT gate)
  python oracle/difffuzz_eval.py <bundle_dir> --cand-file f.c --arm mytag

Candidate bytes come from (in order): --cand-file; --arm identity (= original function);
else data/candidates/<bundle>/<arm>.response.c.
Sidecar -> results/verdicts/<bundle>/<arm>.json (resumable; skipped if present unless --force).
The frozen corpus under data/corpus/<bundle>/ is replayed; --seconds defaults to the budget
that corpus was grown with (see RECIPE in difffuzz.py).
"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from oracle.difffuzz import (CAND_ROOT, DIFF_ROOT, ORACLE_VERSION, DiffResult, budget_for,
                             ensure_corpus, evaluate, write_sidecar)

EVAL_DIRS = [CAND_ROOT]


def find_cand(bundle_name: str, arm: str):
    for d in EVAL_DIRS:
        p = d / bundle_name / f"{arm}.response.c"
        if p.exists():
            return p
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("bundle")
    ap.add_argument("--arm", required=True)
    ap.add_argument("--cand-file")
    ap.add_argument("--seconds", type=int, default=None,
                    help="AFL budget of the corpus (default: the bundle group's recipe)")
    ap.add_argument("--out-dir")
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--keep-scratch", action="store_true")
    args = ap.parse_args()

    bundle = Path(args.bundle).resolve()
    name = bundle.name
    if args.seconds is None:
        args.seconds = budget_for(bundle)
    out_dir = Path(args.out_dir) if args.out_dir else DIFF_ROOT / name
    sidecar = out_dir / f"{args.arm}.json"
    if sidecar.exists() and not args.force:
        try:
            import json
            current = json.loads(sidecar.read_text())
            reusable = (int(current.get("oracle_version", -1)) == ORACLE_VERSION
                        and int(current.get("fuzz_seconds", -1)) == args.seconds
                        and current.get("verdict") != "INFRA")
        except Exception:
            reusable = False
        if reusable:
            print(f"[skip] {sidecar} exists for oracle v{ORACLE_VERSION}"); return

    if args.cand_file:
        cand = Path(args.cand_file).read_bytes()
    elif args.arm == "identity":
        cand = (bundle / "target" / "original_function.c").read_bytes()
    else:
        cp = find_cand(name, args.arm)
        if cp is None:
            print(f"[error] no response.c for {name}/{args.arm}"); sys.exit(2)
        cand = cp.read_bytes()

    # fuzz ORIG once per bundle, freeze, replay for this arm (shared corpus = fair across arms).
    corpus_dir, meta = ensure_corpus(bundle, args.seconds)
    if corpus_dir is None:
        res = DiffResult(verdict="INFRA", bundle=name, arm=args.arm, fuzz_seconds=args.seconds,
                         fuzz_ok=bool(meta.get("fuzz_ok")), afl_rc=meta.get("afl_rc"),
                         error="corpus generation failed: " + str(meta.get("error")))
    else:
        res = evaluate(bundle, cand, arm=args.arm, seconds=args.seconds,
                       keep_scratch=args.keep_scratch, corpus_dir=corpus_dir, corpus_meta=meta)
    write_sidecar(res, out_dir)
    cov = ""
    if res.coverage and "lines_pct" in res.coverage:
        cov = f"  cov(line/branch)={res.coverage['lines_pct']:.0f}/{res.coverage['branches_pct']:.0f}%"
    print(f"{name}/{args.arm}: {res.verdict}  build_cand={res.build_cand}  "
          f"corpus={res.corpus_size}(frozen,fuzz_ok={res.fuzz_ok})  "
          f"divergent={res.n_divergent} {res.div_types}"
          f"{'  VANISH' if res.vanished else ''}{cov}")


if __name__ == "__main__":
    main()
