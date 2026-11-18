/*
 * Direct-call crash harness for cvf_7a395d06 (tcpdump print-chdlc.c, CVE-2017-13687, CWE-125).
 *
 * The target function `chdlc_if_print` only guards `caplen < CHDLC_HDRLEN` (4) before
 * dispatching to `chdlc_print(ndo, p, h->len)`. The actual out-of-bounds READ is inside
 * `chdlc_print` itself: in the ETHERTYPE_ISO case it dereferences `*(p+1)` (the byte right
 * after the 4-byte CHDLC header) with NO bounds check at all -- if the captured packet is
 * only 4 or 5 bytes (caplen<=5), that read runs 1-2 bytes past the end of the packet buffer.
 * (Fixed upstream in a1eefe986065846b6c69dbc09afd9fa1a02c4a3d by adding
 * `if (length < 2) goto trunc; ND_TCHECK_16BITS(p);` before the dereference.)
 *
 * `chdlc_if_print` is embedded VERBATIM (target/original_function.c, byte-for-byte).
 * `chdlc_print` -- the real fault site, a direct callee -- is also embedded VERBATIM from
 * source_code/print-chdlc.c. Everything else (netdissect_options fields actually touched,
 * pcap_pkthdr, the EXTRACT_16BITS macro, the ND_PRINT/ND_TCHECK2 macros, the CHDLC_ and
 * ETHERTYPE_ constants, the chdlc_cast_values table) is copied with REAL names from the real headers
 * (netdissect.h / chdlc.h / ethertype.h / extract.h). `chdlc_print`'s own non-fault-site
 * callees (ip_print/ip6_print/mpls_print/isoclns_print/chdlc_slarp_print/tok2str) are stubbed
 * as no-ops purely so the verbatim body links -- none of them is on the crashing path.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <arpa/inet.h>

/* ---- chdlc.h (verbatim macros) ---- */
#define CHDLC_HDRLEN 		4
#define CHDLC_UNICAST		0x0f
#define CHDLC_BCAST		0x8f
#define CHDLC_TYPE_SLARP	0x8035
#define CHDLC_TYPE_CDP		0x2000

/* ---- ethertype.h (verbatim values) ---- */
#define	ETHERTYPE_IP		0x0800
#define ETHERTYPE_IPV6		0x86dd
#define	ETHERTYPE_MPLS		0x8847
#define	ETHERTYPE_MPLS_MULTI	0x8848
#define	ETHERTYPE_ISO           0xfefe  /* nonstandard - used in Cisco HDLC encapsulation */

/* ---- netdissect.h: struct tok (verbatim) ---- */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};
extern const char *tok2str(const struct tok *, const char *, u_int);
extern const struct tok ethertype_values[];

/* ---- netdissect.h: forward decls of chdlc_print's non-fault-site callees (verbatim signatures) ---- */
typedef struct netdissect_options netdissect_options;
void ip_print(netdissect_options *, const u_char *, u_int);
void ip6_print(netdissect_options *, const u_char *, u_int);
void mpls_print(netdissect_options *, const u_char *, u_int);
void isoclns_print(netdissect_options *, const u_char *, u_int, u_int);
u_int chdlc_print(netdissect_options *, const u_char *, u_int);

