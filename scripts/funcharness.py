"""Generate a memstate-capturing C harness for a single function, from its signature.

The harness reads ONE input file (the raw **safe seed**), rebuilds the function's
arguments deterministically from it (a tiny FuzzedDataProvider-style byte cursor), calls
the function, folds the function's *return value + any output buffers* into a global
digest, and then dumps the program's own writable globals -- the ``.data`` and ``.bss``
segments, bounded by the linker symbols ``__data_start``/``_edata``/``__bss_start``/``_end``
-- to the path in ``argv[2]``. That dump is the **program-exit memory state**.

Only ``func0`` is ever substituted; all the surrounding source runs unchanged, so the
globals at program exit reflect the function's complete effect: its return value (folded
into the ``vb_digest`` global), anything it wrote through pointer/array output parameters
(also folded in), and any module global it touched (captured directly in the dump). The
Python oracle (functional.py) byte-compares this dump to the frozen baseline:

    equal, no crash      -> INTACT  (behaviour preserved)
    different, no crash   -> VANISH  (silent miscomputation -- the headline signal)
    sanitizer / abort     -> DEVIATED (a loud, detectable introduced bug; CWE-labelled)

Heap, stack and the register file are deliberately NOT compared: allocation interleaving,
uninitialised stack slots and the libc load address are not stable across two
independently-linked binaries, and at ``exit_group`` the registers are just the libc
exit-path state (no function signal). The function's exit-time signal lives entirely in
the globals dumped here plus the digest. To keep ``.data`` free of sanitizer metadata
(whose embedded addresses shift when the body changes), the memstate is captured from a
**sanitizer-free** build; a separate ASAN/UBSAN build of the same harness detects crashes.

Supported signatures (others raise ``UnsupportedSignature`` -> the case is skipped and
recorded): return int-like / float|double / ``char*`` / ``void`` ; params int-like,
float|double, ``char*`` (C string), ``T* arr, int n`` array+length pairs, and **lone**
numeric pointer/array params with no following length (``T *p``, ``T p[]``, ``T name[K]``)
-- these get a generous zeroed ``VB_ARRCAP`` buffer with only a fixed prefix (the literal
``[K]`` if given, else ``VB_ARRLEN``) filled+folded, so a modest over-read by the original
lands on deterministic zeros while any read past the cap traps on the original and is dropped
by the safety/determinism filter. A ``void`` return is observable only through what func0
writes, so it must have at least one output pointer param (array/string) -- the memstate dump
captures those writes (and any global it touches), which a return-value compare could not.
Richer signatures (struct / multi-dimensional / double pointer) are still out of scope here.

Two seed formats are supported (see ``LIT_MAGIC`` / ``ddiv.seedencode``). A seed whose
first 8 bytes equal ``LIT_MAGIC`` decodes in **literal mode**: a runtime ``VB_LIT`` branch reads
every field straight off the byte cursor with no derivation/bounding (u32 lengths, 8-byte
int/double slots), so a caller (``seedencode.encode_seed``) can hand-craft exact argument values
instead of letting ``vb_int``/``vb_dbl``/``vb_len`` derive them. Any other seed decodes in
**v1 bounded mode**, byte-for-byte identical to the pre-literal-mode harness -- same draws, same
buffer kinds/sizes, same uninitialized-stack quirks.
"""
from __future__ import annotations

import re
from dataclasses import dataclass, field
from typing import List, Optional


class UnsupportedSignature(Exception):
    pass


_INT_TYPES = {
    "char", "signed char", "unsigned char", "short", "short int", "unsigned short",
    "int", "signed", "signed int", "unsigned", "unsigned int", "long", "long int",
    "unsigned long", "long long", "unsigned long long", "size_t", "ssize_t",
    "bool", "_Bool",
    "int8_t", "int16_t", "int32_t", "int64_t",
    "uint8_t", "uint16_t", "uint32_t", "uint64_t", "intptr_t", "uintptr_t",
}
_FLOAT_TYPES = {"float", "double", "long double"}

