#!/usr/bin/env python3
"""Result tables of the differential-fuzzing oracle, and the check against the paper's verdicts.

  python3 oracle/tables.py                 # tables from data/expected/verdicts.csv (the paper)
  python3 oracle/tables.py --results       # tables from results/verdicts/ (what you ran)
  python3 oracle/tables.py --compare       # every pair you ran, checked against the paper
  python3 oracle/tables.py --same-functions   # the paper's verdicts on just the functions you
                                              # ran (the like-for-like reference for a sample)

One row of data/expected/verdicts.csv per (function, system):

  verdict       INTACT | DEVIATED | BUILD_FAILED | NO_OUTPUT | SPLICE_FAILED
  divergence    for DEVIATED: `output` (a changed output / exit state on an input where neither
                side crashes) or `crash` (a removed, introduced or shifted crash, or a hang)
  crash_absence 1 iff the validated PoC (frozen input c00000) crashes the reference and no
                longer crashes the candidate; defined on the CVE track only
  div_types     the per-channel divergence counts behind the verdict

Paper columns.  Bld = INTACT + DEVIATED (the candidate compiled).  Mat (Matched) = INTACT.
On the four established corpora and GitHub, Div (Divergence) = DEVIATED.  On the CVE track
C-A (Crash Absence) = DEVIATED with crash_absence, and Div = the remaining DEVIATED.
Percentages are of the group's n (every shipped function); raw counts are printed beside them.

HumanEval, ExeBench and MBPP ship their own tests (oracle/shipped_tests.py runs them).
data/expected/shipped_tests.csv holds the paper's outcome for every candidate that exists:
`compiled`, `passed`, and `via` = the attempt of their harness that compiled it (`strict`, or
`compat` behind the decompiler-vocabulary declarations; empty if neither did).  From them:

  Pass    the candidate builds under the corpus's harness and passes every shipped test
  Div|P   of the candidates that pass AND that the oracle scores (Bld), the share that is
          DEVIATED; the denominator is that count, not n
"""
from __future__ import annotations

import argparse
import csv
import json
import sys
from collections import Counter, OrderedDict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BUNDLES = ROOT / "data" / "bundles"
CANDIDATES = ROOT / "data" / "candidates"
EXPECTED = ROOT / "data" / "expected" / "verdicts.csv"
EXPECTED_TESTS = ROOT / "data" / "expected" / "shipped_tests.csv"
EXPECTED_COV = ROOT / "data" / "expected" / "coverage.csv"
RESULTS_COV = ROOT / "results" / "coverage"
RESULTS = ROOT / "results" / "verdicts"
RESULTS_TESTS = ROOT / "results" / "shipped_tests"
TEST_GROUPS = ("humaneval", "exebench", "mbpp")      # the corpora that ship tests

GROUPS = OrderedDict([("humaneval", "HumanEval"), ("exebench", "ExeBench"),
                      ("anghabench", "AnghaBench"), ("mbpp", "MBPP"),
                      ("github_barebone", "GitHub"), ("cve_barebone", "CVE")])
SYSTEMS = OrderedDict([("ghidra", "Ghidra"), ("ida", "Hex-Rays"),
                       ("llm4decompile", "LLM4Decompile"), ("sk2decompile", "SK2Decompile"),
                       ("idioms", "Idioms"), ("glm-refine", "GLM-5.2-Refine"),
                       ("degpt", "DeGPT-Qwen"), ("autodecompiler", "AutoDecompiler"),
                       ("nova", "Nova"), ("slade", "SLaDe"), ("glm-e2e", "GLM-5.2-E2E")])
OUTPUT_TYPES = ("silent_wrong_answer", "exit_code_diff")
CRASH_TYPES = ("vanished_crash", "introduced_crash", "shifted_crash", "introduced_hang")
FIELDS = ["bundle", "group", "system", "verdict", "divergence", "crash_absence",
          "n_divergent", "corpus_size", "div_types"]


def group_of(bundle: str) -> str:
    for g in GROUPS:
        if bundle.startswith(g + "_"):
            return g
    return "?"


def shipped_bundles():
    return sorted(p.name for p in BUNDLES.iterdir() if p.is_dir() and group_of(p.name) != "?")


