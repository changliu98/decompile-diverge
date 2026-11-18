/*
 * Direct-call crash harness for ddiv bundle cve_299f4da7
 * (CVE-2017-13038, tcpdump print-ppp.c: handle_mlppp).
 *
 * The target function (embedded VERBATIM below, unchanged) reads two bytes
 * from its input pointer `p` via EXTRACT_16BITS(p) with no bounds check
 * against the captured packet length -- if the caller hands it a buffer
 * shorter than 2 bytes, EXTRACT_16BITS reads one byte past the end of the
 * allocation.  On the real project this is reached from handle_ppp() when
 * a truncated PPP/multilink frame is dissected; here we call handle_mlppp()
 * directly with a heap buffer sized from the input file, so a 1-byte input
 * reproduces the exact heap-buffer-overflow READ (CWE-125) with no
 * dependency on the rest of tcpdump.
 *
 * Minimal-but-faithful supporting definitions below (struct tok,
 * bittok2str()/bittok2str_internal()/strlcpy(), the ppp_ml_flag_values
 * table, EXTRACT_16BITS(), ND_PRINT()) are copied/reduced verbatim from
 * netdissect.h / extract.h / util-print.c / print-ppp.c in
 * dataset/cve_299f4da7/source_code -- real names, real field layouts,
 * real logic, nothing invented.  The only harness-authored parts are
 * main() (heap-buffer setup) and the no-op ndo_printf stub (an explicit
 * output-function-pointer stub, as permitted by the harness contract).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <arpa/inet.h>

/* ---- real BSD-ish typedefs used throughout tcpdump headers ---- */
typedef unsigned char  u_char;
typedef unsigned int   u_int;

/* ---- extract.h: EXTRACT_16BITS, x86/native-unaligned-load variant ----
 * (the variant tcpdump uses on this architecture; this is the exact
 * code path the baseline crash's dedup_token "EXTRACT_16BITS--..." names)
 */
static inline uint16_t
EXTRACT_16BITS(const void *p)
{
	return ((uint16_t)ntohs(*(const uint16_t *)(p)));
}

/* ---- netdissect.h: struct tok ---- */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

/* ---- netdissect.h: netdissect_options (minimal: only the members
 * handle_mlppp actually touches, real names/types) ---- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int   ndo_eflag;	/* print ethernet header */
	int (*ndo_printf)(netdissect_options *, const char *, ...);
};

/* ---- netdissect.h: ND_PRINT ---- */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- missing/strlcpy.c, verbatim (glibc has no strlcpy); declared before
 * bittok2str_internal() since it is used there (matches real link order,
 * where strlcpy() is declared in a header) ---- */
static size_t
strlcpy(char *dst, const char *src, size_t siz)
{
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0 && --n != 0) {
		do {
			if ((*d++ = *s++) == 0)
				break;
		} while (--n != 0);
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);	/* count does not include NUL */
}

/* ---- util-print.c: bittok2str()/bittok2str_internal(), verbatim ---- */
static char *
bittok2str_internal(register const struct tok *lp, register const char *fmt,
	   register u_int v, const char *sep)
{
        static char buf[1024+1]; /* our string buffer */
        char *bufp = buf;
        size_t space_left = sizeof(buf), string_size;
        register u_int rotbit; /* this is the bit we rotate through all bitpositions */
        register u_int tokval;
        const char * sepstr = "";

	while (lp != NULL && lp->s != NULL) {
            tokval=lp->v;   /* load our first value */
            rotbit=1;
            while (rotbit != 0) {
                /*
                 * lets AND the rotating bit with our token value
                 * and see if we have got a match
                 */
		if (tokval == (v&rotbit)) {
                    /* ok we have found something */
                    if (space_left <= 1)
                        return (buf); /* only enough room left for NUL, if that */
                    string_size = strlcpy(bufp, sepstr, space_left);
                    if (string_size >= space_left)
                        return (buf);    /* we ran out of room */
                    bufp += string_size;
                    space_left -= string_size;
                    if (space_left <= 1)
                        return (buf); /* only enough room left for NUL, if that */
                    string_size = strlcpy(bufp, lp->s, space_left);
                    if (string_size >= space_left)
                        return (buf);    /* we ran out of room */
                    bufp += string_size;
                    space_left -= string_size;
                    sepstr = sep;
                    break;
                }
                rotbit=rotbit<<1; /* no match - lets shift and try again */
            }
            lp++;
	}

        if (bufp == buf)
            /* bummer - lets print the "unknown" message as advised in the fmt string if we got one */
            (void)snprintf(buf, sizeof(buf), fmt == NULL ? "#%08x" : fmt, v);
        return (buf);
}

char *
bittok2str(register const struct tok *lp, register const char *fmt,
	   register u_int v)
{
    return (bittok2str_internal(lp, fmt, v, ", "));
}

/* ---- print-ppp.c: ppp_ml_flag_values, verbatim ---- */
static const struct tok ppp_ml_flag_values[] = {
    { 0x80, "begin" },
    { 0x40, "end" },
    { 0, NULL }
};

/* ==================================================================
 * TARGET FUNCTION -- embedded VERBATIM from
 * dataset/cve_299f4da7/target/original_function.c. Do not modify.
 * ================================================================== */
static void
handle_mlppp(netdissect_options *ndo,
             const u_char *p, int length)
{
    if (!ndo->ndo_eflag)
        ND_PRINT((ndo, "MLPPP, "));

    ND_PRINT((ndo, "seq 0x%03x, Flags [%s], length %u",
           (EXTRACT_16BITS(p))&0x0fff, /* only support 12-Bit sequence space for now */
           bittok2str(ppp_ml_flag_values, "none", *p & 0xc0),
           length));
}
/* ================================================================== */

/* Harness-authored: the ndo_printf output function pointer, stubbed to
 * discard its output (real tcpdump wires this to a vfprintf(stdout, ...)
 * wrapper; we format into a scratch buffer and drop it instead of writing
 * to stdout). It must actually consume the varargs via vsnprintf(), NOT
 * silently ignore them: with a truly no-op body the compiler can prove
 * (via inlining handle_mlppp, a single-call static function) that the
 * EXTRACT_16BITS(p) argument value is dead and elide the load entirely at
 * -O1, which would silently optimize the bug away instead of stubbing
 * "output". Routing through vsnprintf (opaque libc call) forces the real
 * heap read to happen, exactly as it would when the real ndo_printf
 * formats the string for output. */
static int
noop_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	char scratch[256];
	va_list ap;
	va_start(ap, fmt);
	int r = vsnprintf(scratch, sizeof(scratch), fmt, ap);
	va_end(ap);
	return r;
}

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	long sz = ftell(f);
	if (sz < 0) { fclose(f); return 1; }
	rewind(f);

	/* HEAP buffer sized exactly to the input file -- required so ASAN's
	 * heap redzone sits immediately after the attacker-controlled bytes
	 * and catches handle_mlppp()'s 2-byte EXTRACT_16BITS() over-read
	 * when the file is shorter than 2 bytes. */
	size_t alloc_sz = (sz > 0) ? (size_t)sz : 1;
	u_char *buf = (u_char *)malloc(alloc_sz);
	if (!buf) { fclose(f); return 1; }

	size_t n = fread(buf, 1, (size_t)sz, f);
	fclose(f);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_eflag = 0;
	ndo.ndo_printf = noop_printf;

	/* Direct call: exactly how handle_ppp() invokes handle_mlppp() --
	 * (ndo, packet-data pointer, remaining length). */
	handle_mlppp(&ndo, buf, (int)n);

	free(buf);
	return 0;
}
