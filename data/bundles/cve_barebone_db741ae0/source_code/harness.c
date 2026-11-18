/*
 * Decompile-Diverge direct-call harness -- cve_db741ae0 (lighttpd1.4, redmine #2945 /
 * "SIGABRT during GET request handling with url-path-2f-decode enabled")
 *
 * TARGET FUNCTION (embedded VERBATIM below, unmodified): burl_normalize_2F_to_slash_fix
 *   src/burl.c, pre-fix (vulnerable) revision:
 *
 *     static int burl_normalize_2F_to_slash_fix (buffer *b, int qs, int i)
 *     {
 *         char * const s = b->ptr;
 *         const int blen = (int)buffer_string_length(b);
 *         const int used = qs < 0 ? blen : qs;
 *         int j = i;
 *         for (; i < used; ++i, ++j) {
 *             s[j] = s[i];
 *             if (s[i] == '%' && s[i+1] == '2' && s[i+2] == 'F') {
 *                 s[j] = '/';
 *                 i+=2;
 *             }
 *         }
 *         if (qs >= 0) {
 *             memmove(s+j, s+qs, blen - qs);
 *             j += blen - qs;
 *         }
 *         buffer_string_set_length(b, j);
 *         return qs;
 *     }
 *
 * Bug (fix commit 32120d5b8b3203fc21ccb9eafb0eaf824bb59354, "fix abort in
 * http-parseopts", x-ref redmine #2945): the function is only ever memory-safe
 * for callers that guarantee the invariant  0 <= i <= qs <= blen  (qs is
 * supposed to be the CURRENT position of the query-string '?' within the
 * CURRENT buffer b, and i the position where a "%2F" run starts, both found
 * by a fresh scan of b immediately before the call). The fix itself patches a
 * DIFFERENT symptom of the same root cause -- burl_normalize_2F_to_slash_fix
 * returns the OLD, now-stale "qs" even though its own body just shrank the
 * buffer (collapsing "%2F" -> '/'), so a caller that trusts the returned qs
 * against the NEW (shorter) buffer length is handed an out-of-range offset.
 * That same "qs no longer matches the buffer it is being applied to"
 * mismatch, reproduced directly as *this call's own arguments* (qs greater
 * than the buffer's actual current length), is a memory-safety fault fully
 * INSIDE burl_normalize_2F_to_slash_fix's own body, with no other project
 * code involved:
 *
 *   - blen = buffer_string_length(b) is fixed at function entry.
 *   - used = qs (when qs>=0) becomes the loop's upper bound on i.
 *   - if qs is (attacker-controlled, e.g. stale-from-a-prior-shrink) greater
 *     than blen+1, the loop `for (; i<used; ++i,++j) { s[j]=s[i]; ... }`
 *     walks i past the allocated buffer -- `s[j] = s[i];`'s read of s[i]
 *     goes 1+ byte past the heap allocation the instant i exceeds blen (the
 *     allocation is sized exactly blen+1 bytes: content + NUL, matching how
 *     lighttpd's own buffer_realloc/buffer_string_set_length size buffers to
 *     tight power-of-64 multiples of the logical length, not oversized slack
 *     the caller can rely on) => a deterministic ASAN heap-buffer-overflow
 *     READ (CWE-125), squarely inside this function's own for-loop, on the
 *     very first line of the loop body -- no callback, no downstream caller,
 *     no elaborate object state, just the (buffer*, int qs, int i) argument
 *     triple the function itself is declared to take.
 *
 * This is the qs-desynchronized-from-blen condition the security fix exists
 * to prevent (the fix's own added line, `qs = j;`, keeps the RETURNED qs in
 * sync with the buffer's new length after the collapse -- i.e. it is
 * precisely a "keep qs <= blen" fix, just phrased in terms of the *next*
 * call's argument rather than this one's). We exercise the same
 * qs>blen desync condition directly as this call's inputs.
 *
 * Harness I/O contract (all attacker bytes live in a single HEAP buffer,
 * required so ASAN can catch the out-of-bounds access):
 *   argv[1] file layout:
 *     byte[0]     mode selector: bit0 0 => SAFE call (qs kept <= blen,
 *                 exercising the function's normal, in-bounds behavior,
 *                 including the %2F collapse + memmove tail-copy paths),
 *                 bit0 1 => TRIGGER call (qs deliberately desynchronized
 *                 to exceed blen+1, walking the loop off the end of the
 *                 buffer).
 *     byte[1]     submode / gap selector (meaning depends on mode, see
 *                 build_case() in gen_corpus.py).
 *     byte[2]     start-index selector for argument `i` (reduced modulo
 *                 the content length so it always starts in-bounds).
 *     byte[3..]   the buffer's own content bytes (b->ptr[0..blen)); if
 *                 empty, a fixed 8-byte fallback content is used so blen
 *                 is never 0.
 *
 *   main() reads argv[1] into a heap "raw" buffer, derives (content, qs, i)
 *   from it per the layout above, allocates a SEPARATE, TIGHTLY-sized heap
 *   allocation of exactly content_len+1 bytes for the real lighttpd `buffer`
 *   struct's b->ptr (content bytes + NUL terminator -- no slack, so ASAN's
 *   heap redzone begins immediately after byte [content_len]), and calls
 *   burl_normalize_2F_to_slash_fix(&b, qs, i) exactly once -- the same call
 *   burl_normalize_2F_to_slash() makes in the real code.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * REAL type definitions, copied verbatim from src/buffer.h.
 * ============================================================ */

