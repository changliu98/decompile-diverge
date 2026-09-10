"""Real Docker + AFL++ tests; opt in with DDIV_E2E=1.

Every compiler and target process is launched by ddiv inside Docker. The host
only prepares text sources, invokes the Python CLI, and checks saved evidence.
"""
import json
import os
from pathlib import Path
import subprocess
import sys

import pytest

ROOT = Path(__file__).resolve().parents[2]
pytestmark = pytest.mark.skipif(os.environ.get("DDIV_E2E") != "1", reason="set DDIV_E2E=1 for Docker tests")


def evaluate(tmp_path, left, right, data=b"A", *, mode="stdin", fuzz=False, seconds=2, timeout=1):
    a, b = tmp_path / "1.c", tmp_path / "2.c"
    a.write_text(left)
    b.write_text(right)
    seed = tmp_path / "input"
    seed.write_bytes(data)
    out = tmp_path / "result"
    cmd = [sys.executable, "-m", "ddiv", str(a), str(b), "--output", str(out),
           "--image", os.environ.get("DDIV_IMAGE", "ddiv:0.1"), "--input-mode", mode,
           "--timeout", str(timeout), "--replay-seconds", "30"]
    if fuzz:
        seeds = tmp_path / "seeds"
        seeds.mkdir()
        (seeds / "initial").write_bytes(data)
        cmd += ["--seeds", str(seeds), "--seconds", str(seconds)]
    else:
        cmd += ["--input", str(seed)]
    completed = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=150)
    report = out / "result.json"
    assert report.is_file(), completed.stdout + completed.stderr
    result = json.loads(report.read_text())
    assert result["status"] != "INFRA", result
    assert a.read_text() == left and b.read_text() == right
    return result, out, completed.returncode


def test_afl_generates_a_new_distinguishing_input(tmp_path):
    left = "#include <stdio.h>\nunsigned answer; int main(void){int x=getchar(); if(x>=7) answer=1; else answer=0; return 0;}\n"
    right = left.replace("answer=1", "answer=0")
    result, out, rc = evaluate(tmp_path, left, right, data=b"\x00", fuzz=True)
    assert rc == 1 and result["status"] == "DIFFERENT", result
    assert result["corpus"]["fuzz_ok"] is True
    assert int(result["corpus"]["stats"]["execs_done"]) > 0
    witness = result["counterexample"]
    assert "globals" in witness["channels"]
    assert (out / witness["input_file"]).read_bytes() != b"\x00"
    origin = next(x for x in result["corpus"]["inputs"] if x["file"] == witness["corpus_input"])
    assert origin["source"].startswith("afl/")
    assert witness["left"]["globals"]["answer"]["unsigned_le"] == 1
    assert witness["right"]["globals"]["answer"]["unsigned_le"] == 0
    assert (out / "counterexample/left/clean/globals.bin").is_file()


def test_identity_with_no_globals(tmp_path):
    code = "#include <stdio.h>\nint main(void){puts(\"same\");return 0;}\n"
    result, _, rc = evaluate(tmp_path, code, code)
    assert rc == 0 and result["status"] == "NO_DIFFERENCE_FOUND", result
    assert result["global_layouts"]["left"]["symbols"] == {}


def test_symbol_order_and_relocated_pointers_are_not_false_differences(tmp_path):
    a = "#include <stdio.h>\nint a=4; int b=5; int *p=&a; int main(void){a+=getchar();return b;}\n"
    b = "#include <stdio.h>\nint b=5; int a=4; int *p=&a; int main(void){a+=getchar();return b;}\n"
    result, _, rc = evaluate(tmp_path, a, b)
    assert rc == 0 and result["status"] == "NO_DIFFERENCE_FOUND", result
    assert result["global_layouts"]["left"]["relocations"]


@pytest.mark.parametrize("mode,data,code", [
    ("stdin", b"A", '#include <stdio.h>\nint main(void){putchar(getchar()+DELTA);return 0;}'),
    ("file", b"A", '#include <stdio.h>\nint main(int argc,char **argv){FILE*f=fopen(argv[1],"rb"); if(!f)return 3; putchar(fgetc(f)+DELTA); fclose(f);return 0;}'),
    ("argv", b"A\0B\0", '#include <stdio.h>\nint main(int argc,char **argv){if(argc!=3)return 4; putchar(argv[2][0]+DELTA);return 0;}'),
])
def test_input_delivery_modes(tmp_path, mode, data, code):
    result, out, rc = evaluate(tmp_path, code.replace("DELTA", "0"), code.replace("DELTA", "1"),
                               data=data, mode=mode)
    assert rc == 1 and result["status"] == "DIFFERENT", result
    assert "clean.stdout" in result["counterexample"]["channels"]
    assert (out / "counterexample/left/clean/stdout").read_bytes() in (b"A", b"B")


