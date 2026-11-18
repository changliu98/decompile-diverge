"""Differential-fuzzing oracle -- reusable testing facility (host side).

Given a bundle (self-contained direct-call / func0 harness) and a candidate decompiled
function, this decides INTACT vs DEVIATED by DIFFERENTIAL FUZZING rather than a fixed
replay corpus:

  splice cand into the harness  ->  build orig_bin + cand_bin (strict, dockerized)
  ->  AFL-fuzz orig for a time budget to grow a high-coverage corpus
  ->  replay the WHOLE corpus (seeds + queue + crashes) on BOTH binaries
  ->  a case is DEVIATED iff some input makes them diverge:
        * vanished_crash      -- orig crashes, cand doesn't   (THE vanish signal)
        * introduced_crash    -- orig clean, cand crashes
        * shifted_crash       -- both crash, different CWE+location (crashparse.patterns_match)
        * silent_wrong_answer -- both clean, but differ in FULL post-call variable state
                                 (argv[2] exit-memstate dump: return + outputs + globals,
                                 compared by symbol name w/ reloc masking; stdout/stderr
                                 fallback when the harness emits no dump)

Everything that executes runs inside the `ddiv-oracle` image with --network none and a 16g
memory cap. This module (host) does the splice + Docker orchestration + crashparse
refinement; the in-container work is `difffuzz_run.py` / `difffuzz_run_v3.py` (pure stdlib; see RECIPE). Coverage of the
target function is recorded as the confidence attached to an INTACT verdict.

Scope: bundles whose harness is self-contained (cve_barebone / github_barebone direct-call,
and the functional func0 harnesses). Real-project `cve` bundles need a project fuzz harness
and are out of scope for this facility.

Verdicts: INTACT | DEVIATED | BUILD_FAILED | DECOMPILE_FAILED | SPLICE_FAILED | INFRA.
"""
from __future__ import annotations

import json
import os
import shutil
import subprocess
import sys
import threading
import uuid
from collections import defaultdict
from dataclasses import dataclass, field, asdict
from pathlib import Path
from typing import List, Optional, Tuple

# release root = parent of this folder; keep it importable for oracle.crashparse.
_REPO = Path(__file__).resolve().parent.parent
if str(_REPO) not in sys.path:
    sys.path.insert(0, str(_REPO))

try:
    from oracle.crashparse import parse_crash, patterns_match
except Exception:                                   # crashparse optional at import time
    parse_crash = None
    def patterns_match(a, b):                        # type: ignore
        return False

IMAGE = os.environ.get("DDIV_AFL_IMAGE", "ddiv-oracle:22.04")
MEM_LIMIT = os.environ.get("DDIV_AFL_MEM", "16g")
DEFAULT_FUZZ_SECONDS = 300
ORACLE_VERSION = 2
DATA = _REPO / "data"
BUNDLES = DATA / "bundles"                  # one directory per benchmark function
CAND_ROOT = DATA / "candidates"             # <bundle>/<system>.response.c, the evaluated outputs
# Frozen replay inputs: <bundle>/corpus/ + corpus_meta.json. They are shipped; point this at an
# EMPTY directory to re-grow every corpus from the bundle seeds instead of replaying them.
CORPUS_ROOT = Path(os.environ.get("DDIV_CORPUS_ROOT", str(DATA / "corpus")))
DIFF_ROOT = Path(os.environ.get("DDIV_DIFF_ROOT", str(_REPO / "results" / "verdicts")))

# The recipe each group is scored with: (container-side runner, AFL time budget in seconds).
# difffuzz_run_v3.py = difffuzz_run.py + the exit-state dump for hand-written drivers and the
# re-run determinism guard on every channel; the GitHub and CVE tracks are scored with it.
RECIPE = {
    "humaneval":       ("difffuzz_run.py", 300),
    "exebench":        ("difffuzz_run.py", 300),
    "anghabench":      ("difffuzz_run.py", 300),
    "mbpp":            ("difffuzz_run.py", 300),
    "github_barebone": ("difffuzz_run_v3.py", 600),
    "cve_barebone":    ("difffuzz_run_v3.py", 600),
}


