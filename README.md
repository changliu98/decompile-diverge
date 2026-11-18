# Decompile-Diverge: code and data

The data and implementation of the paper [When LLM Decompilers Recompile More and Preserve Less](https://arxiv.org/abs/2609.05370).

| | HumanEval | ExeBench | AnghaBench | MBPP | GitHub | CVE |
|---|---|---|---|---|---|---|
| functions | 161 | 1,538 | 215 | 597 | 291 | 287 |

Systems: Ghidra, Hex-Rays, LLM4Decompile, SK2Decompile, Idioms, GLM-5.2-Refine, DeGPT-Qwen,
AutoDecompiler, Nova, SLaDe, GLM-5.2-E2E.

## Run

Needs Docker (with permission for `--privileged` containers), Python 3.8+ and about 4 GB of disk.

```bash
./build_image.sh                     # ddiv-oracle:22.04
python3 oracle/tables.py             # the paper's tables, from data/expected/
JOBS=32 ./reproduce.sh               # re-score everything and check against the paper
SAMPLE=0.2 JOBS=32 ./reproduce.sh    # the same on a random 20% of each group
LIMIT=5 ./reproduce.sh               # trial run: 5 functions per group
```

`reproduce.sh` replays each function's frozen inputs on the reference and on every candidate,
runs the corpora's own tests, re-measures corpus coverage, and compares every outcome with
`data/expected/`. Nothing is fuzzed and no model is called. A complete run takes about 2.5 hours
at `JOBS=96` on 128 cores and is resumable. Ours reproduced 99.8% of the paper's verdicts; the
rest are flips on 23 functions whose reference is not deterministic on one or two inputs.

One function or one step (bundle paths must be absolute):

```bash
python3 oracle/difffuzz_eval.py "$PWD/data/bundles/cve_barebone_0122e790" --arm identity
python3 oracle/difffuzz_eval.py "$PWD/data/bundles/cve_barebone_0122e790" --arm glm-e2e
python3 oracle/difffuzz_eval.py "$PWD/data/bundles/<id>" --cand-file mine.c --arm mine
python3 oracle/difffuzz_group.py --group cve_barebone --jobs 16
python3 oracle/shipped_tests.py --groups humaneval --jobs 16
python3 oracle/coverage.py --jobs 16
python3 oracle/tables.py --results        # or --compare, --same-functions
```

## Layout

```
oracle/                        the oracle, the test-harness ports, the table scripts
data/bundles/<id>/             one function: reference, decompiler inputs, driver, fuzz seeds
data/corpus/<id>/              its frozen replay inputs
data/candidates/<id>/<system>.response.c       each system's output, as scored
data/candidates_raw/<id>/<system>.response.c   Nova, Idioms, AutoDecompiler: before the rename
data/shipped_tests/<id>.json   the test the corpus releases with the function
data/expected/                 the paper's verdicts, test outcomes and coverage (CSV)
llm_outputs/<system>.jsonl     the nine LLM systems' outputs and verdicts, one line per function
results/                       written at run time
```

## How a verdict is decided

The candidate replaces the reference function in a self-contained driver. Both programs are
built with AddressSanitizer and replayed on the same frozen inputs, which AFL++ grew once from
the reference. The verdict is `DEVIATED` if any input makes them differ, `INTACT` if none does,
and `BUILD_FAILED` if the candidate does not compile in the driver (no name, type or signature
is supplied for it). An input is divergent on one of six channels:

| channel | reference | candidate |
|---|---|---|
| `vanished_crash` | crashes | does not |
| `introduced_crash` | does not crash | crashes |
| `shifted_crash` | crashes | crashes with a different sanitizer report or in a different function |
| `introduced_hang` | terminates | does not |
| `exit_code_diff` | exits normally | exits with a different status |
| `silent_wrong_answer` | exits normally | same status, different output, files or exit state |

* Exit state is the program's writable globals, including a digest of the return value and
  output buffers, compared by symbol name. Source lines are never compared.
* On GitHub and CVE a divergence counts only if both sides reproduce it four times.
* The reference scored against itself (`--arm identity`) must be `INTACT`. The 32 functions
  that fail this are not shipped (`MANIFEST.json`).

## Table columns

| column | meaning |
|---|---|
| Out | the system returned a candidate |
| Bld | the candidate compiles in the driver (`INTACT` + `DEVIATED`) |
| Mat | Matched: `INTACT` |
| Div | Divergence: `DEVIATED`; on CVE, the `DEVIATED` verdicts that are not C-A |
| C-A | Crash Absence (CVE): the validated PoC crashes the reference and not the candidate |
| Pass | (HumanEval, ExeBench, MBPP) the candidate passes every test its corpus ships |
| Div\|P | of the candidates that Pass and build under the oracle, the share that is `DEVIATED` |

Pass uses each corpus's released harness, which compiles with gcc/g++. A candidate that does not
compile verbatim is retried behind declarations for the vocabulary Ghidra and Hex-Rays emit
(`__cdecl`, `_DWORD`, ...), its own text unchanged.

## Notes

* Nova, Idioms and AutoDecompiler take an input that carries no function name, so their
  candidates have the target's name restored on the one function they define. Nothing else is
  changed; the bytes before the rename are in `data/candidates_raw/`.
* The Idioms and AutoDecompiler outputs are the corrected versions: Idioms with that name
  restoration, AutoDecompiler regenerated from the IDA listing input its released pipeline uses.
* To fuzz the corpora again instead of replaying the shipped ones, point `DDIV_CORPUS_ROOT` at
  an empty directory. A re-grown corpus is not byte-identical, so verdicts can differ.
* The systems' outputs and the shipped tests are third-party bytes, included verbatim. In
  ExeBench sources, absolute build paths in preprocessor line markers were cut to the file name.
* The functions and their upstream code remain under their projects' licenses.
