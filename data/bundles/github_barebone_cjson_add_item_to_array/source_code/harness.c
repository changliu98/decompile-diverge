/* BYOH memstate harness for the github functional axis.
 *
 * TARGET SIGNATURE:
 *   static cJSON_bool add_item_to_array(cJSON *array, cJSON *item)
 *   {
 *       cJSON *child = NULL;
 *       if ((item == NULL) || (array == NULL) || (array == item)) { return false; }
 *       child = array->child;
 *       if (child == NULL) { array->child = item; item->prev = item; item->next = NULL; }
 *       else { if (child->prev) { suffix_object(child->prev, item); array->child->prev = item; } }
 *       return true;
 *   }
 *   -- takes two STRUCT POINTERS (`array` mutated in place, `item` linked into it) and returns a
 *   cJSON_bool -- neither pointer is seed-buildable/foldable directly, so the AUTO harness
 *   generator can't synthesise this. `add_item_to_array` is `static`, but the harness is
 *   `#include "func.c"`-d into the SAME translation unit, so it is directly callable by name
 *   (no need to go through the public `cJSON_AddItemToArray` wrapper). Modelled directly on the
 *   already-validated cjson_cJSON_AddItemToArray.c BYOH (same fresh-container + call-under-test +
 *   structural-check-via-getter shape) -- that harness targets the trivial public wrapper that
 *   just forwards to this exact static function, so the same fixture proves the same signal here.
 *
 * FIXED CONSTANTS / SETUP:
 *   `array` is a freshly created EMPTY array (`cJSON_CreateArray()`) and `item` a freshly created
 *   NUMBER node (`cJSON_CreateNumber(seed-derived value)`) -- both always non-NULL and never equal
 *   to each other, so `add_item_to_array`'s guard clause never trips for our inputs: the
 *   interesting signal is whether the callee actually performed the LINK (`array->child == item`),
 *   not which branch of the guard it took.
 *
 *   The number value folded into `item` is seed-derived (`vb_dbl()`) so the digest is
 *   seed-dependent through the item's content even though the structural outcome (append
 *   succeeds) never varies for our always-valid inputs.
 *
 * WHAT'S FOLDED (content only, never an address):
 *   - `has_array`/`has_item`: NULL-ness flags (booleans, not the pointers themselves).
 *   - `before_count`/`after_count`: `cJSON_GetArraySize(array)` before/after the call -- the
 *     STRUCTURAL signal that the array actually gained a child (a stub that never mutates
 *     `array` leaves after_count == before_count == 0).
 *   - `ret`: the function's own `cJSON_bool` return value.
 *   - the item's CONTENT after the call: `->type` (must be `cJSON_Number`), `->valueint` and
 *     `->valuedouble` (quantised) -- these are set at creation time, not by the call under test,
 *     but folding them keeps the digest seed-dependent and detects any candidate that corrupts
 *     the item it was handed instead of just failing to link it.
 *   - `matches`: whether `cJSON_GetArrayItem(array, 0)` retrieves the SAME node passed in as
 *     `item` -- folded as a boolean EQUALITY RESULT (0/1), never the pointer values being
 *     compared. Together with before/after_count this proves the item is really linked into
 *     `array`'s child list, not just left as a detached allocation.
 *
 *   A stub that neutralises the body to `return 0;` always yields ret=0 and
 *   after_count==before_count==0 / matches=0 (the array is never mutated), which disagrees with
 *   the real function's ret=1 / after_count==1 / matches=1 on every input -- maximally
 *   discriminating.
 *
 * Structure = funcharness.PRELUDE + MAIN_OPEN + <middle> + HARNESS_FOOTER (verbatim).
 * Contract: the seed is already in the VB_CUR/VB_N byte cursor (MAIN_OPEN read argv[1]);
 * build the args from the seed, call the target, fold its return value + every output
 * buffer's CONTENT into vb_digest (vb_mix*), then vb_dump(argv[2]) & exit 0. No crypto
 * key/IV/nonce here -- nothing to fix as a compile-time constant.
 *
 * ADDRESS-NOISE NEUTRALISATION (required for ANY cJSON github harness, not specific to this
 * function): cJSON.c's file-scope `static internal_hooks global_hooks = { internal_malloc,
 * internal_free, internal_realloc };` holds three FUNCTION POINTERS into this same PIE image.
 * Because `#include "func.c"` merges the whole of cJSON.c into this translation unit,
 * `global_hooks` lands inside the dumped [.data,.bss) window on EVERY cjson bundle (regardless of
 * which function is targeted) and its content shifts with the PIE load base -- exactly the kind of
 * address noise the memstate contract forbids folding (see the cjson_cJSON_AddItemToArray.c /
 * cjson_cJSON_AddArrayToObject.c / cjson_cJSON_AddNumberToObject.c BYOHs, which document the
 * ASLR-on freeze probe that found this). Fix: memset `global_hooks` back to all-zero bytes right
 * after the call under test and before vb_dump, on EVERY run (baseline capture AND eval-time
 * candidate) -- so that region of the dump is a deterministic constant, never a real address.
 * func0 never legitimately depends on `global_hooks`'s content surviving past its own call, so
 * this cannot hide a real vanish. */
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

  /* the value folded into the fresh NUMBER item -- seed-derived so the digest varies with the
   * seed even though the structural outcome (a fresh, always-valid append) never does. */
  double _val = vb_dbl();

  cJSON *array = cJSON_CreateArray();
  int has_array = (array != NULL) ? 1 : 0;
  vb_mix(&has_array, sizeof has_array);

  cJSON *item = cJSON_CreateNumber(_val);
  int has_item = (item != NULL) ? 1 : 0;
  vb_mix(&has_item, sizeof has_item);

  if (array && item) {
    int before_count = cJSON_GetArraySize(array);
    vb_mix(&before_count, sizeof before_count);

    /* The function under test (static, but callable directly -- same TU via #include "func.c").
     * Fold its result's CONTENT only -- never a pointer/address. */
    cJSON_bool ret = add_item_to_array(array, item);
    long r = (long)ret;
    vb_mix(&r, sizeof r);

    int after_count = cJSON_GetArraySize(array);
    vb_mix(&after_count, sizeof after_count);

    int t = item->type;
    vb_mix(&t, sizeof t);
    long vi = (long)item->valueint;
    vb_mix(&vi, sizeof vi);
    vb_mix_d(item->valuedouble);

    /* structural check: the node passed in as `item` must now be reachable from `array` at
     * index 0 -- fold the EQUALITY RESULT, never the pointers themselves. */
    cJSON *found = cJSON_GetArrayItem(array, 0);
    int matches = (found == item) ? 1 : 0;
    vb_mix(&matches, sizeof matches);

    cJSON_Delete(array);   /* frees `array`; also frees `item` iff the call actually linked it */
  } else if (item) {
    cJSON_Delete(item);    /* `array` alloc failed: `item` was never linked, free it separately */
  } else if (array) {
    cJSON_Delete(array);
  }

  /* neutralise cJSON.c's own allocator-hook table (three function pointers into this same
   * image) before the raw [.data,.bss) dump -- see the top-of-file note. Not func0's state. */
  memset(&global_hooks, 0, sizeof(global_hooks));

  vb_dump(argc>2?argv[2]:NULL);
  return 0;
}
