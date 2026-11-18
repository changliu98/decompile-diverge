"""Parse ARVO `crash_output` sanitizer traces into structured crash info.

Extracts:
  - backtrace frames (`#N 0x.. in <func> <file>:<line>[:<col>]`)
  - the crash-site frame (first frame located in *project* source, skipping the
    sanitizer/runtime frames that often sit at the top, e.g. an asan interceptor)
  - the crash `SUMMARY:` line and `DEDUP_TOKEN` (used as the crash-pattern equivalence
    key in the Decompile-Diverge verdict).

Mirrors how ARVO's own `parseCrash` keys on SUMMARY/DEDUP_TOKEN, but additionally
selects the crash-site function — the decompilation target for Decompile-Diverge.
"""
from __future__ import annotations

import re
from dataclasses import dataclass, asdict
from typing import List, Optional

from .cwe import cwe_of

# `#0 0x55... in funcname /src/proj/file.c:1274:9`  (col optional)
_FRAME_RE = re.compile(
    r"#(?P<idx>\d+)\s+0x[0-9a-fA-F]+\s+in\s+(?P<func>\S+)\s+"
    r"(?P<file>\S+?):(?P<line>\d+)(?::(?P<col>\d+))?(?=\s|$)"
)
_SUMMARY_RE = re.compile(r"^SUMMARY:\s*(.+)$", re.MULTILINE)
_DEDUP_RE = re.compile(r"DEDUP_TOKEN:\s*(.+)")
# The fault class as the sanitizer names it, from the ERROR/WARNING header or SUMMARY:
#   `ERROR: AddressSanitizer: stack-buffer-overflow ...` -> "stack-buffer-overflow"
_BUG_CLASS_RE = re.compile(r"(?:ERROR|WARNING|SUMMARY):\s*\w*Sanitizer:\s*([A-Za-z][\w-]*)")
# Access direction for memory faults: `READ of size 8 ...` / `WRITE of size 1 ...`
_ACCESS_RE = re.compile(r"\b(READ|WRITE) of size \d+")
# UBSAN: `<file>:<line>:<col>: runtime error: <kind>` (e.g. "division by zero"). UBSAN emits no
# DEDUP_TOKEN and only a generic class in its SUMMARY ("undefined-behavior" / "division"), so the
# specific, cwe-mappable kind is taken from this line.
_UBSAN_RE = re.compile(r"\S+:\d+:\d+: runtime error:\s*(?P<msg>.+)")

# Assertion backtrace from server-based targets (Redis, etc.):
#   `/path/to/binary(args)(funcname+0xoffset)[0xaddr]`
# The function name is inside the last pair of parentheses before the `[0x...]` address.
_ASSERT_FRAME_RE = re.compile(
    r"\(\s*(?P<func>[A-Za-z_][A-Za-z0-9_:><]*)(?:\+0x[0-9a-fA-F]+)?\s*\)\s*\[0x[0-9a-fA-F]+\]"
)

# A frame is runtime/sanitizer noise (not a real project crash site) if its file path
# or function name matches any of these. We skip these when choosing the crash site.
_RUNTIME_PATH_MARKERS = (
    "compiler-rt",
    "llvm-project",
    "sanitizer_common",
    "_interceptors",
    "interception",
    "/libfuzzer",
    "FuzzerMain",
    "FuzzerLoop",
    "FuzzerDriver",
    "/usr/include",
    "/usr/lib",
    "sysdeps",
)
_RUNTIME_FUNC_PREFIXES = (
    "__asan",
    "__msan",
    "__ubsan",
    "__tsan",
    "__lsan",
    "__sanitizer",
    "__interceptor",
)
# Auto-generated sources (still valid C, but flagged so downstream can prefer hand-written).
_GENERATED_MARKERS = ("gen_ndr", "/generated/", ".tab.c", "lex.yy", ".yy.c", "_gen.c")


@dataclass
class Frame:
    idx: int
    func: str
    file: str
    line: int
    col: Optional[int]
    is_runtime: bool
    is_generated: bool


@dataclass
class CrashInfo:
    summary: Optional[str]
    dedup_token: Optional[str]
    frames: List[Frame]
    crash_site: Optional[Frame]  # first non-runtime frame
    bug_class: Optional[str] = None   # sanitizer fault class, e.g. "stack-buffer-overflow"
    access: Optional[str] = None      # "READ" | "WRITE" | None
    cwe: Optional[str] = None         # CWE manifestation id, e.g. "CWE-787"; None/UNKNOWN if unmapped

    @property
    def has_crash_site(self) -> bool:
        return self.crash_site is not None

    def to_dict(self) -> dict:
        d = asdict(self)
        d["has_crash_site"] = self.has_crash_site
        return d