def record_from_sidecar(bundle: str, system: str, d: dict) -> dict:
    """Normalize one oracle sidecar (results/verdicts/<bundle>/<system>.json) to a table row."""
    verdict = d.get("verdict") or "INFRA"
    if verdict == "DECOMPILE_FAILED":            # an empty candidate = the system gave no output
        verdict = "NO_OUTPUT"
    dt = d.get("div_types") or {}
    divergence, absence = "", 0
    if verdict == "DEVIATED":
        divergence = "output" if any(dt.get(t) for t in OUTPUT_TYPES) else "crash"
        if group_of(bundle) == "cve_barebone":
            absence = int(any(x.get("type") == "vanished_crash" and x.get("input") == "c00000"
                              for x in d.get("divergences") or []))
    return {"bundle": bundle, "group": group_of(bundle), "system": system, "verdict": verdict,
            "divergence": divergence, "crash_absence": absence,
            "n_divergent": int(d.get("n_divergent") or 0),
            "corpus_size": int(d.get("corpus_size") or 0),
            "div_types": ";".join(f"{k}:{v}" for k, v in sorted(dt.items()))}


def load_expected():
    rows = {}
    with open(EXPECTED, newline="") as fh:
        for r in csv.DictReader(fh):
            r["crash_absence"] = int(r["crash_absence"] or 0)
            rows[(r["bundle"], r["system"])] = r
    return rows


def load_results():
    """Rows for every (shipped function, system) that has been run. A system that produced no
    candidate for a function has no file under data/candidates/ and is recorded as NO_OUTPUT."""
    rows = {}
    for b in shipped_bundles():
        for s in ["identity"] + list(SYSTEMS):
            p = RESULTS / b / f"{s}.json"
            if p.exists():
                try:
                    rows[(b, s)] = record_from_sidecar(b, s, json.loads(p.read_text()))
                except Exception:
                    continue
            elif s != "identity" and not (CANDIDATES / b / f"{s}.response.c").exists() \
                    and (RESULTS / b / "identity.json").exists():
                rows[(b, s)] = {"bundle": b, "group": group_of(b), "system": s,
                                "verdict": "NO_OUTPUT", "divergence": "", "crash_absence": 0,
                                "n_divergent": 0, "corpus_size": 0, "div_types": ""}
    return rows


def load_expected_tests():
    """{(bundle, system): (compiled, passed)} of the paper's shipped-test run."""
    rows = {}
    if EXPECTED_TESTS.exists():
        with open(EXPECTED_TESTS, newline="") as fh:
            for r in csv.DictReader(fh):
                rows[(r["bundle"], r["system"])] = (int(r["compiled"]), int(r["passed"]))
    return rows


def test_outcome(d: dict):
    """(compiled, passed) of one results/shipped_tests sidecar: either attempt counts."""
    s, c = d.get("strict") or {}, d.get("compat") or {}
    return (int(bool(s.get("compiled") or c.get("compiled"))),
            int(bool(s.get("passed") or c.get("passed"))))


def load_result_tests():
    rows = {}
    if RESULTS_TESTS.is_dir():
        for b in shipped_bundles():
            if group_of(b) not in TEST_GROUPS:
                continue
            for s in ["identity"] + list(SYSTEMS):
                p = RESULTS_TESTS / b / f"{s}.json"
                if p.exists():
                    try:
                        rows[(b, s)] = test_outcome(json.loads(p.read_text()))
                    except Exception:
                        continue
    return rows


def pct(v: int, n: int) -> int:
    """Rounded percentage, rounding exactly as the paper's table generator does (Python's
    round(): halves go to the even neighbour, so 12.5% prints as 12)."""
    return round(100 * v / n) if n else 0


def tally(rows, group, system, bundles, tests=None):
    c = Counter()
    for b in bundles:
        r = rows.get((b, system))
        t = (tests or {}).get((b, system))
        if t is not None:
            c["tested"] += 1
            if t[1]:
                c["pass"] += 1
                if r is not None and r["verdict"] in ("INTACT", "DEVIATED"):
                    c["pass_scored"] += 1                 # Div|P denominator
                    c["pass_div"] += r["verdict"] == "DEVIATED"
        if r is None:
            c["not_run"] += 1
            continue
        v = r["verdict"]
        c[v] += 1
        if v != "NO_OUTPUT":
            c["out"] += 1
        if v == "INTACT":
            c["bld"] += 1; c["mat"] += 1
        elif v == "DEVIATED":
            c["bld"] += 1
            if group == "cve_barebone" and r["crash_absence"]:
                c["ca"] += 1
            else:
                c["div"] += 1
                c["div_" + (r["divergence"] or "crash")] += 1
    return c


