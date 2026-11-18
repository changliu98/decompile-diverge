/*
 * Direct-call crash harness for ddiv bundle cve_a387f3f2
 * (pjproject, pjlib-util/src/pjlib-util/scanner.c: pj_scan_skip_line).
 *
 * Upstream fix: pjsip/pjproject commit
 * c4d34984ec92b3d5252a7d5cddd85a1d3a8001ae ("Fixed several issues related
 * to scanning/parsing not-null-terminated buffer") adds, as the very
 * first statement of pj_scan_skip_line():
 *
 *     if (pj_scan_is_eof(scanner)) {
 *         return;
 *     }
 *
 * where pj_scan_is_eof() is defined (scanner.h) as
 *     scanner->curptr >= scanner->end
 *
 * The VULNERABLE body (embedded verbatim below) instead unconditionally
 * computes:
 *
 *     char *s = pj_memchr(scanner->curptr, '\n',
 *                          scanner->end - scanner->curptr);
 *
 * `scanner->end - scanner->curptr` is a pointer difference (signed,
 * ptrdiff_t). If some earlier scanner call has pushed scanner->curptr
 * *past* scanner->end (several sibling functions in this exact same
 * scanner.c -- pj_scan_get_n, pj_scan_get_newline, pj_scan_advance_n,
 * pj_scan_get_until*, ... -- advance curptr without checking against end,
 * and this SAME fix commit hardens every one of them with an added
 * pj_scan_is_eof() guard), the subtraction is negative. pj_memchr()'s
 * third parameter is pj_size_t, an alias of size_t (unsigned) -- so the
 * negative ptrdiff_t is reinterpreted as an enormous unsigned length.
 * pj_memchr() (a thin wrapper over libc memchr(), also embedded verbatim
 * below) then scans forward from scanner->curptr for up to that enormous
 * length looking for '\n', reading far past the end of whatever buffer
 * scanner->curptr pointed into: a heap-buffer-overflow READ (CWE-125).
 *
 * This harness reproduces the bug IN ISOLATION: it builds a pj_scanner
 * whose curptr/end fields are derived directly from attacker-controlled
 * input bytes and calls pj_scan_skip_line() on it directly -- no SIP/SDP
 * parser or any other pjproject subsystem is involved. It simply puts the
 * scanner into exactly the state (scanner->curptr > scanner->end) that
 * the missing pj_scan_is_eof() guard exists to reject.
 *
 * Input format (all bytes attacker-controlled, read from argv[1] into a
 * HEAP buffer):
 *   byte 0       mode: 0 => TRIGGERING (curptr pushed past end),
 *                       else => SAFE (curptr <= end, always)
 *   byte 1       curptr_raw  (SAFE mode only: an offset selector)
 *   byte 2       end_raw     (SAFE mode only: an offset selector)
 *   bytes 3..    "content": copied into its OWN heap allocation of
 *                exactly content_len bytes; the pj_scanner's
 *                begin/curptr/end fields index THIS allocation, so its
 *                ASAN redzone sits directly at content + content_len.
 *
 * TRIGGERING (mode==0): curptr is set to content+content_len (the legal
 * "one past the end" pointer value of the content allocation -- never
 * itself dereferenced by this harness), and end is set to content
 * (offset 0). Since content_len is always >= 1 (enforced in main()),
 * curptr is always strictly greater than end, so `end - curptr` is
 * always negative -- pj_memchr() then starts reading AT
 * content+content_len, the very first byte past the allocation: an
 * immediate, deterministic heap-buffer-overflow READ.
 *
 * SAFE (mode!=0): curptr and end are both offsets into [0, content_len],
 * sorted so curptr <= end always holds -- exactly the invariant every
 * other real caller maintains, and the one case the unfixed function
 * already handles correctly (whether or not a '\n' is found in-range).
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- pjlib/include/pj/config.h: PJ_DEF/PJ_DECL, export-nothing case ---- */
#define PJ_DEF(type)  type

/* ---- pjlib/include/pj/types.h ---- */
typedef size_t pj_size_t;      /* typedef size_t pj_size_t; */

/* ---- pjlib-util/include/pjlib-util/scanner.h: struct pj_scanner and its
 * syntax-error callback typedef -- verbatim field names/layout/order. ---- */
