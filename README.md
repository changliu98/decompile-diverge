# ddiv

A standalone adaptation of the Decompile-Diverge oracle from
[When LLM Decompilers Recompile More and Preserve Less](https://arxiv.org/abs/2609.05370).

`ddiv` uses AFL++ to find behavioral differences between two C programs and saves
the distinguishing input and both post-states. Each source must contain a `main`
that calls the function being tested. The framework is Python with a small C
helper for memory capture.

## Quickstart

Requires Python 3.9+ and Docker with Linux x86-64 containers. From this checkout:

```sh
python -m pip install .
docker build -t ddiv:0.1 ddiv
ddiv 1.c 2.c
```

The sources should be self-contained. Defaults: stdin input, 60 seconds of AFL++
fuzzing, RNG seed 1337. Try the included example:

```sh
ddiv ddiv/examples/1.c ddiv/examples/2.c --seconds 5
```

Input `42` produces stdout and global `answer` values of `84` versus `85`.

## Inputs and replay

```sh
ddiv 1.c 2.c --seeds seeds/ --seconds 300
ddiv 1.c 2.c --input-mode file   # input-file path in argv[1]
ddiv 1.c 2.c --input-mode argv   # NUL-separated arguments
ddiv 1.c 2.c --input previous-run/counterexample/input  # replay without fuzzing
```

`--seconds 0` replays seeds without fuzzing. Use `--timeout` and `--replay-seconds`
for execution and comparison budgets; `ddiv --help` lists all options.

## What is compared

AFL++ fuzzes the **first program**. Initial seeds and retained queue, crash, and
hang inputs are frozen and replayed on both programs. Each gets an ASan/UBSan
build for faults and a clean build for memory. C compilation and target execution
run inside Docker with network access disabled.

- Exit status, signals, timeouts, and sanitizer fault kind, access direction, and
  faulting function; source line numbers are ignored.
- Exact stdout/stderr and final files in a fresh working directory, on normal exits.
- Writable globals at normal exit, matched by symbol name, with relocation
  pointer slots masked to avoid differences caused by linking.

For local values or heap buffers, explicitly observe initialized bytes while valid:

```c
#include <ddiv.h>
/* In main, after calling the function under test: */
DDIV_OBSERVE("result", result);
ddiv_observe("buffer", buffer, initialized_length);
```

The last observation for each name is compared. Arbitrary heap, stack, register,
and thread-local state is not captured automatically; masked pointer targets
are not compared. `_exit`, crashes, and hangs bypass the global dump.

A difference must reproduce on both programs across four additional runs and a
final archived replay. The first confirmed counterexample ends the comparison.

## Results

Output defaults to `ddiv-results/<run-id>/`; `--output` selects a new directory.
It contains `result.json`, the frozen `corpus/`, and, when a difference is found,
`counterexample/input`, `counterexample/{left,right}.json`, and raw observations.
`--json` prints the full report.

| Result | Exit code | Meaning |
|---|---|---|
| `DIFFERENT` | 1 | A saved input has a confirmed difference |
| `NO_DIFFERENCE_FOUND` | 0 | All frozen inputs compared without a difference |
| `INCONCLUSIVE` | 2 | Unresolved observations, incomplete replay, or failed fuzzing |
| `BUILD_FAILED` | 2 | A required build failed |
| `INFRA` | 2 | Infrastructure failure or interrupted run |

`NO_DIFFERENCE_FOUND` is **not a proof of equivalence**: results cover only retained
inputs and observed state. Save the corpus to replay the same inputs.

## Tests

With pytest installed:

```sh
python -m pytest -q
DDIV_E2E=1 python -m pytest -q   # include Docker execution tests
```
