/* BYOH memstate harness for the github functional axis (batch 1).
 *
 * TARGET SIGNATURE:
 *   void tigrFill(Tigr* bmp, int x, int y, int w, int h, TPixel color)
 *     Tigr = { int w,h,cx,cy,cw,ch; TPixel *pix; void *handle; int blitMode; } (tigr.h)
 *     TPixel = { unsigned char r,g,b,a; }
 * WHY BYOH: pointer to an unsupported (project struct) type -- 'Tigr* bmp' -- plus a
 *   pass-by-value struct param (TPixel color), both outside the auto-generator.
 * FIXED CONSTANTS / SETUP: a small (2..21 x 2..21) off-screen bitmap allocated via the
 *   library's OWN tigrBitmap() (TIGR_HEADLESS -- never hand-roll the Tigr/calloc(pix) layout),
 *   zero-initialized. x/y are drawn as SIGNED bytes (-128..127) and w/h (the fill rectangle,
 *   not the bitmap) as unsigned bytes (0..255) -- deliberately often far outside the bitmap's
 *   bounds, to exercise tigrFill's own internal clamp/clip logic (negative-origin clamp,
 *   over-size clamp, empty-after-clip early return) on every safe seed. tigrFill's only
 *   observable effect is what it writes into bmp->pix, so we fold the CONTENT of every pixel in
 *   the bitmap (not just the touched sub-rect -- untouched pixels stay at their deterministic
 *   zeroed value on both identity and stub, so folding the whole buffer is exact and simpler).
 *   Never the `pix`/`handle` POINTER fields themselves.
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

  /* Small off-screen bitmap via the library's OWN tigrBitmap (zero-filled pix buffer). */
  int _bw = vb_len(19) + 2;   /* 2..21 */
  int _bh = vb_len(19) + 2;   /* 2..21 */
  Tigr *_bmp = tigrBitmap(_bw, _bh);

  /* Fill-rect args deliberately span well outside [0,_bw)x[0,_bh) so tigrFill's own
   * negative-origin / over-size clamp logic gets exercised on most seeds. */
  int _fx = (int)(signed char)vb_take(1);   /* -128..127 */
  int _fy = (int)(signed char)vb_take(1);   /* -128..127 */
  int _fw = (int)vb_take(1);                /* 0..255 */
  int _fh = (int)vb_take(1);                /* 0..255 */
  TPixel _color;
  _color.r = (unsigned char)vb_take(1);
  _color.g = (unsigned char)vb_take(1);
  _color.b = (unsigned char)vb_take(1);
  _color.a = (unsigned char)vb_take(1);

  tigrFill(_bmp, _fx, _fy, _fw, _fh, _color);   /* <-- function under test */

  vb_mix(&_bw, sizeof _bw);
  vb_mix(&_bh, sizeof _bh);
  for (int _i = 0; _i < _bw * _bh; _i++) {
    vb_mix(&_bmp->pix[_i], sizeof(TPixel));
  }

  tigrFree(_bmp);   /* library helper (TIGR_HEADLESS): frees pix then the bitmap */

  vb_dump(argc>2?argv[2]:NULL);
  return 0;
}
