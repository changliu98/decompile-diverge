#!/usr/bin/env python3
"""In-container driver for the original-benchmark-oracle replay (stdlib only, py3.10).

Runs INSIDE ``ddiv-oracle:22.04`` (``--network none``) and scores frozen
decompiler outputs against the source benchmarks' OWN executable oracles, ported
VERBATIM (per the follow-the-paper rule — the oracle is part of the recipe):

- humaneval  -> LLM4Decompile ``evaluation/run_evaluation_llm4decompile_vllm.py:evaluate_func``
               (hoist #include from REFERENCE c_func + c_test; ``gcc -S`` of include+candidate
               sets flag_compile; ``gcc`` combine ``-lm``; run with check=True; 10 s per step).
- mbpp       -> SK2Decompile ``sk2decompile/evaluation/metrics/cal_execute_rate.py:execute_rate``
               (``func_dep + candidate + test``, ``gcc -O0 -lm``, run, 10 s per step), scored
               twice: ``strict`` = candidate bytes verbatim (comparable to our strict-mode
               eval), ``renamed`` = the as-published protocol of ``evaluate_exe.py:get_score``,
               which str.replace()s the candidate's own function name with the ground truth.
               The rename is THEIR leaderboard protocol, reported separately — it is exactly
               the output-remap class our strict mode forbids.

Contract: argv[1] = spec.json, argv[2] = results.json. Spec:
    {"kind": "humaneval"|"mbpp", <oracle fields>, "jobs": [{"arm": ..., "candidate_file": ...}]}
Only capture_output/reporting was added to the ported functions; control flow, commands,
flags, timeouts and concat order are unchanged.
"""
import json
import math
import os
import re
import subprocess
import sys
import tempfile
import time

TIMEOUT = 10  # both upstream scripts hardcode timeout = 10 (seconds, per step)
EXEBENCH_RUN_TIMEOUT = 5    # exebench _DEFAULT_CMD_TIMEOUT, verbatim
EXEBENCH_COMPILE_TIMEOUT = 120  # infra bound only: upstream's 5 s _run_command default on
                                # the g++ step is an artifact that flakes under load (their
                                # compile isn't even check'd); semantics live in run+diff

# ---------------------------------------------------------------------------
# Compatibility prelude (opt-in, spec["compat"]) -- the same additive-declaration
# device the CVE track uses for the front-end control arms. The released harnesses
# compile with gcc/g++, which does not declare the decompiler vocabulary Hex-Rays
# and Ghidra emit (__cdecl, __fastcall, __int64, _DWORD, undefined4, uint, ...), so
# such a candidate dies at the compile step before any shipped test runs. This block
# is PREPENDED; it declares that vocabulary and modifies no line of the candidate.
# It is only ever tried after the verbatim run already failed to compile, and its
# result is reported under a separate "compat" key -- the "strict" verdict is the
# untouched verbatim port.
# Tried in order, first one that compiles wins. Stage A only defines reserved-form
# identifiers (leading underscores), which cannot collide with a corpus typedef.
# Stage B adds Ghidra's plain-word vocabulary, which CAN collide (a dep that already
# has ``typedef unsigned int uint;`` would expand to ``typedef unsigned int unsigned
# int;``) -- hence second, and only as a fallback.
_COMPAT_A = """/* additive decompiler-vocabulary declarations; candidate body byte-identical */
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#define __cdecl
#define __fastcall
#define __stdcall
#define __thiscall
#define __usercall
#define __userpurge
#define __noreturn
#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long
#define _BYTE unsigned char
#define _WORD unsigned short
#define _DWORD unsigned int
#define _QWORD unsigned long long
#define _BOOL1 unsigned char
#define _BOOL4 unsigned int
#define _UNKNOWN void
#define LODWORD(x) ((unsigned int)(x))
#define HIDWORD(x) ((unsigned int)(((unsigned long long)(x)) >> 32))
"""
_COMPAT_B = _COMPAT_A + """#define undefined unsigned char
#define undefined1 unsigned char
#define undefined2 unsigned short
#define undefined4 unsigned int
#define undefined8 unsigned long long
#define uint unsigned int
#define ushort unsigned short
#define ulong unsigned long
"""
COMPAT_PRELUDES = [("A", _COMPAT_A), ("B", _COMPAT_B)]