def _is_runtime(func: str, file: str) -> bool:
    if any(m in file for m in _RUNTIME_PATH_MARKERS):
        return True
    if func.startswith("__") and any(func.startswith(p) for p in _RUNTIME_FUNC_PREFIXES):
        return True
    return False


def _is_generated(file: str) -> bool:
    return any(m in file for m in _GENERATED_MARKERS)


def assertion_backtrace_funcs(text: str) -> List[str]:
    """Extract function names from an assertion backtrace (Redis-style).

    Format: ``/path/to/binary(args)(funcname+0xoffset)[0xaddr]``
    Returns the list of function names in order (top frame first).
    """
    return [_ASSERT_FRAME_RE.sub(r"\1", m.group()) for m in _ASSERT_FRAME_RE.finditer(text)]


def _ubsan_bug_class(msg: Optional[str]) -> Optional[str]:
    """Map a UBSAN ``runtime error: <msg>`` to a cwe.py bug_class token (None if unmapped).

    Covers the full set of clang UBSAN diagnostics so a trap yields a SPECIFIC CWE rather than the
    generic ``undefined-behavior`` (CWE-UNKNOWN). NB many of these (misaligned/shift/pointer-overflow)
    are BENIGN UB, not the memory-safety vulnerability -- specific labelling makes that visible."""
    m = (msg or "").lower()
    if "division by zero" in m or "divide by zero" in m:
        return "float-divide-by-zero" if "float" in m else "divide-by-zero"
    if "cannot be represented in type" in m and "float" in m:
        return "float-cast-overflow"
    if "signed integer overflow" in m or ("cannot be represented in type" in m and "unsigned" not in m):
        return "signed-integer-overflow"
    if "unsigned integer overflow" in m:
        return "unsigned-integer-overflow"
    if "shift" in m:                                       # exponent too large / negative / neg-lhs
        return "shift-out-of-bounds"
    if "misaligned address" in m or "misaligned" in m:    # benign: unaligned load/store
        return "misaligned-access"
    if ("null pointer" in m or "reference binding to null" in m
            or "member access within null" in m or "load of null" in m):
        return "null-dereference"
    if "out of bounds for type" in m or "index out of bounds" in m:   # -fsanitize=array-bounds
        return "array-index-out-of-bounds"
    if ("non-zero offset" in m and "null" in m) or "outside the bounds" in m or "pointer index" in m:
        return "pointer-overflow"
    if "incorrect function type" in m or "through pointer to incorrect" in m:
        return "function-type-mismatch"
    if "not a valid value for type" in m:                 # bool/enum with an out-of-range value
        return "invalid-value-load"
    if "variable length array" in m or "vla bound" in m:
        return "non-positive-vla-bound-value"
    return None


def is_sanitizer_crash(text: Optional[str]) -> bool:
    """True if the log shows a sanitizer-detected fault: an AddressSanitizer error, or a fatal
    UndefinedBehaviorSanitizer diagnostic (the cvf builds use ``-fno-sanitize-recover`` for the
    enabled UBSAN checks, so a ``runtime error:`` means the run aborted). Also detects assertion
    failures from server-based targets (e.g. Redis ``=== ASSERTION FAILED ===``). Single source
    of truth for "did this input crash" across the corpus-synthesis tools."""
    t = text or ""
    if "AddressSanitizer" in t and ("ERROR" in t or "SUMMARY" in t):
        return True
    if "UndefinedBehaviorSanitizer" in t:
        return True
    if _UBSAN_RE.search(t):
        return True
    # Assertion failures from server-based targets (Redis, etc.)
    if "ASSERTION FAILED" in t or "REDIS BUG REPORT" in t:
        return True
    return False


