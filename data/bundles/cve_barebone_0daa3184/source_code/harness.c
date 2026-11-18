/*
 * cve_0daa3184 -- CVE-2017-12894 direct-call ASAN harness for tcpdump's
 * lookup_bytestring() (addrtoname.c), a heap-buffer-overflow READ (CWE-125).
 *
 * Root cause (visible in target/original_function.c, unchanged):
 *   lookup_bytestring() keys a bytestringtable[] entry on ONLY the first six
 *   bytes of bs (e_addr0/1/2 = bs[0..5]) but stores the full string in
 *       tp->e_bs = calloc(1, nlen + 1);
 *   A LATER call whose bs shares those same first six bytes but has a LARGER
 *   nlen re-enters the same bucket, matches e_addr0/1/2, and runs
 *       memcmp((const char *)bs, (const char *)(tp->e_bs), nlen) == 0
 *   (target line 24 == addrtoname.c:406). That reads `nlen` bytes out of the
 *   earlier, SHORTER e_bs allocation -> heap-buffer-overflow READ, exactly the
 *   baseline dedup family
 *       MemcmpInterceptorCommon(...)--bcmp--lookup_bytestring.
 *
 * This file assembles, self-contained (compiles+links with only -lm):
 *   1. the real BSD scalar typedefs (u_char/u_short/u_int) normally from
 *      netdissect-stdinc.h;
 *   2. netdissect_options trimmed to the one field lookup_bytestring() may
 *      dereference -- ndo_error (only on a calloc failure, never on the crash
 *      path); field name + signature kept from netdissect.h (attribute macros
 *      dropped);
 *   3. HASHNAMESIZE, struct enamemem (incl. the `#define e_bs e_nsap` alias the
 *      function uses), and the bytestringtable[] global -- copied VERBATIM from
 *      addrtoname.c (lines 84, 147-159);
 *   4. the target function lookup_bytestring() pasted BYTE-FOR-BYTE from
 *      target/original_function.c (unchanged);
 *   5. main(): reads argv[1] into a HEAP buffer (malloc, so ASAN guards it),
 *      consumes two leading bytes as the two call lengths (FDP-style), points
 *      bs at the remaining heap payload, and calls lookup_bytestring() twice
 *      against the SAME payload so both land in one bucket with matching keys.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

/* ---- real BSD scalar typedefs (normally netdissect-stdinc.h) ---- */
typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;

/* ---- netdissect_options: trimmed to the ndo_error field lookup_bytestring()
 * may call (only on calloc failure -- not the crash path). Field name and
 * signature kept from netdissect.h (NORETURN/PRINTFLIKE macros dropped). ---- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	void (*ndo_error)(netdissect_options *, const char *fmt, ...);
};

/* ---- addrtoname.c line 84, verbatim ---- */
#define HASHNAMESIZE 4096

/* ---- addrtoname.c lines 147-159, verbatim (struct + the bytestring table) ---- */
struct enamemem {
	u_short e_addr0;
	u_short e_addr1;
	u_short e_addr2;
	const char *e_name;
	u_char *e_nsap;			/* used only for nsaptable[] */
#define e_bs e_nsap			/* for bytestringtable */
	struct enamemem *e_nxt;
};

static struct enamemem bytestringtable[HASHNAMESIZE];

/* ---- faithful NORETURN error callback (the real ndo_error aborts). Never
 * reached on the crash/safe paths here -- calloc does not fail. ---- */
static void vb_ndo_error(netdissect_options *ndo, const char *fmt, ...)
{
	va_list ap;
	(void)ndo;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputc('\n', stderr);
	exit(1);
}

/* ==================================================================== *
 * TARGET FUNCTION -- verbatim from target/original_function.c (unchanged)
 * ==================================================================== */
static inline struct enamemem *
lookup_bytestring(netdissect_options *ndo, register const u_char *bs,
		  const unsigned int nlen)
{
	struct enamemem *tp;
	register u_int i, j, k;

	if (nlen >= 6) {
		k = (bs[0] << 8) | bs[1];
		j = (bs[2] << 8) | bs[3];
		i = (bs[4] << 8) | bs[5];
	} else if (nlen >= 4) {
		k = (bs[0] << 8) | bs[1];
		j = (bs[2] << 8) | bs[3];
		i = 0;
	} else
		i = j = k = 0;

	tp = &bytestringtable[(i ^ j) & (HASHNAMESIZE-1)];
	while (tp->e_nxt)
		if (tp->e_addr0 == i &&
		    tp->e_addr1 == j &&
		    tp->e_addr2 == k &&
		    memcmp((const char *)bs, (const char *)(tp->e_bs), nlen) == 0)
			return tp;
		else
			tp = tp->e_nxt;

	tp->e_addr0 = i;
	tp->e_addr1 = j;
	tp->e_addr2 = k;

	tp->e_bs = (u_char *) calloc(1, nlen + 1);
	if (tp->e_bs == NULL)
		(*ndo->ndo_error)(ndo, "lookup_bytestring: calloc");

	memcpy(tp->e_bs, bs, nlen);
	tp->e_nxt = (struct enamemem *)calloc(1, sizeof(*tp));
	if (tp->e_nxt == NULL)
		(*ndo->ndo_error)(ndo, "lookup_bytestring: calloc");

	return tp;
}
/* ==================================================================== *
 * FDP driver
 *
 * Consume two leading input bytes as the two call lengths (FDP-style), point
 * bs at the remaining heap payload, and call lookup_bytestring() twice against
 * the SAME payload -- so both calls hash to one bucket with matching e_addr0/1/2
 * keys. The first call stores e_bs = calloc(nlen1+1); when the second call's
 * nlen2 > nlen1+1 its memcmp(bs, e_bs, nlen2) overruns that shorter e_bs ->
 * heap-buffer-overflow READ inside lookup_bytestring (CWE-125). When
 * nlen2 <= nlen1 the read stays in bounds -> clean exit.
 * ==================================================================== */
int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	FILE *f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	fseek(f, 0, SEEK_END);
	long sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (sz < 0) { fclose(f); return 0; }
	u_char *data = (u_char *)malloc((size_t)sz + 1);	/* HEAP so ASAN guards it */
	if (!data) { fclose(f); return 0; }
	size_t total = fread(data, 1, (size_t)sz, f);
	fclose(f);
	if (total < 2) { free(data); return 0; }

	unsigned nlen1 = data[0];
	unsigned nlen2 = data[1];
	const u_char *payload = data + 2;
	size_t plen = total - 2;
	/* keep the bs-side reads in bounds; the intended OOB is on tp->e_bs. */
	if (nlen1 > plen) nlen1 = (unsigned)plen;
	if (nlen2 > plen) nlen2 = (unsigned)plen;

	netdissect_options ndo;
	memset(&ndo, 0, sizeof ndo);
	ndo.ndo_error = vb_ndo_error;

	lookup_bytestring(&ndo, payload, nlen1);
	lookup_bytestring(&ndo, payload, nlen2);

	free(data);
	return 0;
}