# Python mirrors of the harness's C bounds (the #defines in _PRELUDE below) -- used by
# seed_budget() to size seeds to a signature's worst-case byte consumption. Keep in sync.
VB_MAXLEN = 16     # paired-array (T* arr, int n) length bound
VB_STRLEN = 24     # string length bound
VB_ARRLEN = 8      # lone-array default folded-prefix length
VB_ARRCAP = 256    # lone-array literal-mode fill/fold cap (mirrors _PRELUDE's VB_ARRCAP)

# Literal-mode seed magic (see the module docstring): a seed whose first 8 bytes equal this
# decodes VERBATIM off the byte cursor (ddiv/seedencode.py is the Python encoder/
# decoder); any other seed decodes in the legacy v1 bounded mode. Keep byte-for-byte in sync
# with _PRELUDE's C-side ``VB_LIT_MAGIC`` array below.
LIT_MAGIC = bytes([0xDE]) + b"VBLIT2" + bytes([0xF0])
assert len(LIT_MAGIC) == 8


@dataclass
class Param:
    kind: str            # 'int' | 'float' | 'cstr' | 'array'
    ctype: str           # element/scalar C type (for 'array' = element type)
    # array length convention (only meaningful when kind == 'array'):
    #   None        -> PAIRED: an int length param immediately follows (T* arr, int n)
    #   K   (K > 0) -> FIXED:  declared with an explicit literal size, T name[K]
    #   0           -> LONE:   bare pointer / [] with no length -> fold a VB_ARRLEN prefix
    length: Optional[int] = None


@dataclass
class Signature:
    name: str
    ret_kind: str        # 'int' | 'float' | 'cstr'
    params: List[Param] = field(default_factory=list)
    raw: str = ""


# storage-class / qualifier tokens that don't change how we build an argument or a result
_QUALS = {"const", "volatile", "static", "extern", "inline", "register", "auto",
          "__inline", "__inline__", "__restrict", "__restrict__", "restrict",
          "_Noreturn", "__signed__", "__const", "__volatile__"}


def _norm(t: str) -> str:
    t = re.sub(r"__attribute__\s*\(\(.*?\)\)", " ", t)
    toks = [x for x in t.split() if x not in _QUALS]
    return " ".join(toks)


def _classify_base(t: str) -> Optional[str]:
    n = _norm(t)
    if n in _FLOAT_TYPES:
        return "float"
    if n in _INT_TYPES:
        return "int"
    return None


def _split_params(s: str) -> List[str]:
    """Split a parameter list on top-level commas (reject nested parens = fn pointers)."""
    s = s.strip()
    if not s or _norm(s) == "void":
        return []
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur); cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


def _parse_param(p: str) -> Param:
    p = p.strip()
    if "(" in p or ")" in p:
        raise UnsupportedSignature(f"function-pointer / complex param: {p!r}")
    nstars = p.count("*")
    # capture any [] suffixes (with their literal sizes) before normalising them away
    brackets = re.findall(r"\[\s*(\d*)\s*\]", p)
    if len(brackets) >= 2:
        raise UnsupportedSignature(f"multi-dimensional array: {p!r}")
    array_brackets = len(brackets) == 1
    explicit_k = int(brackets[0]) if (array_brackets and brackets[0].strip()) else None
    base = _norm(p.replace("*", " "))
    # drop a trailing identifier (param name) and any [] suffix
    base = re.sub(r"\[\s*\d*\s*\]", "", base)
    toks = base.split()
    if nstars >= 2:
        raise UnsupportedSignature(f"double pointer: {p!r}")
    if nstars == 1 or array_brackets:
        # strip the trailing name token to recover the type
        type_toks = toks[:-1] if len(toks) > 1 else toks
        tstr = " ".join(type_toks)
        if "char" in tstr and "unsigned" not in tstr and "signed" not in tstr:
            return Param("cstr", "char")
        b = _classify_base(tstr)
        if b in ("int", "float"):
            # length 0 = lone (no explicit size); a positive K = fixed declared size.
            # parse_signature later flips this to None if an int length param follows.
            return Param("array", tstr if tstr else "int",
                         length=(explicit_k if explicit_k is not None else 0))
        raise UnsupportedSignature(f"pointer to unsupported type: {p!r}")
    # scalar: type is all tokens except the trailing name (if >1 token)
    type_toks = toks[:-1] if len(toks) > 1 else toks
    tstr = " ".join(type_toks)
    b = _classify_base(tstr)
    if b is None:
        # maybe the whole thing is a bare type with no name (e.g. "int")
        b = _classify_base(base)
        tstr = base
    if b == "int":
        return Param("int", tstr)
    if b == "float":
        return Param("float", tstr)
    raise UnsupportedSignature(f"unsupported scalar param: {p!r}")