def print_tables(rows, title, tests=None, only=None):
    all_b = [b for b in shipped_bundles() if only is None or b in only]
    print(f"==== {title} ====")
    for g, label in GROUPS.items():
        shipped = [b for b in all_b if group_of(b) == g]
        ran = [b for b in shipped if (b, "identity") in rows]
        if not ran:
            continue
        # The oracle's rule: a function whose reference self-check is not INTACT is not
        # adjudicable and is left out of every rate. (All shipped functions pass in the paper.)
        bs = [b for b in ran if rows[(b, "identity")]["verdict"] == "INTACT"]
        n = len(bs)
        cve = g == "cve_barebone"
        with_tests = g in TEST_GROUPS and bool(tests) and any((b, "identity") in tests for b in bs)
        note = "" if len(ran) == len(shipped) else f" of {len(shipped)} shipped"
        if len(ran) != n:
            note += f";  {len(ran) - n} left out: reference self-check not INTACT in this run"
        print(f"\n{label}  (n = {n}{note})")
        hdr = f"  {'system':<16}{'Out':>13}{'Bld':>13}{'Mat':>13}{'Div':>13}"
        hdr += f"{'C-A':>13}" if cve else f"{'(output':>10}{'/crash)':>8}"
        if with_tests:
            hdr += f"{'Pass':>14}{'Div|P':>18}"
        print(hdr)
        for s, slabel in SYSTEMS.items():
            c = tally(rows, g, s, bs, tests if with_tests else None)
            if c["not_run"] == n:
                continue
            def cell(k):
                return f"{c[k]:>6} ({pct(c[k], n):>3}%)"
            line = f"  {slabel:<16}{cell('out')}{cell('bld')}{cell('mat')}{cell('div')}"
            line += cell("ca") if cve else f"{c['div_output']:>10}{c['div_crash']:>8}"
            if with_tests:
                dp = f"{pct(c['pass_div'], c['pass_scored']):>3}%" if c["pass_scored"] else "   -"
                line += f" {cell('pass')}{dp:>6} ({c['pass_div']}/{c['pass_scored']})"
            if c["not_run"]:
                line += f"   [{c['not_run']} not run]"
            print(line)
    if tests:
        pooled(rows, tests, all_b)


def pooled(rows, tests, all_b):
    """The pooled shipped-test vs oracle statistics over HumanEval, ExeBench and MBPP."""
    n = p = pd = pds = fi = 0
    for b in all_b:
        if group_of(b) not in TEST_GROUPS:
            continue
        ident = rows.get((b, "identity"))
        if ident is None or ident["verdict"] != "INTACT":
            continue
        for s in SYSTEMS:
            r, t = rows.get((b, s)), tests.get((b, s))
            if r is None or t is None or r["verdict"] not in ("INTACT", "DEVIATED"):
                continue
            n += 1                                        # scored by both
            if t[1]:
                p += 1
                if r["verdict"] == "DEVIATED":
                    pd += 1
                    pds += not any(k in r["div_types"] for k in CRASH_TYPES)
            elif t[0] and r["verdict"] == "INTACT":
                fi += 1
    if not n:
        return
    print(f"\nShipped tests vs oracle, pooled over HumanEval, ExeBench and MBPP:")
    print(f"  candidates scored by both: {n};  pass every shipped test: {p}")
    if p and pd:
        print(f"  pass yet DEVIATED: {pd} ({100.0 * pd / p:.1f}% of passers, "
              f"{100.0 * pd / n:.1f}% of all);  of these, output-only (no crash or hang): "
              f"{100.0 * pds / pd:.0f}%")
    print(f"  fail a shipped test yet INTACT: {fi} ({100.0 * fi / n:.1f}% of all);  "
          f"the two disagree on {100.0 * (pd + fi) / n:.1f}%")