def _err(e):
    if isinstance(e, subprocess.TimeoutExpired):
        return {"kind": "timeout"}
    if isinstance(e, subprocess.CalledProcessError):
        return {"kind": "nonzero", "rc": e.returncode,
                "stderr": (e.stderr or "")[-800:]}
    return {"kind": type(e).__name__, "msg": str(e)[:300]}


def evaluate_func_decompile_eval(c_func, c_test, c_func_decompile):
    """LLM4Decompile evaluate_func, verbatim port. Returns (flag_compile, flag_run, detail)."""
    flag_compile = 0
    flag_run = 0
    detail = {}
    c_include = ""
    for line in c_func.split("\n"):
        if "#include" in line:
            c_include += line + "\n"
            c_func = c_func.replace(line, "")
    for line in c_test.split("\n"):
        if "#include" in line:
            c_include += line + "\n"
            c_test = c_test.replace(line, "")
    c_combine = c_include + "\n" + c_func_decompile + "\n" + c_test
    c_onlyfunc = c_include + "\n" + c_func_decompile

    with tempfile.TemporaryDirectory() as temp_dir:
        pid = os.getpid()
        c_file = os.path.join(temp_dir, f"combine_{pid}.c")
        executable = os.path.join(temp_dir, f"combine_{pid}")
        c_file_onlyfunc = os.path.join(temp_dir, f"onlyfunc_{pid}.c")
        executable_onlyfunc = os.path.join(temp_dir, f"onlyfunc_{pid}")

        with open(c_file, "w") as f:
            f.write(c_combine)
        with open(c_file_onlyfunc, "w") as f:
            f.write(c_onlyfunc)

        # Compile the C program to an assembly (their flag_compile gate)
        try:
            subprocess.run(["gcc", "-S", c_file_onlyfunc, "-o", executable_onlyfunc, "-lm"],
                           check=True, timeout=TIMEOUT, capture_output=True, text=True)
            flag_compile = 1
        except Exception as e:
            detail["stage"] = "compile_onlyfunc"
            detail["err"] = _err(e)
            return flag_compile, flag_run, detail

        # Compile the C program to an executable
        try:
            subprocess.run(["gcc", c_file, "-o", executable, "-lm"],
                           check=True, timeout=TIMEOUT, capture_output=True, text=True)
            flag_compile = 1
        except Exception as e:
            detail["stage"] = "compile_combine"
            detail["err"] = _err(e)
            return flag_compile, flag_run, detail

        # Run the compiled executable
        try:
            subprocess.run([executable], capture_output=True, text=True,
                           timeout=TIMEOUT, check=True)
            flag_run = 1
        except Exception as e:
            detail["stage"] = "run"
            detail["err"] = _err(e)
            return flag_compile, flag_run, detail

    return flag_compile, flag_run, detail


def execute_rate_mbpp(func_dep, gen_result, func_test):
    """SK2Decompile execute_rate (language='c', opt='-O0'), verbatim port.
    Returns (flag_comp, flag_exe, detail)."""
    flag_exe = 0
    flag_comp = 0
    detail = {}
    func_exe = func_dep + "\n" + gen_result + "\n" + func_test

    with tempfile.TemporaryDirectory() as temp_dir:
        pid = os.getpid()
        file_exe = os.path.join(temp_dir, f"exe_{pid}.c")
        binary_exe = os.path.join(temp_dir, f"exe_{pid}")
        with open(file_exe, "w") as f:
            f.write(func_exe)

        try:
            subprocess.run(["gcc", "-O0", file_exe, "-o", binary_exe, "-lm"],
                           check=True, timeout=TIMEOUT, capture_output=True, text=True)
            flag_comp = 1
        except Exception as e:
            detail["stage"] = "compile"
            detail["err"] = _err(e)
            return flag_comp, flag_exe, detail

        try:
            subprocess.run([binary_exe], timeout=TIMEOUT, check=True,
                           capture_output=True, text=True)
            flag_exe = 1
        except Exception as e:
            detail["stage"] = "run"
            detail["err"] = _err(e)
            return flag_comp, flag_exe, detail

    return flag_comp, flag_exe, detail


