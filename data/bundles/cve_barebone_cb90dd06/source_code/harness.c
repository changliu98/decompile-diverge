/*
 * Decompile-Diverge direct-call harness -- cve_cb90dd06 (libvips, CVE-2026-3145)
 *
 * TARGET FUNCTION (embedded VERBATIM below, byte-for-byte from
 * data_cve/cve_cb90dd06/target/original_function.c): parse_matrix_header
 *   libvips/foreign/matrixload.c, pre-fix (vulnerable) revision
 *   24795bb3d19d84f7b6f5ed86451ad556c8f2fe70.
 *
 * BUG (CWE-476, NULL pointer dereference):
 *   The fix commit (d4ce337c76bff1b278d7085c3c4f4725e3aa6ece) changes the
 *   caller, vips_foreign_load_matrix_header():
 *
 *       -	line = vips_sbuf_get_line_copy(matrix->sbuf);
 *       +	if (!(line = vips_sbuf_get_line_copy(matrix->sbuf))) {
 *       +		vips_error("matrixload", "%s", _("invalid header"));
 *       +		return -1;
 *       +	}
 *          result = parse_matrix_header(line, &width, &height, &scale, &offset);
 *
 *   i.e. pre-fix, the caller forwards vips_sbuf_get_line_copy()'s return
 *   value into parse_matrix_header() WITHOUT checking it for NULL.
 *   vips_sbuf_get_line_copy() (and the sibling vips_sbuf_get_line(), see
 *   libvips/iofuncs/sbuf.c) returns NULL exactly when the very first read
 *   hits EOF immediately (write_point == 0) -- i.e. for a completely empty
 *   (0-byte) matrix file/source. So loading a 0-byte ".mat" file makes the
 *   pre-fix vips_foreign_load_matrix_header() call
 *   parse_matrix_header(NULL, ...), and parse_matrix_header's very first
 *   statement,
 *       if ((p = strchr(line, '\r')) || ...)
 *   dereferences that NULL pointer inside strchr() -- a SEGV squarely
 *   inside parse_matrix_header's own body.
 *
 *   This harness IS the caller (main() plays the role of
 *   vips_foreign_load_matrix_header()): it reads argv[1] into a heap
 *   buffer and, mirroring vips_sbuf_get_line_copy()'s documented contract
 *   ("Returns NULL on end of file"), passes a literal NULL for `line` iff
 *   the input file is 0 bytes -- exactly the value the real (unpatched)
 *   caller would have forwarded for that same input. Any non-empty input
 *   is copied into a heap buffer and passed as a normal, real header line
 *   (the safe / exercising path).
 *
 * Real callees on/near the vulnerable body (vips_break_token, and its
 * static helper strcspne, and vips_strtod) are embedded VERBATIM from
 * libvips/iofuncs/util.c so the loop that walks header tokens behaves
 * exactly as upstream on non-crashing inputs. vips_error() is a faithful
 * no-op stand-in for the incidental error-logging path (it only ever
 * records a message string for later retrieval; it has no effect on
 * control flow or memory safety).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <ctype.h>

/* gettext no-op, as libvips/iofuncs' glib/gi18n-lib.h would provide it in
 * the "C" locale -- parse_matrix_header only ever passes the returned
 * string straight to vips_error() as a format string. */
#define _(S) (S)

/* Faithful no-op stand-in for vips/error.c's vips_error(): the real one
 * appends a formatted message to a thread-local error buffer for later
 * retrieval by the caller. Message content/formatting is incidental to
 * the bug (parse_matrix_header's control flow and the NULL-deref crash
 * site do not depend on it), so this only needs to be call-compatible. */
static void
vips_error(const char *domain, const char *fmt, ...)
{
	(void) domain;
	(void) fmt;
}

/* ==== VERBATIM from source_code/libvips/iofuncs/util.c ====
 * (static helper used only by vips_break_token(), below) */
static size_t
strcspne(const char *s, const char *reject)
{
	size_t skip;

	/* If \ is one of the reject chars, no need for any looping.
	 */
	if (strchr(reject, '\\'))
		return strcspn(s, reject);

	skip = 0;
	for (;;) {
		skip += strcspn(s + skip, reject);

		/* s[skip] is at the start of the string, or the end, or on a
		 * break character.
		 */
		if (skip == 0 ||
			!s[skip] ||
			s[skip - 1] != '\\')
			break;

		/* So skip points at break char and we have a '\' in the char
		 * before. Step over the break.
		 */
		skip += 1;
	}

	return skip;
}

/* ==== VERBATIM from source_code/libvips/iofuncs/util.c ==== */
char *
vips_break_token(char *str, const char *brk)
{
	char *p;
	char *q;

	/* Is the string empty? If yes, return NULL immediately.
	 */
	if (!str ||
		!*str)
		return NULL;

	/* Skip initial break characters.
	 */
	p = str + strspn(str, brk);

	/* No item?
	 */
	if (!*p)
		return NULL;

	/* We have a token ... search for the first break character after the
	 * token. strcspne() allows '\' to escape breaks, see above.
	 */
	p += strcspne(p, brk);

	/* Is there string left?
	 */
	if (*p) {
		/* Write in an end-of-string mark and return the start of the
		 * next token.
		 */
		*p++ = '\0';
		p += strspn(p, brk);
	}

	/* There may be escaped break characters in str. Loop, squashing them
	 * out.
	 */
	for (q = strchr(str, '\\'); q && *q; q = strchr(q, '\\')) {
		memmove(q, q + 1, strlen(q));

		/* If there's \\, we don't want to squash out the second \.
		 */
		q += 1;
	}

	return p;
}