def group_of(bundle_dir) -> str:
    """The benchmark group of a bundle: case.json `group`, else the directory-name prefix."""
    bundle_dir = Path(bundle_dir)
    try:
        g = json.loads((bundle_dir / "case.json").read_text()).get("group")
        if g in RECIPE:
            return g
    except Exception:
        pass
    for g in RECIPE:
        if bundle_dir.name.startswith(g + "_"):
            return g
    return ""


def runner_for(bundle_dir) -> Path:
    """Container-side runner for this bundle's group (DDIV_RUNNER overrides)."""
    env = os.environ.get("DDIV_RUNNER")
    if env:
        return Path(env)
    return Path(__file__).resolve().parent / RECIPE.get(group_of(bundle_dir),
                                                        ("difffuzz_run.py", 300))[0]


def budget_for(bundle_dir) -> int:
    """AFL time budget (seconds) of this bundle's group -- part of the corpus recipe."""
    return RECIPE.get(group_of(bundle_dir), ("", DEFAULT_FUZZ_SECONDS))[1]

# Per-bundle corpus cache: fuzz ORIG once, freeze, replay for every arm. The lock serializes
# generation within a run (arms of one bundle wait for the first to freeze it); the mem cache
# avoids re-reading disk. A FAILED generation is cached in-memory only (NOT persisted) so a fresh
# process retries it (INFRA is retryable); a SUCCESS is persisted under CORPUS_ROOT/<name>/.
_CORPUS_LOCKS: dict = defaultdict(threading.Lock)
_CORPUS_MEM: dict = {}


@dataclass
class DiffResult:
    verdict: str
    bundle: str
    arm: str = ""
    build_orig: bool = False
    build_cand: bool = False
    corpus_size: int = 0
    corpus_frozen: bool = False            # replayed the shared per-bundle FROZEN corpus (fair)
    fuzz_ok: bool = False                  # AFL actually launched during corpus generation
    corpus_source: Optional[str] = None    # "fuzz" | "seeds_fallback" (all-seeds-crash -> io corpus)
    afl_rc: Optional[int] = None           # AFL return code from corpus generation
    n_divergent: int = 0
    vanished: bool = False                 # any vanished_crash divergence (the vanish signal)
    memstate_compared: bool = False        # harness dumps argv[2] -> full-variable compare live
    memstate_inputs: int = 0               # both-clean inputs whose full variable state was diffed
    replay_truncated: bool = False         # replay hit the wall-time budget (verdict on partial corpus)
    div_types: dict = field(default_factory=dict)
    coverage: Optional[dict] = None
    divergences: list = field(default_factory=list)
    error: Optional[str] = None
    fuzz_seconds: int = DEFAULT_FUZZ_SECONDS
    oracle_version: int = ORACLE_VERSION
    enhanced_harness: bool = False         # generated harness: errno/full-buffer/two-call observers
    multi_call: bool = False               # target exercised twice with freshly rebuilt arguments
    external_state_compared: bool = False  # stdout/stderr + isolated-cwd filesystem state

    def to_json(self) -> str:
        return json.dumps(asdict(self), indent=1)


# --------------------------------------------------------------------------- #
# bundle loading + splice
# --------------------------------------------------------------------------- #

