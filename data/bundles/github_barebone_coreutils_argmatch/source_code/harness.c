/* BYOH memstate harness for the github functional axis (coreutils/gnulib).
 *
 * TARGET SIGNATURE:
 *   ptrdiff_t argmatch (const char *arg, const char *const *arglist,
 *                        const void *vallist, size_t valsize);
 *   (gnulib lib/argmatch.c -- abbreviation-tolerant match of ARG against the NULL-terminated
 *   ARGLIST: returns the index of an exact match immediately; if ARG is a prefix of exactly
 *   one entry, returns that entry's index; if it is a prefix of more than one entry, VALLIST
 *   (an array of VALSIZE-byte records parallel to ARGLIST, or NULL) is used to see whether
 *   the matches are mere synonyms (-> return the first) or a real ambiguity (-> -2); with no
 *   match at all, returns -1. Used by coreutils option parsing, e.g. `--sort=SIZE-or-TIME`.)
 *
 * WHY BYOH: the signature takes a NULL-terminated array of `char*` (a double pointer) plus a
 * `const void *vallist` typed only by the runtime `valsize` -- both outside what
 * funcharness.generate_harness can auto-synthesise (it rejects nstars >= 2 and has no notion
 * of a caller-defined element size). argmatch only READS arg/arglist/vallist and returns a
 * small signed index (0..N-1, -1, or -2) -- a plain integer, never an address -- so folding
 * just the return value is address-free by construction (same pattern as the sibling
 * coreutils_argmatch_exact.c harness for argmatch_exact, the exact-match-only cousin in this
 * same file).
 *
 * COMPAT SHIMS (func.c IS the WHOLE lib/argmatch.c file, so every sibling function in it --
 * argmatch_exact / argmatch_invalid / argmatch_valid / __xargmatch_internal /
 * argmatch_to_argument, none of which we ever call -- still needs to COMPILE+LINK in this
 * single-TU build; none of these shims is ever executed since main() only calls argmatch),
 * identical to coreutils_argmatch_exact.c's shim block:
 *   - `streq`/`memeq`: gnulib functions normally supplied by gnulib's *replacement*
 *     <string.h> (only pulled in via a full gnulib-tool bootstrap); with the plain system
 *     <string.h> they are undeclared. Defined here as macros over strcmp/memcmp BEFORE
 *     func.c is included. argmatch() itself calls `memeq` (to compare two VALSIZE-byte
 *     vallist records) -- that call site IS exercised at runtime, unlike the other shims.
 *   - `GNULIB_TEXT_DOMAIN`: argmatch.c's own `_(msgid)` macro references this token (used
 *     only inside argmatch_invalid, which we never call, but the translation unit must still
 *     preprocess/compile it); defined as a plain string literal.
 *   - `quote`/`quote_n`/`quotearg_n_style`/`exit_failure`: declared (not defined) by the
 *     headers this bundle ships (quote.h/quotearg.h/exitfail.h) -- their .c bodies are not
 *     part of this bundle's extra_files, so the single-TU LINK needs *some* definition.
 *     Trivial passthrough/constant stubs, signature-matched against the shipped headers
 *     (included here first so `enum quoting_style` is visible when these are declared).
 *
 * Structure = funcharness.PRELUDE + funcharness.MAIN_OPEN + <middle> + funcharness.HARNESS_FOOTER
 * (all three blocks copied verbatim, byte-for-byte, from ddiv/funcharness.py -- only the
 * compat-shim block below is inserted BEFORE the verbatim PRELUDE, exactly like
 * coreutils_argmatch_exact.c). Contract: the seed is already in the VB_CUR/VB_N byte cursor
 * (MAIN_OPEN read argv[1]); build `arg` + a NULL-terminated `arglist` + a parallel `vallist`
 * from the seed, call the target, fold its return value (an index/-1/-2, never an address)
 * into vb_digest, then vb_dump(argv[2]) & exit 0. */
#include <stdbool.h>
#include "exitfail.h"
#include "gettext.h"
#include "quote.h"
#include "quotearg.h"

/* argmatch.h itself is UNBUILDABLE here: it unconditionally pulls in the brand-new gnulib
 * "stdcountof" module via `#include <stdcountof.h>` (for the ARGMATCH_VERIFY macro's
 * `countof`), which is not in this bundle's shipped headers (only lib/argmatch.h itself is,
 * not its own new transitive angle-bracket dependency) and can't be added without touching
 * the registry. argmatch.c needs only ONE thing from argmatch.h at file scope: the
 * `argmatch_exit_fn` typedef (for its `argmatch_die` global). So pre-define the include
 * guard to make argmatch.c's own `#include "argmatch.h"` a no-op, and supply that one
 * typedef by hand -- everything else argmatch.h would have declared (prototypes for the
 * sibling functions, including argmatch itself) is unnecessary: they are DEFINITIONS in
 * argmatch.c, which is legal in C without a prior prototype, and our own call to argmatch()
 * below comes textually AFTER func.c has already defined it. */