struct pj_scanner;
typedef void (*pj_syn_err_func_ptr)(struct pj_scanner *scanner);

typedef struct pj_scanner
{
    char *begin;        /* Start of input buffer.      */
    char *end;           /* End of input buffer.        */
    char *curptr;        /* Current pointer.            */
    int   line;           /* Current line.               */
    char *start_line;    /* Where current line starts.  */
    int   skip_ws;         /* Skip whitespace flag.      */
    pj_syn_err_func_ptr callback;   /* Syntax error callback. */
} pj_scanner;

/* ---- pjlib/include/pj/string.h: pj_memchr(), verbatim minus the
 * PJ_INLINE export-visibility macro (a plain wrapper over libc memchr()
 * either way). ---- */
static void *pj_memchr(const void *buf, int c, pj_size_t size)
{
    return (void *) memchr((void *) buf, c, size);
}

/* pj_scan_skip_line() never touches scanner->callback; this stub exists
 * only so the struct is fully populated with a valid function pointer. */
static void dummy_syntax_err(pj_scanner *scanner)
{
    (void) scanner;
}

/* noinline: forward declaration only, added SO THAT -O1 cannot inline
 * this single-call-site frame out of the symbolized crash stack; the
 * definition immediately below is the untouched, byte-for-byte verbatim
 * copy of target/original_function.c. */
PJ_DEF(void) pj_scan_skip_line( pj_scanner *scanner ) __attribute__((noinline));

/* ==================================================================
 * TARGET FUNCTION -- embedded VERBATIM from
 * data_cve/cve_a387f3f2/target/original_function.c. Do not modify.
 * ================================================================== */
PJ_DEF(void) pj_scan_skip_line( pj_scanner *scanner )
{
    char *s = pj_memchr(scanner->curptr, '\n', scanner->end - scanner->curptr);
    if (!s) {
	scanner->curptr = scanner->end;
    } else {
	scanner->curptr = scanner->start_line = s+1;
	scanner->line++;
   }
}
/* ================================================================== */

/* Harness-authored: build a pj_scanner directly from attacker-controlled
 * bytes (see the input-format comment at the top of this file). */
static void build_scanner(unsigned char *content, size_t content_len,
                           int mode, unsigned char curptr_raw, unsigned char end_raw,
                           pj_scanner *scanner)
{
    scanner->begin      = (char *) content;
    scanner->line       = 1;
    scanner->start_line = (char *) content;
    scanner->skip_ws    = 0;
    scanner->callback   = dummy_syntax_err;

    if (mode == 0) {
        /* TRIGGERING: curptr one-past content's own heap allocation,
         * end at its start -> end < curptr always -> negative length. */
        scanner->curptr = (char *) content + content_len;
        scanner->end    = (char *) content;
    } else {
        /* SAFE: sort so curptr <= end always holds. */
        size_t mod = content_len + 1;
        size_t a = (size_t) curptr_raw % mod;
        size_t b = (size_t) end_raw % mod;
        if (a > b) { size_t t = a; a = b; b = t; }
        scanner->curptr = (char *) content + a;
        scanner->end    = (char *) content + b;
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long fsz = ftell(f);
    if (fsz < 4) { fclose(f); return 0; }   /* 3-byte header + >=1 content byte */
    rewind(f);

    unsigned char *raw = (unsigned char *) malloc((size_t) fsz);
    if (!raw) { fclose(f); return 0; }
    size_t rd = fread(raw, 1, (size_t) fsz, f);
    fclose(f);
    if (rd < 4) { free(raw); return 0; }

    unsigned char mode       = raw[0];
    unsigned char curptr_raw = raw[1];
    unsigned char end_raw    = raw[2];
    size_t content_len = rd - 3;

    /* Content lives in its OWN heap allocation (decoupled from `raw`) so
     * that begin/curptr/end index a buffer whose ASAN redzone directly
     * follows its content_len'th byte. */
    unsigned char *content = (unsigned char *) malloc(content_len);
    if (!content) { free(raw); return 0; }
    memcpy(content, raw + 3, content_len);
    free(raw);

    pj_scanner scanner;
    build_scanner(content, content_len, (int) mode, curptr_raw, end_raw, &scanner);

    pj_scan_skip_line(&scanner);

    free(content);
    return 0;
}