def _load(bundle_dir: Path):
    case = json.loads((bundle_dir / "case.json").read_text())
    meta = json.loads((bundle_dir / "target" / "meta.json").read_text())
    relpath = meta.get("repo_relpath", "harness.c")
    orig_fn = (bundle_dir / "target" / "original_function.c").read_bytes()
    flags_files = list((bundle_dir / "source_code").glob("*.flags"))
    flags = flags_files[0].read_text().strip() if flags_files else ""
    # case.json:extra_cflags carries the -D guards / -I paths the harness needs to compile (e.g.
    # xxhash's -DXXH_STATIC_LINKING_ONLY that unlocks its typedefs). The functional oracle passes
    # these; difffuzz must too, or orig fails to build -> corpus-gen INFRA -> the whole bundle drops.
    xcf = (case.get("extra_cflags") or "").strip()
    if xcf:
        flags = (flags + " " + xcf).strip()
    baseline = case.get("baseline") or {}
    return {
        "case": case, "meta": meta, "relpath": relpath, "orig_fn": orig_fn,
        "flags": flags, "target_func": meta.get("name", ""),
        "poc_should_crash": bool(baseline.get("crashed")),
    }


class _SpliceError(Exception):
    pass


def _splice(harness: bytes, orig_fn: bytes, cand: bytes) -> bytes:
    """Blind byte replace of the original function with the candidate. Guard: the original
    bytes must occur exactly once (else the strict splice is ambiguous -> SPLICE_FAILED)."""
    n = harness.count(orig_fn)
    if n != 1:
        raise _SpliceError(f"original function occurs {n}x in harness (need exactly 1)")
    return harness.replace(orig_fn, cand)


# --------------------------------------------------------------------------- #
# docker + corpus generation (once per bundle)
# --------------------------------------------------------------------------- #

def _docker_run(scratch: Path, cname: str, image: str, timeout: int) -> bool:
    """Run the container-side runner on `scratch` mounted at /work. False on timeout (kills it)."""
    cmd = ["docker", "run", "--rm", "--network", "none", "--privileged",
           "--name", cname, "--label", "ddiv-difffuzz=1",
           "--memory", MEM_LIMIT, "--memory-swap", MEM_LIMIT,   # cap RAM (no swap) per container
           "-v", f"{scratch}:/work", image,
           "bash", "-c", "python3 /work/difffuzz_run.py"]
    try:
        subprocess.run(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, timeout=timeout)
        return True
    except subprocess.TimeoutExpired:
        subprocess.run(["docker", "kill", cname], stdout=subprocess.DEVNULL,
                       stderr=subprocess.DEVNULL)
        return False


def _copy_seeds(bundle_dir: Path, dest: Path) -> int:
    dest.mkdir(parents=True, exist_ok=True)
    io_in = bundle_dir / "io" / "input"
    n = 0
    if io_in.is_dir():
        for f in sorted(io_in.iterdir()):
            if f.is_file():
                shutil.copy(f, dest / f.name); n += 1
    return n