def diff_io(observed_output, expected_output) -> bool:
    """exebench/__init__.py:diff_io, verbatim port (type-strict; math.isclose on floats)."""
    if type(observed_output) is not type(expected_output):
        return False
    if isinstance(observed_output, list):
        if len(observed_output) != len(expected_output):
            return False
        for e1, e2 in zip(observed_output, expected_output):
            if not diff_io(e1, e2):
                return False
    elif isinstance(observed_output, dict):
        for key in observed_output:
            if key not in expected_output:
                return False
            if not diff_io(observed_output[key], expected_output[key]):
                return False
    elif isinstance(observed_output, float):
        if not math.isclose(observed_output, expected_output):
            return False
    else:
        if observed_output != expected_output:
            return False
    return True


def exebench_eval(spec, cand):
    """ExeBench oracle. The stored ``real_exe_wrapper`` is the exact artifact whose
    execution produced ``real_io_pairs`` at dataset-construction time — a C++ main that
    ``extern "C" { #include }``s the C function file, reads an input JSON, calls the
    function, and writes the liveout JSON. We re-point that include (their own
    ``_DefaultAssembler`` regex) at ``real_deps + CANDIDATE``: our decompilers emit C
    source, so the candidate takes the seat the reference source occupied at generation
    time (their ``.s``-linking assembler is the path for model-ASM eval, which their own
    example notes is flaky — "better to recompile everything and run it all together").
    Compile command (g++ -fpermissive -O0 -I json -I clib) and diff_io are verbatim; the
    run step is uncheck'd like theirs (success = output JSON exists, parses, and matches).
    Returns (flag_compile, flag_pass, detail)."""
    detail = {}
    with tempfile.TemporaryDirectory() as td:
        func_c = os.path.join(td, "func.c")
        with open(func_c, "w") as f:
            f.write(spec["c_deps"] + "\n" + cand)
        cpp_wrapper = re.sub(r'extern\s\"C\"\s\{\s.*\s\}',
                             'extern "C" \n{\n#include "' + func_c + '"\n}\n',
                             spec["cpp_wrapper"])
        wrapper_cpp = os.path.join(td, "wrapper.cpp")
        with open(wrapper_cpp, "w") as f:
            f.write(cpp_wrapper)
        exe = os.path.join(td, "exe.x")
        inc = spec["include_root"]
        try:
            subprocess.run(["g++", "-fpermissive", "-O0", "-o", exe, wrapper_cpp,
                            "-I", inc, f"-I{inc}"],
                           check=True, timeout=EXEBENCH_COMPILE_TIMEOUT,
                           capture_output=True, text=True)
        except Exception as e:
            detail["stage"] = "compile"
            detail["err"] = _err(e)
            return 0, 0, detail

        pairs = spec["io_pairs"]
        n_match = 0
        for i, pair in enumerate(pairs):
            inp_p = os.path.join(td, f"in_{i}.json")
            out_p = os.path.join(td, f"out_{i}.json")
            with open(inp_p, "w") as f:
                json.dump(pair["input"], f)
            try:
                subprocess.run([exe, inp_p, out_p], timeout=EXEBENCH_RUN_TIMEOUT,
                               capture_output=True, text=True)
                with open(out_p) as f:
                    observed = json.load(f)
            except Exception as e:
                detail["stage"] = "run"
                detail["err"] = _err(e)
                detail["pair"] = i
                break
            if diff_io(observed, pair["output"]):
                n_match += 1
            else:
                detail["stage"] = "io_mismatch"
                detail["pair"] = i
                break
        detail["n_pairs"] = len(pairs)
        detail["n_match"] = n_match
        passed = len(pairs) > 0 and n_match == len(pairs)
        return 1, int(passed), detail


