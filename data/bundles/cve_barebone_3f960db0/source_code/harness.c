/*
 * cve_barebone direct-call harness for a gpac stack-buffer-overflow
 * (fix commit 377ab25f3e502db2934a9cf4b54739e1c89a02ff, project gpac).
 * target: gf_text_get_utf8_line  (src/filters/load_text.c)  CWE-787 stack OOB WRITE
 *
 * The real bug: gf_text_get_utf8_line() re-encodes a line read from a text file
 * into a FIXED 2048-byte stack buffer `char szLineConv[2048]`, walking the input
 * byte-by-byte with a running output index `j`. For a plain ASCII byte it does a
 * single `szLineConv[j] = szLine[i]; j++;` and only THEN checks
 * `if (j >= GF_ARRAY_LENGTH(szLineConv) - 1) break;` -- one write, one check, so
 * that path is self-limiting and safe.
 *
 * BUT the four multi-byte "raw win-CP / UTF-8 2/3/4-byte" decode branches each
 * write 1, 1, 2 or 3 bytes to szLineConv[j..] BEFORE that check ever runs (the
 * check sits only after the shared fallthrough write that follows the whole
 * if/else-if chain). For the 3-byte and 4-byte UTF-8 branches this means up to
 * 3 unchecked writes happen in a single loop iteration, and the fallthrough
 * write immediately after them is the FIRST place `j` is re-validated. If the
 * running index `j` is already within 1-2 bytes of the 2048 boundary when a
 * UTF-8 3- or 4-byte lead byte (0xE0-0xEF / 0xF0-0xF7) is seen, the branch's
 * own writes plus the fallthrough write land at index 2048 (and beyond) --
 * one-or-more bytes past the end of the 2048-byte stack array. This harness
 * puts a 2045- or 2046-byte run of ordinary bytes right before such a lead
 * byte so `j` is sitting exactly on that edge when the multi-byte branch
 * fires -> stack-buffer-overflow WRITE inside gf_text_get_utf8_line's own
 * frame (CWE-787).
 *
 * The upstream fix (377ab25f) adds a `if (j [+1|+2] >= GF_ARRAY_LENGTH(szLineConv))
 * break;` guard in front of every one of those branches (and folds the trailing
 * NUL-terminator write into a single post-loop clamp), closing exactly this gap.
 *
 * main() mimics a real caller (all in-tree callers pass `lineSize == 2048`,
 * matching szLineConv's own size; this harness passes a larger `lineSize` so
 * gf_fgets()/fgets() can actually deliver the full crafted line up to and past
 * the 2048-byte edge -- gf_text_get_utf8_line's own body, the vulnerable
 * function, is untouched by that choice): it reads the whole input file into a
 * malloc'd HEAP buffer, opens that heap buffer as a FILE* via fmemopen() (so
 * the exact bytes gf_fgets()/fgets() reads are the attacker-controlled file
 * content), allocates a heap `szLine` scratch buffer, and calls
 * gf_text_get_utf8_line(szLine, lineSize, txt_in, /*unicode_type=*//*0) once,
 * directly -- unicode_type==0 is required to enter the vulnerable multi-byte
 * decode branches at all (`!unicode_type && (szLine[i] & 0x80)`).
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- include/gpac/setup.h (verbatim names, standard x86_64 Linux sizes) ---- */
typedef unsigned int   u32;
typedef int             s32;
typedef unsigned short u16;

/* ---- include/gpac/tools.h ---- */
#define GF_ARRAY_LENGTH(a) (sizeof(a) / sizeof((a)[0]))

/* Logging is incidental to the bug -- GF_LOG only fires on the SAFE
 * "line too long, truncated" break path, never on the crash itself (ASAN
 * aborts at the offending store before this line could run). Stub it as a
 * no-op so the full gf_log_* subsystem isn't needed; the preprocessor never
 * substitutes GF_LOG_DEBUG/GF_LOG_PARSER into the (unused) macro body, so
 * they don't need separate definitions either. */
