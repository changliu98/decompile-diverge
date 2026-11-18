/* cve_745093c1 -- mupdf mcid_char_imp direct-call harness.
 *
 * Bug: source/pdf/pdf-op-filter.c walk_string() indexes str->utf8[str->pos]
 * without checking str->pos == -1 (the fix, commit 97096297d409, adds
 * `|| str->pos == -1` to the NULL guard).  mcid_char_imp() drives
 * walk_string() twice per call (once for tr->alt, once for tr->actualtext);
 * a prior call that mismatched the expected character sets str->pos = -1,
 * and the NEXT call to mcid_char_imp() on the same tag_record re-enters
 * walk_string() with str->pos still -1, so `s = &str->utf8[str->pos]`
 * reads str->utf8[-1] -- one byte before the heap allocation.  This is a
 * genuine heap-buffer-overflow READ (CWE-125) reachable purely by calling
 * mcid_char_imp() twice on an attacker-shaped tag_record; no PDF parsing
 * pipeline required.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- opaque handle types: passed through mcid_char_imp/walk_string but
 * never dereferenced by either function, so an incomplete type is
 * sufficient and faithful (no invented fields). ---- */
typedef struct fz_context_s fz_context;
typedef struct pdf_obj_s pdf_obj;
typedef struct pdf_filter_processor_s pdf_filter_processor;

/* ---- real struct layouts, copied from source/pdf/pdf-op-filter.c (verbatim
 * field names/types/order -- these are the types mcid_char_imp's own body
 * directly dereferences). ---- */
typedef struct editable_str_s
{
	char *utf8;
	int edited;
	int pos;
} editable_str;

typedef struct tag_record_s
{
	int bdc;
	char *tag;
	pdf_obj *raw;
	pdf_obj *cooked;

	int mcid_num;
	pdf_obj *mcid_obj;
	editable_str alt;
	editable_str actualtext;

	struct tag_record_s *prev;
} tag_record;

/* ---- include/mupdf/pdf/object.h PDF_NAME() voodoo: real macro, real enum
 * name prefix; a PDF_NAME(X) is a small integer tag cast to pdf_obj*, never
 * a real heap object, so it is never dereferenced by pdf_dict_del's stub
 * below.  We only mint the 4 tags mcid_char_imp actually references instead
 * of pulling in the full generated name-table.h. ---- */
enum { PDF_ENUM_NAME_E = 1, PDF_ENUM_NAME_T = 2, PDF_ENUM_NAME_ActualText = 3, PDF_ENUM_NAME_Alt = 4 };
#define PDF_NAME(X) ((pdf_obj*)(intptr_t)PDF_ENUM_NAME_##X)

/* ---- incidental callees (include/mupdf/{fitz/context.h,pdf/object.h}
 * signatures, real names): only reached when `remove` resolves true, which
 * never happens on the triggering path (remove=0 throughout) -- minimal
 * faithful no-op stubs, matching the task note that PDF_NAME/pdf_dict_del
 * are not on the crash path. ---- */
static void pdf_dict_del(fz_context *ctx, pdf_obj *dict, pdf_obj *key) { (void)ctx; (void)dict; (void)key; }
static void pdf_drop_obj(fz_context *ctx, pdf_obj *obj) { (void)ctx; (void)obj; }
static void fz_free(fz_context *ctx, void *p) { (void)ctx; free(p); }

/* ---- real callee ON the crash path: source/fitz/string.c fz_chartorune(),
 * copied verbatim (needs its private Tx/T2../Rune../Testx bit-pattern
 * constants from the same file, also copied verbatim).  walk_string()'s
 * `s = &str->utf8[str->pos]` OOB pointer is only actually dereferenced
 * here, at `c = *(const unsigned char*)str;` -- the exact byte ASAN flags. */
enum
{
	UTFmax = 4, /* maximum bytes per rune */
	Runesync = 0x80, /* cannot represent part of a UTF sequence (<) */
	Runeself = 0x80, /* rune and UTF sequences are the same (<) */
	Runeerror = 0xFFFD, /* decoding error in UTF */
	Runemax = 0x10FFFF, /* maximum rune value */
};

enum
{
	Bit1 = 7,
	Bitx = 6,
	Bit2 = 5,
	Bit3 = 4,
	Bit4 = 3,
	Bit5 = 2,

	T1 = ((1<<(Bit1+1))-1) ^ 0xFF, /* 0000 0000 */
	Tx = ((1<<(Bitx+1))-1) ^ 0xFF, /* 1000 0000 */
	T2 = ((1<<(Bit2+1))-1) ^ 0xFF, /* 1100 0000 */
	T3 = ((1<<(Bit3+1))-1) ^ 0xFF, /* 1110 0000 */
	T4 = ((1<<(Bit4+1))-1) ^ 0xFF, /* 1111 0000 */
	T5 = ((1<<(Bit5+1))-1) ^ 0xFF, /* 1111 1000 */

