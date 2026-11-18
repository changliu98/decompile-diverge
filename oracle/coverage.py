#!/usr/bin/env python3
"""Measure frozen-corpus reach (region/line/branch coverage of the target function) over
every shipped function. This is the measurement behind the paper's reach table.

Per bundle: stage source_code + the FROZEN corpus (data/corpus/<b>/corpus/), build the
reference at -O0 with LLVM source coverage (oracle/coverage_run.py: continuous profiling,
so crashing inputs contribute; raw counts, so a branchless function is undefined, not 0%),
replay every input, report the target's row. Resumable per bundle
(results/coverage/<bundle>.json), parallel, dockerized (--network none).

  python oracle/coverage.py --jobs 16                    # full run (resumable)
  python oracle/coverage.py --groups cve_barebone        # one group
  python oracle/coverage.py --retry-failed --jobs 16     # re-attempt failed bundles
  python oracle/coverage.py --report-only                # aggregate what is on disk
  python oracle/coverage.py --expected                   # the paper's reach table
"""
from __future__ import annotations

import argparse
import concurrent.futures as cf
import json
import math
import os
import shutil
import statistics
import subprocess
import sys
import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DATASET = ROOT / "data" / "bundles"
CORPUS = Path(os.environ.get("DDIV_CORPUS_ROOT", str(ROOT / "data" / "corpus")))
DIFF = Path(os.environ.get("DDIV_DIFF_ROOT", str(ROOT / "results" / "verdicts")))
COV = ROOT / "results" / "coverage"
EXPECTED = ROOT / "data" / "expected" / "coverage.csv"
IMAGE = os.environ.get("DDIV_AFL_IMAGE", "ddiv-oracle:22.04")
MEM = os.environ.get("DDIV_AFL_MEM", "8g")
RUNNER = ROOT / "oracle" / "coverage_run.py"

# (dataset prefix, paper label). Order matches the paper's table.
GROUPS = [("humaneval", "HumanEval"), ("exebench", "ExeBench"), ("anghabench", "AnghaBench"),
          ("mbpp", "MBPP"), ("github_barebone", "GitHub"), ("cve_barebone", "CVE")]


ONLY = None          # optional set of bundle ids (--bundles-file), e.g. a sampled subset


def bundles(group: str):
    return sorted(p.name for p in DATASET.glob(f"{group}_*")
                  if p.is_dir() and (ONLY is None or p.name in ONLY))


def _identity_sidecar(bundle: str) -> Path:
    """The reference self-check of a bundle, once it has been run (results/verdicts/)."""
    return DIFF / bundle / "identity.json"


def identity_broken(bundle: str) -> bool:
    """Identity control not INTACT => a nondeterministic/unevaluable harness, excluded from
    every reported rate (the same rule as the result tables)."""
    p = _identity_sidecar(bundle)
    if not p.exists():
        return False
    try:
        v = json.loads(p.read_text()).get("verdict")
    except Exception:
        return False
    return v is not None and v != "INTACT"


def _cfg(bundle_dir: Path) -> dict:
    case = json.loads((bundle_dir / "case.json").read_text())
    meta = json.loads((bundle_dir / "target" / "meta.json").read_text())
    flags_files = list((bundle_dir / "source_code").glob("*.flags"))
    flags = flags_files[0].read_text().strip() if flags_files else ""
    xcf = (case.get("extra_cflags") or "").strip()
    if xcf:
        flags = (flags + " " + xcf).strip()
    return {"orig_dir": "/work/orig", "entry": "harness.c",
            "relpath": meta.get("repo_relpath") or "harness.c",
            "target_func": meta.get("name", ""), "flags": flags,
            "replay_timeout": 10, "bundle": bundle_dir.name}


def measure(bundle: str) -> dict:
    """Run one bundle in its own container. Returns the parsed sidecar (also written to disk)."""
    bdir = DATASET / bundle
    corpus = CORPUS / bundle / "corpus"
    out = COV / f"{bundle}.json"
    if not corpus.is_dir() or not any(corpus.iterdir()):
        rec = {"bundle": bundle, "ok": False, "error": "no frozen corpus"}
        out.write_text(json.dumps(rec, indent=1))
        return rec

    scratch = COV / "_scratch" / f"{bundle}.{uuid.uuid4().hex[:8]}"
    try:
        shutil.rmtree(scratch, ignore_errors=True)
        scratch.mkdir(parents=True)
        shutil.copytree(bdir / "source_code", scratch / "orig")
        (scratch / "corpus").mkdir()
        n = 0
        for f in sorted(corpus.iterdir()):
            if f.is_file():
                shutil.copy(f, scratch / "corpus" / f.name)
                n += 1
        (scratch / "config.json").write_text(json.dumps(_cfg(bdir), indent=1))
        shutil.copy(RUNNER, scratch / "coverage_run.py")

        cname = f"vbcov_{bundle}_{uuid.uuid4().hex[:6]}"[:120]
        # build (<=300s) + n replays (<=10s each) + merge/report, with headroom.
        timeout = min(3000, 420 + 12 * n)
        cmd = ["docker", "run", "--rm", "--network", "none", "--privileged",
               "--name", cname, "--label", "ddiv-coverage=1",
               "--memory", MEM, "--memory-swap", MEM,
               "-v", f"{scratch}:/work", IMAGE,
               "bash", "-c", "python3 /work/coverage_run.py"]
        try:
            subprocess.run(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                           timeout=timeout)
        except subprocess.TimeoutExpired:
            subprocess.run(["docker", "kill", cname], stdout=subprocess.DEVNULL,
                           stderr=subprocess.DEVNULL)

        rp = scratch / "out" / "coverage.json"          # read the FILE, never stdout
        if rp.exists():
            rec = json.loads(rp.read_text())
        else:
            rec = {"bundle": bundle, "ok": False, "error": "container produced no result"}
        rec["bundle"] = bundle
        out.write_text(json.dumps(rec, indent=1))
        return rec
    except Exception as ex:
        rec = {"bundle": bundle, "ok": False, "error": f"host: {ex}"}
        out.write_text(json.dumps(rec, indent=1))
        return rec
    finally:
        shutil.rmtree(scratch, ignore_errors=True)