/*
 * netdissect_options -- minimal but FAITHFUL subset (real field names, from netdissect.h)
 * of the fields chdlc_if_print/chdlc_print actually touch: ndo_eflag, ndo_vflag, ndo_printf,
 * ndo_snapend.
 */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int ndo_eflag;			/* print ethernet header */
	int ndo_vflag;			/* verbosity level */
	const u_char *ndo_snapend;	/* end of captured packet data */
	int  (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---- netdissect.h macros (verbatim) ---- */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- extract.h: EXTRACT_16BITS (verbatim, natively-unaligned x86 variant) ---- */
typedef struct { uint16_t val; } __attribute__((packed)) unaligned_uint16_t;
static inline uint16_t
EXTRACT_16BITS(const void *p)
{
	return ((uint16_t)ntohs(*(const uint16_t *)(p)));
}

/* ---- pcap_pkthdr (real field names: ts/caplen/len; minimal standalone redefinition) ---- */
struct pcap_pkthdr {
	struct { long tv_sec; long tv_usec; } ts;
	uint32_t caplen;
	uint32_t len;
};

/* ================= print-chdlc.c (verbatim excerpt) ================= */

static void chdlc_slarp_print(netdissect_options *, const u_char *, u_int);

static const struct tok chdlc_cast_values[] = {
    { CHDLC_UNICAST, "unicast" },
    { CHDLC_BCAST, "bcast" },
    { 0, NULL}
};


/* Standard CHDLC printer */
u_int
chdlc_if_print(netdissect_options *ndo, const struct pcap_pkthdr *h, register const u_char *p)
{
	register u_int length = h->len;
	register u_int caplen = h->caplen;

	if (caplen < CHDLC_HDRLEN) {
		ND_PRINT((ndo, "[|chdlc]"));
		return (caplen);
	}
        return (chdlc_print(ndo, p,length));
}

u_int
chdlc_print(netdissect_options *ndo, register const u_char *p, u_int length)
{
	u_int proto;

	proto = EXTRACT_16BITS(&p[2]);
	if (ndo->ndo_eflag) {
                ND_PRINT((ndo, "%s, ethertype %s (0x%04x), length %u: ",
                       tok2str(chdlc_cast_values, "0x%02x", p[0]),
                       tok2str(ethertype_values, "Unknown", proto),
                       proto,
                       length));
	}

	length -= CHDLC_HDRLEN;
	p += CHDLC_HDRLEN;

	switch (proto) {
	case ETHERTYPE_IP:
		ip_print(ndo, p, length);
		break;
	case ETHERTYPE_IPV6:
		ip6_print(ndo, p, length);
		break;
	case CHDLC_TYPE_SLARP:
		chdlc_slarp_print(ndo, p, length);
		break;
#if 0
	case CHDLC_TYPE_CDP:
		chdlc_cdp_print(p, length);
		break;
#endif
        case ETHERTYPE_MPLS:
        case ETHERTYPE_MPLS_MULTI:
                mpls_print(ndo, p, length);
		break;
        case ETHERTYPE_ISO:
                /* is the fudge byte set ? lets verify by spotting ISO headers */
                if (*(p+1) == 0x81 ||
                    *(p+1) == 0x82 ||
                    *(p+1) == 0x83)
                    isoclns_print(ndo, p + 1, length - 1, ndo->ndo_snapend - p - 1);
                else
                    isoclns_print(ndo, p, length, ndo->ndo_snapend - p);
                break;
	default:
                if (!ndo->ndo_eflag)
                        ND_PRINT((ndo, "unknown CHDLC protocol (0x%04x)", proto));
                break;
	}

	return (CHDLC_HDRLEN);
}

/* ================= end print-chdlc.c verbatim excerpt ================= */

/*
 * Non-fault-site callees of chdlc_print, stubbed as no-ops purely for linkage.
 * The OOB read (`*(p+1)`) happens BEFORE any of these are ever reached on the
 * triggering inputs; ip_print/ip6_print/mpls_print/isoclns_print are only invoked
 * on the (deliberately in-bounds) SAFE corpus inputs, where a no-op is exactly
 * correct (real tcpdump would just keep printing -- behavior irrelevant here).
 */
void ip_print(netdissect_options *ndo, const u_char *bp, u_int length) { (void)ndo; (void)bp; (void)length; }
void ip6_print(netdissect_options *ndo, const u_char *bp, u_int length) { (void)ndo; (void)bp; (void)length; }
void mpls_print(netdissect_options *ndo, const u_char *bp, u_int length) { (void)ndo; (void)bp; (void)length; }
void isoclns_print(netdissect_options *ndo, const u_char *bp, u_int length, u_int t) { (void)ndo; (void)bp; (void)length; (void)t; }

static void
chdlc_slarp_print(netdissect_options *ndo, const u_char *cp, u_int length)
{
	/* not the fault site (dedup_token top frame is chdlc_print itself); no-op stub */
	(void)ndo; (void)cp; (void)length;
}

const char *
tok2str(const struct tok *lp, const char *fmt, u_int v)
{
	(void)lp; (void)fmt; (void)v;
	return "?";
}

const struct tok ethertype_values[] = { { 0, NULL } };

static int
nd_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo; (void)fmt;
	return 0;
}

/* ================= main: direct call, heap buffer, single call ================= */

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
	long sz = ftell(f);
	if (sz < 0) { fclose(f); return 2; }
	rewind(f);

	/* Heap buffer for the attacker-controlled packet bytes -- REQUIRED so ASAN's
	 * heap-buffer-overflow redzone catches the out-of-bounds read. */
	size_t n = (size_t)sz;
	u_char *buf = (u_char *)malloc(n > 0 ? n : 1);
	if (!buf) { fclose(f); return 2; }
	if (n > 0 && fread(buf, 1, n, f) != n) { fclose(f); free(buf); return 2; }
	fclose(f);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_eflag = 0;
	ndo.ndo_vflag = 0;
	ndo.ndo_printf = nd_printf;
	ndo.ndo_snapend = buf + n;	/* exactly n bytes were captured/allocated */

	struct pcap_pkthdr h;
	memset(&h, 0, sizeof(h));
	h.caplen = (uint32_t)n;
	h.len = (uint32_t)n;

	/* single direct call to the target function */
	(void)chdlc_if_print(&ndo, &h, buf);

	free(buf);
	return 0;
}