#define GF_LOG(_ll, _lm, __args) ((void) 0)

/* ---- include/gpac/utf.h ----
 * u32 gf_utf8_wcstombs(char* dst, size_t dst_len, const unsigned short** srcp);
 * Only called from the unicode_type>=2 (UTF-16) branch of the target, which
 * this harness never takes (unicode_type is fixed at 0) -- the call is still
 * present in the compiled function body, so the symbol must exist to link.
 * Unreachable stub. */
#define GF_UTF8_FAIL 0xFFFFFFFF
u32 gf_utf8_wcstombs(char *dst, size_t dst_len, const unsigned short **srcp)
{
	(void) dst; (void) dst_len; (void) srcp;
	return GF_UTF8_FAIL;
}

/* ---- src/utils/os_file.c ----
 * char *gf_fgets(char *ptr, size_t size, FILE *stream)
 * Real body:
 *   GF_EXPORT
 *   char *gf_fgets(char *ptr, size_t size, FILE *stream)
 *   {
 *       if (gf_fileio_check(stream)) { ... GF_FileIO virtual-fs path ... }
 *       return fgets(ptr, (u32) size, stream);
 *   }
 * This harness only ever calls gf_text_get_utf8_line with a plain FILE*
 * (never a GF_FileIO), so gf_fileio_check() would always be false and the
 * real function always falls through to `return fgets(ptr, (u32) size,
 * stream);` -- reproduced verbatim (the GF_FileIO branch is dead code on
 * this call path, so it is omitted rather than faithfully-stubbed). */
char *gf_fgets(char *ptr, size_t size, FILE *stream)
{
	return fgets(ptr, (int) size, stream);
}

/* ---- src/utils/os_file.c ----
 * int gf_fgetc(FILE *stream)
 * Only reached at the very end of gf_text_get_utf8_line when unicode_type==3,
 * never on this harness's unicode_type==0 trigger path. Real body for a
 * plain FILE* is `return fgetc(stream);` (same reasoning as gf_fgets above). */
int gf_fgetc(FILE *stream)
{
	return fgetc(stream);
}

/* ===================================================================== */
/* ==== TARGET FUNCTION: gf_text_get_utf8_line, byte-for-byte from    ==== */
/* ==== data_cve/cve_3f960db0/target/original_function.c              ==== */
/* ===================================================================== */
char *gf_text_get_utf8_line(char *szLine, u32 lineSize, FILE *txt_in, s32 unicode_type)
{
	u32 i, j, len;
	char *sOK;
	char szLineConv[2048];
	unsigned short *sptr;

	memset(szLine, 0, sizeof(char)*lineSize);
	sOK = gf_fgets(szLine, lineSize, txt_in);
	if (!sOK) return NULL;
	if (unicode_type<=1) {
		j=0;
		len = (u32) strlen(szLine);
		for (i=0; i<len; i++) {
			if (!unicode_type && (szLine[i] & 0x80)) {
				/*non UTF8 (likely some win-CP)*/
				if ((szLine[i+1] & 0xc0) != 0x80) {
					szLineConv[j] = 0xc0 | ( (szLine[i] >> 6) & 0x3 );
					j++;
					szLine[i] &= 0xbf;
				}
				/*UTF8 2 bytes char*/
				else if ( (szLine[i] & 0xe0) == 0xc0) {
					szLineConv[j] = szLine[i];
					i++;
					j++;
				}
				/*UTF8 3 bytes char*/
				else if ( (szLine[i] & 0xf0) == 0xe0) {
					szLineConv[j] = szLine[i];
					i++;
					j++;
					szLineConv[j] = szLine[i];
					i++;
					j++;
				}
				/*UTF8 4 bytes char*/
				else if ( (szLine[i] & 0xf8) == 0xf0) {
					szLineConv[j] = szLine[i];
					i++;
					j++;
					szLineConv[j] = szLine[i];
					i++;
					j++;
					szLineConv[j] = szLine[i];
					i++;
					j++;
				} else {
					i+=1;
					continue;
				}
			}
			szLineConv[j] = szLine[i];
			j++;

			if (j >= GF_ARRAY_LENGTH(szLineConv) - 1) {
				GF_LOG(GF_LOG_DEBUG, GF_LOG_PARSER, ("[TXTIn] Line too long to convert to utf8 (len: %d)\n", len));
				break;
			}

		}
		szLineConv[j] = 0;
		strcpy(szLine, szLineConv);
		return sOK;
	}

#ifdef GPAC_BIG_ENDIAN
	if (unicode_type==3)
#else
	if (unicode_type==2)
#endif
	{
		i=0;
		while (1) {
			char c;
			if (!szLine[i] && !szLine[i+1]) break;
			c = szLine[i+1];
			szLine[i+1] = szLine[i];
			szLine[i] = c;
			i+=2;
		}
	}
	sptr = (u16 *)szLine;
	i = gf_utf8_wcstombs(szLineConv, 2048, (const unsigned short **) &sptr);
	if (i == GF_UTF8_FAIL) i = 0;
	szLineConv[i] = 0;
	strcpy(szLine, szLineConv);
	/*this is ugly indeed: since input is UTF16-LE, there are many chances the gf_fgets never reads the \0 after a \n*/
	if (unicode_type==3) gf_fgetc(txt_in);
	return sOK;
}/* ===================================================================== */
/* ==== END TARGET FUNCTION ==== */
/* ===================================================================== */