	Rune1 = (1<<(Bit1+0*Bitx))-1, /* 0000 0000 0111 1111 */
	Rune2 = (1<<(Bit2+1*Bitx))-1, /* 0000 0111 1111 1111 */
	Rune3 = (1<<(Bit3+2*Bitx))-1, /* 1111 1111 1111 1111 */
	Rune4 = (1<<(Bit4+3*Bitx))-1, /* 0001 1111 1111 1111 1111 1111 */

	Maskx = (1<<Bitx)-1,	/* 0011 1111 */
	Testx = Maskx ^ 0xFF,	/* 1100 0000 */

	Bad = Runeerror,
};

int fz_chartorune(int *rune, const char *str) __attribute__((noinline));

int
fz_chartorune(int *rune, const char *str)
{
	int c, c1, c2, c3;
	int l;

	/*
	 * one character sequence
	 *	00000-0007F => T1
	 */
	c = *(const unsigned char*)str;
	if(c < Tx) {
		*rune = c;
		return 1;
	}

	/*
	 * two character sequence
	 *	0080-07FF => T2 Tx
	 */
	c1 = *(const unsigned char*)(str+1) ^ Tx;
	if(c1 & Testx)
		goto bad;
	if(c < T3) {
		if(c < T2)
			goto bad;
		l = ((c << Bitx) | c1) & Rune2;
		if(l <= Rune1)
			goto bad;
		*rune = l;
		return 2;
	}

	/*
	 * three character sequence
	 *	0800-FFFF => T3 Tx Tx
	 */
	c2 = *(const unsigned char*)(str+2) ^ Tx;
	if(c2 & Testx)
		goto bad;
	if(c < T4) {
		l = ((((c << Bitx) | c1) << Bitx) | c2) & Rune3;
		if(l <= Rune2)
			goto bad;
		*rune = l;
		return 3;
	}

	/*
	 * four character sequence (21-bit value)
	 *	10000-1FFFFF => T4 Tx Tx Tx
	 */
	c3 = *(const unsigned char*)(str+3) ^ Tx;
	if (c3 & Testx)
		goto bad;
	if (c < T5) {
		l = ((((((c << Bitx) | c1) << Bitx) | c2) << Bitx) | c3) & Rune4;
		if (l <= Rune3)
			goto bad;
		*rune = l;
		return 4;
	}
	/*
	 * Support for 5-byte or longer UTF-8 would go here, but
	 * since we don't have that, we'll just fall through to bad.
	 */

	/*
	 * bad decoding
	 */
bad:
	*rune = Bad;
	return 1;
}

/* ---- real callee ON the crash path: source/pdf/pdf-op-filter.c
 * walk_string(), copied verbatim (this is the UNPATCHED, vulnerable
 * version -- the fix adds `|| str->pos == -1` to the guard below). ---- */
static void walk_string(fz_context *ctx, int uni, int remove, editable_str *str) __attribute__((noinline));

static void
walk_string(fz_context *ctx, int uni, int remove, editable_str *str)
{
	int rune;

	if (str->utf8 == NULL)
		return;

	do
	{
		char *s = &str->utf8[str->pos];
		size_t len;
		int n = fz_chartorune(&rune, s);
		if (rune == uni)
		{
			/* Match. Skip over that one. */
			str->pos += n;
		}
		else if (uni == 32) {
			/* We don't care if we're given whitespace
			 * and it doesn't match the string. Don't
			 * skip forward. Nothing to remove. */
			break;
		}
		else if (rune == 32) {
			/* The string has a whitespace, and we
			 * don't match it; that's forgivable as
			 * PDF often misses out spaces. Remove this
			 * if we are removing stuff. */
		}
		else
		{
			/* Mismatch. No point in tracking through any more. */
			str->pos = -1;
			break;
		}
		if (remove)
		{
			len = strlen(s+n);
			memmove(s, s+n, len+1);
			str->edited = 1;
		}
	}
	while (rune != uni);
}

/* ---- target function: byte-for-byte copy of
 * data_cve/cve_745093c1/target/original_function.c is concatenated verbatim
 * right after this comment by the build script.  Only a forward
 * declaration + noinline attribute is added here, ahead of the pasted
 * definition, so the pasted bytes themselves are untouched. ---- */
static void mcid_char_imp(fz_context *ctx, pdf_filter_processor *p, tag_record *tr, int uni, int remove) __attribute__((noinline));

static void
mcid_char_imp(fz_context *ctx, pdf_filter_processor *p, tag_record *tr, int uni, int remove)
{
	if (tr->mcid_obj == NULL)
		/* No object, or already deleted */
		return;

	if (remove)
	{
		/* Remove the expanded abbreviation, if there is one. */
		pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(E));
		/* Remove the structure title, if there is one. */
		pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(T));
	}
	/* Edit the Alt string */
	walk_string(ctx, uni, remove, &tr->alt);
	/* Edit the ActualText string */
	walk_string(ctx, uni, remove, &tr->actualtext);
	/* If we're removing a character, and either of the strings
	 * haven't matched up to what we were expecting, then just
	 * delete the whole string. */
	if (remove)
		remove = (tr->alt.pos == -1 || tr->actualtext.pos == -1);
	else if (tr->alt.pos >= 0 || tr->actualtext.pos >= 0)
	{
		/* The strings are making sense so far */
		remove = 0;
	}
	if (remove)
	{
		/* Anything else we have to err on the side of caution and
		 * delete everything that might leak info. */
		if (tr->actualtext.pos == -1)
			pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(ActualText));
		if (tr->alt.pos == -1)
			pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(Alt));
		pdf_drop_obj(ctx, tr->mcid_obj);
		tr->mcid_obj = NULL;
		fz_free(ctx, tr->alt.utf8);
		tr->alt.utf8 = NULL;
		fz_free(ctx, tr->actualtext.utf8);
		tr->actualtext.utf8 = NULL;
	}
}


