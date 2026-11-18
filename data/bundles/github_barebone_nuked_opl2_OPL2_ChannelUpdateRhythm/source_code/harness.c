/* BYOH memstate harness for the github functional axis (batch 1).
 *
 * TARGET SIGNATURE:
 *   static void OPL2_ChannelUpdateRhythm(opl2_chip *chip, uint8_t data)
 *     opl2_chip / opl2_channel / opl2_slot are project structs (opl2.h) -- the auto-generator
 *     only knows scalar/cstr/numeric-array params, hence BYOH.
 * FIXED CONSTANTS / SETUP: a LOCAL (stack) opl2_chip, brought to a valid well-formed state via
 *   the library's OWN OPL2_Reset() (memsets + wires up channel->slotz[] pointers into
 *   chip->slot[] -- never hand-roll that layout), then OPL2_ChannelUpdateRhythm is called with
 *   a single seed byte (`data`): bit 0x20 selects rhythm-mode vs normal-mode for channels 6..8,
 *   the low nibble toggles hh/tc/tom/sd/bd envelope key on/off. We fold `chip->rhy` (set
 *   directly from `data`), each of channel[6..8].chtype, and each of their two slots' `key`
 *   byte (mutated via OPL2_EnvelopeKeyOn/Off) into vb_digest. NEVER the `slotz`/`mod`/`chip`/
 *   `channel` POINTER fields themselves -- only the scalar content OPL2_ChannelUpdateRhythm
 *   actually writes. `chip` is a plain local (not `static`/global), so it never lands in the
 *   .data/.bss dump at all -- only what we explicitly fold does.
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

  /* A plain LOCAL chip -- OPL2_Reset (the library's own init helper) fully memsets it and wires
   * up every channel->slotz[] pointer into chip->slot[]; never hand-roll that layout. */
  opl2_chip _chip;
  OPL2_Reset(&_chip, 44100u);

  uint8_t _data = (uint8_t)vb_take(1);
  OPL2_ChannelUpdateRhythm(&_chip, _data);   /* <-- function under test */

  vb_mix(&_chip.rhy, sizeof _chip.rhy);
  for (int _c = 6; _c <= 8; _c++) {
    vb_mix(&_chip.channel[_c].chtype, sizeof _chip.channel[_c].chtype);
    vb_mix(&_chip.channel[_c].slotz[0]->key, sizeof _chip.channel[_c].slotz[0]->key);
    vb_mix(&_chip.channel[_c].slotz[1]->key, sizeof _chip.channel[_c].slotz[1]->key);
  }

  vb_dump(argc>2?argv[2]:NULL);
  return 0;
}
