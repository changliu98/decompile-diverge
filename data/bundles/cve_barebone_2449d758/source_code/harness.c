/* cve_barebone direct-call harness for CVE-2022-21723 (GHSA-7fw8-54cv-r7pm, pjproject)
 * Target: pj_scan_get_char  (pjlib-util/src/pjlib-util/scanner.c)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * Fix commit 077b465c33f0aec05a49cd2ca456f9a1b112e896 ("Prevent OOB read in multipart
 * parsing") adds two bounds checks that the vulnerable pj_scan_get_char below is
 * missing:
 *   1. `s >= scanner->end` before the FIRST dereference (`int chr = *scanner->curptr`).
 *   2. `PJ_SCAN_CHECK_EOF(s)` (i.e. `s != scanner->end`) before the SECOND dereference
 *      -- the whitespace peek `PJ_SCAN_IS_PROBABLY_SPACE(*scanner->curptr)` that runs
 *      right after `++scanner->curptr`.
 * Neither check exists in the body copied below. pjsip's SIP multipart-body parser
 * builds a `pj_scanner` over a body span carved out of the middle of a larger receive
 * buffer; when that span's logical `end` coincides with the actual end of the
 * underlying heap allocation (no spare NUL-pad byte past the span), advancing
 * `curptr` to `end` and then peeking `*curptr` for whitespace reads one byte past the
 * allocation.
 *
 * This harness reproduces that exact layout directly: the input file's bytes become
 * an EXACTLY `sz`-byte malloc() buffer (no padding), and the scanner is positioned at
 * the buffer's last byte (`curptr = end - 1`) before calling pj_scan_get_char(). If
 * that last byte is non-NUL, pj_scan_get_char() unconditionally advances `curptr` to
 * `end` and then dereferences it as the LEFT operand of
 * `PJ_SCAN_IS_PROBABLY_SPACE(*scanner->curptr) && scanner->skip_ws` (the left operand
 * of `&&` always evaluates, regardless of `skip_ws`'s value) -> 1-byte
 * heap-buffer-overflow READ. If the last byte is NUL, pj_scan_get_char() instead takes
 * the `if (!chr)` early-return branch and never touches memory past the allocation ->
 * safe.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>

/* ---- pjlib visibility macro, non-Windows path (pjlib/include/pj/config.h:1247) ---- */
#define PJ_DEF(type)   type

/* ==== real type definitions, verbatim from pjlib-util/include/pjlib-util/scanner.h ==== */
struct pj_scanner;

/**
 * The callback function type to be called by the scanner when it encounters
 * syntax error.
 */
typedef void (*pj_syn_err_func_ptr)(struct pj_scanner *scanner);

/**
 * The text scanner structure.
 */
typedef struct pj_scanner
{
    char *begin;        /**< Start of input buffer.	*/
    char *end;          /**< End of input buffer.	*/
    char *curptr;       /**< Current pointer.		*/
    int   line;         /**< Current line.		*/
    char *start_line;   /**< Where current line starts.	*/
    int   skip_ws;      /**< Skip whitespace flag.	*/
    pj_syn_err_func_ptr callback;   /**< Syntax error callback. */
} pj_scanner;

/**
 * Flags for scanner.
 */
enum
{
    PJ_SCAN_AUTOSKIP_WS = 1,
    PJ_SCAN_AUTOSKIP_WS_HEADER = 3,
    PJ_SCAN_AUTOSKIP_NEWLINE = 4
};

/* ==== macros, verbatim from pjlib-util/src/pjlib-util/scanner.c:31-33 ==== */
#define PJ_SCAN_IS_SPACE(c)		((c)==' ' || (c)=='\t')
#define PJ_SCAN_IS_NEWLINE(c)		((c)=='\r' || (c)=='\n')
#define PJ_SCAN_IS_PROBABLY_SPACE(c)	((c) <= 32)

/* ==== real callee, verbatim from scanner.c:44-47 ==== */
static void pj_scan_syntax_err(pj_scanner *scanner)
{
    (*scanner->callback)(scanner);
}

