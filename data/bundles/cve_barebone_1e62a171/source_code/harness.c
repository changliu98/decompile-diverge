/*
 * Direct-call crash harness for cve_1e62a171 (CVE-2017-12893, tcpdump smbutil.c,
 * name_len()). Embeds the vulnerable function VERBATIM and calls it directly on a
 * heap-allocated buffer read from argv[1], so ASan catches the exact
 * heap-buffer-overflow READ this CVE describes, with no dependency on the rest of
 * tcpdump.
 *
 * Bug recap (matches baseline dedup_token "name_len--smb_fdata1--smb_fdata" /
 * summary "smbutil.c:235:12 in name_len"): the loop condition `while (*s)`
 * dereferences the ALREADY-ADVANCED pointer `s` before the in-body bounds check
 * (`if (s >= maxbuf)`) gets a chance to run again. So if `s += (*s) + 1` walks `s`
 * past the end of the captured buffer, the very next `while (*s)` reads out of
 * bounds. `original_function.c` line 14 (`while (*s) {`) == source line 235.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char u_char;

/* ---- minimal, faithful subset of netdissect.h ---- */

/* Real struct from netdissect.h; only the field name_len()'s macros actually
 * dereference (ndo_snapend) is kept -- everything else in the real struct is
 * unused by this function. */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
    const u_char *ndo_snapend;
};

/* netdissect.h verbatim (IS_NOT_NEGATIVE / ND_TTEST2 / ND_TCHECK2) */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc

/* smb.h verbatim */
#define PTR_DIFF(p1, p2) ((size_t)(((const char *)(p1)) - (const char *)(p2)))

/* ---- target function, embedded VERBATIM from target/original_function.c ---- */
static int
name_len(netdissect_options *ndo,
         const unsigned char *s, const unsigned char *maxbuf)
{
    const unsigned char *s0 = s;
    unsigned char c;

    if (s >= maxbuf)
	return(-1);	/* name goes past the end of the buffer */
    ND_TCHECK2(*s, 1);
    c = *s;
    if ((c & 0xC0) == 0xC0)
	return(2);
    while (*s) {
	if (s >= maxbuf)
	    return(-1);	/* name goes past the end of the buffer */
	ND_TCHECK2(*s, 1);
	s += (*s) + 1;
    }
    return(PTR_DIFF(s, s0) + 1);

trunc:
    return(-1);	/* name goes past the end of the buffer */
}
/* ---- end verbatim ---- */

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
    long len = ftell(f);
    if (len < 0) { fclose(f); return 1; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }
    if (len == 0) {
        /* nothing to feed -- avoid malloc(0) edge cases */
        fclose(f);
        return 0;
    }

    /* REQUIRED: heap buffer for attacker-controlled bytes, so ASan's heap
     * redzone catches the overflow. */
    unsigned char *buf = malloc((size_t)len);
    if (!buf) { fclose(f); return 1; }
    size_t rd = fread(buf, 1, (size_t)len, f);
    fclose(f);
    if (rd != (size_t)len) { free(buf); return 1; }

    /* Set up the ndo/snapend + maxbuf the way tcpdump's SMB dissector does:
     * ndo_snapend = the end of the captured packet data (here: the whole heap
     * buffer, i.e. everything is "captured"); maxbuf = the logical end of the
     * name field the caller computed (also the buffer end here) -- matching the
     * real caller's typical case (name field runs to the end of the captured
     * SMB data). Both point exactly at buf+len so any read past the buffer is a
     * true heap-buffer-overflow. */
    netdissect_options ndo_storage;
    memset(&ndo_storage, 0, sizeof(ndo_storage));
    netdissect_options *ndo = &ndo_storage;
    ndo->ndo_snapend = buf + len;

    const unsigned char *maxbuf = buf + len;

    int r = name_len(ndo, buf, maxbuf);
    printf("name_len returned %d (len=%ld)\n", r, len);

    free(buf);
    return 0;
}
