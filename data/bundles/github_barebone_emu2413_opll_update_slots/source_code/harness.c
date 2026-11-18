/* BYOH memstate harness for the github functional axis (recompile-pool promotion).
 *
 * TARGET SIGNATURE:
 *   static void update_slots(OPLL *opll)
 *
 * WHY HAND-WRITTEN: `OPLL *opll` is a pointer to a big STRUCT (an embedded `slot[18]`
 * array of OPLL_SLOT + top-level counters) -- funcharness's automatic signature parser
 * only knows int/float/char-string/T-array params, so `OPLL *` is UnsupportedSignature
 * for the generator (same reason as the sibling emu2413_opll_get_parameter_rate.c
 * harness). There is no separate-buffer pointer-relationship precondition here (no
 * end/limit-into-another-arg contract) -- the one pointer relationship that matters is
 * INTERNAL to update_slots itself: for slot i it forms `buddy = &opll->slot[i+1]`
 * (type==0) or `&opll->slot[i-1]` (type==1), which is automatically in-object-valid as
 * long as `opll` is one real OPLL containing its own `slot[18]` (update_slots computes
 * buddy itself -- we just have to hand it a real, whole OPLL). The only thing WE must
 * avoid is steering `type` into the two BOUNDARY combinations that would make
 * update_slots compute an out-of-bounds `&slot[-1]` (i==0,type==1) or `&slot[18]`
 * (i==17,type==0) subscript -- UBSan's array-bounds check instruments the subscript
 * itself (a compile-time-sized array), independent of whether the result is later
 * dereferenced -- so we bias `type` away from the single unsafe direction at each
 * boundary index and leave every interior slot free to draw type 0/1/2.
 *
 * update_slots mutates a purely local aggregate (no globals it touches), so unlike
 * emu2413_opll_makeSinTable.c's file-scope table globals, NONE of its effect would show
 * up in the auto .data/.bss dump. We declare `opll` + its patches as ORDINARY STACK
 * locals (matching the sibling get_parameter_rate harness) and manually fold the
 * CONTENT of every field update_slots can mutate -- never the `patch` pointer itself
 * (our own stack address; folding it would be an address leak into the digest).
 *
 * Exercised body, per slot: `commit_slot_update` only runs if `update_requests != 0`;
 * every slot's `update_requests` stays at its zero-inited value so that whole
 * table-heavy branch (wave_table_map/tll_table/rks_table) is skipped, shrinking the
 * precondition down to "a valid, non-NULL `patch`". The unconditional
 * `calc_envelope`+`calc_phase` calls are what we exercise: `eg_state` is drawn from
 * {ATTACK,DECAY,SUSTAIN,RELEASE} (skip DAMP=4, whose DAMP->ATTACK transition writes
 * through the buddy pointer -- not needed for a solid signal, so we just don't reach
 * it); `eg_rate_h`/`eg_rate_l`/`eg_shift`/`eg_out` are drawn within their real
 * bit-widths so `eg_step_tables[eg_rate_l][idx]` stays in bounds and `1<<eg_shift`
 * never over-shifts; `patch->SL`/`patch->ML` are bounded to their real 4-bit fields
 * (SL is compared against `eg_out>>3`, ML indexes the 16-entry `ml_table`); `patch->PM`
 * is held at 0 so calc_phase's `(fnum&0x1ff)*2+pm` term (which would go negative
 * through `pm_table` on a PM!=0 slot) stays non-negative before its `<<blk` --
 * left-shifting a negative int is UB and isn't needed for a solid differential. `blk`
 * is bounded to its real 3-bit field so the shift amount itself always stays small.
 *
 * A single always-true differentiator underwrites the whole harness no matter how the
 * rest lands: update_slots's FIRST line unconditionally does `opll->eg_counter++`, and
 * we fold `eg_counter` post-call -- identity always changes it, while the `stub` mock
 * (void return -> a bare `return;` body) never does, so identity vs. stub reliably
 * disagree on every seed. The per-slot `eg_out`/`eg_state`/`update_requests`/
 * `pg_phase`/`pg_out` fields are folded on top for a richer signal.
 *
 * KEEP-ALIVE (found by empirically diffing `size`/`nm` output between an identity and a
 * stub build): `eg_step_tables`/`ml_table`/`pm_table` are referenced ONLY inside
 * calc_envelope/calc_phase, which are themselves called ONLY from update_slots. A
 * stubbed update_slots has no call sites left anywhere in the TU, so clang -- even at
 * -O0 -- drops those now-fully-unreferenced statics from `.data` (an internal-linkage
 * "unused static" elision, not an optimization pass), shrinking the segment by exactly
 * 160 bytes and tripping the memstate LAYOUT gate (INCOMPARABLE, not WRONG_ANSWER) no
 * matter what values the harness feeds. This is purely a build-time artifact of which
 * OTHER statics happen to hang off update_slots's own callees, not a real behavioral
 * signal, so a volatile side-effect-only read of those three tables (after the call,
 * never folded into vb_digest) keeps their size fixed regardless of the candidate.
 *
 * Structure = funcharness.PRELUDE + MAIN_OPEN + <middle> + HARNESS_FOOTER (verbatim).
 * Contract: the seed is already in the VB_CUR/VB_N byte cursor (MAIN_OPEN read argv[1]);
 * build the args from the seed, call the target, fold its return value + every output's
 * CONTENT into vb_digest (vb_mix*), then vb_dump(argv[2]) & exit 0. */
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

  /* `opll` + its 18 patches: ordinary stack locals, fully zeroed first so every field
   * update_slots might read is deterministic (either explicitly seeded below or 0). */
  OPLL_PATCH patches[18];
  OPLL opll;
  memset(&patches, 0, sizeof patches);
  memset(&opll, 0, sizeof opll);

  opll.eg_counter = (uint32_t)vb_int();
  opll.test_flag  = (uint8_t)vb_len(7);   /* bit0 -> calc_envelope `test`, bit2 -> calc_phase `reset` */
  opll.pm_phase   = (uint32_t)vb_int();

  for (int i = 0; i < 18; i++) {
    int t = (int)vb_len(2);        /* 0, 1, or 2 ("neither" -- buddy stays NULL) */
    if (i == 0  && t == 1) t = 0;  /* would make update_slots compute &opll.slot[-1] */
    if (i == 17 && t == 0) t = 1;  /* would make update_slots compute &opll.slot[18] */

    OPLL_SLOT *slot = &opll.slot[i];
    slot->type      = (uint8_t)t;
    slot->eg_state  = (uint8_t)vb_len(3);    /* ATTACK,DECAY,SUSTAIN,RELEASE (skip DAMP/UNKNOWN) */
    slot->eg_out    = (uint32_t)vb_len(127); /* EG_MUTE's real range */
    slot->eg_rate_h = (uint8_t)vb_len(15);   /* real 4-bit field */
    slot->eg_rate_l = (uint8_t)vb_len(3);    /* indexes eg_step_tables[4][..] */
    slot->eg_shift  = (uint32_t)vb_len(13);  /* keeps 1<<eg_shift well within int range */
    slot->blk       = (uint8_t)vb_len(7);    /* real 3-bit field -- bounds the <<blk shift */
    slot->fnum      = (uint16_t)vb_int();    /* only ever used masked, any value is safe */
    slot->pg_phase  = (uint32_t)vb_int();

    patches[i].SL = (uint32_t)vb_len(15);    /* real 4-bit field, compared to eg_out>>3 */
    patches[i].PM = 0;                       /* keeps calc_phase's pre-<<blk term non-negative */
    patches[i].ML = (uint32_t)vb_len(15);    /* indexes the 16-entry ml_table */
    slot->patch = &patches[i];
  }

  update_slots(&opll);

  /* keep-alive: eg_step_tables/ml_table/pm_table are referenced ONLY from
   * calc_envelope/calc_phase (never from anywhere else in func.c); a STUBBED
   * update_slots (e.g. the ground-truth `stub` mock, or a decompile that dropped the
   * body) never calls into them, so the compiler drops those now-unreferenced statics
   * from .data entirely -- a genuine 160-byte segment-size shrink that has NOTHING to
   * do with update_slots's actual behavior, but trips the memstate LAYOUT gate
   * (candidate INCOMPARABLE instead of PASS/WRONG_ANSWER) regardless of any seed. A
   * side-effect-only volatile read forces the compiler to keep them emitted at a fixed
   * size no matter what the spliced candidate's body does, so LAYOUT stays stable and
   * the oracle can actually compare content. Never folded into vb_digest (constant
   * compiled-in data, not update_slots's output -- folding it would add zero signal). */
  {
    volatile uint32_t _keep = 0;
    _keep ^= (uint32_t)eg_step_tables[0][0];
    _keep ^= (uint32_t)ml_table[0];
    _keep ^= (uint32_t)pm_table[0][0];
    (void)_keep;
  }

  /* Fold the CONTENT of every field update_slots can mutate -- never `slot->patch`
   * (our own stack address). */
  vb_mix(&opll.eg_counter, sizeof opll.eg_counter);
  for (int i = 0; i < 18; i++) {
    OPLL_SLOT *slot = &opll.slot[i];
    vb_mix(&slot->eg_out, sizeof slot->eg_out);
    vb_mix(&slot->eg_state, sizeof slot->eg_state);
    vb_mix(&slot->update_requests, sizeof slot->update_requests);
    vb_mix(&slot->pg_phase, sizeof slot->pg_phase);
    vb_mix(&slot->pg_out, sizeof slot->pg_out);
  }

  vb_dump(argc>2?argv[2]:NULL);
  return 0;
}