def generate_corpus(bundle_dir, seconds: int, image: str = IMAGE) -> Tuple[Optional[Path], dict]:
    """Fuzz ORIG ONCE and FREEZE the deduped corpus to CORPUS_ROOT/<name>/corpus/. Returns
    (corpus_dir | None, meta); None => fuzzing failed to launch or baseline no-repro (caller makes
    the arms INFRA). On success, persists corpus/ + corpus_meta.json there. No candidate is involved --
    the corpus depends only on ORIG, so every arm replays the identical inputs."""
    bundle_dir = Path(bundle_dir).resolve(); name = bundle_dir.name
    corpus_dir = CORPUS_ROOT / name / "corpus"
    meta_path = CORPUS_ROOT / name / "corpus_meta.json"
    try:
        b = _load(bundle_dir)
    except Exception as ex:
        return None, {"fuzz_ok": False, "error": f"load: {ex}"}

    scratch = DIFF_ROOT / "_scratch" / f"{name}.gen.{uuid.uuid4().hex[:8]}"
    if scratch.exists():
        shutil.rmtree(scratch, ignore_errors=True)
    scratch.mkdir(parents=True, exist_ok=True)
    shutil.copytree(bundle_dir / "source_code", scratch / "orig")
    nseed = _copy_seeds(bundle_dir, scratch / "seeds_in")
    force_nofuzz = os.environ.get("DDIV_DIFFFUZZ_NOFUZZ") == "1"
    cfg = {"mode": "generate", "orig_dir": "/work/orig", "entry": "harness.c",
           "flags": b["flags"], "target_func": b["target_func"], "fuzz_seconds": seconds,
           "seeds_dir": "/work/seeds_in" if nseed else "", "replay_timeout": 10,
           "poc_should_crash": b["poc_should_crash"], "no_fuzz": force_nofuzz,
           "oracle_version": ORACLE_VERSION}
    (scratch / "config.json").write_text(json.dumps(cfg, indent=1))
    shutil.copy(runner_for(bundle_dir), scratch / "difffuzz_run.py")
    cname = f"difffuzzgen_{name}_{uuid.uuid4().hex[:8]}"[:120]
    # Budget = fuzz (inner-capped at secs+8) + freeze + llvm-cov coverage. The +600 post-fuzz
    # buffer scales for the 600s budget; the old +240 was sized for the retired 60s default and
    # timed out cve_barebone's crash-heavy corpora (coverage over crashing inputs is slow).
    ok = _docker_run(scratch, cname, image, timeout=(300 if cfg["no_fuzz"] else seconds + 600))
    if not ok and not cfg["no_fuzz"]:
        # Fuzz gen timed out (pathological reference -- e.g. CWE-674 deep recursion whose fuzz
        # target setsid's out of the killable group and rides the container to the docker kill).
        # Retry ONCE with fuzzing DISABLED: the runner freezes the crafted io corpus directly, so
        # the bundle gets a real verdict off the differential set instead of INFRA. Reuse the
        # staged scratch; drop the killed run's partial out/ and flip the flag.
        cfg["no_fuzz"] = True
        (scratch / "config.json").write_text(json.dumps(cfg, indent=1))
        shutil.rmtree(scratch / "out", ignore_errors=True)
        cname = f"difffuzzgen_{name}_nf_{uuid.uuid4().hex[:8]}"[:120]
        ok = _docker_run(scratch, cname, image, timeout=300)
    if not ok:
        shutil.rmtree(scratch, ignore_errors=True)
        return None, {"fuzz_ok": False, "error": "gen container timeout"}
    mp = scratch / "out" / "corpus_meta.json"
    if not mp.exists():
        shutil.rmtree(scratch, ignore_errors=True)
        return None, {"fuzz_ok": False, "error": "no corpus_meta"}
    meta = json.loads(mp.read_text())
    result: Tuple[Optional[Path], dict] = (None, meta)
    if meta.get("corpus_ok") and (scratch / "corpus_out").is_dir():   # fuzzed OR seeds-fallback
        (CORPUS_ROOT / name).mkdir(parents=True, exist_ok=True)
        if corpus_dir.exists():
            shutil.rmtree(corpus_dir, ignore_errors=True)
        corpus_dir.mkdir(parents=True, exist_ok=True)
        # copy file-by-file (skip any stray unreadable entry rather than aborting the whole freeze)
        for f in sorted((scratch / "corpus_out").iterdir()):
            if f.is_file():
                try:
                    shutil.copy(f, corpus_dir / f.name)
                except OSError:
                    pass
        meta_path.write_text(json.dumps(meta, indent=1))    # persist success only
        result = (corpus_dir, meta)
    shutil.rmtree(scratch, ignore_errors=True)
    return result