/* ==== real callee, verbatim from scanner.c:141-194 ====
 * Not actually reached by any input this harness crafts (the trigger path faults
 * mid-expression on the whitespace-peek dereference itself, before this would be
 * called; the safe path takes the early `if (!chr)` return instead) but included
 * verbatim rather than stubbed, since it is a real, direct callee of the target
 * function and costs nothing to keep faithful.
 */
PJ_DEF(void) pj_scan_skip_whitespace( pj_scanner *scanner )
{
    register char *s = scanner->curptr;

    while (PJ_SCAN_IS_SPACE(*s)) {
	++s;
    }

    if (PJ_SCAN_IS_NEWLINE(*s) && (scanner->skip_ws & PJ_SCAN_AUTOSKIP_NEWLINE)) {
	for (;;) {
	    if (*s == '\r') {
		++s;
		if (*s == '\n') ++s;
		++scanner->line;
		scanner->curptr = scanner->start_line = s;
	    } else if (*s == '\n') {
		++s;
		++scanner->line;
		scanner->curptr = scanner->start_line = s;
	    } else if (PJ_SCAN_IS_SPACE(*s)) {
		do {
		    ++s;
		} while (PJ_SCAN_IS_SPACE(*s));
	    } else {
		break;
	    }
	}
    }

    if (PJ_SCAN_IS_NEWLINE(*s) && (scanner->skip_ws & PJ_SCAN_AUTOSKIP_WS_HEADER)==PJ_SCAN_AUTOSKIP_WS_HEADER) {
	/* Check for header continuation. */
	scanner->curptr = s;

	if (*s == '\r') {
	    ++s;
	}
	if (*s == '\n') {
	    ++s;
	}
	scanner->start_line = s;

	if (PJ_SCAN_IS_SPACE(*s)) {
	    register char *t = s;
	    do {
		++t;
	    } while (PJ_SCAN_IS_SPACE(*t));

	    ++scanner->line;
	    scanner->curptr = t;
	}
    } else {
	scanner->curptr = s;
    }
}

/* ==== TARGET FUNCTION -- byte-for-byte from data_cve/cve_2449d758/target/original_function.c ==== */
PJ_DEF(int) pj_scan_get_char( pj_scanner *scanner )
{
    int chr = *scanner->curptr;

    if (!chr) {
	pj_scan_syntax_err(scanner);
	return 0;
    }

    ++scanner->curptr;

    if (PJ_SCAN_IS_PROBABLY_SPACE(*scanner->curptr) && scanner->skip_ws) {
	pj_scan_skip_whitespace(scanner);
    }
    return chr;
}
/* ==== END TARGET FUNCTION ==== */

/* Harness's own syntax-error callback -- a real, correctly-typed
 * pj_syn_err_func_ptr. In the full library this would longjmp out via PJ_THROW;
 * without a PJ_TRY frame installed it simply returns, which is exactly what lets
 * pj_scan_get_char's own `return 0;` (right after the call) run normally on the
 * safe path.
 */
static void harness_syntax_err_cb(pj_scanner *scanner)
{
    (void)scanner;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        return 0;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        return 0;
    }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz <= 0) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* Heap-allocate EXACTLY sz bytes -- no NUL pad, no slack -- so ASAN's redzone
     * begins immediately at buf+sz. This mirrors a pjsip multipart body span carved
     * out of a larger receive buffer, whose logical end is not followed by a spare
     * terminator byte inside the allocation the scanner believes it owns. */
    char *buf = (char *)malloc((size_t)sz);
    if (!buf) { fclose(f); return 0; }

    size_t n = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    if (n != (size_t)sz) { free(buf); return 0; }

    pj_scanner scanner;
    scanner.begin      = buf;
    scanner.end        = buf + sz;
    scanner.curptr     = buf + sz - 1;   /* positioned at the buffer's LAST byte */
    scanner.line       = 1;
    scanner.start_line = buf;
    scanner.skip_ws    = PJ_SCAN_AUTOSKIP_WS;
    scanner.callback   = &harness_syntax_err_cb;

    int c = pj_scan_get_char(&scanner);
    (void)c;

    free(buf);
    return 0;
}
