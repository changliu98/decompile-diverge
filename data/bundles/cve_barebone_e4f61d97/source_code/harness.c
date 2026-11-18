/* cve_barebone direct-call harness for cve_e4f61d97 (sofia-sip)
 * Target: url_canonize2  (libsofia-sip-ua/url/url.c)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * url_canonize2(d, s, n, syn33, m32, m64, m96) canonicalizes up to `n` bytes of
 * the component `s` into `d`. Its main loop is:
 *
 *     for (; s[i] && i < n; d++, i++) { ... }
 *
 * `&&` evaluates left-to-right: `s[i]` is read FIRST, UNCONDITIONALLY, on every
 * re-check of the loop condition -- including the final one that decides
 * whether to stop -- and only afterwards is `i < n` consulted. For an
 * ordinarily NUL-terminated C string this is harmless (the NUL byte itself is
 * always a valid in-bounds read, so the loop always finds its stop condition
 * via `s[i]==0` at or before index n). But url_canonize2's own signature takes
 * an explicit LENGTH `n` -- "operate on these n bytes of s" is its entire
 * contract -- and nothing in the function requires or checks that `s[n]` (one
 * byte past the described range) is safely readable. A caller that honors the
 * length-prefixed contract literally -- allocating exactly `n` bytes for `s`
 * with no trailing NUL, e.g. a length-prefixed buffer straight off a parser or
 * a fuzz harness calling this internal helper in isolation -- makes the loop's
 * own termination re-check, once i reaches n, read `s[n]`: one byte past the
 * allocation => ASAN heap-buffer-overflow, READ of size 1, inside
 * url_canonize2's own loop condition (no project callee, no elaborate object
 * state -- just `d`, `s`, `n` and the four mask/syn33 scalars).
 *
 * (The upstream fix_commit a99804b336d0e16d26ab7119d56184d2d7110a36 patches
 * the identical *pattern* -- an unchecked `s[n]` read past a length-prefixed-
 * but-not-necessarily-long-enough buffer -- in this same source drop's
 * sip_parser.c:sip_method_d via `if (strlen(s) < n) return
 * sip_method_invalid;`. url_canonize2 carries the same unguarded `s[n]` read
 * in its own loop condition; reproduced here in isolation.)
 *
 * IS_HEX / IS_EXCLUDED / IS_SYN33 are url_canonize2's own macros, reproduced
 * verbatim (real names) from libsofia-sip-ua/url/url.c and
 * libsofia-sip-ua/bnf/sofia-sip/bnf.h -- no invented behaviour.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- libsofia-sip-ua/bnf/sofia-sip/bnf.h (verbatim) ---- */
#define IS_HEX(c)        (((c) >= '0' && (c) <= '9') || ((c) >= 'A' && (c) <= 'F') || ((c) >= 'a' && (c) <= 'f'))

/* ---- libsofia-sip-ua/url/url.c (verbatim, immediately above url_canonize2) ---- */
#define IS_EXCLUDED(u, m32, m64, m96)			\
  (u <= ' '						\
   || u >= '\177'					\
   || (u < 64 ? (m32 & (1 << (63 - u)))			\
       : (u < 96 ? (m64 & (1 << (95 - u)))		\
	  : /*u < 128*/ (m96 & (1 << (127 - u))))) != 0)

#define SYN33(c) (1U << (c - 33))
#define IS_SYN33(syn33, c) ((syn33 & (1U << (c - 33))) != 0)

/* ==== VERBATIM from data_cve/cve_e4f61d97/target/original_function.c ==== */
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

    h1 = s[i + 1];
    if (!h1) {
        *d = '\0';
        return NULL;
    }
    h2 = s[i + 2];

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
/* ==== end verbatim ==== */

int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }
    if (sz <= 0) { fclose(f); return 0; }

    size_t n = (size_t)sz;

    /* HEAP-allocate the raw file bytes as the `s` buffer, sized EXACTLY `n`
     * bytes -- the length url_canonize2 is told about -- with NO trailing NUL.
     * This is the literal, faithful reading of the function's own
     * length-prefixed contract: "s has n valid bytes". */
    char *s = (char *)malloc(n);
    if (!s) { fclose(f); return 0; }
    size_t got = fread(s, 1, n, f);
    fclose(f);
    if (got != n) { free(s); return 0; }

    /* Destination buffer: generous + zero-filled. This harness exercises the
     * READ-side bug (the loop condition's own s[i] check); output can never
     * exceed n+1 bytes (1 byte written per input byte consumed, at most), so
     * n+8 slack makes sure a write is never anywhere near its own bound --
     * the fault under test is exclusively the s[] over-read. */
    char *d = (char *)malloc(n + 8);
    if (!d) { free(s); return 0; }
    memset(d, 0, n + 8);

    /* syn33/m32/m64/m96 all clear => IS_EXCLUDED(c,...) reduces to
     * `c <= ' ' || c >= 0177`: every printable ASCII byte ('!'..'~',
     * 0x21..0x7e) is accepted, so a printable-only input runs the loop for
     * its FULL n bytes and hits the s[n] read. An input with an embedded
     * NUL byte instead makes the loop stop at that NUL (a valid in-bounds
     * read) with no out-of-bounds access at all -- the SAFE control case,
     * driven through the exact same call with the exact same arguments. */
    unsigned syn33 = 0, m32 = 0, m64 = 0, m96 = 0;

    /* volatile function-pointer indirect call: defeats inlining url_canonize2
     * into main, so it stays a real, separately-symbolized stack frame in the
     * ASAN report. */
    char *(*volatile canon)(char *, char const * const, size_t,
                             unsigned, unsigned, unsigned, unsigned) = url_canonize2;
    char *r = canon(d, s, n, syn33, m32, m64, m96);
    (void)r;

    free(s);
    free(d);
    return 0;
}