typedef struct {
    char *ptr;

    /* "used" includes a terminating 0 */
    size_t used;
    /* size of allocated buffer at *ptr */
    size_t size;
} buffer;

#define __attribute_noreturn__ __attribute__((__noreturn__))
#define LI_NORETURN __attribute_noreturn__

void log_failed_assert(const char *filename, unsigned int line, const char *msg) LI_NORETURN;

#define force_assert(x) do { if (!(x)) log_failed_assert(__FILE__, __LINE__, "assertion failed: " #x); } while(0)

static inline size_t buffer_string_length(const buffer *b) {          /* buffer.h, verbatim */
    return NULL != b && 0 != b->used ? b->used - 1 : 0;
}

/* ============================================================
 * REAL callees, embedded verbatim from src/buffer.c (the only
 * functions burl_normalize_2F_to_slash_fix's own body calls besides
 * memmove()): buffer_string_set_length() -> buffer_realloc().
 * log_failed_assert() itself (declared LI_NORETURN, defined only as a
 * fprintf+fatal error path in log.c using server-wide logging state we
 * don't have) is replaced by a minimal faithful stand-in with the same
 * noreturn contract (abort on assertion failure) -- the "incidental
 * callee" allowance.
 * ============================================================ */

void log_failed_assert(const char *filename, unsigned int line, const char *msg) {
    fprintf(stderr, "%s:%u: %s\n", filename, line, msg);
    abort();
}

#define BUFFER_PIECE_SIZE 64uL  /*(must be power-of-2)*/

__attribute__((__cold__))
static void buffer_realloc(buffer *b, size_t len) {                    /* buffer.c, verbatim */
    const size_t sz = (len + 1 + BUFFER_PIECE_SIZE-1) & ~(BUFFER_PIECE_SIZE-1);
    force_assert(sz > len);

    b->size = sz;
    b->ptr = realloc(b->ptr, sz);

    force_assert(NULL != b->ptr);
}

void buffer_string_set_length(buffer *b, size_t len) {                 /* buffer.c, verbatim */
    force_assert(NULL != b);

    if (len >= b->size) buffer_realloc(b, len);

    b->used = len + 1;
    b->ptr[len] = '\0';
}

/* ============================================================
 * TARGET FUNCTION, embedded VERBATIM (byte-for-byte from
 * target/original_function.c): src/burl.c burl_normalize_2F_to_slash_fix()
 * ============================================================ */

static int burl_normalize_2F_to_slash_fix (buffer *b, int qs, int i)
{
    char * const s = b->ptr;
    const int blen = (int)buffer_string_length(b);
    const int used = qs < 0 ? blen : qs;
    int j = i;
    for (; i < used; ++i, ++j) {
        s[j] = s[i];
        if (s[i] == '%' && s[i+1] == '2' && s[i+2] == 'F') {
            s[j] = '/';
            i+=2;
        }
    }
    if (qs >= 0) {
        memmove(s+j, s+qs, blen - qs);
        j += blen - qs;
    }
    buffer_string_set_length(b, j);
    return qs;
}