def parse_signature(src: str) -> Signature:
    """Parse the function definition's signature (text up to the body '{')."""
    head = src.split("{", 1)[0].strip()
    lp = head.find("(")
    rp = head.rfind(")")
    if lp == -1 or rp == -1 or rp < lp:
        raise UnsupportedSignature("no parameter list")
    before = head[:lp].strip()
    params_str = head[lp + 1:rp]
    m = re.search(r"([A-Za-z_]\w*)\s*$", before)
    if not m:
        raise UnsupportedSignature(f"cannot find function name in {before!r}")
    name = m.group(1)
    ret = before[:m.start()].strip()
    rn = _norm(ret)
    if "*" in ret:
        if "char" in rn and "unsigned" not in rn and "signed" not in rn:
            ret_kind = "cstr"
        else:
            raise UnsupportedSignature(f"unsupported pointer return: {ret!r}")
    elif rn == "void":
        ret_kind = "void"
    elif rn in _FLOAT_TYPES:
        ret_kind = "float"
    elif rn in _INT_TYPES:
        ret_kind = "int"
    else:
        raise UnsupportedSignature(f"unsupported return type: {ret!r}")

    raw_params = _split_params(params_str)
    params = [_parse_param(p) for p in raw_params]
    # decide each array param's length convention:
    #   followed by an int -> PAIRED (length=None, consume the int as the runtime length)
    #   otherwise          -> LONE (keep length=K for a fixed [K] declaration, else 0 = default
    #                          VB_ARRLEN prefix into a generous zeroed VB_ARRCAP buffer)
    i = 0
    while i < len(params):
        if params[i].kind == "array":
            if i + 1 < len(params) and params[i + 1].kind == "int":
                params[i].length = None      # paired T* arr, int n
                i += 2
            else:
                i += 1                        # lone array / fixed-size array
        else:
            i += 1
    # a void function has no return value to fold, so it is only observable through what it
    # writes -- it MUST have at least one output-capable pointer param (array/string) for the
    # exit-memstate oracle to have a signal. (A pure void(scalars) fn would be trivially INTACT
    # for any body and would be dropped by the stub->DEVIATED promote gate anyway.)
    if ret_kind == "void" and not any(p.kind in ("array", "cstr") for p in params):
        raise UnsupportedSignature("void return with no pointer/output parameter to capture")
    return Signature(name=name, ret_kind=ret_kind, params=params, raw=head)


def seed_budget(sig: Signature) -> int:
    """Worst-case seed bytes the generated harness can consume for `sig`.

    ``vb_take`` reads 0 past the seed end, so an under-sized seed collapses the tail
    params to CONSTANTS (ints -> -VB_INTBOUND, later array/string lengths -> 0): those
    parameters are then never exercised and a candidate that mangles only their code
    paths still scores INTACT. Seeds must be sized to at least this budget for every
    parameter to carry entropy. Per param: int/float = 4 (one vb_take(4)); cstr =
    1 length byte + VB_STRLEN chars; paired array = 1 length byte + 4*VB_MAXLEN element
    draws; lone array = 4 bytes per folded-prefix element (the literal [K], else
    VB_ARRLEN). The paired length var itself consumes nothing extra.
    """
    total, i = 0, 0
    while i < len(sig.params):                   # mirror _build_args's iteration exactly
        p = sig.params[i]
        if p.kind in ("int", "float"):
            total += 4
            i += 1
        elif p.kind == "cstr":
            total += 1 + VB_STRLEN
            i += 1
        elif p.kind == "array" and p.length is None:
            total += 1 + 4 * VB_MAXLEN           # paired: T* arr, int n -- the int consumes
            i += 2                               # nothing (it IS the drawn length), skip it
        elif p.kind == "array":
            total += 4 * (p.length if p.length > 0 else VB_ARRLEN)   # lone [K] / VB_ARRLEN
            i += 1
        else:
            i += 1
    return total


