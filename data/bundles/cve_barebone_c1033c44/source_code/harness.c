/* cve_barebone direct-call harness for CVE-2020-36401 (mruby)
 * Target: mrb_realloc  (src/gc.c)
 * Bug class: double-free / use-after-free (CWE-415/CWE-416), fix commit
 *   97319697c8f9f6ff27b32589947e1918e3015503 "Cancel 9cdf439 - Should not
 *   free the pointer in `realloc` since it can cause use-after-free
 *   problem.": on an allocation failure (p2 == NULL) the vulnerable
 *   mrb_realloc unconditionally calls `mrb_free(mrb, p)` and then raises a
 *   *rescuable* Ruby-level NoMemoryError. If the caller rescues that
 *   exception, the C object that owned `p` still holds the now-freed
 *   pointer value (mrb_realloc never got to report success/failure back
 *   into the caller's field), so the NEXT allocator activity on that same
 *   stale pointer double-frees / use-after-frees it. That is exactly what
 *   this harness reproduces: drive a real allocation-failure condition
 *   through mrb_realloc twice on the SAME buffer -- the first call frees it
 *   (the bug), the second call's `mrb_free(mrb, p);` (mrb_realloc's own
 *   line, unmodified) is the double free ASAN catches.
 *
 * mrb_state/mrb_gc below are reduced to the REAL fields (real names, real
 * types) mrb_realloc / mrb_realloc_simple / mrb_free actually dereference
 * (allocf, allocf_ud, gc.heaps, gc.out_of_memory); the rest of the upstream
 * mrb_state (class table, symbol table, VM context, ...) is untouched by
 * these functions and is not needed to link with just -lm.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- src/mrbconf.h ---- */
#ifndef FALSE
# define FALSE 0
#endif
#ifndef TRUE
# define TRUE 1
#endif

/* ---- include/mruby/common.h ---- */
#define MRB_API extern

/* ---- include/mruby/value.h ---- */
typedef uint8_t mrb_bool;

/* ---- include/mruby.h ---- */
struct mrb_state;
typedef void* (*mrb_allocf) (struct mrb_state *mrb, void*, size_t, void *ud);
struct mrb_jmpbuf;

/* ---- include/mruby/gc.h : mrb_gc, REAL struct, verbatim (only .heaps and
 * .out_of_memory are touched by the functions under test; mrb_heap_page and
 * RBasic stay opaque -- their contents are never dereferenced here). ---- */
struct mrb_heap_page;
struct RBasic;

typedef enum {
  MRB_GC_STATE_ROOT = 0,
  MRB_GC_STATE_MARK,
  MRB_GC_STATE_SWEEP
} mrb_gc_state;

typedef struct mrb_gc {
  struct mrb_heap_page *heaps;             /* heaps for GC */
  struct mrb_heap_page *sweeps;
  struct mrb_heap_page *free_heaps;
  size_t live;
  struct RBasic **arena;
  int arena_capa;
  int arena_idx;

  mrb_gc_state state;
  int current_white_part;
  struct RBasic *gray_list;
  struct RBasic *atomic_gray_list;
  size_t live_after_mark;
  size_t threshold;
  int interval_ratio;
  int step_ratio;
  mrb_bool iterating     :1;
  mrb_bool disabled      :1;
  mrb_bool full          :1;
  mrb_bool generational  :1;
  mrb_bool out_of_memory :1;
  size_t majorgc_old_threshold;
} mrb_gc;

/* ---- include/mruby.h : mrb_state, reduced to the fields actually
 * dereferenced by mrb_realloc/mrb_realloc_simple/mrb_free (real names,
 * real types); the dozens of unrelated class-table/VM/symtab fields on the
 * upstream struct are never touched by these functions. ---- */
typedef struct mrb_state {
  struct mrb_jmpbuf *jmp;
  mrb_allocf allocf;                      /* memory allocation function */
  void *allocf_ud;                        /* auxiliary data of allocf */
  mrb_gc gc;
} mrb_state;

/* ---- forward decls (real names/signatures) for mrb_realloc's callees.
 * noinline via a SEPARATE prototype so the crash-site frame (mrb_realloc
 * itself) always survives in the ASAN backtrace; this does not touch the
 * verbatim DEFINITIONS below in any way. ---- */
MRB_API void *mrb_realloc_simple(mrb_state *mrb, void *p, size_t len) __attribute__((noinline));
MRB_API void  mrb_free(mrb_state *mrb, void *p) __attribute__((noinline));
void mrb_raise_nomemory(mrb_state *mrb) __attribute__((noinline));
void mrb_full_gc(mrb_state *mrb) __attribute__((noinline));
void *mrb_realloc(mrb_state *mrb, void *p, size_t len) __attribute__((noinline));

/* ==== src/gc.c: mrb_realloc_simple, VERBATIM (real callee, directly on the
 * crash path -- mrb_realloc's first statement calls it). ==== */
MRB_API void*
mrb_realloc_simple(mrb_state *mrb, void *p,  size_t len)
{
  void *p2;

  p2 = (mrb->allocf)(mrb, p, len, mrb->allocf_ud);
  if (!p2 && len > 0 && mrb->gc.heaps) {
    mrb_full_gc(mrb);
    p2 = (mrb->allocf)(mrb, p, len, mrb->allocf_ud);
  }

  return p2;
}

/* ==== src/gc.c: mrb_free, VERBATIM (real callee, directly on the crash
 * path -- the line mrb_realloc calls that performs the actual free). ==== */
MRB_API void
mrb_free(mrb_state *mrb, void *p)
{
  (mrb->allocf)(mrb, p, 0, mrb->allocf_ud);
}