def ensure_corpus(bundle_dir, seconds: int, image: str = IMAGE,
                  refresh: bool = False) -> Tuple[Optional[Path], dict]:
    """(frozen corpus dir | None, meta) for a bundle, generating+freezing ONCE. Threadsafe: a
    per-bundle lock serializes generation so every arm replays the same corpus. A cached SUCCESS
    is reused (reproducible); a FAILURE is cached in-memory only so a fresh process retries it.
    `refresh=True` forces regeneration."""
    bundle_dir = Path(bundle_dir).resolve(); name = bundle_dir.name
    corpus_dir = CORPUS_ROOT / name / "corpus"
    meta_path = CORPUS_ROOT / name / "corpus_meta.json"
    with _CORPUS_LOCKS[name]:
        if refresh:
            _CORPUS_MEM.pop(name, None)
            shutil.rmtree(corpus_dir, ignore_errors=True)
            if meta_path.exists():
                meta_path.unlink()
        if name in _CORPUS_MEM:
            cached = _CORPUS_MEM[name]
            if (int(cached[1].get("fuzz_seconds", -1)) == int(seconds)
                    and int(cached[1].get("oracle_version", -1)) == ORACLE_VERSION):
                return cached
            _CORPUS_MEM.pop(name, None)
        if meta_path.exists() and corpus_dir.is_dir():
            try:
                meta = json.loads(meta_path.read_text())
                # corpus_ok = fuzzed OR seeds-fallback; `fuzz_ok` back-compat for corpora frozen
                # before corpus_ok existed (they only froze on a successful fuzz).
                # The time budget is part of the corpus recipe: never silently reuse a corpus
                # grown with a different budget (notably the retired 60-second default).
                budget_matches = int(meta.get("fuzz_seconds", -1)) == int(seconds)
                recipe_matches = int(meta.get("oracle_version", -1)) == ORACLE_VERSION
                if budget_matches and recipe_matches \
                        and (meta.get("corpus_ok") or meta.get("fuzz_ok")):
                    _CORPUS_MEM[name] = (corpus_dir, meta)
                    return _CORPUS_MEM[name]
            except Exception:
                pass
        got = generate_corpus(bundle_dir, seconds, image)
        _CORPUS_MEM[name] = got
        return got


# --------------------------------------------------------------------------- #
# main entry -- per-arm replay of the frozen corpus
# --------------------------------------------------------------------------- #

