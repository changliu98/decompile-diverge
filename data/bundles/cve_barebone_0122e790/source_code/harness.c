/* cve_barebone direct-call harness for CVE-2023-28097 (opensips)
 * Target: parse_content_length  (parser/parse_content.c)
 * Bug class: signed-integer-overflow (CWE-190) at `number = number*10 + (*p)-'0';`
 *   A long run of decimal digits in the Content-Length value overflows the signed
 *   int `number` before the (too-late) `if (number<0)` guard runs -> UBSAN traps.
 *
 * The vulnerable function only depends on primitive types (char*, int*) plus the
 * project LM_ERR logging macro. opensips itself ships a no-op LM_ERR variant
 * (dprint.h:164 `#define LM_ERR( ...)`), so a no-op stub is the faithful minimal
 * stand-in for the incidental logging on the error path.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 *   + harness.flags: -fsanitize=signed-integer-overflow -fno-sanitize-recover=signed-integer-overflow
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Faithful minimal stub for the incidental logging macro (opensips ships a no-op
 * LM_ERR variant); logging has no effect on the integer-overflow bug. */
#define LM_ERR(...) ((void)0)

/* ==== VERBATIM from data_cve/cve_0122e790/target/original_function.c ==== */
char* parse_content_length( char* buffer, char* end, int* length)
{
	int number;
	char *p;
	int  size;

	p = buffer;
	/* search the beginning of the number */
	while ( p<end && (*p==' ' || *p=='\t' || (*p=='\r' && *(p+1)=='\n') ||
	(*p=='\n' && (*(p+1)==' '||*(p+1)=='\t')) ))
		p++;
	if (p==end)
		goto error;
	/* parse the number */
	size = 0;
	number = 0;
	while (p<end && *p>='0' && *p<='9') {
		number = number*10 + (*p)-'0';
		if (number<0) {
			LM_ERR("number overflow at pos %d in len number [%.*s]\n",
				(int)(p-buffer),(int)(end-buffer), buffer);
			return 0;
		}
		size ++;
		p++;
	}
	if (p==end || size==0)
		goto error;
	/* now we should have only spaces at the end */
	while ( p<end && (*p==' ' || *p=='\t' ||
	(*p=='\n' && (*(p+1)==' '||*(p+1)=='\t')) ))
		p++;
	if (p==end)
		goto error;
	/* the header ends proper? */
	if ( (*(p++)!='\n') && (*(p-1)!='\r' || *(p++)!='\n' ) )
		goto error;

	*length = number;
	return p;
error:
	LM_ERR("parse error near char [%d][%c]\n",*p,*p);
	return 0;
}
/* ==== end verbatim ==== */

int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;
	FILE* f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long sz = ftell(f);
	if (sz < 0) { fclose(f); return 0; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	/* HEAP-allocate the input so ASAN guards it. A small zero-padded guard region
	 * after the content keeps the function's legitimate one-past-`end` look-aheads
	 * (`*(p+1)` / the trailing `*(p++)` header check / the error-label `*p`) inside
	 * valid heap, so the ONLY fault a triggering input can raise is the intended
	 * CWE-190 integer overflow -- not an incidental heap read past `end`. */
	const size_t PAD = 64;
	char* buf = (char*)malloc((size_t)sz + PAD);
	if (!buf) { fclose(f); return 0; }
	size_t n = fread(buf, 1, (size_t)sz, f);
	fclose(f);
	memset(buf + n, 0, PAD);

	/* FDP-style argument construction: the whole input region is the Content-Length
	 * header value; buffer/end delimit it, length is the out-param. */
	char* buffer = buf;
	char* end = buf + n;
	int length = 0;

	char* r = parse_content_length(buffer, end, &length);
	if (r)
		fprintf(stderr, "ok len=%d off=%ld\n", length, (long)(r - buffer));

	free(buf);
	return 0;
}
