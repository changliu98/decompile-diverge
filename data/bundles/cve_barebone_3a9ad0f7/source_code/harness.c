/* cve_barebone direct-call harness for CVE-2026-22770 (imagemagick)
 * Target: AcquireBilateralTLS  (MagickCore/effect.c)
 * Bug class: invalid-free / CWE-590 (Free of Memory Not on the Heap)
 *
 *   AcquireBilateralTLS allocates `number_threads+1` pointer slots but the guard memset
 *   only zeroes `number_threads` of them:
 *
 *       weights=(double **) AcquireQuantumMemory(number_threads+1,sizeof(*weights));
 *       ...
 *       (void) memset(weights,0,number_threads*sizeof(*weights));   // BUG: should be (number_threads+1)*..
 *       for (i=0; i <= (ssize_t) number_threads; i++)
 *       {
 *         weights[i]=(double *) AcquireQuantumMemory(width,height*sizeof(**weights));
 *         if (weights[i] == (double *) NULL)
 *           return(DestroyBilateralTLS(number_threads,weights));
 *       }
 *
 *   So slot weights[number_threads] (the LAST slot, one past what memset covers) starts
 *   life as uninitialized heap garbage. If any AcquireQuantumMemory call INSIDE the loop
 *   fails at an index i < number_threads (a normal allocation-failure/resource-limit path
 *   -- this is production code reacting to `-limit memory`/OOM, not a hypothetical), the
 *   function bails out via DestroyBilateralTLS() *before* the loop ever reaches index
 *   number_threads, so that last slot is NEVER assigned:
 *
 *       for (i=0; i <= (ssize_t) number_threads; i++)
 *         if (weights[i] != (double *) NULL)
 *           weights[i]=(double *) RelinquishMagickMemory(weights[i]);   // frees GARBAGE
 *
 *   DestroyBilateralTLS only skips a slot that is exactly NULL; the never-written garbage
 *   slot is essentially never NULL, so RelinquishMagickMemory (-> free()) is handed an
 *   uninitialized "pointer" -- an invalid free. The upstream fix (commit
 *   3e0330721020e0c5bb52e4b77c347527dd71658e) widens the memset to
 *   `(number_threads+1)*sizeof(*weights)`.
 *
 *   The fix commit *also* adds a `HeapOverflowSanityCheckGetSize(height,...)` guard for a
 *   SEPARATE integer-overflow issue in the `width,height*sizeof(**weights)` size computation
 *   whose fallout lands in a distant caller, not inside this function's own body -- that part
 *   is not reproduced here (this harness targets the invalid-free that manifests directly
 *   inside AcquireBilateralTLS/DestroyBilateralTLS).
 *
 * AcquireQuantumMemory/RelinquishMagickMemory are MagickCore's custom allocator entry points
 * (MagickCore/memory.c): real AcquireQuantumMemory ends up calling a private free-list heap
 * (or plain malloc, depending on build config) gated by an overflow check and a configurable
 * "max memory request" policy; real RelinquishMagickMemory symmetrically releases through the
 * same layer. Pulling that whole allocator (semaphores, policy lookups, a private coalescing
 * heap) in verbatim is unrelated to this bug, so both are minimal faithful stubs here: the
 * overflow guard is preserved, and mid-sequence allocation failure is made attacker-selectable
 * (standing in for the real "resource limit hit while allocating the i-th thread buffer" path)
 * via a call-index counter; RelinquishMagickMemory genuinely calls free() so that handing it
 * the garbage slot is a real, ASAN-visible invalid free -- exactly like production.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 *   + harness.flags: -fno-inline   (keeps AcquireBilateralTLS/DestroyBilateralTLS/
 *     RelinquishMagickMemory as distinct frames in the ASAN backtrace at -O1; changes no
 *     semantics, touches no function's text)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <sys/types.h>   /* ssize_t */

/* ---- Minimal faithful stand-ins for MagickCore's allocator layer (see header comment). ---- */
static unsigned long qm_call_index = 0;
static unsigned long qm_fail_at = (unsigned long) -1;   /* which 0-based call fails; -1 = never */