def evaluate(bundle_dir, cand_src, *, arm: str = "", seconds: int = DEFAULT_FUZZ_SECONDS,
             image: str = IMAGE, keep_scratch: bool = False,
             corpus_dir: Optional[Path] = None,
             corpus_meta: Optional[dict] = None) -> DiffResult:
    """Replay the FROZEN per-bundle corpus (`corpus_dir`, from ensure_corpus/generate_corpus) on
    ORIG vs the spliced candidate. Every arm of a bundle gets the SAME corpus_dir, so the
    comparison is fair + reproducible. Returns a DiffResult."""
    bundle_dir = Path(bundle_dir).resolve()
    name = bundle_dir.name
    meta = corpus_meta or {}
    res = DiffResult(verdict="INFRA", bundle=name, arm=arm,
                     fuzz_seconds=int(meta.get("fuzz_seconds", seconds)),
                     corpus_frozen=True, fuzz_ok=bool(meta.get("fuzz_ok")),
                     corpus_source=meta.get("corpus_source"),
                     afl_rc=meta.get("afl_rc"), corpus_size=int(meta.get("corpus_size", 0)))

    if corpus_dir is None or not Path(corpus_dir).is_dir():
        res.error = "no frozen corpus (generation failed)"; return res
    if isinstance(cand_src, str):
        cand_src = cand_src.encode("utf-8", "replace")
    if not cand_src or not cand_src.strip():
        res.verdict = "DECOMPILE_FAILED"; return res

    try:
        b = _load(bundle_dir)
    except Exception as ex:
        res.error = f"load: {ex}"; return res

    harness_path = bundle_dir / "source_code" / b["relpath"]
    if not harness_path.exists():
        res.error = f"missing {b['relpath']}"; return res
    try:
        spliced = _splice(harness_path.read_bytes(), b["orig_fn"], cand_src)
    except _SpliceError as ex:
        res.verdict = "SPLICE_FAILED"; res.error = str(ex); return res

    # scratch: /work/{orig,cand,frozen_corpus,config.json,difffuzz_run.py}
    scratch = DIFF_ROOT / "_scratch" / f"{name}.{arm or 'x'}.{uuid.uuid4().hex[:8]}"
    if scratch.exists():
        shutil.rmtree(scratch, ignore_errors=True)
    scratch.mkdir(parents=True, exist_ok=True)
    shutil.copytree(bundle_dir / "source_code", scratch / "orig")
    shutil.copytree(bundle_dir / "source_code", scratch / "cand")
    (scratch / "cand" / b["relpath"]).write_bytes(spliced)
    shutil.copytree(Path(corpus_dir), scratch / "frozen_corpus")   # the SAME corpus for every arm

    cfg = {
        "mode": "replay", "orig_dir": "/work/orig", "cand_dir": "/work/cand", "entry": "harness.c",
        "flags": b["flags"], "target_func": b["target_func"],
        "frozen_corpus": "/work/frozen_corpus", "replay_timeout": 10,
        "oracle_version": ORACLE_VERSION,
    }
    (scratch / "config.json").write_text(json.dumps(cfg, indent=1))
    shutil.copy(runner_for(bundle_dir), scratch / "difffuzz_run.py")

    cname = f"difffuzz_{name}_{arm or 'x'}_{uuid.uuid4().hex[:8]}"[:120]
    ok = _docker_run(scratch, cname, image, timeout=1200)  # replay+builds only (no fuzz); big 600s crash corpora replay >600s
    if not ok:
        res.verdict = "INFRA"; res.error = "container timeout"
        if not keep_scratch:
            shutil.rmtree(scratch, ignore_errors=True)
        return res

    rp = scratch / "out" / "result.json"
    if not rp.exists():
        res.verdict = "INFRA"; res.error = "no result.json"
        if not keep_scratch:
            shutil.rmtree(scratch, ignore_errors=True)
        return res
    raw = json.loads(rp.read_text())

    res.verdict = raw.get("verdict", "INFRA")
    res.build_orig = raw.get("build_orig", False)
    res.build_cand = raw.get("build_cand", False)
    res.corpus_size = raw.get("corpus_size", res.corpus_size)
    res.memstate_compared = raw.get("memstate_compared", False)
    res.memstate_inputs = raw.get("memstate_inputs", 0)
    res.replay_truncated = raw.get("replay_truncated", False)
    res.coverage = raw.get("coverage")
    res.error = raw.get("error")
    res.enhanced_harness = raw.get("enhanced_harness", False)
    res.multi_call = raw.get("multi_call", False)
    res.external_state_compared = raw.get("external_state_compared", False)

    # crashparse refinement: drop shifted_crash divergences that are actually the SAME
    # weakness+location (patterns_match), matching Decompile-Diverge crash-equivalence semantics.
    divs = _refine(raw.get("divergences", []))
    res.divergences = divs
    res.n_divergent = len(divs)
    res.div_types = {}
    for d in divs:
        res.div_types[d["type"]] = res.div_types.get(d["type"], 0) + 1
    res.vanished = res.div_types.get("vanished_crash", 0) > 0
    if res.verdict in ("INTACT", "DEVIATED"):
        res.verdict = "DEVIATED" if divs else "INTACT"

    if not keep_scratch:
        shutil.rmtree(scratch, ignore_errors=True)
    return res


def _refine(divs: List[dict]) -> List[dict]:
    if parse_crash is None:
        return divs
    kept = []
    for d in divs:
        if d.get("type") == "shifted_crash" and d.get("orig_log") and d.get("cand_log"):
            try:
                a = parse_crash(d["orig_log"]); c = parse_crash(d["cand_log"])
                if a and c and patterns_match(a, c):
                    continue                    # same weakness+location -> not a divergence
            except Exception:
                pass
        kept.append(d)
    return kept


def write_sidecar(res: DiffResult, out_dir: Path) -> Path:
    out_dir = Path(out_dir); out_dir.mkdir(parents=True, exist_ok=True)
    p = out_dir / f"{res.arm or 'cand'}.json"
    p.write_text(res.to_json())
    return p