def parse_crash(crash_output: Optional[str]) -> CrashInfo:
    """Parse a raw sanitizer crash trace into structured CrashInfo.

    Handles both ASAN/UBSAN traces and assertion backtraces from server-based targets.
    """
    text = crash_output or ""
    frames: List[Frame] = []
    for m in _FRAME_RE.finditer(text):
        func, file = m.group("func"), m.group("file")
        frames.append(
            Frame(
                idx=int(m.group("idx")),
                func=func,
                file=file,
                line=int(m.group("line")),
                col=int(m.group("col")) if m.group("col") else None,
                is_runtime=_is_runtime(func, file),
                is_generated=_is_generated(file),
            )
        )

    # If no ASAN frames but assertion backtrace found, parse those too
    if not frames and is_sanitizer_crash(text):
        idx = 0
        for m in _ASSERT_FRAME_RE.finditer(text):
            func_name = m.group("func")
            frames.append(
                Frame(
                    idx=idx,
                    func=func_name,
                    file="<assertion>",
                    line=0,
                    col=None,
                    is_runtime=func_name.startswith("_") or func_name.startswith("__"),
                    is_generated=False,
                )
            )
            idx += 1

    crash_site = next((f for f in frames if not f.is_runtime), None)

    summary_m = _SUMMARY_RE.search(text)
    dedup_m = _DEDUP_RE.search(text)
    class_m = _BUG_CLASS_RE.search(text)
    access_m = _ACCESS_RE.search(text)
    ubsan_m = _UBSAN_RE.search(text)

    bug_class = class_m.group(1) if class_m else None
    # UBSAN's header/SUMMARY only names the generic kind ("undefined-behavior", or a bare word
    # like "division"); the cwe-mappable kind is on the `runtime error:` line. Prefer it ONLY
    # when the ASAN class is absent or generic, so real ASAN classes are never overridden.
    if ubsan_m and (not bug_class or bug_class.lower() in ("undefined-behavior", "division")):
        ub = _ubsan_bug_class(ubsan_m.group("msg"))
        if ub:
            bug_class = ub
    access = access_m.group(1) if access_m else None
    cwe, _ = cwe_of(bug_class, access)

    dedup_token = dedup_m.group(1).strip() if dedup_m else None
    # UBSAN emits no DEDUP_TOKEN; synthesize the ARVO-style top-3 non-runtime frame signature
    # (mirrors ASAN_OPTIONS dedup_token_length=3) so the crash carries a location key for
    # patterns_match. Gated on a UBSAN line so the ASAN path is untouched.
    if dedup_token is None and ubsan_m:
        sig = [f.func for f in frames if not f.is_runtime][:3]
        if sig:
            dedup_token = "--".join(sig)

    # Assertion backtraces also lack DEDUP_TOKEN; synthesize from parsed frames
    is_assertion = "ASSERTION FAILED" in text or "REDIS BUG REPORT" in text
    if dedup_token is None and is_assertion and frames:
        sig = [f.func for f in frames if not f.is_runtime][:3]
        if sig:
            dedup_token = "--".join(sig)

    summary = summary_m.group(1).strip() if summary_m else None
    if summary is None and ubsan_m:
        loc = crash_site.func if crash_site else ubsan_m.group("msg")
        summary = f"UndefinedBehaviorSanitizer: {bug_class or 'undefined-behavior'} in {loc}"
    if summary is None and is_assertion:
        loc = crash_site.func if crash_site else "<assertion>"
        summary = f"Assertion failure in {loc}"

    return CrashInfo(
        summary=summary,
        dedup_token=dedup_token,
        frames=frames,
        crash_site=crash_site,
        bug_class=bug_class,
        access=access,
        cwe=cwe,
    )


def _weakness(ci: CrashInfo) -> Optional[str]:
    """The CWE manifestation key, or None when unknown (so it can't force a (mis)match)."""
    return ci.cwe if (ci.cwe and ci.cwe != "CWE-UNKNOWN") else None


# A source ``file:line[:col]`` is a COORDINATE, not a crash identity: the spliced function is
# re-synthesized (and comments/reformatting move lines), so the SAME check fails at a different
# line. The SUMMARY fallback must therefore strip the coordinate before comparing -- otherwise a
# UBSAN crash (which carries no DEDUP_TOKEN, so it lands on this fallback) reads as "shifted" purely
# because the line moved. Keeps the file/sanitizer/bug-class text; drops the ``:line[:col]``.
_SUMMARY_LOC = re.compile(r":\d+(?::\d+)?")


def _norm_summary(s: str) -> str:
    return re.sub(r"\s+", " ", _SUMMARY_LOC.sub("", s)).strip()


def patterns_match(baseline: CrashInfo, candidate: CrashInfo) -> bool:
    """Crash-pattern equivalence used by the Decompile-Diverge verdict (INTACT vs DEVIATED).

    A crash matches only if BOTH agree:
      * weakness (CWE manifestation) -- separates an out-of-bounds WRITE (CWE-787) from a
        READ (CWE-125) at the *same* call site, which DEDUP_TOKEN (call-stack only) cannot;
      * location -- same DEDUP_TOKEN (call stack), or same **coordinate-free** SUMMARY as a
        fallback (file/sanitizer/bug-class, line/col stripped).

    Each key is enforced only when present on both sides, so a crash whose CWE is unknown
    (or a pre-CWE frozen baseline) degrades gracefully to the legacy location-only check.
    Line/column are deliberately NOT compared -- neither in the DEDUP_TOKEN (call stack) nor in
    the SUMMARY fallback (``_norm_summary`` strips ``:line[:col]``): the spliced function is
    re-synthesized, so the same logical bug legitimately reports a different line. A line-number
    change alone must never produce a mismatch.
    """
    bw, cw = _weakness(baseline), _weakness(candidate)
    if bw and cw and bw != cw:
        return False
    if baseline.dedup_token and candidate.dedup_token:
        return baseline.dedup_token == candidate.dedup_token
    if baseline.summary and candidate.summary:
        return _norm_summary(baseline.summary) == _norm_summary(candidate.summary)
    return bool(bw and cw and bw == cw)
