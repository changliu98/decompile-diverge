/* harness.c for CVE-2016-4478 in atheme xmlrpc_char_encode (cve_056c0355)
 *
 * Direct-call ASAN harness: reads an input file, builds a NUL-terminated
 * heap string from it, and calls xmlrpc_char_encode() on it directly.
 *
 * Bug (fixed by atheme commit 87580d767868360d2fed503980129504da84b63e):
 *     memcpy(outbuffer, s->str, XMLRPC_BUFSIZE);
 * unconditionally copies XMLRPC_BUFSIZE (4096) bytes out of s->str, a
 * mowgli_string_t buffer whose actual heap allocation (s->size) starts at
 * 64 bytes and only grows (by doubling / to fit the appended content) as
 * characters are appended. For any input whose HTML-escaped encoding stays
 * under ~4096 bytes -- i.e. essentially every normal input -- s->size is
 * far smaller than 4096, so the memcpy reads past the end of s->str's heap
 * allocation: a heap-buffer-overflow READ (CWE-125). The fix replaced the
 * fixed-size memcpy with strncpy (bounded by the actual string) plus an
 * explicit NUL append.
 *
 * Supporting types/functions below are copied VERBATIM (real field names,
 * real order, real growth algorithm) from:
 *   libmowgli-2/src/libmowgli/core/mowgli_string.h
 *   libmowgli-2/src/libmowgli/core/mowgli_string.c
 * mowgli_alloc()/mowgli_free() are minimal faithful stubs for libmowgli's
 * own bootstrap allocator (libmowgli-2/src/libmowgli/core/alloc.c:
 * _mowgli_bootstrap_alloc/_mowgli_bootstrap_free are themselves plain
 * calloc(size,1)/free() -- mowgli_alloc()/mowgli_free() route to exactly
 * that policy by default, modulo an allocation-tag header used only for
 * pluggable-allocator bookkeeping that is irrelevant to this bug).
 * mowgli_strlcpy is copied verbatim (inlined) from
 *   libmowgli-2/src/libmowgli/core/alloc.c-adjacent util, see
 *   libmowgli-2/src/libmowgli/... (mowgli_strlcpy implementation used
 *   unmodified by mowgli_string_append/append_char's realloc path).
 *
 * XMLRPC_BUFSIZE is copied from modules/transport/xmlrpc/xmlrpclib.h.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XMLRPC_BUFSIZE 4096   /* modules/transport/xmlrpc/xmlrpclib.h */

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

/* ---- verbatim from libmowgli-2/src/libmowgli/core/mowgli_string.h ---- */
typedef struct mowgli_string_
{
	char *str;
	size_t pos;
	size_t size;

	void (*reset)(struct mowgli_string_ *self);

	void (*append)(struct mowgli_string_ *self, const char *src, size_t n);

	void (*append_char)(struct mowgli_string_ *self, const char c);

	void (*destroy)(struct mowgli_string_ *self);
} mowgli_string_t;

extern mowgli_string_t *mowgli_string_create(void);
extern void mowgli_string_reset(mowgli_string_t *self);
extern void mowgli_string_destroy(mowgli_string_t *self);
extern void mowgli_string_append(mowgli_string_t *self, const char *src, size_t n);
extern void mowgli_string_append_char(mowgli_string_t *self, const char c);

/* ---- minimal faithful stubs for libmowgli-2/src/libmowgli/core/alloc.c's
 * default bootstrap allocator (plain calloc/free) ---- */
static void *
mowgli_alloc(size_t size)
{
	return calloc(size, 1);
}

static void
mowgli_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

/* ---- verbatim from libmowgli-2/src/libmowgli/core/alloc.c's
 * mowgli_strlcpy (used unmodified by mowgli_string_append/append_char) ---- */
static size_t
mowgli_strlcpy(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0)
		while (--n != 0)
		{
			if ((*d++ = *s++) == '\0')
				break;
		}

	/* Not enough room in dst, add NUL and traverse rest of src */

	if (n == 0)
	{
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */

		while (*s++)
		{ }
	}

	return s - src - 1;	/* count does not include NUL */
}

/* ---- verbatim from libmowgli-2/src/libmowgli/core/mowgli_string.c ---- */
mowgli_string_t *
mowgli_string_create(void)
{
	mowgli_string_t *self = mowgli_alloc(sizeof(mowgli_string_t));

	self->size = 64;
	self->pos = 0;
	self->str = mowgli_alloc(self->size);

	self->append = &mowgli_string_append;
	self->append_char = &mowgli_string_append_char;
	self->reset = &mowgli_string_reset;
	self->destroy = &mowgli_string_destroy;

	return self;
}