def compare(expected, results):
    keys = [k for k in expected if k in results]
    if not keys:
        print("nothing to compare: results/verdicts/ holds no evaluated pair yet")
        return 1
    same, diff = 0, []
    for k in sorted(keys):
        e, r = expected[k], results[k]
        if (e["verdict"], int(e["crash_absence"])) == (r["verdict"], int(r["crash_absence"])):
            same += 1
        else:
            diff.append((k, e, r))
    per = Counter(group_of(b) for b, _ in keys)
    print(f"compared {len(keys)} (function, system) pairs of {len(expected)} in the paper: "
          f"{same} identical, {len(diff)} different")
    print("  pairs per group: " + ", ".join(f"{GROUPS[g]} {per[g]}" for g in GROUPS if per[g]))
    for (b, s), e, r in diff[:200]:
        ca_e = " +crash_absence" if int(e["crash_absence"]) else ""
        ca_r = " +crash_absence" if int(r["crash_absence"]) else ""
        print(f"  DIFF {b} / {s}: paper {e['verdict']}{ca_e} [{e['div_types']}]"
              f"  !=  here {r['verdict']}{ca_r} [{r['div_types']}]")
    if len(diff) > 200:
        print(f"  ... and {len(diff) - 200} more")
    tdiff = compare_tests()
    cdiff = compare_coverage()
    return 0 if not (diff or tdiff or cdiff) else 2


def compare_tests():
    """Check results/shipped_tests/ against the paper's shipped-test outcomes."""
    exp, got = load_expected_tests(), load_result_tests()
    keys = sorted(k for k in exp if k in got)
    if not keys:
        return 0
    diff = [(k, exp[k], got[k]) for k in keys if exp[k] != got[k]]
    print(f"\nshipped tests: compared {len(keys)} (function, system) pairs of {len(exp)} in the "
          f"paper: {len(keys) - len(diff)} identical, {len(diff)} different")
    def word(t):
        return "pass" if t[1] else ("fail" if t[0] else "no build")
    for (b, s), e, r in diff[:200]:
        print(f"  DIFF {b} / {s}: paper {word(e)}  !=  here {word(r)}")
    if len(diff) > 200:
        print(f"  ... and {len(diff) - 200} more")
    return len(diff)


def compare_coverage():
    """Check results/coverage/ against the paper's per-function coverage measurement."""
    if not (RESULTS_COV.is_dir() and EXPECTED_COV.exists()):
        return 0
    keys = ("regions_total", "regions_covered", "lines_total", "lines_covered",
            "branches_total", "branches_covered", "n_inputs")
    same, diff = 0, []
    with open(EXPECTED_COV, newline="") as fh:
        for e in csv.DictReader(fh):
            p = RESULTS_COV / f"{e['bundle']}.json"
            if not p.exists():
                continue
            try:
                r = json.loads(p.read_text())
            except Exception:
                continue
            if not r.get("ok"):
                diff.append((e["bundle"], "measurement failed: " + str(r.get("error"))))
                continue
            got = {"n_inputs": r.get("n_inputs")}
            for m in ("regions", "lines", "branches"):
                got[m + "_total"] = r[m]["total"]
                got[m + "_covered"] = r[m]["covered"]
            moved = [k for k in keys if int(e[k]) != int(got[k] or 0)]
            if moved:
                diff.append((e["bundle"], ", ".join(f"{k} {e[k]}->{got[k]}" for k in moved)))
            else:
                same += 1
    if not same and not diff:
        return 0
    print(f"\ncoverage: compared {same + len(diff)} functions: {same} identical, "
          f"{len(diff)} different")
    for b, what in diff[:50]:
        print(f"  DIFF {b}: {what}")
    return len(diff)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--results", action="store_true",
                    help="tabulate results/verdicts/ instead of the shipped expected verdicts")
    ap.add_argument("--compare", action="store_true",
                    help="check every pair in results/verdicts/ against the expected verdicts")
    ap.add_argument("--same-functions", action="store_true",
                    help="print the expected (paper) tables over only the functions in results/")
    ap.add_argument("--export", metavar="CSV",
                    help="write the rows of results/verdicts/ in the expected-verdicts format")
    args = ap.parse_args()

    if args.export:
        rows = load_results()
        with open(args.export, "w", newline="") as fh:
            w = csv.DictWriter(fh, fieldnames=FIELDS, lineterminator="\n")
            w.writeheader()
            for k in sorted(rows):
                w.writerow(rows[k])
        print(f"wrote {len(rows)} rows -> {args.export}")
        return 0
    if args.compare:
        return compare(load_expected(), load_results())
    if args.same_functions:
        ran = {b for (b, s) in load_results() if s == "identity"}
        print_tables(load_expected(), f"data/expected/ (the paper's verdicts) on the {len(ran)} "
                     "functions in results/", load_expected_tests(), only=ran)
        return 0
    if args.results:
        print_tables(load_results(), "results/ (this machine)", load_result_tests())
    else:
        print_tables(load_expected(), "data/expected/ (the paper's verdicts)",
                     load_expected_tests())
    return 0


if __name__ == "__main__":
    sys.exit(main())
