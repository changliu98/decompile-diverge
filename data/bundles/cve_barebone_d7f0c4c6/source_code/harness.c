/* cve_barebone direct-call harness for cve_d7f0c4c6 (gpac / CVE-2024-0321)
 * Target: gf_text_get_utf8_line (src/filters/load_text.c)
 * Bug class: missing `lineSize` bound check after UTF8 re-encoding of the input line
 * -> heap-buffer-overflow WRITE (CWE-787). See fix_commit
 * d0ced41651b279bb054eb6390751e2d4eb84819a. Full analysis: see the module docstring in
 * scripts/gen_dc_cve_d7f0c4c6.py.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include/gpac/setup.h */
typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef unsigned char u8;

/* include/gpac/tools.h */
#define GF_ARRAY_LENGTH(a) (sizeof(a) / sizeof((a)[0]))

/* include/gpac/tools.h log levels/tools -- the exact numeric values are irrelevant:
 * GF_LOG below is a no-op (pure diagnostic logging, never touches the overflow). */
#define GF_LOG_DEBUG 0
#define GF_LOG_PARSER 0
#define GF_LOG(_ll, _lt, __args) do {} while (0)

/* include/gpac/utf.h -- only reachable via unicode_type==2/3, never selected by this
 * harness (the bug is in the unicode_type<=1 branch); minimal stub keeps it linkable
 * without pulling in the whole UTF16 conversion machinery, which is incidental here. */
#define GF_UTF8_FAIL ((u32)-1)
static u32 gf_utf8_wcstombs(char *dst, u32 dst_len, const unsigned short **srcp)
{
    (void)dst; (void)dst_len; (void)srcp;
    return GF_UTF8_FAIL;
}

/* src/utils/os_file.c -- gf_fgets()/gf_fgetc() for a plain (non-GF_FileIO) FILE*,
 * which is exactly what this harness ever passes (a real fopen()'d temp file):
 * verbatim libc calls, the exact branch the real gf_fgets/gf_fgetc themselves take
 * once gf_fileio_check(stream) is false. */
static char *gf_fgets(char *ptr, size_t size, FILE *stream)
{
    return fgets(ptr, (int) size, stream);
}
static int gf_fgetc(FILE *stream)
{
    return fgetc(stream);
}

/* ==== VERBATIM from data_cve/cve_d7f0c4c6/target/original_function.c ==== */
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
					if (j >= GF_ARRAY_LENGTH(szLineConv))
						break;
					szLineConv[j] = 0xc0 | ( (szLine[i] >> 6) & 0x3 );
					j++;
					szLine[i] &= 0xbf;
				}
				/*UTF8 2 bytes char*/
				else if ( (szLine[i] & 0xe0) == 0xc0) {
					if (j >= GF_ARRAY_LENGTH(szLineConv))
						break;
					szLineConv[j] = szLine[i];
					i++;
					j++;
				}
				/*UTF8 3 bytes char*/
				else if ( (szLine[i] & 0xf0) == 0xe0) {
					if (j+1 >= GF_ARRAY_LENGTH(szLineConv))
						break;
					szLineConv[j] = szLine[i];
					i++;
					j++;
					szLineConv[j] = szLine[i];
					i++;
					j++;
				}
				/*UTF8 4 bytes char*/
				else if ( (szLine[i] & 0xf8) == 0xf0) {
					if (j+2 >= GF_ARRAY_LENGTH(szLineConv))
						break;
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

			if (j >= GF_ARRAY_LENGTH(szLineConv))
				break;

			szLineConv[j] = szLine[i];
			j++;


		}
		if ( j >= GF_ARRAY_LENGTH(szLineConv) ) {
			GF_LOG(GF_LOG_DEBUG, GF_LOG_PARSER, ("[TXTIn] Line too long to convert to utf8 (len: %d)\n", len));
			j = GF_ARRAY_LENGTH(szLineConv) -1 ;
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
}
/* ==== end verbatim ==== */

static const char *VB_LINE = "/tmp/vb_dc_cve_d7f0c4c6_line.txt";

static void vb_write_file(const char *path, const unsigned char *buf, size_t n) {
    FILE *f = fopen(path, "wb");
    if (!f) return;
    if (n) fwrite(buf, 1, n, f);
    fclose(f);
}

int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) sz = 0;
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* HEAP-allocate the raw input (ASAN-guarded). */
    unsigned char *seed = (unsigned char *)malloc((size_t)sz + 1);
    if (!seed) { fclose(f); return 0; }
    size_t n = sz > 0 ? fread(seed, 1, (size_t)sz, f) : 0;
    fclose(f);
    seed[n] = 0;

    if (n < 2) { free(seed); return 0; }

    /* seed[0] selects lineSize (the caller-supplied capacity of szLine), seed[1]'s LSB
     * selects unicode_type (0 -> the vulnerable win-CP re-encoding path is live; 1 ->
     * the inherently-safe 1:1-copy path), the remaining bytes are the raw "line"
     * content handed to gf_text_get_utf8_line() through a real FILE* (a fopen()'d temp
     * file, matching the function's real fgets()-based input contract exactly). */
    u32 lineSize = 4u + (u32)(seed[0] % 24);      /* range [4, 27] */
    s32 unicode_type = (s32)(seed[1] & 1);        /* 0 or 1 */

    size_t clen = n - 2;
    const unsigned char *content = seed + 2;

    /* Backing bytes for the line file: content + a trailing '\n' so gf_fgets/fgets
     * always terminates the line on its own terms (never relies on EOF-truncation
     * semantics beyond the lineSize cap itself). */
    unsigned char *stream_buf = (unsigned char *)malloc(clen + 1);
    if (!stream_buf) { free(seed); return 0; }
    if (clen) memcpy(stream_buf, content, clen);
    stream_buf[clen] = '\n';
    vb_write_file(VB_LINE, stream_buf, clen + 1);

    FILE *txt_in = fopen(VB_LINE, "rb");
    if (!txt_in) { free(stream_buf); free(seed); return 0; }

    /* szLine: the exact-size HEAP buffer gf_text_get_utf8_line() writes into -- ASAN's
     * redzone sits immediately past these `lineSize` bytes. */
    char *szLine = (char *)malloc(lineSize);
    if (!szLine) { fclose(txt_in); free(stream_buf); free(seed); return 0; }

    char *ret = gf_text_get_utf8_line(szLine, lineSize, txt_in, unicode_type);
    (void)ret;

    fclose(txt_in);
    free(szLine);
    free(stream_buf);
    free(seed);
    return 0;
}
