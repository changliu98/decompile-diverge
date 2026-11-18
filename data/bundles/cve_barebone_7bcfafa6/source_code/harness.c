/*
 * Direct-call crash harness for cve_7bcfafa6 (CVE-2022-31002, sofia-sip).
 *
 * TARGET FUNCTION: url_canonize2 (libsofia-sip-ua/url/url.c) -- embedded
 * VERBATIM below, byte-for-byte from
 * data_cve/cve_7bcfafa6/target/original_function.c.
 *
 * ROOT CAUSE (fix commit 51841eb5): when the input string s ends with a bare
 * '%' as its LAST character before the terminating NUL, the unescape path
 * does
 *     h1 = s[i + 1], h2 = s[i + 2];
 * unconditionally, with NO check that h1 itself is non-NUL before reading
 * h2. h1 == s[i+1] == '\0' (in bounds -- the terminator) but h2 == s[i+2]
 * reads ONE BYTE PAST the terminator. When s is a heap allocation sized to
 * exactly strlen(s)+1 bytes (the terminator is the very last byte of the
 * allocation), that second read is a 1-byte heap-buffer-overflow READ
 * (CWE-125) squarely inside url_canonize2's own body. The fix adds
 * `if (!h1) { *d='\0'; return NULL; }` between the two reads (see
 * https://github.com/freeswitch/sofia-sip/commit/51841eb5).
 *
 * DIRECT-CALL REPRODUCTION: main() reads argv[1] into a HEAP buffer sized to
 * EXACTLY (filesize + 1) bytes (the file's raw bytes plus our own appended
 * NUL terminator, so the allocation boundary sits exactly at the natural
 * end of the string with zero slack -- matching the real-world scenario
 * where s is some other heap-allocated string url_canonize2 is asked to
 * canonicalize, whose ASAN redzone starts immediately after the
 * terminator). A file whose LAST byte is '%' makes url_canonize2's internal
 * walk read one byte past that allocation the moment it reaches the
 * trailing '%'. `n` (max chars to scan) is passed as the full string
 * length, so it never itself blocks reaching the trailing '%'. `d` is a
 * separate, generously-sized heap output buffer (url_canonize2 never
 * writes more bytes than it reads, so the output side never itself
 * overflows) and `syn33`/`m32`/`m64`/`m96` are chosen (all zero) so that
 * IS_EXCLUDED(u,0,0,0) reduces to `u <= ' ' || u >= '\177'` -- every
 * printable ASCII filler byte (33..126) we emit is accepted verbatim, so
 * plain filler never itself causes an early `return NULL`; only a '%'
 * placed within 2 bytes of the string's end does anything interesting.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------- url.c macros (verbatim -- the IS_EXCLUDED/IS_HEX/
 * IS_SYN33 block url_canonize2's body references), copied unchanged from
 * libsofia-sip-ua/url/url.c lines ~83-141 and ~341-342. ---------------- */

#define IS_HEX(c)        (((c) >= '0' && (c) <= '9') || ((c) >= 'A' && (c) <= 'F') || ((c) >= 'a' && (c) <= 'f'))

#define IS_EXCLUDED(u, m32, m64, m96)			\
  (u <= ' '						\
   || u >= '\177'					\
   || (u < 64 ? (m32 & (1 << (63 - u)))			\
       : (u < 96 ? (m64 & (1 << (95 - u)))		\
	  : /*u < 128*/ (m96 & (1 << (127 - u))))) != 0)

#define SYN33(c) (1U << (c - 33))
#define IS_SYN33(syn33, c) ((syn33 & (1U << (c - 33))) != 0)

/* =====================================================================
 * TARGET FUNCTION -- VERBATIM from
 * data_cve/cve_7bcfafa6/target/original_function.c. DO NOT EDIT.
 * ===================================================================== */
static
char *url_canonize2(char *d, char const * const s, size_t n,
		    unsigned syn33,
		    unsigned m32, unsigned m64, unsigned m96)
{
  size_t i = 0;

  if (d == s)
    for (;s[i] && i < n; d++, i++)
      if (s[i] == '%')
	break;

  for (;s[i] && i < n; d++, i++) {
    unsigned char c = s[i], h1, h2;

    if (c != '%') {
      if (!IS_SYN33(syn33, c) && IS_EXCLUDED(c, m32, m64, m96))
	return NULL;
      *d = c;
      continue;
    }

    h1 = s[i + 1], h2 = s[i + 2];

    if (!IS_HEX(h1) || !IS_HEX(h2)) {
      *d = '\0';
      return NULL;
    }

#define UNHEX(a) (a - (a >= 'a' ? 'a' - 10 : (a >= 'A' ? 'A' - 10 : '0')))
    c = (UNHEX(h1) << 4) | UNHEX(h2);

    if (!IS_EXCLUDED(c, m32, m64, m96)) {
      /* Convert hex to normal character */
      *d = c, i += 2;
      continue;
    }

    /* Convert hex to uppercase */
    if (h1 >= 'a' /* && h1 <= 'f' */)
      h1 = h1 - 'a' + 'A';
    if (h2 >= 'a' /* && h2 <= 'f' */)
      h2 = h2 - 'a' + 'A';

    d[0] = '%', d[1] = h1, d[2] = h2;

    d +=2, i += 2;
#undef    UNHEX
  }

  *d = '\0';

  return d;
}
/* ===================================================================== */

/* ---------------- harness plumbing ---------------- */

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
	rewind(f);

	unsigned char *raw = (unsigned char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if (!raw) { fclose(f); return 1; }
	size_t got = fread(raw, 1, (size_t)fsz, f);
	fclose(f);

	/* Reject embedded NUL bytes in the raw file content (our crafted
	 * corpus never contains any) so `got` really is the string length and
	 * the heap allocation below has zero slack past the terminator. */
	for (size_t k = 0; k < got; k++) {
		if (raw[k] == '\0') { free(raw); return 0; /* not a valid probe */ }
	}

	size_t n = got;

	/* Heap-allocate the source string sized to EXACTLY n+1 bytes: the NUL
	 * terminator we append is the very last byte of the allocation, so any
	 * read past it lands in the ASAN redzone. */
	char *s = (char *)malloc(n + 1);
	if (!s) { free(raw); return 1; }
	if (n > 0)
		memcpy(s, raw, n);
	s[n] = '\0';
	free(raw);

	/* Output buffer: url_canonize2 never writes more bytes than it reads
	 * (each 3-byte "%XY" maps to <=3 output bytes, each plain byte maps to
	 * 1), so n+16 is always ample -- generous on purpose so the output
	 * side never itself trips ASAN and muddies the read-overflow signal
	 * we're after. Kept as a SEPARATE allocation from s (d != s), so
	 * url_canonize2's `if (d == s)` in-place preamble is not exercised. */
	char *d = (char *)malloc(n + 16);
	if (!d) { free(s); return 1; }
	memset(d, 0, n + 16);

	/* syn33=0, m32=m64=m96=0: IS_EXCLUDED(u,0,0,0) reduces to
	 * (u <= ' ' || u >= '\177'), so every printable ASCII filler byte
	 * (33..126) we emit is accepted verbatim -- only a trailing bare '%'
	 * does anything interesting. */
	url_canonize2(d, s, n, 0u, 0u, 0u, 0u);

	free(s);
	free(d);
	return 0;
}
