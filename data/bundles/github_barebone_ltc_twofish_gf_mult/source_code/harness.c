/* BYOH memstate harness for the github functional axis (batch 1).
 *
 * TARGET SIGNATURE:
 *   static ulong32 gf_mult(ulong32 a, ulong32 b, ulong32 p)
 *     (libtomcrypt twofish.c -- GF(2^8) multiply-with-reduction, used by the MDS/RS matrix
 *     setup: `gf_mult(in, 0x5B, MDS_POLY)`, `gf_mult(in, 0xEF, MDS_POLY)`, and
 *     `gf_mult(in[y], RS[x][y], RS_POLY)`.)
 * WHY BYOH: `ulong32` is a project typedef the auto-generator's scalar classifier doesn't
 *   recognise (only the standard C/stdint names), so it reports "unsupported return type".
 * FIXED CONSTANTS / SETUP: pure combinational function, no output params, no globals touched
 *   -- the only observable effect is the return value. At EVERY real call site `b` is always a
 *   small constant/table byte (<=255) and `p` is one of exactly two fixed reduction
 *   polynomials (`MDS_POLY`=0x169, `RS_POLY`=0x14D); the internal unrolled loop indexes a
 *   2-element array via `B[1]>>7`, which is only guaranteed in-range when `b` stays a byte and
 *   `p` is one of those two real polynomials -- so we replicate that exact contract (`a` is the
 *   free/varying byte, `b` bounded to a byte, `p` chosen between the two real polynomials)
 *   rather than feeding arbitrary 32-bit noise, which would trip the array over-read on
 *   the ORIGINAL build and just get discarded as unsafe (starving n_safe). NOTE: `MDS_POLY`/
 *   `RS_POLY` are `#undef`-ed near the end of the TU (before our own code, appended after the
 *   whole `#include "func.c"`), so we hardcode the two literal polynomial values instead of
 *   referencing the (by-then-undefined) macro names.
 *
 * Structure = funcharness.PRELUDE + MAIN_OPEN + <middle> + HARNESS_FOOTER (verbatim).
 * Contract: the seed is already in the VB_CUR/VB_N byte cursor (MAIN_OPEN read argv[1]);
 * build the args from the seed, call the target, fold its return value + every output
 * buffer's CONTENT into vb_digest (vb_mix*), then vb_dump(argv[2]) & exit 0. */
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

  /* `a` is free (any 32-bit magnitude is safe -- only ever used via `a&1`/`a>>=1`); `b` MUST
   * stay a byte and `p` MUST be one of the two real reduction polynomials, or the unrolled
   * loop's `B[1]>>7` array index can run off the end of the 2-element P[]/B[] arrays (a real
   * over-read the original library never triggers because every real call site honours this
   * same contract). Literal polynomials: MDS_POLY=0x169, RS_POLY=0x14D (already #undef-ed by
   * the time this code runs, appended after the whole TU). */
  ulong32 _a = (ulong32)vb_take(4);
  ulong32 _b = (ulong32)vb_take(1);
  ulong32 _p = (vb_take(1) & 1u) ? (ulong32)0x169 : (ulong32)0x14D;

  ulong32 _ret = gf_mult(_a, _b, _p);   /* <-- function under test */

  vb_mix(&_ret, sizeof _ret);

  vb_dump(argc>2?argv[2]:NULL);
  return 0;
}