# --------------------------------------------------------------------------- #
# C code generation
# --------------------------------------------------------------------------- #

_PRELUDE = r"""/* auto-generated by ddiv.funcharness -- DO NOT EDIT */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "func.c"

/* ---- program-exit memstate capture (see ddiv/functional.py) -----------------
 * Run func0 on a SAFE seed, fold its return value + any output buffers into a global
 * digest, then dump the program's own writable globals -- [.data, .bss], the part of
 * "all memory at program exit" that is deterministic across two independently-linked
 * binaries -- to argv[2]. The oracle byte-compares this dump to the frozen baseline:
 * equal => INTACT, differ-without-crash => silent VANISH, sanitizer/abort => DEVIATED. */

extern char __data_start[], _edata[], __bss_start[], _end[];

#define VB_MAXLEN   16     /* array length bound (paired T* arr, int n) */
#define VB_STRLEN   24     /* string length bound */
#define VB_INTBOUND 1000   /* scalar int magnitude bound */
#define VB_ARRLEN   8      /* default folded prefix for a lone array/pointer param */
#define VB_ARRCAP   256    /* generous zeroed allocation for a lone array/pointer param --
                            * modest over-reads by the original land on deterministic zeros;
                            * a read past the cap traps on the ORIGINAL build and the case is
                            * dropped by the safety/determinism filter (never a wrong verdict). */
#define VB_LIT_MAGIC_LEN 8 /* literal-mode magic prefix length (see funcharness.LIT_MAGIC) */

static const unsigned char *VB_CUR; static long VB_N, VB_I; static int VB_LIT;
/* literal-mode magic: a seed starting with these 8 bytes decodes VERBATIM (VB_LIT branches
 * below); any other seed decodes in legacy v1 BOUNDED mode. Keep byte-for-byte in sync with
 * ddiv/funcharness.py:LIT_MAGIC / ddiv/seedencode.py:MAGIC. */
static const unsigned char VB_LIT_MAGIC[VB_LIT_MAGIC_LEN] = {0xDE,'V','B','L','I','T','2',0xF0};
static unsigned long vb_take(int nb){ unsigned long v=0; int k;
  for(k=0;k<nb;k++){ v |= (unsigned long)(VB_I<VB_N?VB_CUR[VB_I]:0) << (8*k); VB_I++; } return v; }
static long vb_int(void){ long m=2L*VB_INTBOUND+1; return (long)(vb_take(4)%m) - VB_INTBOUND; }
static double vb_dbl(void){ long x=(long)(vb_take(4)% (2000001UL)) - 1000000L; return (double)x/1000.0; }
static int vb_len(int bound){ return (int)(vb_take(1) % (unsigned)(bound+1)); }
/* literal-mode 8-byte double: reinterpret the next 8 cursor bytes as an IEEE-754 bit pattern
 * (verbatim, unlike vb_dbl's derived/bounded value). */
static double vb_lit_dbl(void){ unsigned long b=vb_take(8); double d; memcpy(&d,&b,8); return d; }

/* result digest -- a global (lives in .data), so it is part of the dumped memstate.
 * FNV-1a over the function's return value + output buffers. */
static uint64_t vb_digest = 1469598103934665603ULL;
static void vb_mix(const void *p, unsigned long n){
  const unsigned char *b=(const unsigned char*)p; unsigned long i;
  for(i=0;i<n;i++){ vb_digest ^= b[i]; vb_digest *= 1099511628211ULL; } }
/* quantise a double to fixed-point (~1e-6 tolerance) so a numerically-equal result that
 * differs in the low mantissa bits (FMA / instruction-selection) still compares equal. */
static void vb_mix_d(double x){ long q;
  if(isnan(x)) q = (long)0x7ff8000000000000LL;
  else if(isinf(x)) q = (x>0?1:-1)*0x7fffffffffffffffLL;
  else q = (long)llround(x*1e6);
  vb_mix(&q, sizeof q); }
static void vb_mix_s(const char *s){
  if(!s){ unsigned char z=0; vb_mix(&z,1); return; }
  unsigned char nz=1; vb_mix(&nz,1); vb_mix(s, (unsigned long)strlen(s)); }

/* dump the program's writable globals (the deterministic part of the exit memstate). */
static void vb_dump(const char *path){
  VB_CUR=0; VB_N=0; VB_I=0;                  /* zero bookkeeping (VB_CUR holds a heap ptr) */
  if(!path) return;
  FILE *out = fopen(path, "wb"); if(!out) return;
  fwrite(__data_start, 1, (size_t)((char*)_edata   - (char*)__data_start), out);
  fwrite(__bss_start,  1, (size_t)((char*)_end     - (char*)__bss_start),  out);
  fclose(out); }
"""