/* Minimal faithful stub: mrb_realloc_simple only calls mrb_full_gc when
 * gc.heaps is non-NULL, which this harness never sets (heaps stays NULL
 * throughout), so this body is never exercised on any input -- a full GC
 * needs the whole object subsystem, incidental to this bug. */
void
mrb_full_gc(mrb_state *mrb)
{
  (void)mrb;
}

/* Minimal faithful stub for mrb_raise_nomemory. Real mruby raises a
 * catchable Ruby-level NoMemoryError and (mrb_noreturn) longjmps to the
 * nearest rescue handler; that propagation mechanism is incidental to the
 * memory-safety fault itself, which is already committed by the time this
 * is reached (mrb_realloc's own `mrb_free(mrb, p);` line, immediately
 * above the call, already ran). Returning normally here stands in for "the
 * NoMemoryError is rescued and the caller resumes" -- precisely the
 * scenario the fix commit's message describes -- letting the harness
 * re-drive mrb_realloc on the caller's now-stale pointer below. */
void
mrb_raise_nomemory(mrb_state *mrb)
{
  mrb->gc.out_of_memory = TRUE;
}

/* ==== VERBATIM from data_cve/cve_c1033c44/target/original_function.c
 * (src/gc.c:220-237). Do not edit. ==== */
MRB_API void*
mrb_realloc(mrb_state *mrb, void *p, size_t len)
{
  void *p2;

  p2 = mrb_realloc_simple(mrb, p, len);
  if (len == 0) return p2;
  if (p2 == NULL) {
    mrb_free(mrb, p);
    mrb->gc.out_of_memory = TRUE;
    mrb_raise_nomemory(mrb);
  }
  else {
    mrb->gc.out_of_memory = FALSE;
  }

  return p2;
}
/* ==== end verbatim ==== */

/* Harness allocator: an `mrb_allocf` must behave like realloc() (NULL ptr
 * -> allocate, size 0 -> free), per mruby.h's documented contract. A global
 * flag lets the crafted input select "the allocator is out of memory"
 * (force_fail) -- modelling the real-world sustained-OOM condition
 * mrb_realloc's own logic exists to handle, driven by the corpus below. */
static int g_force_fail = 0;

__attribute__((noinline))
static void *
bench_allocf(mrb_state *mrb, void *ptr, size_t size, void *ud)
{
  (void)mrb; (void)ud;
  if (size == 0) {
    free(ptr);
    return NULL;
  }
  if (g_force_fail) {
    return NULL;
  }
  return realloc(ptr, size);
}

__attribute__((noinline))
static unsigned char *
read_file(const char *path, size_t *out_n)
{
  unsigned char *buf = NULL;
  size_t n = 0;
  FILE *f = fopen(path, "rb");
  if (f) {
    if (fseek(f, 0, SEEK_END) == 0) {
      long sz = ftell(f);
      if (sz > 0) {
        rewind(f);
        buf = (unsigned char *)malloc((size_t)sz);
        if (buf) {
          n = fread(buf, 1, (size_t)sz, f);
        }
      }
    }
    fclose(f);
  }
  *out_n = n;
  return buf;
}

int
main(int argc, char **argv)
{
  if (argc < 2) return 0;

  size_t n = 0;
  unsigned char *data = read_file(argv[1], &n);
  unsigned char b0 = n > 0 ? data[0] : 0;
  unsigned char b1 = n > 1 ? data[1] : 0;
  unsigned char b2 = n > 2 ? data[2] : 0;
  free(data);

  /* FDP-style argument construction from the input bytes. */
  size_t len  = 16 + (size_t)(b1 % 64);            /* 16..79: a small,
                                                        always-satisfiable
                                                        real allocation */
  size_t len2 = len + 8 + (size_t)(b2 % 32);        /* the "grow" request */

  mrb_state st;
  memset(&st, 0, sizeof(st));
  st.jmp = NULL;
  st.allocf = bench_allocf;
  st.allocf_ud = NULL;
  st.gc.heaps = NULL;             /* keep mrb_realloc_simple's full-GC retry
                                      branch inert (incidental subsystem) */
  st.gc.out_of_memory = FALSE;

  /* The "object" buffer mrb_realloc will manage, allocated through the
   * SAME allocator mrb_realloc itself uses. */
  void *p = bench_allocf(&st, NULL, len, st.allocf_ud);
  if (!p) return 0;

  if (b0 & 1) {
    /* TRIGGERING: sustained allocator OOM. The 1st mrb_realloc call's
     * failed realloc makes it free `p` internally (the CVE) and then
     * "raise" (our stub returns instead of unwinding, standing in for a
     * rescued NoMemoryError so the caller -- main, here -- resumes with
     * `p` still holding the now-freed address, exactly like a real
     * caller's un-updated object field). The 2nd call re-enters the same
     * failure path on that stale `p`: its `mrb_free(mrb, p);` -- a line of
     * mrb_realloc's own, unmodified body -- is the double free. */
    g_force_fail = 1;
    void *r1 = mrb_realloc(&st, p, len2);
    (void)r1;
    void *r2 = mrb_realloc(&st, p, len2);   /* crashes inside mrb_realloc's
                                                own mrb_free(mrb, p) call */
    (void)r2;
  } else {
    /* SAFE: the allocator succeeds, mrb_realloc simply grows `p` (taking
     * its "else" success branch) and returns the buffer; freed once,
     * cleanly, no failure path touched. */
    g_force_fail = 0;
    void *r = mrb_realloc(&st, p, len2);
    if (r) {
      memset(r, 0, len2);
      mrb_free(&st, r);
    }
  }

  return 0;
}