def test_relative_filesystem_poststate_is_captured(tmp_path):
    code = '#include <stdio.h>\nint main(void){FILE*f=fopen("answer.txt","w");fputs("VALUE",f);fclose(f);return 0;}'
    result, out, rc = evaluate(tmp_path, code.replace("VALUE", "one"), code.replace("VALUE", "two"))
    assert rc == 1 and "clean.files" in result["counterexample"]["channels"], result
    assert (out / "counterexample/left/clean/files/answer.txt").read_bytes() == b"one"
    assert (out / "counterexample/right/clean/files/answer.txt").read_bytes() == b"two"


def test_explicit_local_and_buffer_observations(tmp_path):
    code = '#include <ddiv.h>\nint main(void){int x=VALUE; char b[2]={1,VALUE}; DDIV_OBSERVE("result",x); ddiv_observe("buffer",b,2);return 0;}'
    result, _, rc = evaluate(tmp_path, code.replace("VALUE", "2"), code.replace("VALUE", "3"))
    assert rc == 1 and "observations" in result["counterexample"]["channels"], result
    assert result["counterexample"]["left"]["observations"]["buffer"]["hex"] == "0102"


def test_fault_difference_and_coordinate_independence(tmp_path):
    code = '#include <stdlib.h>\nint target(void){volatile char*p=malloc(1);p[8]=1;return 0;}\nint main(void){return target();}'
    result, _, rc = evaluate(tmp_path, code, "\n\n\n" + code, timeout=3)
    assert rc == 0 and result["status"] == "NO_DIFFERENCE_FOUND", result
    other = tmp_path / "different"
    other.mkdir()
    result, _, rc = evaluate(other, code, code.replace("p[8]=1", "p[0]=1"), timeout=3)
    assert rc == 1 and "sanitized.termination" in result["counterexample"]["channels"], result
    crash = result["counterexample"]["left"]["sanitized"]["crash"]
    assert crash["access"] == "WRITE" and crash["function"] == "target"


def test_exit_139_is_a_normal_exit_not_a_signal(tmp_path):
    result, _, rc = evaluate(tmp_path, "int main(void){return 139;}", "int main(void){return 140;}")
    assert rc == 1
    assert result["counterexample"]["left"]["clean"]["status"] == "exited"


def test_nondeterministic_identity_is_inconclusive(tmp_path):
    code = '#include <unistd.h>\n#include <stdio.h>\nint main(void){printf("%ld\\n",(long)getpid());return 0;}'
    result, _, rc = evaluate(tmp_path, code, code)
    assert rc == 2 and result["status"] == "INCONCLUSIVE", result
    assert result["comparison"]["unresolved"] == 1
    assert "counterexample" not in result


def test_missing_snapshot_cannot_claim_equivalence(tmp_path):
    code = '#include <unistd.h>\nint main(void){_exit(0);}'
    result, _, rc = evaluate(tmp_path, code, code)
    assert rc == 2 and result["status"] == "INCONCLUSIVE", result
    other = tmp_path / "different"
    other.mkdir()
    result, _, rc = evaluate(other, code, code.replace("_exit(0)", "_exit(1)"))
    assert rc == 1 and result["status"] == "DIFFERENT", result


def test_hang_and_compile_failure_are_distinct_results(tmp_path):
    result, _, rc = evaluate(tmp_path, "int main(void){return 0;}", "int main(void){for(;;){}return 0;}")
    assert rc == 1 and result["status"] == "DIFFERENT", result
    assert result["counterexample"]["right"]["clean"]["status"] == "timeout"
    other = tmp_path / "invalid"
    other.mkdir()
    result, _, rc = evaluate(other, "int main(void){return 0;}", "int main(void){invalid C;}")
    assert rc == 2 and result["status"] == "BUILD_FAILED", result
    assert not result["builds"]["right.clean"]["ok"]