_MAIN_OPEN = r"""
int main(int argc, char **argv){
  if(argc<2){ fprintf(stderr,"usage: %s <seed> [dump]\n", argv[0]); return 64; }
  FILE *fp=fopen(argv[1],"rb"); if(!fp){ perror("open"); return 64; }
  fseek(fp,0,SEEK_END); long fsz=ftell(fp); fseek(fp,0,SEEK_SET);
  unsigned char *buf=(unsigned char*)malloc(fsz>0?fsz:1);
  long nread=(long)fread(buf,1,fsz>0?fsz:0,fp); fclose(fp);
  VB_CUR=buf; VB_N=nread; VB_I=0;
  VB_LIT = (VB_N>=VB_LIT_MAGIC_LEN && memcmp(buf, VB_LIT_MAGIC, VB_LIT_MAGIC_LEN)==0);
  if(VB_LIT){ VB_I=VB_LIT_MAGIC_LEN; }
"""


def _build_args(sig: Signature):
    """Emit C that constructs each argument.

    Each parameter is built by a runtime ``VB_LIT`` branch: the literal-mode arm reads its
    field(s) verbatim off the byte cursor (u32 lengths, 8-byte int/double slots -- see
    ``ddiv.seedencode`` for the matching Python encoder), no derivation/bounding; the
    OTHER arm is the legacy v1 bounded derivation via ``vb_int``/``vb_dbl``/``vb_len``. The
    v1 arm's existing draw statements are NEVER reordered/rewritten -- they are copied
    verbatim and only wrapped in ``if(VB_LIT){...}else{ <here> }``, so a non-magic seed
    produces byte-identical draws/buffers to the pre-literal-mode harness. (Lone-array's
    ``int a0_n = <default>;`` + its ``calloc`` stay fully UNCONDITIONAL, exactly as before --
    neither is a draw, so hoisting them ahead of the branch is a no-op for v1 and lets the
    literal arm simply overwrite ``a0_n`` afterwards.)

    Returns ``(decl_lines, call_arg_names, outputs)`` where ``outputs`` is the list of
    ``(kind, var, len_var, elem_ctype)`` for pointer/array/string params -- func0 may
    modify these in place, so they are folded into the digest after the call.
    """
    lines, call, outputs = [], [], []
    i = 0
    a = 0
    while i < len(sig.params):
        p = sig.params[i]
        v = f"a{a}"
        if p.kind == "int":
            lines.append(f"  long {v};")
            lines.append("  if(VB_LIT){")
            lines.append(f"    {v} = (long)vb_take(8);")
            lines.append("  }else{")
            lines.append(f"    {v} = vb_int();")
            lines.append("  }")
            call.append(v)
            a += 1; i += 1
        elif p.kind == "float":
            lines.append(f"  double {v};")
            lines.append("  if(VB_LIT){")
            lines.append(f"    {v} = vb_lit_dbl();")
            lines.append("  }else{")
            lines.append(f"    {v} = vb_dbl();")
            lines.append("  }")
            call.append(v)
            a += 1; i += 1
        elif p.kind == "cstr":
            # v1 keeps its ORIGINAL stack buffer (incl. its uninitialized tail past a0_n) --
            # now named {v}_sbuf so {v} can be a char* pointing at it (v1) or a heap buffer
            # sized exactly to the literal length (literal mode); downstream code (the call
            # site + vb_mix_s) only ever sees {v} as a char*, unchanged either way.
            lines.append(f"  char {v}_sbuf[VB_STRLEN+1];")
            lines.append(f"  char *{v}; int {v}_n;")
            lines.append("  if(VB_LIT){")
            lines.append(f"    unsigned long {v}_len = vb_take(4);")
            lines.append(f"    {v} = (char*)calloc({v}_len + 1 + VB_STRLEN, 1);")
            lines.append(f"    for(unsigned long _k=0;_k<{v}_len;_k++){{ {v}[_k]=(char)vb_take(1); }}")
            lines.append(f"    {v}_n = (int){v}_len;")
            lines.append("  }else{")
            lines.append(f"    {v}_n = vb_len(VB_STRLEN);")
            lines.append(f"    for(int _k=0;_k<{v}_n;_k++){{ {v}_sbuf[_k]=(char)(32+(vb_take(1)%95)); }}")
            lines.append(f"    {v}_sbuf[{v}_n]='\\0';")
            lines.append(f"    {v} = {v}_sbuf;")
            lines.append("  }")
            call.append(v)
            outputs.append(("cstr", v, None, "char"))
            a += 1; i += 1
        elif p.kind == "array" and p.length is None:
            # PAIRED idiom: T* arr, int n -- runtime length from the seed, exact-size buffer.
            lv = f"a{a+1}"
            et = p.ctype
            is_f = p.ctype in _FLOAT_TYPES
            lines.append(f"  int {v}_n; {et} *{v}; long {lv};")
            lines.append("  if(VB_LIT){")
            lines.append(f"    unsigned long {v}_alloc = vb_take(4);")
            lines.append(f"    unsigned long {v}_pass = vb_take(4);")
            lines.append(f"    {v} = ({et}*)malloc(sizeof({et})*({v}_alloc?{v}_alloc:1));")
            if is_f:
                lines.append(f"    for(unsigned long _k=0;_k<{v}_alloc;_k++){{ {v}[_k]=({et})vb_lit_dbl(); }}")
            else:
                lines.append(f"    for(unsigned long _k=0;_k<{v}_alloc;_k++){{ {v}[_k]=({et})(long)vb_take(8); }}")
            lines.append(f"    {v}_n = (int){v}_alloc;")
            lines.append(f"    {lv} = (long){v}_pass;")
            lines.append("  }else{")
            lines.append(f"    {v}_n = vb_len(VB_MAXLEN);")
            lines.append(f"    {v} = ({et}*)malloc(sizeof({et})*({v}_n?{v}_n:1));")
            if is_f:
                lines.append(f"    for(int _k=0;_k<{v}_n;_k++){{ {v}[_k]=({et})vb_dbl(); }}")
            else:
                lines.append(f"    for(int _k=0;_k<{v}_n;_k++){{ {v}[_k]=({et})vb_int(); }}")
            lines.append(f"    {lv} = {v}_n;")
            lines.append("  }")
            call.append(v); call.append(lv)
            outputs.append(("array", v, f"{v}_n", et))
            a += 2; i += 2
        elif p.kind == "array":
            # LONE pointer / array (no following length): generous zeroed VB_ARRCAP buffer,
            # fill+fold only a fixed prefix (explicit [K], else VB_ARRLEN). The pointer is the
            # only argument -- no length is passed/consumed. The first two lines below are
            # UNCHANGED v1 statements (no draw in either -- {ln} is a compile-time constant),
            # kept unconditional; the literal arm simply overwrites {v}_n afterwards.
            et = p.ctype
            is_f = p.ctype in _FLOAT_TYPES
            ln = str(p.length) if (p.length and p.length > 0) else "VB_ARRLEN"
            lines.append(f"  int {v}_n = {ln};")
            lines.append(f"  {et} *{v} = ({et}*)calloc(VB_ARRCAP, sizeof({et}));")
            lines.append("  if(VB_LIT){")
            lines.append(f"    unsigned long {v}_fill = vb_take(4);")
            lines.append(f"    if({v}_fill > (unsigned long)VB_ARRCAP) {v}_fill = VB_ARRCAP;")
            if is_f:
                lines.append(f"    for(unsigned long _k=0;_k<{v}_fill;_k++){{ {v}[_k]=({et})vb_lit_dbl(); }}")
            else:
                lines.append(f"    for(unsigned long _k=0;_k<{v}_fill;_k++){{ {v}[_k]=({et})(long)vb_take(8); }}")
            lines.append(f"    {v}_n = (int){v}_fill;")
            lines.append(f"    if({v}_n < ({ln})) {v}_n = ({ln});")
            lines.append(f"    if({v}_n > VB_ARRCAP) {v}_n = VB_ARRCAP;")
            lines.append("  }else{")
            if is_f:
                lines.append(f"    for(int _k=0;_k<{v}_n;_k++){{ {v}[_k]=({et})vb_dbl(); }}")
            else:
                lines.append(f"    for(int _k=0;_k<{v}_n;_k++){{ {v}[_k]=({et})vb_int(); }}")
            lines.append("  }")
            call.append(v)
            outputs.append(("array", v, f"{v}_n", et))
            a += 1; i += 1
        else:
            i += 1
    return lines, call, outputs


