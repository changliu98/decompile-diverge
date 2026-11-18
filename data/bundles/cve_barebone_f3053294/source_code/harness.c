/*
 * cve_barebone direct-call harness for CVE-2025-11964 (libpcap
 * utf_16le_to_utf_8_truncated, fmtutils.c).
 *
 * Bug (per fix commit 7fabf607f2319a36a0bd78444247180acb838e69): in the
 * 4-byte UTF-8 emission branch the function decrements the caller's
 * remaining-buffer bookkeeping (utf_8_len) by 3 even though it just wrote
 * 4 bytes to utf_8. Every surrogate pair that maps to a 4-byte UTF-8
 * sequence therefore makes utf_8_len over-count the true remaining room
 * by 1 byte. After enough such pairs, utf_8_len still looks >= 5 (so the
 * "enough room" guard passes) while the real buffer is already exhausted,
 * and the next 4-byte write goes past the end of the caller-supplied
 * heap buffer: a heap-buffer-overflow WRITE (CWE-787).
 *
 * This harness calls utf_16le_to_utf_8_truncated directly and in
 * isolation: argv[1] is read as a flat byte file, reinterpreted as a
 * sequence of UTF-16LE code units (2 bytes each, little-endian), and
 * passed as the `utf_16` argument together with a fixed-size heap
 * `utf_8` output buffer. Enough leading+trailing surrogate pairs in the
 * input drive the length-arithmetic bug into an out-of-bounds write on
 * the heap output buffer.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wchar.h>
#include <string.h>

/* ---- macros utf_16le_to_utf_8_truncated needs (verbatim from
 * source_code/fmtutils.c, normally guarded by #ifdef _WIN32) ---- */
#define IS_LEADING_SURROGATE(c) \
	((c) >= 0xd800 && (c) < 0xdc00)
#define IS_TRAILING_SURROGATE(c) \
	((c) >= 0xdc00 && (c) < 0xe000)
#define SURROGATE_VALUE(leading, trailing) \
	(((((leading) - 0xd800) << 10) | ((trailing) - 0xdc00)) + 0x10000)
#define REPLACEMENT_CHARACTER	0x0FFFD

/* ---- target function, pasted byte-for-byte from
 * data_cve/cve_f3053294/target/original_function.c ---- */
static char *
utf_16le_to_utf_8_truncated(const wchar_t *utf_16, char *utf_8,
    size_t utf_8_len)
{
	wchar_t c, c2;
	uint32_t uc;

	if (utf_8_len == 0) {
		/*
		 * Not even enough room for a trailing '\0'.
		 * Don't put anything into the buffer.
		 */
		return (utf_8);
	}

	while ((c = *utf_16++) != '\0') {
		if (IS_LEADING_SURROGATE(c)) {
			/*
			 * Leading surrogate.  Must be followed by
			 * a trailing surrogate.
			 */
			c2 = *utf_16;
			if (c2 == '\0') {
				/*
				 * Oops, string ends with a lead
				 * surrogate.  Try to drop in
				 * a REPLACEMENT CHARACTER, and
				 * don't move the string pointer,
				 * so on the next trip through
				 * the loop we grab the terminating
				 * '\0' and quit.
				 */
				uc = REPLACEMENT_CHARACTER;
			} else {
				/*
				 * OK, we can consume this 2-octet
				 * value.
				 */
				utf_16++;
				if (IS_TRAILING_SURROGATE(c2)) {
					/*
					 * Trailing surrogate.
					 * This calculation will,
					 * for c being a leading
					 * surrogate and c2 being
					 * a trailing surrogate,
					 * produce a value between
					 * 0x100000 and 0x10ffff,
					 * so it's always going to be
					 * a valid Unicode code point.
					 */
					uc = SURROGATE_VALUE(c, c2);
				} else {
					/*
					 * Not a trailing surrogate;
					 * try to drop in a
					 * REPLACEMENT CHARACTER.
					 */
					uc = REPLACEMENT_CHARACTER;
				}
			}
		} else {
			/*
			 * Not a leading surrogate.
			 */
			if (IS_TRAILING_SURROGATE(c)) {
				/*
				 * Trailing surrogate without
				 * a preceding leading surrogate.
				 * Try to drop in a REPLACEMENT
				 * CHARACTER.
				 */
				uc = REPLACEMENT_CHARACTER;
			} else {
				/*
				 * This is a valid BMP character;
				 * drop it in.
				 */
				uc = c;
			}
		}

		/*
		 * OK, uc is a valid Unicode character; how
		 * many bytes worth of UTF-8 does it require?
		 */
		if (uc < 0x0080) {
			/* 1 byte. */
			if (utf_8_len < 2) {
				/*
				 * Not enough room for that byte
				 * plus a trailing '\0'.
				 */
				break;
			}
			*utf_8++ = (char)uc;
			utf_8_len--;
		} else if (uc < 0x0800) {
			/* 2 bytes. */
			if (utf_8_len < 3) {
				/*
				 * Not enough room for those bytes
				 * plus a trailing '\0'.
				 */
				break;
			}
			*utf_8++ = ((uc >> 6) & 0x3F) | 0xC0;
			*utf_8++ = ((uc >> 0) & 0x3F) | 0x80;
			utf_8_len -= 2;
		} else if (uc < 0x010000) {
			/* 3 bytes. */
			if (utf_8_len < 4) {
				/*
				 * Not enough room for those bytes
				 * plus a trailing '\0'.
				 */
				break;
			}
			*utf_8++ = ((uc >> 12) & 0x0F) | 0xE0;
			*utf_8++ = ((uc >> 6) & 0x3F) | 0x80;
			*utf_8++ = ((uc >> 0) & 0x3F) | 0x80;
			utf_8_len -= 3;
		} else {
			/* 4 bytes. */
			if (utf_8_len < 5) {
				/*
				 * Not enough room for those bytes
				 * plus a trailing '\0'.
				 */
				break;
			}
			*utf_8++ = ((uc >> 18) & 0x03) | 0xF0;
			*utf_8++ = ((uc >> 12) & 0x3F) | 0x80;
			*utf_8++ = ((uc >> 6) & 0x3F) | 0x80;
			*utf_8++ = ((uc >> 0) & 0x3F) | 0x80;
			utf_8_len -= 3;
		}
	}

	/*
	 * OK, we have enough room for (at least) a trailing '\0'.
	 * (We started out with enough room, thanks to the test
	 * for a zero-length buffer at the beginning, and if
	 * there wasn't enough room for any character we wanted
	 * to put into the buffer *plus* a trailing '\0',
	 * we'd have quit before putting it into the buffer,
	 * and thus would have left enough room for the trailing
	 * '\0'.)
	 *
	 * Drop it in.
	 */
	*utf_8 = '\0';

	/*
	 * Return a pointer to the terminating '\0', in case we
	 * want to drop something in after that.
	 */
	return (utf_8);
}