/* ==== VERBATIM from source_code/libvips/iofuncs/util.c, EXCEPT
 * g_ascii_isdigit()/g_ascii_strtod() (glib's locale-independent ASCII
 * variants) are replaced with the standard-C equivalents isdigit()/
 * strtod() -- equivalent behavior for ASCII digits / the "C" locale this
 * harness runs in, and this loop is incidental (not on the crash path;
 * the crash is parse_matrix_header's very first statement, executed
 * before vips_strtod is ever reached). ==== */
int
vips_strtod(const char *str, double *out)
{
	const char *p;

	*out = 0;

	/* The str we fetched must contain at least 1 digit. This
	 * helps stop us trying to convert "MATLAB" (for example) to
	 * a number and getting zero.
	 */
	for (p = str; *p; p++)
		if (isdigit((unsigned char) *p))
			break;
	if (!*p)
		return -1;

	/* This will fail for out of range numbers, like 1e343434, but
	 * is quite happy with eg. "banana".
	 */
	errno = 0;
	*out = strtod(str, NULL);
	if (errno)
		return -1;

	return 0;
}

/* ==== VERBATIM from data_cve/cve_cb90dd06/target/original_function.c ==== */
static int
parse_matrix_header(char *line,
	int *width, int *height, double *scale, double *offset)
{
	double header[4];
	char *p, *q;
	int i;

	/* Stop at newline.
	 */
	if ((p = strchr(line, '\r')) ||
		((p = strchr(line, '\n'))))
		*p = '\0';

	for (i = 0, p = line; (q = vips_break_token(p, " \t")) && i < 4; i++, p = q)
		if (vips_strtod(p, &header[i])) {
			vips_error("matload", _("bad number \"%s\""), p);
			return -1;
		}

	if (i < 4)
		header[3] = 0.0;
	if (i < 3)
		header[2] = 1.0;
	if (i < 2) {
		vips_error("matload", "%s", _("no width / height"));
		return -1;
	}

	if (floor(header[0]) != header[0] ||
		floor(header[1]) != header[1]) {
		vips_error("mask2vips", "%s", _("width / height not int"));
		return -1;
	}

	/* Width / height can be 65536 for a 16-bit LUT, for example.
	 */
	*width = header[0];
	*height = header[1];
	if (*width <= 0 ||
		*width > 100000 ||
		*height <= 0 ||
		*height > 100000) {
		vips_error("mask2vips", "%s", _("width / height out of range"));
		return -1;
	}
	if (header[2] == 0.0) {
		vips_error("mask2vips", "%s", _("zero scale"));
		return -1;
	}

	*scale = header[2];
	*offset = header[3];

	return 0;
}

/* ============================================================
 * main() -- plays the role of vips_foreign_load_matrix_header(): reads
 * argv[1] into a HEAP buffer and calls parse_matrix_header() exactly
 * once, mirroring vips_sbuf_get_line_copy()'s real contract:
 *   - a 0-byte input reproduces vips_sbuf_get_line_copy() returning NULL
 *     on immediate EOF (sbuf.c: write_point == 0 -> return NULL) -- the
 *     pre-fix caller forwarded that NULL straight into
 *     parse_matrix_header(), unchecked. TRIGGERING.
 *   - any non-empty input is the real "line of text" the loader would
 *     have handed parse_matrix_header(): copied into its own
 *     NUL-terminated heap buffer (mutable, since parse_matrix_header
 *     writes into it) and passed as-is. SAFE.
 * ============================================================ */
int
main(int argc, char **argv)
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
	if (fsz < 0)
		fsz = 0;
	fseek(f, 0, SEEK_SET);

	char *line = NULL;
	if (fsz > 0) {
		/* Attacker-controlled bytes MUST live on the heap so ASAN can
		 * catch an out-of-bounds access into/around them. Exact-size
		 * allocation (+1 for the NUL terminator) gives ASAN redzones
		 * tight against both ends of the buffer. */
		line = (char *) malloc((size_t) fsz + 1);
		if (!line) {
			fclose(f);
			return 1;
		}
		size_t n = fread(line, 1, (size_t) fsz, f);
		line[n] = '\0';
	}
	/* else: fsz == 0 -> leave line == NULL, reproducing exactly what
	 * vips_sbuf_get_line_copy() returns for a 0-byte source, and what
	 * the pre-fix caller forwarded unchecked. */
	fclose(f);

	int width = 0, height = 0;
	double scale = 0, offset = 0;
	int rc = parse_matrix_header(line, &width, &height, &scale, &offset);

	fprintf(stderr, "rc=%d width=%d height=%d scale=%g offset=%g\n",
		rc, width, height, scale, offset);

	free(line);
	return 0;
}