def _fold_lines(sig: Signature, call_expr: str, outputs):
    """Emit C that calls the function and folds its return value + outputs into vb_digest."""
    lines = []
    if sig.ret_kind == "int":
        lines.append(f"  long vb_ret = (long)({call_expr});")
        lines.append("  vb_mix(&vb_ret, sizeof vb_ret);")
    elif sig.ret_kind == "float":
        lines.append(f"  double vb_ret = (double)({call_expr});")
        lines.append("  vb_mix_d(vb_ret);")
    elif sig.ret_kind == "cstr":
        lines.append(f"  char *vb_ret = (char*)({call_expr});")
        lines.append("  vb_mix_s(vb_ret);")
    elif sig.ret_kind == "void":
        # no return value to fold; func0 is observable only through its output buffers
        # (folded below) and any global it writes (captured by the .data/.bss dump).
        lines.append(f"  {call_expr};")
    else:
        raise UnsupportedSignature(sig.ret_kind)
    # fold output-param buffers (func0 may sort/fill an array or write a string in place)
    for kind, v, _lenv, et in outputs:
        if kind == "cstr":
            lines.append(f"  vb_mix_s({v});")
        elif kind == "array":
            if et in _FLOAT_TYPES:
                lines.append(f"  for(int _k=0;_k<{v}_n;_k++){{ vb_mix_d((double){v}[_k]); }}")
            else:
                lines.append(f"  for(int _k=0;_k<{v}_n;_k++){{ vb_mix(&{v}[_k], sizeof {v}[_k]); }}")
    return lines