/* -------------------------- driver -------------------------- */
#define VB_LINE_SIZE 4096  /* > 2048 headroom so gf_fgets/fgets can deliver a
                             * crafted line all the way up to and past the
                             * szLineConv[2048] edge; does not touch the
                             * target function's own body. */

int main(int argc, char **argv)
{
	if (argc < 2) {
		return 0;
	}

	FILE *f = fopen(argv[1], "rb");
	if (f == NULL) {
		return 0;
	}
	if (fseek(f, 0, SEEK_END) != 0) {
		fclose(f);
		return 0;
	}
	long sz = ftell(f);
	if (sz < 0) {
		fclose(f);
		return 0;
	}
	rewind(f);

	/* HEAP-allocated input buffer so any over-read of the raw file bytes
	 * themselves would also be ASAN-visible. */
	unsigned char *filebuf = (unsigned char *) malloc(sz ? (size_t) sz : 1);
	if (filebuf == NULL) {
		fclose(f);
		return 0;
	}
	size_t got = (sz > 0) ? fread(filebuf, 1, (size_t) sz, f) : 0;
	fclose(f);

	/* Open the heap buffer as a FILE* so gf_fgets()/fgets() reads the exact
	 * attacker-controlled bytes, matching a real caller handing
	 * gf_text_get_utf8_line a FILE* positioned over untrusted file content. */
	FILE *txt_in = fmemopen(filebuf, got, "rb");
	if (txt_in == NULL) {
		free(filebuf);
		return 0;
	}

	char *szLine = (char *) malloc(VB_LINE_SIZE);
	if (szLine == NULL) {
		fclose(txt_in);
		free(filebuf);
		return 0;
	}

	/* indirect call through a volatile pointer keeps the target a real,
	 * non-inlined frame so it appears by name in the ASAN crash stack. */
	char *(*volatile fn)(char *, u32, FILE *, s32) = gf_text_get_utf8_line;

	/* unicode_type = 0 is required to enter the vulnerable multi-byte
	 * decode branches at all (`if (!unicode_type && (szLine[i] & 0x80))`). */
	char *r = fn(szLine, (u32) VB_LINE_SIZE, txt_in, /*unicode_type=*/0);

	fprintf(stderr, "gf_text_get_utf8_line returned %s\n", r ? "line" : "NULL");

	fclose(txt_in);
	free(szLine);
	free(filebuf);
	return 0;
}