/* ---- driver: read argv[1] into a heap buffer, build a tag_record from it,
 * call mcid_char_imp() directly (no PDF parser, no fz_context machinery). */

static unsigned char *read_file(const char *path, long *out_len)
{
	FILE *f = fopen(path, "rb");
	long sz;
	unsigned char *buf;
	size_t got;

	if (!f) { *out_len = -1; return NULL; }
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); *out_len = -1; return NULL; }
	sz = ftell(f);
	if (sz < 0) { fclose(f); *out_len = -1; return NULL; }
	rewind(f);
	buf = (unsigned char *)malloc(sz > 0 ? (size_t)sz : 1);
	if (!buf) { fclose(f); *out_len = -1; return NULL; }
	got = sz > 0 ? fread(buf, 1, (size_t)sz, f) : 0;
	fclose(f);
	if ((long)got != sz) { free(buf); *out_len = -1; return NULL; }
	*out_len = sz;
	return buf;
}

int
main(int argc, char **argv)
{
	long flen = 0;
	unsigned char *filebuf;
	unsigned char mode;
	unsigned char *payload;
	long paylen;
	unsigned char *altbuf;
	fz_context *ctx;
	pdf_filter_processor *p;
	tag_record tr;

	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 0;
	}

	filebuf = read_file(argv[1], &flen);
	if (!filebuf || flen < 3)
	{
		/* Malformed/too-short input: nothing to drive the harness with.
		 * Not a crash -- exit clean. */
		free(filebuf);
		return 0;
	}

	mode = filebuf[0];
	payload = filebuf + 1;
	paylen = flen - 1;   /* >= 2, guaranteed by the flen < 3 check above */

	/* HEAP-allocate the exact-sized, ASAN-guarded string buffer that
	 * tr.alt.utf8 will point at -- this is the buffer walk_string() walks
	 * and the one whose left redzone the bug reads across. */
	altbuf = (unsigned char *)malloc((size_t)paylen + 1);
	if (!altbuf)
	{
		free(filebuf);
		return 0;
	}
	memcpy(altbuf, payload, (size_t)paylen);
	altbuf[paylen] = 0;

	ctx = NULL;   /* never dereferenced by mcid_char_imp/walk_string/fz_chartorune */
	p = NULL;     /* never dereferenced by mcid_char_imp (unused parameter in the real body) */

	memset(&tr, 0, sizeof(tr));
	tr.mcid_obj = (pdf_obj *)(intptr_t)1;   /* non-NULL PDF_NAME()-style tag; pdf_dict_del/pdf_drop_obj stubs never dereference it */
	tr.alt.utf8 = (char *)altbuf;
	tr.alt.pos = 0;
	tr.alt.edited = 0;
	tr.actualtext.utf8 = NULL;   /* keeps the actualtext half of mcid_char_imp inert (walk_string's NULL guard returns immediately) */
	tr.actualtext.pos = 0;
	tr.actualtext.edited = 0;

	if (mode == 0)
	{
		/* SAFE: matched walk. uni1/uni2 are read straight off the
		 * buffer's own first two bytes, so both calls match exactly the
		 * character they are given; tr.alt.pos only ever advances
		 * (stays >= 0, in-bounds) -- there is no way to reach the
		 * `str->pos == -1` reentry state on this path. */
		int uni1 = (int)(unsigned char)payload[0];
		int uni2 = (int)(unsigned char)payload[1];
		mcid_char_imp(ctx, p, &tr, uni1, 0);
		mcid_char_imp(ctx, p, &tr, uni2, 0);
	}
	else
	{
		/* TRIGGER: call #1 deliberately mismatches the first character
		 * (uni1 != payload[0], uni1 != ' ') so walk_string() takes its
		 * "Mismatch" branch and sets tr.alt.pos = -1 -- itself an
		 * in-bounds read (str->pos was still 0). Call #2 re-enters
		 * walk_string() on the SAME tag_record with tr.alt.pos still
		 * -1: `s = &str->utf8[str->pos]` now points one byte before
		 * altbuf's heap allocation, and fz_chartorune()'s very first
		 * dereference reads it -- the exact missing-guard bug the fix
		 * commit patches (`str->pos == -1` added to walk_string()'s
		 * entry check). */
		unsigned char first = payload[0];
		int uni1 = (first == 0x7E) ? 0x21 : 0x7E;
		mcid_char_imp(ctx, p, &tr, uni1, 0);
		mcid_char_imp(ctx, p, &tr, 0x41, 0);
	}

	free(altbuf);
	free(filebuf);
	return 0;
}