# --------------------------------------------------------------------------- #
# aggregation
# --------------------------------------------------------------------------- #

_EXPECTED_ROWS = None


def _expected(bundle: str):
    """The paper's measurement of one bundle, from data/expected/coverage.csv."""
    global _EXPECTED_ROWS
    if _EXPECTED_ROWS is None:
        import csv
        _EXPECTED_ROWS = {}
        with open(EXPECTED, newline="") as fh:
            for r in csv.DictReader(fh):
                rec = {"bundle": r["bundle"], "ok": True, "n_inputs": int(r["n_inputs"]),
                       "n_crashed": int(r["n_crashed"])}
                for m in ("regions", "lines", "branches"):
                    tot, cov = int(r[m + "_total"]), int(r[m + "_covered"])
                    rec[m] = {"total": tot, "covered": cov,
                              "pct": (100.0 * cov / tot) if tot else None}
                _EXPECTED_ROWS[r["bundle"]] = rec
    return _EXPECTED_ROWS.get(bundle)


_USE_EXPECTED = False


def _load(bundle: str):
    if _USE_EXPECTED:
        return _expected(bundle)
    p = COV / f"{bundle}.json"
    if not p.exists():
        return None
    try:
        return json.loads(p.read_text())
    except Exception:
        return None


def aggregate(groups):
    """Per-group reach. Reported over the EVALUATED population (identity-broken excluded), the
    same denominator as the result tables.

    Two means per metric, because they answer different questions and diverge sharply on
    branches: `macro` is the mean of per-function percentages with EMPTY DENOMINATORS EXCLUDED
    (a branchless function has no branch coverage to average), `pooled` is total covered /
    total present across the group. Averaging a branchless function in as 0% -- which the old
    percentage-only path did -- is what pushes a corpus like ExeBench to a branch figure far
    below its line figure.
    """
    rows = []
    for g, label in groups:
        bs = [b for b in bundles(g) if not identity_broken(b)]
        recs = [r for r in (_load(b) for b in bs) if r and r.get("ok")]
        row = {"group": g, "label": label, "n_pop": len(bs), "n_measured": len(recs)}
        sizes = [r.get("n_inputs", 0) for r in recs]
        row["inputs_per_fn"] = statistics.mean(sizes) if sizes else 0.0
        row["n_crashed"] = sum(r.get("n_crashed", 0) for r in recs)
        row["n_substring"] = sum(1 for r in recs if r.get("match") == "substring")
        row["n_noncontinuous"] = sum(1 for r in recs if not r.get("continuous", True))
        for metric in ("regions", "lines", "branches"):
            pcts = [r[metric]["pct"] for r in recs
                    if r.get(metric) and r[metric].get("pct") is not None]
            tot = sum(r[metric]["total"] for r in recs if r.get(metric))
            cov = sum(r[metric]["covered"] for r in recs if r.get(metric))
            row[f"{metric}_macro"] = statistics.mean(pcts) if pcts else None
            row[f"{metric}_pooled"] = (100.0 * cov / tot) if tot else None
            row[f"{metric}_defined"] = len(pcts)
        rows.append(row)
    return rows


def _f(v, w=5):
    return f"{v:{w}.1f}" if v is not None else "    -"


