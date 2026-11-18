/* BYOH memstate harness for the github functional axis.
 *
 * TARGET SIGNATURE:
 *   CJSON_PUBLIC(cJSON*) cJSON_AddNumberToObject(cJSON * const object,
 *                                                 const char * const name,
 *                                                 const double number)
 *   -- creates a new number item (cJSON_CreateNumber(number)) and appends it to `object`
 *   under key `name` via the internal add_item_to_object()/add_item_to_array(); returns
 *   the new node on success, or NULL (after deleting the orphaned node) on failure. Both
 *   `object` (struct pointer PARAM) and the RETURN (struct pointer) are things the AUTO
 *   harness generator can't synthesise -> BYOH. Modelled directly on the validated
 *   cjson_cJSON_AddArrayToObject.c BYOH (same object/name scaffold), with the extra
 *   `number` argument and the Number-specific fields (valueint/valuedouble) folded in.
 *
 * FIXED CONSTANTS / SETUP:
 *   `object` is a freshly created EMPTY object (`cJSON_CreateObject()`) -- this function
 *   doesn't need any pre-existing fields to retrieve, just a valid non-NULL object to
 *   mutate, so parsing a JSON literal would be unnecessary ceremony. `add_item_to_object`/
 *   `add_item_to_array` only fail on NULL args or `object == item` (never true here: the
 *   number item is fresh), so the call always takes the SUCCESS path for our always-valid
 *   (non-NULL object, non-NULL name) inputs -- the interesting signal is therefore whether
 *   the callee actually performed the mutation, not which branch it took.
 *
 *   `name` is a short, seed-derived lowercase string (0..10 chars, always NUL-terminated
 *   in-buffer) used as the new key. `number` is a seed-derived double via vb_dbl() (bounded
 *   +-1000, three decimal digits) -- well inside int range so cJSON_CreateNumber's overflow
 *   saturation never triggers, keeping valueint a deterministic function of the seed.
 *
 * WHAT'S FOLDED (content only, never an address):
 *   - `has_root`/`has_num`: NULL-ness flags (booleans, not the pointers themselves).
 *   - `before_count`/`after_count`: `cJSON_GetArraySize(root)` before/after the call --
 *     the STRUCTURAL signal that the object actually gained a child (a stub that never
 *     mutates `object` leaves after_count == before_count == 0).
 *   - the returned node's CONTENT: `->type`, `->valueint`, `->valuedouble` (quantised),
 *     `->valuestring` (NULL for a number -- `vb_mix_s` folds the NULL marker byte), `->string`
 *     (the CONTENT of the strdup'd key, via `vb_mix_s` -- never the pointer), and whether
 *     `->child == NULL` (a number leaf has none). `cJSON_New_Item` zero-fills every field via
 *     memset, so fields cJSON_CreateNumber doesn't set are deterministic zeros, never
 *     uninitialised memory.
 *   - `matches`: whether `cJSON_GetObjectItem(root, name)` retrieves the SAME node the call
 *     returned -- folded as a boolean EQUALITY RESULT (0/1), never the pointer values being
 *     compared. Together with before/after_count this proves the returned node is really
 *     linked into `object` under `name`, not just a detached allocation.
 *
 *   A stub that neutralises the body to `return 0;` always yields has_num=0 and
 *   after_count==before_count==0 (no `if(item)` block ever runs), which disagrees with the
 *   real function's has_num=1 / after_count==1 on every input -- maximally discriminating.
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
 * `global_hooks` lands inside the dumped [.data,.bss) window on EVERY cjson bundle
 * (regardless of which function is targeted or whether it even runs -- it's a static
 * initializer applied at load time) and its content shifts with the PIE load base, i.e. it
 * is exactly the kind of address noise the memstate contract forbids folding. Verified by
 * an ASLR-on freeze probe (both this target AND the pre-existing cJSON_GetObjectItem BYOH
 * harness): those bytes -- and ONLY those bytes -- differ across a randomized-base rerun.
 * Fix: memset `global_hooks` back to all-zero bytes right after the call under test and
 * before vb_dump, on EVERY run (baseline capture AND eval-time candidate) -- so that region
 * of the dump is a deterministic constant, never a real address. This mirrors the
 * framework's own `__dso_handle` masking, just applied proactively in the harness since
 * `global_hooks` isn't a single well-known CRT symbol the infra already masks. func0 never
 * legitimately depends on `global_hooks`'s content surviving past its own call (it's an
 * allocator-hook table, not part of cJSON_AddNumberToObject's return/output contract), so
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

  /* `name`: a short, seed-derived lowercase key (0..10 chars, always NUL-terminated). */
  int _namelen = vb_len(10);
  char _name[11];
  for (int _k = 0; _k < _namelen; _k++) { _name[_k] = (char)('a' + (vb_take(1) % 26)); }
  _name[_namelen] = '\0';

  /* `number`: a seed-derived double, bounded well inside int range (no saturation). */
  double _number = vb_dbl();

  /* A fresh, always-valid object to mutate -- no parse needed (this function doesn't read
   * any pre-existing field, just appends a new child). */
  cJSON *root = cJSON_CreateObject();
  int has_root = (root != NULL) ? 1 : 0;
  vb_mix(&has_root, sizeof has_root);

  if (root) {
    int before_count = cJSON_GetArraySize(root);
    vb_mix(&before_count, sizeof before_count);

    /* The function under test. Fold its result's CONTENT only -- never the returned pointer
     * itself (an address would differ on every relink and masquerade as a silent vanish). */
    cJSON *item = cJSON_AddNumberToObject(root, _name, _number);
    int has_num = (item != NULL) ? 1 : 0;
    vb_mix(&has_num, sizeof has_num);

    int after_count = cJSON_GetArraySize(root);
    vb_mix(&after_count, sizeof after_count);

    if (item) {
      int t = item->type;
      vb_mix(&t, sizeof t);
      long vi = (long)item->valueint;
      vb_mix(&vi, sizeof vi);
      vb_mix_d(item->valuedouble);
      vb_mix_s(item->valuestring);
      vb_mix_s(item->string);
      int child_is_null = (item->child == NULL) ? 1 : 0;
      vb_mix(&child_is_null, sizeof child_is_null);

      /* structural check: the node the call returned must be the SAME one now reachable
       * from `root` under `name` -- fold the EQUALITY RESULT, never the pointers. */
      cJSON *found = cJSON_GetObjectItem(root, _name);
      int matches = (found == item) ? 1 : 0;
      vb_mix(&matches, sizeof matches);
    }

    cJSON_Delete(root);
  }

  /* neutralise cJSON.c's own allocator-hook table (three function pointers into this same
   * image) before the raw [.data,.bss) dump -- see the top-of-file note. Not func0's state. */
  memset(&global_hooks, 0, sizeof(global_hooks));

  vb_dump(argc>2?argv[2]:NULL);
  return 0;
}
