/*
 * Direct-call crash harness for cvf_c94719d8 (CVE-2017-12992, tcpdump
 * print-ripng.c, ripng_print) -- CWE-125 heap-buffer-overflow READ.
 *
 * Root cause (see the upstream fix, commit
 * e942fb84fbe3a73a98a00d2a279425872b5fb9d2, "CVE-2017-12992/RIPng: Clean up
 * bounds checking."): in the RIP6_REQUEST case, the "single dump entry"
 * short-circuit
 *
 *     j = length / sizeof(*ni);
 *     if (j == 1
 *         &&  rp->rip6_nets->rip6_metric == HOPCNT_INFINITY6
 *         &&  IN6_IS_ADDR_UNSPECIFIED(&rp->rip6_nets->rip6_dest)) { ... }
 *
 * computes "j" from "length" -- the RIPng message's OWN claimed length
 * (taken by the caller from the enclosing UDP header, fully attacker
 * controlled and INDEPENDENT of how many bytes were actually captured) --
 * and, if j==1, immediately dereferences rp->rip6_nets->rip6_metric (and,
 * short-circuit permitting, rip6_dest) WITHOUT ever checking that those
 * bytes are within ndo->ndo_snapend. The function DOES compute a
 * capture-bounded budget ("i = min(length, amt) - 4", amt = snapend - dat)
 * a few lines above, but that budget only ever gates the entry-walk loop
 * further down -- never the j==1 fast path. So a RIP6_REQUEST message that
 * (a) claims (via its enclosing length) exactly one netinfo6 record
 * (length in [20,39), sizeof(struct netinfo6)==20) but (b) is truncated in
 * the actual capture to fewer than sizeof(struct rip6)==24 bytes causes
 * ripng_print() to read struct netinfo6::rip6_metric (offset 23 from
 * "dat") straight off the end of the captured/allocated buffer --
 * heap-buffer-overflow READ, exactly the class the frozen baseline records
 * ("AddressSanitizer: heap-buffer-overflow ... in ripng_print",
 * dedup_token "ripng_print--udp_print--ip_print_demux" in the real
 * program's udp_print()->ip_print_demux()->ripng_print() call chain; here
 * we call ripng_print() directly).
 *
 * Every struct/macro/helper ripng_print() needs (struct rip6, struct
 * netinfo6, RIP6_REQUEST/RESPONSE/VERSION, HOPCNT_INFINITY6,
 * IN6_IS_ADDR_UNSPECIFIED, rip6_entry_print) is lifted VERBATIM from
 * source_code/print-ripng.c (they are literally defined immediately above
 * ripng_print() in the real file, so this is not a reconstruction -- it's
 * the same text). The one real callee that is NOT where the fault is,
 * ip6addr_string() (address/host-name stringification, addrtoname.c), is
 * replaced with a minimal non-crashing stand-in matching its real
 * signature (netdissect_options*, const void*) -> const char*; it is only
 * reachable via rip6_entry_print() on the SAFE entry-walk loop paths, never
 * on the crashing j==1 fast path.
 *
 * ---- Input file format (argv[1], read into a HEAP buffer) ----
 *   bytes [0..3]   = "length" (big-endian uint32_t), the RIPng message's
 *                    OWN claimed length as ripng_print() receives it from
 *                    its caller (udp_print(): the UDP payload length) --
 *                    entirely independent of how many bytes follow.
 *   bytes [4..EOF) = "dat", the ACTUAL captured RIPng message bytes; this
 *                    is malloc()'d on the HEAP with size == (filesize - 4)
 *                    and ndo->ndo_snapend is set to EXACTLY buf + that
 *                    size, so any out-of-bounds read lands in ASAN's heap
 *                    redzone. The corpus controls the bug purely by making
 *                    "length" (bytes 0..3) claim more netinfo6 records than
 *                    "dat" (bytes 4..EOF) actually contains.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <netinet/in.h>   /* struct in6_addr */

