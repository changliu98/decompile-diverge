/* BYOH memstate harness for the github functional axis.
 *
 * TARGET SIGNATURE:
 *   CJSON_PUBLIC(cJSON *) cJSON_CreateString(const char *string)
 *   {
 *       cJSON *item = cJSON_New_Item(&global_hooks);
 *       if(item)
 *       {
 *           item->type = cJSON_String;
 *           item->valuestring = (char*)cJSON_strdup((const unsigned char*)string, &global_hooks);
 *           if(!item->valuestring)
 *           {
 *               cJSON_Delete(item);
 *               return NULL;
 *           }
 *       }
 *
 *       return item;
 *   }
 *   -- cJSON_New_Item allocates a fresh node (zero-filled via memset). This function stamps
 *   `item->type` = cJSON_String and `item->valuestring` = a freshly-allocated COPY of `string`
 *   (via cJSON_strdup). `cJSON_strdup(NULL, ...)` returns NULL immediately (see cJSON.c:188-207),
 *   so when `string` is NULL, `item->valuestring` stays NULL and this function deletes the node
 *   and returns NULL too -- a real, deterministic branch of the function, not an allocation-failure
 *   edge case. Returns a POINTER to the new item (or NULL) -> not seed-buildable/foldable directly
 *   (it's a struct pointer, not a scalar/cstr), so the AUTO harness generator can't synthesise this.
 *   Modelled directly on the validated cjson_cJSON_CreateBool.c / cjson_cJSON_CreateNumber.c BYOHs
 *   (identical freshly-created-detached-node idiom), swapping the argument for a seed-derived
 *   `char*` (built with the SAME cstr idiom the auto generator itself uses for `char*` params) and
 *   folding `valuestring`'s CONTENT instead of a numeric field.
 *
 * FIXED CONSTANTS / SETUP:
 *   `string` is the only argument. It is built with the standard vb_len(VB_STRLEN)+fill cstr
 *   idiom (0..24 printable-ASCII chars, always NUL-terminated in-buffer), PLUS one extra
 *   seed bit that can force the pointer itself to NULL -- covering the real
 *   `cJSON_CreateString(NULL)` early-return branch documented above. No crypto key/IV/nonce here.
 *
 * WHAT'S FOLDED (content only, never an address):
 *   - `has_item`: NULL-ness flag of the returned pointer (a boolean, not the pointer itself).
 *   - the returned node's CONTENT (only when non-NULL): `->type` (must be cJSON_String),
 *     `->valuestring` (must equal the seed-built input string byte-for-byte -- folded via
 *     vb_mix_s, i.e. its CONTENT, never the pointer), `->valueint`/`->valuedouble` (deterministic
 *     zeros -- cJSON_New_Item zero-fills every field via memset and this function never touches
 *     them), `->string` (NULL), and whether `->next`/`->prev`/`->child` are NULL (structural
 *     flags, never the pointers themselves -- a fresh detached node has none of these).
 *
 *   A stub that neutralises the body to `return 0;` always yields has_item=0 -- disagreeing with
 *   the real function's has_item=1 (whenever the seed-built string isn't the forced-NULL case,
 *   i.e. on roughly half of all inputs) and, whenever it does run, with a real valuestring COPY
 *   that a neutralised body never produces -- maximally discriminating, and it never dereferences
 *   the NULL pointer itself, so it scores as a silent WRONG_ANSWER (bundle-level DEVIATED), not a
 *   crash.
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
 * address noise the memstate contract forbids folding (see the cjson_cJSON_AddTrueToObject.c /
 * cjson_cJSON_AddNumberToObject.c / cjson_cJSON_CreateBool.c / cjson_cJSON_CreateNumber.c BYOHs,
 * which document the ASLR-on freeze probe that found this; the automatic relocation-masking in
 * functional.py's capture_baseline/replay_safe_inputs also neutralises this class of slot, but the
 * explicit memset below keeps this harness self-consistent with its closest siblings). Fix: memset
 * `global_hooks` back to all-zero bytes right after the call under test and before vb_dump, on
 * EVERY run (baseline capture AND eval-time candidate) -- so that region of the dump is a
 * deterministic constant, never a real address. func0 never legitimately depends on
 * `global_hooks`'s content surviving past its own call, so this cannot hide a real vanish. */
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

  /* `string`: the only argument -- the standard cstr idiom (a seed-derived length up to
   * VB_STRLEN, printable-ASCII fill, always NUL-terminated in-buffer), PLUS one extra seed bit
   * that can force the pointer itself to NULL -- covering the real `cJSON_CreateString(NULL)`
   * early-return branch (see top-of-file note). */
  int _force_null = (int)(vb_take(1) & 1);
  int _str_n = vb_len(VB_STRLEN);
  char _str[VB_STRLEN + 1];
  for (int _k = 0; _k < _str_n; _k++) { _str[_k] = (char)(32 + (vb_take(1) % 95)); }
  _str[_str_n] = '\0';
  const char *_string_arg = _force_null ? NULL : _str;

  /* The function under test. Fold its result's CONTENT only -- never the returned pointer
   * itself (an address would differ on every relink and masquerade as a silent vanish). */
  cJSON *item = cJSON_CreateString(_string_arg);
  int has_item = (item != NULL) ? 1 : 0;
  vb_mix(&has_item, sizeof has_item);

  if (item) {
    int t = item->type;
    vb_mix(&t, sizeof t);
    long vi = (long)item->valueint;
    vb_mix(&vi, sizeof vi);
    vb_mix_d(item->valuedouble);
    vb_mix_s(item->valuestring);
    vb_mix_s(item->string);

    int next_is_null = (item->next == NULL) ? 1 : 0;
    vb_mix(&next_is_null, sizeof next_is_null);
    int prev_is_null = (item->prev == NULL) ? 1 : 0;
    vb_mix(&prev_is_null, sizeof prev_is_null);
    int child_is_null = (item->child == NULL) ? 1 : 0;
    vb_mix(&child_is_null, sizeof child_is_null);

    cJSON_Delete(item);
  }

  /* neutralise cJSON.c's own allocator-hook table (three function pointers into this same
   * image) before the raw [.data,.bss) dump -- see the top-of-file note. Not func0's state. */
  memset(&global_hooks, 0, sizeof(global_hooks));

  vb_dump(argc>2?argv[2]:NULL);
  return 0;
}