/*
 * Fixed-size output buffer for the utf_8 destination. Chosen so that
 * >=6 back-to-back 4-byte-UTF-8 surrogate pairs reliably overrun it
 * (verified by simulating the length arithmetic: with a 20-byte buffer
 * the 6th such pair writes real bytes [20,23], 4 bytes past the end),
 * while <=4 such pairs (or any amount of plain BMP content that fits)
 * complete cleanly.
 */
#define OUT_LEN 20

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	long fsz = ftell(f);
	if (fsz < 0) { fclose(f); return 1; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	unsigned char *raw = NULL;
	size_t rawlen = (size_t)fsz;
	if (rawlen > 0) {
		raw = malloc(rawlen);
		if (!raw) { fclose(f); return 1; }
		size_t got = fread(raw, 1, rawlen, f);
		if (got != rawlen) { free(raw); fclose(f); return 1; }
	}
	fclose(f);

	/* Reinterpret the raw file bytes as little-endian UTF-16 code
	 * units (2 bytes each; a trailing odd byte, if any, is dropped).
	 * Build a HEAP wchar_t array holding exactly those code units
	 * plus ONE explicit NUL terminator that we own -- this keeps the
	 * function's `while ((c = *utf_16++) != '\0')` scan bounded
	 * inside our own allocation, so any crash we observe comes from
	 * utf_16le_to_utf_8_truncated's own body, not from scaffolding
	 * reading past an unterminated buffer. */
	size_t n_units = rawlen / 2;
	wchar_t *utf16_buf = malloc((n_units + 1) * sizeof(wchar_t));
	if (!utf16_buf) { free(raw); return 1; }
	for (size_t i = 0; i < n_units; i++) {
		unsigned int lo = raw[2 * i];
		unsigned int hi = raw[2 * i + 1];
		utf16_buf[i] = (wchar_t)(lo | (hi << 8));
	}
	utf16_buf[n_units] = (wchar_t)0;
	free(raw);

	/* Heap-allocate the destination buffer with EXACTLY OUT_LEN
	 * bytes so ASAN's redzone sits immediately after it. */
	char *out = malloc(OUT_LEN);
	if (!out) { free(utf16_buf); return 1; }
	memset(out, 0xAA, OUT_LEN);

	char *end = utf_16le_to_utf_8_truncated(utf16_buf, out, (size_t)OUT_LEN);
	(void)end;

	printf("ok utf16_units=%zu produced=%ld\n", n_units,
	    (long)(end - out));

	free(out);
	free(utf16_buf);
	return 0;
}