#define ARGMATCH_H_ 1
typedef void (*argmatch_exit_fn) (void);

#define GNULIB_TEXT_DOMAIN "gnulib"
#define streq(a, b) (strcmp((a), (b)) == 0)
#define memeq(a, b, n) (memcmp((a), (b), (n)) == 0)

int volatile exit_failure = 1;
char const *quote_n_mem(int n, char const *arg, size_t argsize) { (void)n; (void)argsize; return arg; }
char const *quote_mem(char const *arg, size_t argsize) { (void)argsize; return arg; }
char const *quote_n(int n, char const *arg) { (void)n; return arg; }
char const *quote(char const *arg) { return arg; }
char *quotearg_n_style(int n, enum quoting_style s, char const *arg) { (void)n; (void)s; return (char *)arg; }
/* auto-generated by ddiv.funcharness -- DO NOT EDIT */
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

static const unsigned char *VB_CUR; static long VB_N, VB_I;
static unsigned long vb_take(int nb){ unsigned long v=0; int k;
  for(k=0;k<nb;k++){ v |= (unsigned long)(VB_I<VB_N?VB_CUR[VB_I]:0) << (8*k); VB_I++; } return v; }
static long vb_int(void){ long m=2L*VB_INTBOUND+1; return (long)(vb_take(4)%m) - VB_INTBOUND; }
static double vb_dbl(void){ long x=(long)(vb_take(4)% (2000001UL)) - 1000000L; return (double)x/1000.0; }
static int vb_len(int bound){ return (int)(vb_take(1) % (unsigned)(bound+1)); }

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

int main(int argc, char **argv){
  if(argc<2){ fprintf(stderr,"usage: %s <seed> [dump]\n", argv[0]); return 64; }
  FILE *fp=fopen(argv[1],"rb"); if(!fp){ perror("open"); return 64; }
  fseek(fp,0,SEEK_END); long fsz=ftell(fp); fseek(fp,0,SEEK_SET);
  unsigned char *buf=(unsigned char*)malloc(fsz>0?fsz:1);
  long nread=(long)fread(buf,1,fsz>0?fsz:0,fp); fclose(fp);
  VB_CUR=buf; VB_N=nread; VB_I=0;

  /* Build `arg`: a NUL-terminated printable-ASCII string (32..126). Note argmatch() computes
   * strncmp(arglist[i], arg, strlen(arg)) -- when arg is EMPTY that comparison is trivially
   * true for every arglist[i], so an empty arg (arg_n==0, which vb_len(VB_STRLEN) yields on
   * ~1/25 seeds) exercises the multi-match / ambiguous / vallist-disambiguation branches. */
  int arg_n = vb_len(VB_STRLEN);
  char arg_buf[VB_STRLEN+1];
  for (int _k = 0; _k < arg_n; _k++) { arg_buf[_k] = (char)(32 + (vb_take(1) % 95)); }
  arg_buf[arg_n] = '\0';

  /* Build a NULL-terminated `arglist` of 4 candidate strings, with a companion `vallist` of
   * 4 ints (one per arglist entry, valsize == sizeof(int) so every memeq() inside argmatch()
   * compares exactly one whole element -- always in-bounds regardless of which index it
   * picks, since i ranges only over the 4 populated slots). One arglist slot is seed-gated to
   * be copied verbatim from `arg` so the exact-match branch (return i immediately) is
   * exercised as well as the prefix/no-match/ambiguous branches -- all deterministic from the
   * seed cursor, never rand()/address-derived. */
  char items[4][VB_STRLEN+1];
  char *arglist[5];
  int vals[4];
  for (int _i = 0; _i < 4; _i++) {
    int _n = vb_len(VB_STRLEN);
    for (int _k = 0; _k < _n; _k++) { items[_i][_k] = (char)(32 + (vb_take(1) % 95)); }
    items[_i][_n] = '\0';
    arglist[_i] = items[_i];
    vals[_i] = (int)vb_int();
  }
  if (vb_take(1) % 2) {
    int _slot = (int)(vb_take(1) % 4);
    strncpy(items[_slot], arg_buf, VB_STRLEN);
    items[_slot][VB_STRLEN] = '\0';
  }
  arglist[4] = NULL;

  /* Seed-gate whether a vallist is supplied at all: argmatch() treats a NULL vallist as "no
   * way to disambiguate synonyms" (any second nonexact match is unconditionally ambiguous),
   * vs. a real vallist (which lets equal-valued prefix matches be treated as non-ambiguous
   * synonyms) -- exercising both of argmatch()'s documented disambiguation paths. */
  int use_vallist = (int)(vb_take(1) % 2);
  const void *vallist = use_vallist ? (const void *)vals : NULL;
  size_t valsize = sizeof(int);

  long vb_ret = (long)argmatch(arg_buf, (char const *const *)arglist, vallist, valsize);
  vb_mix(&vb_ret, sizeof vb_ret);

  vb_dump(argc>2?argv[2]:NULL);
  return 0;
}
