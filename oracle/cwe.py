"""Map a sanitizer crash class (+ READ/WRITE access) to a CWE *manifestation* label.

The sanitizer reports what *manifested* (an out-of-bounds read, a use-after-free, ...),
not the root weakness (an integer overflow that led to a bad size that led to the write).
So this returns the **observed-effect CWE** -- which is exactly the axis Decompile-Diverge needs:
when a decompiler turns an out-of-bounds WRITE (CWE-787) into an out-of-bounds READ
(CWE-125), or removes it entirely, the manifestation CWE is what changes.

Derivation is deterministic from data we already have on every ARVO row (``crash_type`` =
``"<Class> <ACCESS> <size>"``) and on every parsed sanitizer log -- no LLM, no network.

``cwe_of(bug_class, access)`` is the single entry point; ``classify_crash_type`` splits an
ARVO ``crash_type`` string into ``(bug_class, access)``.
"""
from __future__ import annotations

import re
from typing import Optional, Tuple

UNKNOWN = ("CWE-UNKNOWN", "Unmapped or operational (timeout/oom/leak/unparsed)")

# Out-of-bounds classes whose CWE depends on the access direction (READ vs WRITE).
_BUFFER_OOB = {
    "heap-buffer-overflow", "stack-buffer-overflow", "global-buffer-overflow",
    "dynamic-stack-buffer-overflow", "container-overflow", "index-out-of-bounds",
    "object-size", "unknown-crash-oob",
}
_UNDERFLOW = {"stack-buffer-underflow", "heap-buffer-underflow", "global-buffer-underflow"}

# Access-independent classes -> fixed CWE.
_TABLE = {
    # use-after-free family
    "heap-use-after-free": ("CWE-416", "Use After Free"),
    "use-after-free": ("CWE-416", "Use After Free"),
    "use-after-poison": ("CWE-416", "Use After Free"),
    "stack-use-after-return": ("CWE-562", "Return of Stack Variable Address"),
    "stack-use-after-scope": ("CWE-825", "Expired Pointer Dereference"),
    # free errors
    "heap-double-free": ("CWE-415", "Double Free"),
    "double-free": ("CWE-415", "Double Free"),
    "invalid-free": ("CWE-590", "Free of Memory Not on the Heap"),
    "bad-free": ("CWE-590", "Free of Memory Not on the Heap"),
    "alloc-dealloc-mismatch": ("CWE-762", "Mismatched Memory Management Routines"),
    "new-delete-type-mismatch": ("CWE-762", "Mismatched Memory Management Routines"),
    # uninitialized / type
    "use-of-uninitialized-value": ("CWE-457", "Use of Uninitialized Variable"),
    "bad-cast": ("CWE-843", "Type Confusion"),
    "incorrect-function-pointer-type": ("CWE-843", "Type Confusion"),
    # null / wild pointer
    "null-dereference": ("CWE-476", "NULL Pointer Dereference"),
    "segv on unknown address": ("CWE-476", "NULL Pointer Dereference"),
    "segv": ("CWE-476", "NULL Pointer Dereference"),
    # sizing / allocation
    "negative-size-param": ("CWE-131", "Incorrect Calculation of Buffer Size"),
    "calloc-overflow": ("CWE-131", "Incorrect Calculation of Buffer Size"),
    "non-positive-vla-bound-value": ("CWE-1284", "Improper Validation of Specified Quantity"),
    "allocation-size-too-big": ("CWE-789", "Memory Allocation with Excessive Size Value"),
    "requested-allocation-size-exceeds": ("CWE-789", "Memory Allocation with Excessive Size Value"),
    # overlapping copies (undefined behavior)
    "memcpy-param-overlap": ("CWE-758", "Reliance on Undefined Behavior"),
    "strcpy-param-overlap": ("CWE-758", "Reliance on Undefined Behavior"),
    "strncpy-param-overlap": ("CWE-758", "Reliance on Undefined Behavior"),
    # recursion / leak
    "stack-overflow": ("CWE-674", "Uncontrolled Recursion"),
    "out-of-memory": ("CWE-789", "Memory Allocation with Excessive Size Value"),
    "detected-memory-leaks": ("CWE-401", "Missing Release of Memory after Lifetime"),
    "memory-leak": ("CWE-401", "Missing Release of Memory after Lifetime"),
    # UBSAN integer / arithmetic
    "signed-integer-overflow": ("CWE-190", "Integer Overflow or Wraparound"),
    "unsigned-integer-overflow": ("CWE-190", "Integer Overflow or Wraparound"),
    "integer-overflow": ("CWE-190", "Integer Overflow or Wraparound"),
    "divide-by-zero": ("CWE-369", "Divide By Zero"),
    "float-divide-by-zero": ("CWE-369", "Divide By Zero"),
    "float-cast-overflow": ("CWE-681", "Incorrect Conversion between Numeric Types"),
    "implicit-conversion": ("CWE-704", "Incorrect Type Conversion or Cast"),
    # UBSAN misc (full diagnostic set -> specific CWE instead of generic undefined-behavior).
    # shift/misaligned/invalid-value are typically BENIGN UB, not the memory-safety vuln.
    "shift-out-of-bounds": ("CWE-1335", "Incorrect Bitwise Shift of Integer"),
    "misaligned-access": ("CWE-1093", "Excessively Complex Data Representation"),
    "array-index-out-of-bounds": ("CWE-125", "Out-of-bounds Read"),
    "pointer-overflow": ("CWE-823", "Use of Out-of-range Pointer Offset"),
    "function-type-mismatch": ("CWE-843", "Type Confusion"),
    "invalid-value-load": ("CWE-758", "Reliance on Undefined Behavior"),
}