# Public building blocks for bring-your-own-harness authors (see
# functional.freeze_functional_bundle ``harness_src=``). A custom harness for a signature the
# generator can't synthesise = PRELUDE + MAIN_OPEN + <build args / call func0 / fold its result
# and output buffers into vb_digest via vb_mix/vb_mix_d/vb_mix_s> + HARNESS_FOOTER. The PRELUDE
# defines the byte cursor (vb_take/vb_int/vb_dbl/vb_len), the digest mixers, and vb_dump; MAIN_OPEN
# reads the seed file into the cursor; the FOOTER dumps the exit memstate and exits 0.
PRELUDE = _PRELUDE
MAIN_OPEN = _MAIN_OPEN
HARNESS_FOOTER = "  vb_dump(argc>2?argv[2]:NULL);\n  return 0;\n}\n"


def generate_harness(sig: Signature) -> str:
    arg_lines, call, outputs = _build_args(sig)
    call_expr = f"{sig.name}(" + ", ".join(call) + ")"
    fold = _fold_lines(sig, call_expr, outputs)
    body = [_PRELUDE, _MAIN_OPEN]
    body += arg_lines
    body += fold
    body.append("  vb_dump(argc>2?argv[2]:NULL);")
    body.append("  return 0;")
    body.append("}")
    return "\n".join(body) + "\n"