def sk2_rename(one, target_name):
    """evaluate_exe.py:get_score's output rename, verbatim: detect the candidate's own
    function name from its first '(' and str.replace() every occurrence with the ground
    truth. Guard: an empty detected name would make str.replace('') interleave the target
    between every character — upstream that garbage just fails to compile; we skip the
    no-op instead (same verdict, no pathological blowup)."""
    func_name = one.split('(')[0].split(' ')[-1].strip()
    if func_name.strip() and func_name[0:2] == '**':
        func_name = func_name[2:]
    elif func_name.strip() and func_name[0] == '*':
        func_name = func_name[1:]
    if not func_name:
        return one, ""
    return one.replace(func_name, target_name), func_name


def _score(kind, spec, cand):
    """Run the kind's ported oracle on one candidate text -> {compiled, passed, detail}."""
    if kind == "humaneval":
        comp, run, detail = evaluate_func_decompile_eval(spec["c_func"], spec["c_test"], cand)
    elif kind == "exebench":
        comp, run, detail = exebench_eval(spec, cand)
    elif kind == "mbpp":
        comp, run, detail = execute_rate_mbpp(spec["func_dep"], cand, spec["test"])
    else:
        raise ValueError(f"unknown kind {kind}")
    return {"compiled": bool(comp), "passed": bool(run), "detail": detail}


def _compat_score(kind, spec, cand):
    """Re-score behind the additive compatibility prelude. Only meaningful after the
    verbatim run failed to COMPILE; returns the first prelude stage that gets past the
    compiler (or the last attempt's failure)."""
    last = None
    for tag, prelude in COMPAT_PRELUDES:
        rec = _score(kind, spec, prelude + "\n" + cand)
        rec["prelude"] = tag
        if rec["compiled"]:
            return rec
        last = rec
    return last


def main():
    spec = json.loads(open(sys.argv[1]).read())
    kind = spec["kind"]
    compat = bool(spec.get("compat"))
    results = []
    for job in spec["jobs"]:
        arm = job["arm"]
        t0 = time.time()
        rec = {"arm": arm}
        try:
            with open(job["candidate_file"], "rb") as f:
                cand = f.read().decode("utf-8", errors="replace")
            rec["candidate_bytes"] = len(cand)
            if kind == "humaneval":
                comp, run, detail = evaluate_func_decompile_eval(
                    spec["c_func"], spec["c_test"], cand)
                rec["strict"] = {"compiled": bool(comp), "passed": bool(run),
                                 "detail": detail}
            elif kind == "exebench":
                comp, run, detail = exebench_eval(spec, cand)
                rec["strict"] = {"compiled": bool(comp), "passed": bool(run),
                                 "detail": detail}
            elif kind == "mbpp":
                comp, run, detail = execute_rate_mbpp(spec["func_dep"], cand, spec["test"])
                rec["strict"] = {"compiled": bool(comp), "passed": bool(run),
                                 "detail": detail}
                renamed, detected = sk2_rename(cand, spec["func_name"])
                if renamed == cand:
                    rec["renamed"] = dict(rec["strict"], same_as_strict=True,
                                          detected_name=detected)
                else:
                    comp2, run2, detail2 = execute_rate_mbpp(
                        spec["func_dep"], renamed, spec["test"])
                    rec["renamed"] = {"compiled": bool(comp2), "passed": bool(run2),
                                      "detail": detail2, "same_as_strict": False,
                                      "detected_name": detected}
            else:
                rec["error"] = f"unknown kind {kind}"
            # Additive-compatibility retry: only where the verbatim port never reached
            # the tests because the harness compiler rejected decompiler vocabulary.
            if compat and rec.get("strict") and not rec["strict"]["compiled"]:
                rec["compat"] = _compat_score(kind, spec, cand)
        except Exception as e:  # one bad arm must not kill the batch
            rec["error"] = f"{type(e).__name__}: {e}"
        rec["elapsed"] = round(time.time() - t0, 2)
        results.append(rec)

    tmp = sys.argv[2] + ".tmp"
    with open(tmp, "w") as f:
        json.dump(results, f)
    os.replace(tmp, sys.argv[2])


if __name__ == "__main__":
    main()