/* ============================================================
 * main() -- reads argv[1] into a HEAP buffer, derives (content, qs, i),
 * builds a real `buffer` struct with a TIGHTLY-sized heap allocation for
 * b.ptr, and calls burl_normalize_2F_to_slash_fix() exactly once.
 * ============================================================ */

static const uint8_t FALLBACK_CONTENT[8] = "abcdefg"; /* 7 chars + NUL byte in array, blen=7 if used */

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("fopen");
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long fsz = ftell(f);
    if (fsz < 0) fsz = 0;
    fseek(f, 0, SEEK_SET);

    /* Attacker-controlled data MUST live on the heap so ASAN can catch an
     * out-of-bounds access into/around it. */
    size_t alloc_len = (size_t) fsz > 0 ? (size_t) fsz : 1;
    uint8_t *raw = (uint8_t *) malloc(alloc_len);
    if (!raw) { fclose(f); return 1; }
    size_t raw_len = fsz > 0 ? fread(raw, 1, (size_t) fsz, f) : 0;
    fclose(f);

    uint8_t mode = raw_len > 0 ? raw[0] : 0;
    uint8_t sub  = raw_len > 1 ? raw[1] : 0;
    uint8_t isel = raw_len > 2 ? raw[2] : 0;

    const uint8_t *content;
    size_t content_len;
    if (raw_len > 3) {
        content = raw + 3;
        content_len = raw_len - 3;
    } else {
        content = FALLBACK_CONTENT;
        content_len = 7; /* "abcdefg", no embedded NUL */
    }
    if (content_len == 0) { content = FALLBACK_CONTENT; content_len = 7; }

    int blen = (int) content_len;

    /* SEPARATE, TIGHTLY-sized heap allocation for b.ptr: exactly
     * blen+1 bytes (content + NUL terminator), no slack -- so ASAN's
     * redzone begins immediately at offset blen+1, matching how
     * buffer_realloc/buffer_string_set_length size real lighttpd
     * buffers to the logical length (rounded to a small fixed piece
     * size), never to arbitrary caller-assumed slack. */
    char *bp = (char *) malloc((size_t) blen + 1);
    if (!bp) { free(raw); return 1; }
    memcpy(bp, content, (size_t) blen);
    bp[blen] = '\0';

    buffer b;
    b.ptr = bp;
    b.used = (size_t) blen + 1;
    b.size = (size_t) blen + 1;

    int qs, i;

    if (mode & 1) {
        /* TRIGGER: desynchronize qs from blen (qs > blen+1) so the loop's
         * own `for (; i<used; ++i,++j) { s[j]=s[i]; ... }` walks i past
         * the tightly-sized allocation -- a deterministic heap-buffer-
         * overflow READ inside burl_normalize_2F_to_slash_fix's own body. */
        int gap = 2 + (int) (sub % 40);           /* qs = blen + gap, gap in [2,41] */
        qs = blen + gap;
        int istart = blen > 0 ? (int) (isel % (uint8_t) (blen > 8 ? 8 : blen)) : 0;
        i = istart;                                /* always < blen, always in-bounds start */
    } else {
        /* SAFE: keep the 0 <= i <= qs <= blen invariant the function
         * actually needs, exercising its normal in-bounds behavior
         * (with/without a query-string tail, with/without %2F content). */
        switch (sub % 5) {
            case 0: qs = -1; break;                          /* no query-string branch */
            case 1: qs = blen; break;                         /* qs==blen: memmove copies 0 bytes */
            case 2: qs = blen / 2; break;                      /* mid-buffer qs */
            case 3: qs = blen > 0 ? blen - 1 : 0; break;        /* qs one below blen */
            default: qs = blen; break;
        }
        if (qs < 0) {
            i = blen > 0 ? (int) (isel % (uint8_t) (blen > 8 ? 8 : blen)) : 0;
        } else {
            int cap = qs > 0 ? qs : 1;
            int capb = cap > 8 ? 8 : cap;
            i = (int) (isel % (uint8_t) capb);
            if (i > qs) i = qs;
        }
    }

    int rv = burl_normalize_2F_to_slash_fix(&b, qs, i);
    fprintf(stderr, "burl_normalize_2F_to_slash_fix returned %d (blen=%d qs=%d i=%d mode=%u)\n",
            rv, blen, qs, i, (unsigned) mode);

    free(b.ptr);
    free(raw);
    return 0;
}