static void *AcquireQuantumMemory(const size_t count,const size_t quantum)
{
  size_t size;
  unsigned long my_call;

  if ((quantum != 0) && (count > (SIZE_MAX / quantum)))
    return (void *) NULL;                 /* overflow guard, mirrors HeapOverflowSanityCheckGetSize */
  size = count * quantum;
  my_call = qm_call_index++;
  if (my_call == qm_fail_at)
    return (void *) NULL;                 /* simulated allocation failure (resource-limit stand-in) */
  return malloc(size == 0 ? 1 : size);
}

static void *RelinquishMagickMemory(void *memory)
{
  if (memory == (void *) NULL)
    return (void *) NULL;
  free(memory);                           /* real free() -- a garbage arg is a genuine invalid-free */
  return (void *) NULL;
}

/* ==== VERBATIM from source_code/MagickCore/effect.c (real callee on the crash path) ==== */
static double **DestroyBilateralTLS(const size_t number_threads,
  double **weights)
{
  ssize_t
    i;

  assert(weights != (double **) NULL);
  for (i=0; i <= (ssize_t) number_threads; i++)
    if (weights[i] != (double *) NULL)
      weights[i]=(double *) RelinquishMagickMemory(weights[i]);
  weights=(double **) RelinquishMagickMemory(weights);
  return(weights);
}
/* ==== end verbatim (DestroyBilateralTLS) ==== */

/* ==== VERBATIM from data_cve/cve_3a9ad0f7/target/original_function.c ==== */
static double **AcquireBilateralTLS(const size_t number_threads,
  const size_t width,const size_t height)
{
  double
    **weights;

  ssize_t
    i;

  weights=(double **) AcquireQuantumMemory(number_threads+1,sizeof(*weights));
  if (weights == (double **) NULL)
    return((double **) NULL);
  (void) memset(weights,0,number_threads*sizeof(*weights));
  for (i=0; i <= (ssize_t) number_threads; i++)
  {
    weights[i]=(double *) AcquireQuantumMemory(width,height*sizeof(**weights));
    if (weights[i] == (double *) NULL)
      return(DestroyBilateralTLS(number_threads,weights));
  }
  return(weights);
}
/* ==== end verbatim (AcquireBilateralTLS) ==== */

static unsigned long long read_u64(const unsigned char *buf,size_t n,size_t off,
  unsigned long long dflt)
{
  unsigned long long v;
  size_t i;

  if (off + 8 > n)
    return dflt;
  v = 0;
  for (i = 0; i < 8; i++)
    v |= ((unsigned long long) buf[off + i]) << (8 * i);
  return v;
}

int main(int argc,char **argv)
{
  FILE *f;
  long sz;
  unsigned char *buf;
  size_t n;
  unsigned long long number_threads, width, height, fail_at;
  double **weights;

  if (argc < 2)
    return 0;
  f = fopen(argv[1], "rb");
  if (!f)
    return 0;
  if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
  sz = ftell(f);
  if (sz < 0) { fclose(f); return 0; }
  if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

  /* HEAP-allocate the input so ASAN guards it (the harness's own read buffer, not the bug). */
  buf = (unsigned char *) malloc((size_t) sz > 0 ? (size_t) sz : 1);
  if (!buf) { fclose(f); return 0; }
  n = fread(buf, 1, (size_t) sz, f);
  fclose(f);

  /* FDP-style argument construction: 4 little-endian u64 fields (missing/short -> defaults). */
  number_threads = read_u64(buf, n, 0, 3);
  width          = read_u64(buf, n, 8, 4);
  height         = read_u64(buf, n, 16, 4);
  fail_at        = read_u64(buf, n, 24, (unsigned long long) -1);
  free(buf);

  /* Bound the attacker-controlled sizes so the HARNESS's own scaffolding stays small & fast.
   * Does not touch AcquireBilateralTLS's logic -- only the values we hand it as arguments. */
  if (number_threads == 0) number_threads = 1;
  if (number_threads > 16) number_threads = (number_threads % 16) + 1;
  if (width == 0) width = 1;
  if (width > 64) width = (width % 64) + 1;
  if (height == 0) height = 1;
  if (height > 64) height = (height % 64) + 1;

  qm_call_index = 0;
  qm_fail_at = (unsigned long) fail_at;

  weights = AcquireBilateralTLS((size_t) number_threads,(size_t) width,(size_t) height);
  if (weights != (double **) NULL)
    weights = DestroyBilateralTLS((size_t) number_threads, weights);

  return 0;
}
