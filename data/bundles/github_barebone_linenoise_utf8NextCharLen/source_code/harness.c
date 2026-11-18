/* BYOH harness for github_linenoise_utf8NextCharLen (ddiv/funcharness.py contract).
 *
 * Target: static size_t utf8NextCharLen(const char *buf, size_t pos, size_t len)
 *
 * Pointer-relationship precondition the auto-harness can't express: `buf` is a single
 * buffer and `len` is its logical length within that SAME buffer; `pos` must be a valid
 * cursor into it. Internally utf8NextCharLen (and the utf8DecodeChar it calls) does NOT
 * bounds-check its multi-byte UTF-8 lookahead against `len` -- a decode started at
 * curpos < len may still read up to 4 raw bytes from the buffer regardless of how close
 * curpos is to len. The auto-harness allocates an independent buffer per pointer arg and
 * has no notion that `len` must describe THIS buffer, so it would either pass a length
 * that doesn't match the buffer's real size (spurious ASAN heap-buffer-overflow on the
 * ORIGINAL function) or leave the relationship undefined. Here we build one fixed-capacity
 * buffer, fill it COMPLETELY and deterministically from the seed, cap the logical `len` we
 * hand to the function well below the real capacity (leaving slack for the un-bounds-checked
 * lookahead), and draw `pos` in [0, len] -- an always-in-contract call.
 */
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

  /* ---- build the in-contract argument set ------------------------------------------ */
#define VB_BUFCAP 48   /* logical length ceiling we ever hand to the fn as `len` */
#define VB_BUFPAD 8    /* real slack past VB_BUFCAP: utf8DecodeChar's multi-byte lookahead
                        * is not bounds-checked against `len`, so the REAL buffer must be
                        * larger than the logical length we claim it has. Worst case the
                        * fn touches offset (len-1)+3 = len+2, so len<=48 + 8 slack is
                        * generous headroom against the real allocation of 56 bytes. */

  unsigned char ubuf[VB_BUFCAP + VB_BUFPAD];
  for (int _k = 0; _k < (int)sizeof(ubuf); _k++) ubuf[_k] = (unsigned char)vb_take(1);

  int len_i = vb_len(VB_BUFCAP);      /* len  in [0, VB_BUFCAP]      -- fits in ubuf w/ slack */
  int pos_i = vb_len(len_i);          /* pos  in [0, len_i]          -- honours pos<=len       */

  size_t vb_ret = utf8NextCharLen((const char *)ubuf, (size_t)pos_i, (size_t)len_i);
  vb_mix(&vb_ret, sizeof vb_ret);

  vb_dump(argc>2?argv[2]:NULL);
  return 0;
}
