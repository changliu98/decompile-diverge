/*
 * Direct-call crash harness for CVE-2017-13031 (tcpdump, frag6_print).
 *
 * Reproduces the heap-buffer-overflow READ (CWE-125) at
 * EXTRACT_32BITS(&dp->ip6f_ident) in print-frag6.c: frag6_print() only
 * ND_TCHECK()s dp->ip6f_offlg (the first 4 bytes of struct ip6_frag) before
 * unconditionally reading dp->ip6f_ident (bytes 4..7) whenever ndo_vflag is
 * set. If the captured/allocated packet ends exactly 4 bytes past the start
 * of the fragment header, the offlg bounds check passes but the ident read
 * runs off the end of the heap buffer.
 *
 * All type/macro definitions below are copied verbatim (field names, types,
 * values) from the real tcpdump headers referenced by print-frag6.c:
 *   - struct ip6_hdr, struct ip6_frag, IP6F_OFF_MASK  <- ip6.h
 *   - ND_TTEST2/ND_TCHECK2/ND_TCHECK/ND_PRINT, netdissect_options (subset:
 *     only the fields frag6_print actually touches) <- netdissect.h
 *   - EXTRACT_16BITS/EXTRACT_32BITS (native-unaligned variant, matches the
 *     baseline crash site "extract.h:190:20 in EXTRACT_32BITS") <- extract.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <netinet/in.h>   /* struct in6_addr */
#include <arpa/inet.h>    /* ntohl/ntohs */
#include <sys/types.h>    /* u_char, u_int */

/* ---- ip6.h (verbatim subset) ---- */

#define UNALIGNED __attribute__((packed))

struct ip6_hdr {
	union {
		struct ip6_hdrctl {
			uint32_t ip6_un1_flow;	/* 20 bits of flow-ID */
			uint16_t ip6_un1_plen;	/* payload length */
			uint8_t  ip6_un1_nxt;	/* next header */
			uint8_t  ip6_un1_hlim;	/* hop limit */
		} ip6_un1;
		uint8_t ip6_un2_vfc;	/* 4 bits version, top 4 bits class */
	} ip6_ctlun;
	struct in6_addr ip6_src;	/* source address */
	struct in6_addr ip6_dst;	/* destination address */
} UNALIGNED;

#define ip6_plen	ip6_ctlun.ip6_un1.ip6_un1_plen

struct ip6_frag {
	uint8_t  ip6f_nxt;		/* next header */
	uint8_t  ip6f_reserved;	/* reserved field */
	uint16_t ip6f_offlg;		/* offset, reserved, and flag */
	uint32_t ip6f_ident;		/* identification */
} UNALIGNED;

#define IP6F_OFF_MASK		0xfff8	/* mask out offset from ip6f_offlg */

/* ---- netdissect.h (verbatim subset: only fields frag6_print uses) ---- */

typedef struct netdissect_options netdissect_options;

struct netdissect_options {
	int ndo_vflag;			/* verbosity level */
	const u_char *ndo_snapend;	/* end of captured/allocated packet */
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- extract.h (verbatim subset, native-unaligned-load variant) ---- */

static inline uint16_t
EXTRACT_16BITS(const void *p)
{
	return ((uint16_t)ntohs(*(const uint16_t *)(p)));
}

static inline uint32_t
EXTRACT_32BITS(const void *p)
{
	return ((uint32_t)ntohl(*(const uint32_t *)(p)));
}

/* ================= target function, embedded verbatim ================= */

int
frag6_print(netdissect_options *ndo, register const u_char *bp, register const u_char *bp2)
{
	register const struct ip6_frag *dp;
	register const struct ip6_hdr *ip6;

	dp = (const struct ip6_frag *)bp;
	ip6 = (const struct ip6_hdr *)bp2;

	ND_TCHECK(dp->ip6f_offlg);

	if (ndo->ndo_vflag) {
		ND_PRINT((ndo, "frag (0x%08x:%d|%ld)",
		       EXTRACT_32BITS(&dp->ip6f_ident),
		       EXTRACT_16BITS(&dp->ip6f_offlg) & IP6F_OFF_MASK,
		       sizeof(struct ip6_hdr) + EXTRACT_16BITS(&ip6->ip6_plen) -
			       (long)(bp - bp2) - sizeof(struct ip6_frag)));
	} else {
		ND_PRINT((ndo, "frag (%d|%ld)",
		       EXTRACT_16BITS(&dp->ip6f_offlg) & IP6F_OFF_MASK,
		       sizeof(struct ip6_hdr) + EXTRACT_16BITS(&ip6->ip6_plen) -
			       (long)(bp - bp2) - sizeof(struct ip6_frag)));
	}

	/* it is meaningless to decode non-first fragment */
	if ((EXTRACT_16BITS(&dp->ip6f_offlg) & IP6F_OFF_MASK) != 0)
		return -1;
	else
	{
		ND_PRINT((ndo, " "));
		return sizeof(struct ip6_frag);
	}
trunc:
	ND_PRINT((ndo, "[|frag]"));
	return -1;
}

/* ============================= harness main ============================= */

/* no-op sink for ndo_printf: we only care about the memory-safety of the
 * parse, not the formatted text it would have produced. */
static int
stub_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	(void)fmt;
	return 0;
}

/* Fragment header (struct ip6_frag) is placed right after a full IPv6
 * header, exactly as ip6_print() would hand frag6_print() "bp2" (start of
 * the IPv6 header) and "bp" (start of the next-header, here the fragment
 * header) pointers into the SAME captured packet buffer. */
#define FRAG_OFFSET (sizeof(struct ip6_hdr))

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input file>\n", argv[0]);
		return 1;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	long n = ftell(f);
	if (n < 0) { fclose(f); return 1; }
	rewind(f);

	if (n == 0) {
		/* nothing to parse */
		fclose(f);
		return 0;
	}

	/* HEAP buffer for the attacker-controlled bytes, sized EXACTLY to the
	 * input file length -- this is what lets the fragment-header read run
	 * off the end of the allocation when the file is short. */
	unsigned char *buf = (unsigned char *)malloc((size_t)n);
	if (!buf) { fclose(f); return 1; }

	size_t got = fread(buf, 1, (size_t)n, f);
	fclose(f);
	if (got != (size_t)n) { free(buf); return 1; }

	/* Need at least a full IPv6 header before the fragment header even
	 * starts, or there is nothing meaningful to feed frag6_print(). */
	if ((size_t)n < FRAG_OFFSET) {
		free(buf);
		return 0;
	}

	netdissect_options ndo_s;
	memset(&ndo_s, 0, sizeof(ndo_s));	/* zero-init unused fields */
	ndo_s.ndo_vflag = 1;			/* -v: takes the EXTRACT_32BITS(ident) path */
	ndo_s.ndo_printf = stub_printf;	/* stub output function pointer */
	ndo_s.ndo_snapend = buf + n;		/* end of the captured/allocated packet */

	const u_char *bp2 = buf;		/* start of struct ip6_hdr  */
	const u_char *bp  = buf + FRAG_OFFSET;	/* start of struct ip6_frag */

	int rc = frag6_print(&ndo_s, bp, bp2);
	(void)rc;

	free(buf);
	return 0;
}