# Memory-safety CWEs a sanitizer (ASAN/UBSAN) can actually catch at runtime -- the subset
# worth selecting from a CVE dataset when the goal is a reproducible sanitizer crash.
# NB: selection-vs-build coverage. The cvf corpus build (cvf_synth_corpus.CFLAGS) enables ASAN +
# UBSAN *integer-divide-by-zero* only. So the ASAN classes + CWE-369 are actually trippable, but
# the int-overflow entries (CWE-190/191) are admitted-but-not-yet-caught (their UBSAN checks --
# signed-integer-overflow -- aren't enabled, and unsigned overflow is well-defined, not UB). Enable
# `-fsanitize=signed-integer-overflow` in the build (+ map it in crashparse._ubsan_bug_class)
# before relying on those, or they yield all-safe corpora.
MEMORY_SAFETY_CWES = frozenset({
    "CWE-787", "CWE-125", "CWE-119", "CWE-124", "CWE-127", "CWE-786", "CWE-788",  # OOB
    "CWE-416", "CWE-415", "CWE-590", "CWE-825", "CWE-562", "CWE-763",             # free/lifetime
    "CWE-476",                                                                    # null deref
    "CWE-457", "CWE-908",                                                         # uninit
    "CWE-843",                                                                    # type confusion
    "CWE-190", "CWE-191", "CWE-131", "CWE-680",                                   # int -> overflow (NOT yet built)
    "CWE-369",                                                                    # div by zero (ASAN+UBSAN int-div-0)
})


def is_memory_safety(cwe_id: Optional[str]) -> bool:
    return (cwe_id or "").strip().upper() in MEMORY_SAFETY_CWES


def _norm(s: Optional[str]) -> str:
    return (s or "").strip().lower()


def cwe_of(bug_class: Optional[str], access: Optional[str] = None) -> Tuple[str, str]:
    """(``bug_class``, ``access``) -> (``cwe_id``, ``name``); UNKNOWN if unmapped."""
    c = _norm(bug_class)
    a = (access or "").strip().upper() or None
    if not c:
        return UNKNOWN
    if c in _BUFFER_OOB:
        if a == "WRITE":
            return ("CWE-787", "Out-of-bounds Write")
        if a == "READ":
            return ("CWE-125", "Out-of-bounds Read")
        return ("CWE-119", "Improper Restriction of Operations within Memory Buffer Bounds")
    if c in _UNDERFLOW:
        if a == "WRITE":
            return ("CWE-124", "Buffer Underwrite")
        if a == "READ":
            return ("CWE-127", "Buffer Under-read")
        return ("CWE-786", "Access of Memory Location Before Start of Buffer")
    return _TABLE.get(c, UNKNOWN)


def cwe_id(bug_class: Optional[str], access: Optional[str] = None) -> str:
    return cwe_of(bug_class, access)[0]


# `Stack-buffer-overflow READ 8`, `Heap-use-after-free WRITE 4`, `Use-of-uninitialized-value`,
# `Heap-buffer-overflow READ {*}` (OSS-Fuzz uses {*} as a wildcard size when it varies).
_CRASH_TYPE_RE = re.compile(
    r"^(?P<klass>.+?)(?:\s+(?P<access>READ|WRITE))?(?:\s+(?:\d+|\{[^}]*\}))?\s*$")


def classify_crash_type(crash_type: Optional[str]) -> Tuple[Optional[str], Optional[str]]:
    """Split an ARVO ``crash_type`` into (bug_class, access). Inverse of how OSS-Fuzz
    formats it: ``"<Class> [READ|WRITE] [size]"``."""
    if not crash_type or not crash_type.strip():
        return None, None
    m = _CRASH_TYPE_RE.match(crash_type.strip())
    if not m:
        return crash_type.strip(), None
    return m.group("klass").strip(), m.group("access")