/* ---- base types (real names, from netdissect-stdinc.h / sys/types.h) ---- */
typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;

/* ---- netdissect.h, verbatim (trimmed to the fields/macros ripng_print
 * and rip6_entry_print actually use) ---- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int ndo_vflag;			/* verbosity level */
	const u_char *ndo_snapend;	/* global pointer to end of current packet */
	int  (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- extract.h, verbatim (x86_64: no LBL_ALIGN -> native unaligned loads) ---- */
#if defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 409)
#define UNALIGNED_OK	__attribute__((no_sanitize_undefined))
#elif defined(__has_attribute)
#if __has_attribute(no_sanitize)
#define UNALIGNED_OK	__attribute__((no_sanitize("undefined")))
#else
#define UNALIGNED_OK
#endif
#else
#define UNALIGNED_OK
#endif

static inline uint16_t UNALIGNED_OK
EXTRACT_16BITS(const void *p)
{
	return ((uint16_t)ntohs(*(const uint16_t *)(p)));
}

/* ---- addrtoname.h stand-in: the bug is not inside ip6addr_string(), and
 * it is only reached (via rip6_entry_print) on the SAFE, properly
 * bounds-checked entry-walk-loop paths -- never on the crashing j==1 fast
 * path -- so a minimal non-crashing stand-in (real signature) suffices. ---- */
static const char *
ip6addr_string(netdissect_options *ndo, const void *p)
{
	(void)ndo; (void)p;
	return "::";
}

/* ---- print-ripng.c, verbatim (structs/macros/static helper immediately
 * preceding ripng_print() in the real file) ---- */
#define	RIP6_VERSION	1

#define	RIP6_REQUEST	1
#define	RIP6_RESPONSE	2

struct netinfo6 {
	struct in6_addr	rip6_dest;
	uint16_t	rip6_tag;
	uint8_t		rip6_plen;
	uint8_t		rip6_metric;
};

struct	rip6 {
	uint8_t		rip6_cmd;
	uint8_t		rip6_vers;
	uint8_t		rip6_res1[2];
	union {
		struct	netinfo6	ru6_nets[1];
		char	ru6_tracefile[1];
	} rip6un;
#define	rip6_nets	rip6un.ru6_nets
#define	rip6_tracefile	rip6un.ru6_tracefile
};

#define	HOPCNT_INFINITY6	16

#if !defined(IN6_IS_ADDR_UNSPECIFIED) && !defined(_MSC_VER) /* MSVC inline */
static int IN6_IS_ADDR_UNSPECIFIED(const struct in6_addr *addr)
{
    static const struct in6_addr in6addr_any;        /* :: */
    return (memcmp(addr, &in6addr_any, sizeof(*addr)) == 0);
}
#endif

static int
rip6_entry_print(netdissect_options *ndo, register const struct netinfo6 *ni, int metric)
{
	int l;
	l = ND_PRINT((ndo, "%s/%d", ip6addr_string(ndo, &ni->rip6_dest), ni->rip6_plen));
	if (ni->rip6_tag)
		l += ND_PRINT((ndo, " [%d]", EXTRACT_16BITS(&ni->rip6_tag)));
	if (metric)
		l += ND_PRINT((ndo, " (%d)", ni->rip6_metric));
	return l;
}

/* ---- target function, VERBATIM from target/original_function.c ---- */
void
ripng_print(netdissect_options *ndo, const u_char *dat, unsigned int length)
{
	register const struct rip6 *rp = (const struct rip6 *)dat;
	register const struct netinfo6 *ni;
	register u_int amt;
	register u_int i;
	int j;
	int trunc;

	if (ndo->ndo_snapend < dat)
		return;
	amt = ndo->ndo_snapend - dat;
	i = min(length, amt);
	if (i < (sizeof(struct rip6) - sizeof(struct netinfo6)))
		return;
	i -= (sizeof(struct rip6) - sizeof(struct netinfo6));

	switch (rp->rip6_cmd) {

	case RIP6_REQUEST:
		j = length / sizeof(*ni);
		if (j == 1
		    &&  rp->rip6_nets->rip6_metric == HOPCNT_INFINITY6
		    &&  IN6_IS_ADDR_UNSPECIFIED(&rp->rip6_nets->rip6_dest)) {
			ND_PRINT((ndo, " ripng-req dump"));
			break;
		}
		if (j * sizeof(*ni) != length - 4)
			ND_PRINT((ndo, " ripng-req %d[%u]:", j, length));
		else
			ND_PRINT((ndo, " ripng-req %d:", j));
		trunc = ((i / sizeof(*ni)) * sizeof(*ni) != i);
		for (ni = rp->rip6_nets; i >= sizeof(*ni);
		    i -= sizeof(*ni), ++ni) {
			if (ndo->ndo_vflag > 1)
				ND_PRINT((ndo, "\n\t"));
			else
				ND_PRINT((ndo, " "));
			rip6_entry_print(ndo, ni, 0);
		}
		break;
	case RIP6_RESPONSE:
		j = length / sizeof(*ni);
		if (j * sizeof(*ni) != length - 4)
			ND_PRINT((ndo, " ripng-resp %d[%u]:", j, length));
		else
			ND_PRINT((ndo, " ripng-resp %d:", j));
		trunc = ((i / sizeof(*ni)) * sizeof(*ni) != i);
		for (ni = rp->rip6_nets; i >= sizeof(*ni);
		    i -= sizeof(*ni), ++ni) {
			if (ndo->ndo_vflag > 1)
				ND_PRINT((ndo, "\n\t"));
			else
				ND_PRINT((ndo, " "));
			rip6_entry_print(ndo, ni, ni->rip6_metric);
		}
		if (trunc)
			ND_PRINT((ndo, "[|ripng]"));
		break;
	default:
		ND_PRINT((ndo, " ripng-%d ?? %u", rp->rip6_cmd, length));
		break;
	}
	if (rp->rip6_vers != RIP6_VERSION)
		ND_PRINT((ndo, " [vers %d]", rp->rip6_vers));
}

/* ---- harness driver ---- */
static int
ndo_printf_stub(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	va_start(ap, fmt);
	int r = vfprintf(stdout, fmt, ap);
	va_end(ap);
	return r;
}

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 2;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 2;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 2; }
	long fsz = ftell(f);
	if (fsz < 4) { fclose(f); return 2; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 2; }

	unsigned char hdr[4];
	if (fread(hdr, 1, 4, f) != 4) { fclose(f); return 2; }
	uint32_t length = ((uint32_t)hdr[0] << 24) | ((uint32_t)hdr[1] << 16) |
	                   ((uint32_t)hdr[2] << 8)  |  (uint32_t)hdr[3];

	size_t dat_len = (size_t)(fsz - 4);

	/* HEAP buffer holding EXACTLY the "captured" RIPng message bytes --
	 * required so ASAN's heap redzone sits right at ndo_snapend, matching
	 * a real truncated capture. (malloc(0) is legal and returns either
	 * NULL or a unique pointer that may not be dereferenced -- dat_len==0
	 * inputs never dereference it: ripng_print's own "i < 4" guard
	 * returns before any access.) */
	unsigned char *dat = (unsigned char *)malloc(dat_len ? dat_len : 1);
	if (!dat) { fclose(f); return 2; }
	size_t got = dat_len ? fread(dat, 1, dat_len, f) : 0;
	fclose(f);
	if (got != dat_len) { free(dat); return 2; }

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_vflag = 1;
	ndo.ndo_printf = ndo_printf_stub;
	ndo.ndo_snapend = dat + dat_len;	/* exactly where the "capture" ends */

	ripng_print(&ndo, dat, (unsigned int)length);

	free(dat);
	return 0;
}
