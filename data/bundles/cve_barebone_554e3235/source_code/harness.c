/*
 * cve_barebone direct-call harness for CVE-2026 (libvips) parse_matrix_header()
 * NULL-pointer dereference (CWE-476).
 *
 * Fix commit d4ce337c76bff1b278d7085c3c4f4725e3aa6ece added a NULL check in the
 * caller vips_foreign_load_matrix_header():
 *
 *     -    line = vips_sbuf_get_line_copy(matrix->sbuf);
 *     +    if (!(line = vips_sbuf_get_line_copy(matrix->sbuf))) {
 *     +        vips_error("matrixload", "%s", _("invalid header"));
 *     +        return -1;
 *     +    }
 *          result = parse_matrix_header(line, &width, &height, &scale, &offset);
 *
 * vips_sbuf_get_line_copy() (libvips/iofuncs/sbuf.c) returns NULL exactly when
 * the source hits *immediate* EOF (zero bytes read before end-of-stream). Prior
 * to the fix, that NULL was passed straight into parse_matrix_header(), whose
 * very first statement is:
 *
 *     if ((p = strchr(line, '\r')) || ((p = strchr(line, '\n'))))
 *
 * strchr(NULL, ...) dereferences a NULL pointer -> SIGSEGV, inside
 * parse_matrix_header's own body, on the very first line executed. The two
 * OTHER call sites of parse_matrix_header() in this file (the file/source
 * "is_a" sniffers) already guard with `bytes <= 0` before calling, so only the
 * real load path was vulnerable -- exactly matching the fix.
 *
 * This harness reproduces the caller's real contract directly: it reads
 * argv[1] as the "source" bytes. An EMPTY file models vips_sbuf_get_line_copy()
 * hitting immediate EOF (its documented NULL-returning case) and the harness
 * passes that NULL straight into parse_matrix_header(), exactly like the
 * unpatched caller. A NON-EMPTY file models a successfully-read line: the
 * bytes are copied into a heap (malloc), ASAN-guarded, NUL-terminated buffer
 * (mirroring vips_sbuf_get_line_copy()'s heap-allocated, g_free()-owned
 * result) and that pointer is passed instead.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

/* ---- libvips/include/vips/intl.h: NLS disabled -> _() is the identity. ---- */
#define _(String) (String)

/* ---- minimal stand-in for vips_error() (libvips/iofuncs/error.c). Only
 * used on non-crashing (error-return) paths inside parse_matrix_header; not
 * on the crash path itself. Real signature: void vips_error(const char
 * *domain, const char *fmt, ...); faithfully variadic-printf here. ---- */
static void
vips_error(const char *domain, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputc('\n', stderr);
	(void) domain;
}

/* ---- faithful minimal stand-ins for the two glib primitives vips_strtod()
 * needs, so the file needs no glib to link. g_ascii_isdigit/g_ascii_strtod
 * are locale-independent (ASCII / "C" locale); we never call setlocale(), so
 * the process is already in the "C" locale and plain isdigit-on-ASCII-range
 * / strtod() are exactly equivalent. ---- */
static int
g_ascii_isdigit(char c)
{
	return c >= '0' && c <= '9';
}

static double
g_ascii_strtod(const char *nptr, char **endptr)
{
	return strtod(nptr, endptr);
}

/* ---- verbatim from libvips/iofuncs/util.c: static helper used by
 * vips_break_token() to allow '\' as a break-escape. ---- */
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

/* ---- verbatim from libvips/iofuncs/util.c: vips_break_token(). Real callee
 * on parse_matrix_header's tokenizer loop. ---- */
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

/* ---- verbatim from libvips/iofuncs/util.c: vips_strtod(). Real callee on
 * parse_matrix_header's tokenizer loop (uses the faithful g_ascii_* stand-ins
 * above instead of glib). ---- */
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
		if (g_ascii_isdigit(*p))
			break;
	if (!*p)
		return -1;

	/* This will fail for out of range numbers, like 1e343434, but
	 * is quite happy with eg. "banana".
	 */
	*out = g_ascii_strtod(str, NULL);
	if (errno)
		return -1;

	return 0;
}

/* ==== target function, copied BYTE-FOR-BYTE from
 * data_cve/cve_554e3235/target/original_function.c ==== */
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

int
main(int argc, char **argv)
{
	FILE *f;
	long fsize;
	char *line;
	int width = 0, height = 0;
	double scale = 0.0, offset = 0.0;

	if (argc < 2)
		return 0;

	f = fopen(argv[1], "rb");
	if (!f)
		return 0;

	if (fseek(f, 0, SEEK_END) != 0) {
		fclose(f);
		return 0;
	}
	fsize = ftell(f);
	if (fsize < 0)
		fsize = 0;
	rewind(f);

	if (fsize == 0) {
		/* Immediate EOF: vips_sbuf_get_line_copy() returns NULL in
		 * exactly this case (empty buffer at ch==-1). The unpatched
		 * caller passed that NULL straight into parse_matrix_header().
		 */
		fclose(f);
		line = NULL;
	} else {
		/* Non-empty source: vips_sbuf_get_line_copy() would return a
		 * heap-allocated, NUL-terminated copy of the bytes read (EOL
		 * stripped by the caller's line-reading loop; parse_matrix_header
		 * itself also strips '\r'/'\n', so we don't need to strip here).
		 */
		line = malloc((size_t) fsize + 1);
		if (!line) {
			fclose(f);
			return 0;
		}
		{
			size_t nread = fread(line, 1, (size_t) fsize, f);
			line[nread] = '\0';
		}
		fclose(f);
	}

	parse_matrix_header(line, &width, &height, &scale, &offset);

	free(line);

	return 0;
}