def report(rows, latex=False):
    print(f"\n{'Corpus':<12}{'n':>6}{'meas':>6}{'inp/fn':>8}"
          f"{'Line':>8}{'Branch':>8}{'Region':>8}   |{'  Line':>8}{'Branch':>8}{'Region':>8}")
    print(f"{'':<12}{'':>6}{'':>6}{'':>8}{'---- macro-avg ----':>24}   |{'---- pooled ----':>24}")
    print("-" * 96)
    for r in rows:
        print(f"{r['label']:<12}{r['n_pop']:>6}{r['n_measured']:>6}{r['inputs_per_fn']:>8.1f}"
              f"{_f(r['lines_macro'],8)}{_f(r['branches_macro'],8)}{_f(r['regions_macro'],8)}   |"
              f"{_f(r['lines_pooled'],8)}{_f(r['branches_pooled'],8)}{_f(r['regions_pooled'],8)}")
    print("-" * 96)
    for r in rows:
        nb = r["n_measured"] - r["branches_defined"]
        extra = []
        if nb:
            extra.append(f"{nb} branchless fn excluded from branch mean")
        if r["n_substring"]:
            extra.append(f"{r['n_substring']} substring name match")
        if r["n_noncontinuous"]:
            extra.append(f"{r['n_noncontinuous']} without continuous profiling")
        if r["n_measured"] < r["n_pop"]:
            extra.append(f"{r['n_pop'] - r['n_measured']} unmeasured")
        if extra:
            print(f"  {r['label']}: " + "; ".join(extra))

    if latex:
        # half-UP, not Python's default half-to-even: several cells land exactly on .5
        # (HumanEval 72.5 inputs/fn, CVE 74.5% branches) where banker's rounding reads as an
        # off-by-one against the conventionally-rounded value.
        def r0(x):
            return int(math.floor(x + 0.5))
        print("\n% --- tab:reach rows (macro-average, branchless excluded from Branch) ---")
        for r in rows:
            print(f"{r['label']} & {r0(r['inputs_per_fn'])} & "
                  f"{r0(r['lines_macro'])} & {r0(r['branches_macro'])} \\\\")
        lo_l = min(r["lines_macro"] for r in rows)
        hi_l = max(r["lines_macro"] for r in rows)
        lo_b = min(r["branches_macro"] for r in rows)
        hi_b = max(r["branches_macro"] for r in rows)
        lo_i = min(r["inputs_per_fn"] for r in rows)
        hi_i = max(r["inputs_per_fn"] for r in rows)
        print(f"% prose ranges: {lo_i:.0f}--{hi_i:.0f} inputs/fn, "
              f"{lo_l:.0f}--{hi_l:.0f}% lines, {lo_b:.0f}--{hi_b:.0f}% branches")


def failures(groups, limit=25):
    bad = []
    for g, _ in groups:
        for b in bundles(g):
            if identity_broken(b):
                continue
            r = _load(b)
            if r is not None and not r.get("ok"):
                bad.append((b, r.get("error", "?"), r.get("match", "")))
    if bad:
        print(f"\n{len(bad)} failed measurements; first {min(limit, len(bad))}:")
        for b, e, m in bad[:limit]:
            print(f"  {b:<55} {e} {m}")
    return bad


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--groups", default="", help="comma-separated group prefixes (default all)")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--force", action="store_true", help="re-measure bundles that already have a sidecar")
    ap.add_argument("--retry-failed", action="store_true", help="re-measure only failed sidecars")
    ap.add_argument("--report-only", action="store_true")
    ap.add_argument("--expected", action="store_true",
                    help="print the paper's reach table from data/expected/coverage.csv")
    ap.add_argument("--bundles-file",
                    help="only the function ids listed in this file (see oracle/sample.py)")
    ap.add_argument("--latex", action="store_true")
    ap.add_argument("--limit", type=int, default=0, help="cap bundles per group (trial runs)")
    args = ap.parse_args()

    sel = [gp for gp in GROUPS if not args.groups or gp[0] in args.groups.split(",")]
    if args.bundles_file:
        global ONLY
        ONLY = set(Path(args.bundles_file).read_text().split())
    if args.expected:
        global _USE_EXPECTED
        _USE_EXPECTED = True
        report(aggregate(sel), latex=args.latex)
        return 0
    COV.mkdir(parents=True, exist_ok=True)

    if not args.report_only:
        todo = []
        for g, _ in sel:
            picked = 0
            for b in bundles(g):
                # Measure EVERY bundle with a frozen corpus, including identity-broken ones:
                # coverage is a property of corpus+reference, independent of any arm. The
                # evaluated-population filter is applied at aggregation, so the reported
                # denominator can be re-cut without re-running the measurement.
                rec = _load(b)
                if rec is not None and not args.force:
                    if not (args.retry_failed and not rec.get("ok")):
                        continue
                todo.append(b)
                picked += 1
                if args.limit and picked >= args.limit:
                    break
        print(f"measuring {len(todo)} bundles with {args.jobs} jobs (image {IMAGE})", flush=True)
        done = ok = 0
        with cf.ThreadPoolExecutor(max_workers=args.jobs) as ex:
            for rec in ex.map(measure, todo):
                done += 1
                ok += bool(rec.get("ok"))
                if done % 25 == 0 or done == len(todo):
                    print(f"  {done}/{len(todo)}  ok={ok}", flush=True)

    rows = aggregate(sel)
    report(rows, latex=args.latex)
    failures(sel)
    (COV / "_summary.json").write_text(json.dumps(rows, indent=1))
    print(f"\nper-group summary -> {COV / '_summary.json'}")


if __name__ == "__main__":
    sys.exit(main())
