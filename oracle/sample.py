#!/usr/bin/env python3
"""Draw a stratified random sample of the benchmark functions, for a cheaper replication.

  python3 oracle/sample.py --fraction 0.2 --seed 2027 --out results/sample.txt

Takes round(fraction x n) functions from each of the six groups (at least one per group),
with a fixed seed, and writes their ids one per line. Every tool accepts the list:

  python3 oracle/difffuzz_group.py --group mbpp --bundles-file results/sample.txt
  python3 oracle/shipped_tests.py --bundles-file results/sample.txt
  python3 oracle/coverage.py --bundles-file results/sample.txt

and `oracle/tables.py` reports over whatever has been run. Each sampled function is scored for
every system, so all systems are measured on the same functions.
"""
from __future__ import annotations

import argparse
import random
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BUNDLES = ROOT / "data" / "bundles"
GROUPS = ["humaneval", "exebench", "anghabench", "mbpp", "github_barebone", "cve_barebone"]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--fraction", type=float, required=True, help="e.g. 0.2 for 20%%")
    ap.add_argument("--seed", type=int, default=2027)
    ap.add_argument("--out", required=True)
    args = ap.parse_args()
    if not 0 < args.fraction <= 1:
        sys.exit("--fraction must be in (0, 1]")
    rng = random.Random(args.seed)
    picked = []
    for g in GROUPS:
        ids = sorted(p.name for p in BUNDLES.glob(f"{g}_*") if p.is_dir())
        k = max(1, round(args.fraction * len(ids)))
        chosen = sorted(rng.sample(ids, k))
        picked += chosen
        print(f"  {g:<16} {k:>5} of {len(ids)}", file=sys.stderr)
    Path(args.out).parent.mkdir(parents=True, exist_ok=True)
    Path(args.out).write_text("\n".join(picked) + "\n")
    print(f"{len(picked)} functions -> {args.out}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