void
mowgli_string_reset(mowgli_string_t *self)
{
	if (self == NULL)
		return;

	self->str[0] = self->pos = 0;
}

void
mowgli_string_destroy(mowgli_string_t *self)
{
	if (self == NULL)
		return;

	mowgli_free(self->str);
	mowgli_free(self);
}

void
mowgli_string_append(mowgli_string_t *self, const char *src, size_t n)
{
	if (self->size - self->pos <= n)
	{
		char *new_ptr;

		self->size = MAX(self->size * 2, self->pos + n + 8);

		new_ptr = mowgli_alloc(self->size);
		mowgli_strlcpy(new_ptr, self->str, self->size);

		mowgli_free(self->str);
		self->str = new_ptr;
	}

	memcpy(self->str + self->pos, src, n);
	self->pos += n;
	self->str[self->pos] = 0;
}

void
mowgli_string_append_char(mowgli_string_t *self, const char c)
{
	if (self->size - self->pos <= 1)
	{
		char *new_ptr;

		self->size = MAX(self->size * 2, self->pos + 9);

		new_ptr = mowgli_alloc(self->size);
		mowgli_strlcpy(new_ptr, self->str, self->size);

		mowgli_free(self->str);
		self->str = new_ptr;
	}

	self->str[self->pos++] = c;
	self->str[self->pos] = 0;
}

/* ---- target function: BYTE-FOR-BYTE from
 * data_cve/cve_056c0355/target/original_function.c
 * (modules/transport/xmlrpc/xmlrpclib.c, xmlrpc_char_encode) ---- */
void xmlrpc_char_encode(char *outbuffer, const char *s1)
{
	long unsigned int i;
	unsigned char c;
	char buf2[15];
	mowgli_string_t *s = mowgli_string_create();
	*buf2 = '\0';
	*outbuffer = '\0';

	if ((!(s1) || (*(s1) == '\0')))
	{
		return;
	}

	for (i = 0; s1[i] != '\0'; i++)
	{
		c = s1[i];
		if (c > 127)
		{
			snprintf(buf2, sizeof buf2, "&#%d;", c);
			s->append(s, buf2, strlen(buf2));
		}
		else if (c == '&')
		{
			s->append(s, "&amp;", 5);
		}
		else if (c == '<')
		{
			s->append(s, "&lt;", 4);
		}
		else if (c == '>')
		{
			s->append(s, "&gt;", 4);
		}
		else if (c == '"')
		{
			s->append(s, "&quot;", 6);
		}
		else
		{
			s->append_char(s, c);
		}
	}

	memcpy(outbuffer, s->str, XMLRPC_BUFSIZE);
}

/* ---- driver ---- */
int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f)
	{
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}

	fseek(f, 0, SEEK_END);
	long flen = ftell(f);
	rewind(f);
	if (flen < 0)
	{
		fclose(f);
		return 1;
	}

	/* heap-allocate the input buffer (ASAN-guarded), NUL-terminated */
	char *s1 = malloc((size_t) flen + 1);
	if (!s1)
	{
		fclose(f);
		return 1;
	}
	size_t n = fread(s1, 1, (size_t) flen, f);
	fclose(f);
	s1[n] = '\0';

	/* heap-allocate an exactly-XMLRPC_BUFSIZE outbuffer, matching real
	 * callers (e.g. xmlrpc_append_char_encode's char buf[XMLRPC_BUFSIZE])
	 * so the only fault surface exercised is the READ overflow out of
	 * s->str, not an incidental write overflow of our own scratch buffer */
	char *outbuffer = malloc(XMLRPC_BUFSIZE);
	if (!outbuffer)
	{
		free(s1);
		return 1;
	}

	xmlrpc_char_encode(outbuffer, s1);

	/* NOTE: outbuffer is NOT guaranteed NUL-terminated within its
	 * XMLRPC_BUFSIZE allocation (that is exactly the class of bug this
	 * harness targets -- for a "safe" long input the encoded string can
	 * run past byte XMLRPC_BUFSIZE with no NUL in between), so touch only
	 * fixed, in-bounds offsets here -- do NOT strlen(outbuffer), that
	 * would be a scaffolding-introduced overflow in main(), not in
	 * xmlrpc_char_encode. */
	printf("first-byte=%d last-byte=%d\n",
	       (int) (unsigned char) outbuffer[0],
	       (int) (unsigned char) outbuffer[XMLRPC_BUFSIZE - 1]);

	free(outbuffer);
	free(s1);
	return 0;
}
