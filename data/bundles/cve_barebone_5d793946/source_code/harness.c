/*
 * Direct-call crash harness for cvf_5d793946 (CVE-2017-13043, CWE-125,
 * tcpdump print-bgp.c, decode_multicast_vpn()).
 *
 * Bug recap (matches baseline dedup_token
 * "EXTRACT_32BITS--decode_multicast_vpn--bgp_attr_print" / summary
 * "AddressSanitizer: heap-buffer-overflow /work/./extract.h:190:20 in
 * EXTRACT_32BITS"):
 *
 * In the BGP_MULTICAST_VPN_ROUTE_TYPE_SHARED_TREE_JOIN /
 * BGP_MULTICAST_VPN_ROUTE_TYPE_SOURCE_TREE_JOIN cases (original_function.c
 * lines 60-71, source print-bgp.c ~966-974):
 *
 *     ND_TCHECK2(pptr[0], BGP_VPN_RD_LEN);          // proves 8 bytes present
 *     ...
 *     snprintf(buf + offset, buflen - offset, ", RD: %s, Source-AS %s",
 *         bgp_vpn_rd_print(ndo, pptr),
 *         as_printf(ndo, astostr, sizeof(astostr),
 *         EXTRACT_32BITS(pptr + BGP_VPN_RD_LEN)));  // reads 4 MORE bytes
 *
 * ND_TCHECK2(pptr[0], BGP_VPN_RD_LEN) (BGP_VPN_RD_LEN == 8) only proves
 * pptr[0..7] are captured. But EXTRACT_32BITS(pptr + BGP_VPN_RD_LEN) reads
 * a fixed 4 bytes starting at pptr[8], i.e. pptr[8..11] -- 4 bytes past the
 * end of the window the check actually verified. (Contrast the sibling
 * BGP_MULTICAST_VPN_ROUTE_TYPE_INTER_AS_I_PMSI case a few lines up, which
 * correctly checks `ND_TCHECK2(pptr[0], BGP_VPN_RD_LEN + 4)` before the
 * same EXTRACT_32BITS(pptr + BGP_VPN_RD_LEN) -- this is exactly the missing
 * "+ 4" that CVE-2017-13043 fixes.) So whenever the captured buffer has
 * between 10 and 13 bytes from pptr[0] (i.e. the initial 2-byte
 * route_type/route_length header + exactly the 8-byte RD, but fewer than
 * the needed 12), the check passes vacuously and EXTRACT_32BITS reads into
 * the ASan redzone right after the heap allocation -> heap-buffer-overflow
 * READ, CWE-125.
 *
 * main() mimics the real caller (bgp_attr_print() in print-bgp.c, which
 * calls `decode_multicast_vpn(ndo, tptr, buf, sizeof(buf))` with tptr
 * pointing into the captured packet buffer): it reads argv[1] into a
 * malloc'd heap buffer sized EXACTLY to the file length (heap required so
 * ASan's redzone sits immediately past the real data), sets
 * ndo->ndo_snapend = data + len (only the file's own bytes are "captured"),
 * and calls decode_multicast_vpn(&ndo, data, buf, sizeof(buf)) once,
 * directly, with buf/buflen matching the real caller's local
 * `char buf[MAXHOSTNAMELEN + 100]`.
 *
 * decode_multicast_vpn's own switch references ALL of its real callees
 * (bgp_vpn_rd_print, bgp_vpn_ip_print, bgp_vpn_sg_print, as_printf,
 * tok2str) regardless of which route_type the input selects at runtime, so
 * all are embedded verbatim from print-bgp.c/util-print.c below. The two
 * that end up doing IPv4/IPv6-address-to-string formatting
 * (ipaddr_string/getname, ip6addr_string/getname6) are NOT on the crash
 * path -- the real addrtoname.c versions do DNS-hostname-cache lookups we
 * neither need nor want inside a --network none sandbox, so those two are
 * kept as minimal-but-real-named numeric-only substitutes (real function
 * names/signatures, always the "-n"/numeric path -- exactly what the real
 * getname()/getname6() do when ndo_nflag is set) built on the verbatim
 * intoa() helper.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>    /* ntohs/ntohl/inet_ntop */
#include <netinet/in.h>   /* struct in6_addr, INET6_ADDRSTRLEN */

/* ---- minimal but faithful type/macro defs (real names, from
 * netdissect-stdinc.h / netdissect.h / extract.h / print-bgp.c) ---- */

typedef unsigned char u_char;
typedef unsigned int u_int;

#define MAXHOSTNAMELEN	64

struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int ndo_bflag;			/* print 4 byte ASes in ASDOT notation */
	const u_char *ndo_snapend;	/* global pointer to end of current packet */
};

/* extract.h -- native (non-LBL_ALIGN) unaligned-load variant */
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

static inline uint32_t UNALIGNED_OK
EXTRACT_32BITS(const void *p)
{
	return ((uint32_t)ntohl(*(const uint32_t *)(p)));
}

/* netdissect.h -- "l" bytes of "var" captured? (verbatim) */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

/* print-bgp.c verbatim defines */
#define BGP_VPN_RD_LEN                  8

#define BGP_MULTICAST_VPN_ROUTE_TYPE_INTRA_AS_I_PMSI   1
#define BGP_MULTICAST_VPN_ROUTE_TYPE_INTER_AS_I_PMSI   2
#define BGP_MULTICAST_VPN_ROUTE_TYPE_S_PMSI            3
#define BGP_MULTICAST_VPN_ROUTE_TYPE_INTRA_AS_SEG_LEAF 4
#define BGP_MULTICAST_VPN_ROUTE_TYPE_SOURCE_ACTIVE     5
#define BGP_MULTICAST_VPN_ROUTE_TYPE_SHARED_TREE_JOIN  6
#define BGP_MULTICAST_VPN_ROUTE_TYPE_SOURCE_TREE_JOIN  7

static const struct tok bgp_multicast_vpn_route_type_values[] = {
    { BGP_MULTICAST_VPN_ROUTE_TYPE_INTRA_AS_I_PMSI, "Intra-AS I-PMSI"},
    { BGP_MULTICAST_VPN_ROUTE_TYPE_INTER_AS_I_PMSI, "Inter-AS I-PMSI"},
    { BGP_MULTICAST_VPN_ROUTE_TYPE_S_PMSI, "S-PMSI"},
    { BGP_MULTICAST_VPN_ROUTE_TYPE_INTRA_AS_SEG_LEAF, "Intra-AS Segment-Leaf"},
    { BGP_MULTICAST_VPN_ROUTE_TYPE_SOURCE_ACTIVE, "Source-Active"},
    { BGP_MULTICAST_VPN_ROUTE_TYPE_SHARED_TREE_JOIN, "Shared Tree Join"},
    { BGP_MULTICAST_VPN_ROUTE_TYPE_SOURCE_TREE_JOIN, "Source Tree Join"},
    { 0, NULL}
};

/* ---- util-print.c verbatim (tok2strbuf / tok2str) ---- */
#define TOKBUFSIZE 128

static const char *
tok2strbuf(const struct tok *lp, const char *fmt,
	   u_int v, char *buf, size_t bufsize)
{
	if (lp != NULL) {
		while (lp->s != NULL) {
			if (lp->v == v)
				return (lp->s);
			++lp;
		}
	}
	if (fmt == NULL)
		fmt = "#%d";

	(void)snprintf(buf, bufsize, fmt, v);
	return (const char *)buf;
}

static const char *
tok2str(const struct tok *lp, const char *fmt, u_int v)
{
	static char buf[4][TOKBUFSIZE];
	static int idx = 0;
	char *ret;

	ret = buf[idx];
	idx = (idx+1) & 3;
	return tok2strbuf(lp, fmt, v, ret, sizeof(buf[0]));
}

/* ---- print-bgp.c verbatim (as_printf) ---- */
static char astostr[20];

static char *
as_printf(netdissect_options *ndo,
          char *str, int size, u_int asnum)
{
	if (!ndo->ndo_bflag || asnum <= 0xFFFF) {
		snprintf(str, size, "%u", asnum);
	} else {
		snprintf(str, size, "%u.%u", asnum >> 16, asnum & 0xFFFF);
	}
	return str;
}

/* ---- addrtoname.c verbatim helper (intoa), used unchanged by the
 * minimal getname() below ---- */
#ifndef NTOHL
#define NTOHL(x)	(x) = ntohl(x)
#endif

static const char *
intoa(uint32_t addr)
{
	char *cp;
	u_int byte;
	int n;
	static char buf[sizeof(".xxx.xxx.xxx.xxx")];

	NTOHL(addr);
	cp = buf + sizeof(buf);
	*--cp = '\0';

	n = 4;
	do {
		byte = addr & 0xff;
		*--cp = byte % 10 + '0';
		byte /= 10;
		if (byte > 0) {
			*--cp = byte % 10 + '0';
			byte /= 10;
			if (byte > 0)
				*--cp = byte + '0';
		}
		*--cp = '.';
		addr >>= 8;
	} while (--n > 0);

	return cp + 1;
}

/* Minimal-but-real-named substitute for addrtoname.c's getname()/getname6():
 * the real functions do DNS-hostname-cache lookups (gethostbyaddr, a
 * hnametable/h6nametable cache) which are irrelevant to this CWE-125 (they
 * run, if at all, only AFTER the address bytes are already known-in-bounds
 * via bgp_vpn_ip_print's own ND_TCHECK2) and undesirable inside a
 * --network none sandbox. These always take the numeric path -- exactly
 * what the real getname()/getname6() do when ndo_nflag is set ("-n"). */
static const char *
getname(netdissect_options *ndo, const u_char *ap)
{
	uint32_t addr;
	(void)ndo;
	memcpy(&addr, ap, sizeof(addr));
	return intoa(addr);
}

static const char *
getname6(netdissect_options *ndo, const u_char *ap)
{
	static char ntop_buf[INET6_ADDRSTRLEN];
	struct in6_addr addr;
	(void)ndo;
	memcpy(&addr, ap, sizeof(addr));
	return inet_ntop(AF_INET6, &addr, ntop_buf, sizeof(ntop_buf));
}

#define ipaddr_string(ndo, p) getname(ndo, (const u_char *)(p))
#define ip6addr_string(ndo, p) getname6(ndo, (const u_char *)(p))

/* ---- print-bgp.c verbatim (bgp_vpn_ip_print) ---- */
static char *
bgp_vpn_ip_print(netdissect_options *ndo,
                 const u_char *pptr, u_int addr_length)
{

    /* worst case string is s fully formatted v6 address */
    static char addr[sizeof("1234:5678:89ab:cdef:1234:5678:89ab:cdef")];
    char *pos = addr;

    switch(addr_length) {
    case (sizeof(struct in_addr) << 3): /* 32 */
        ND_TCHECK2(pptr[0], sizeof(struct in_addr));
        snprintf(pos, sizeof(addr), "%s", ipaddr_string(ndo, pptr));
        break;
    case (sizeof(struct in6_addr) << 3): /* 128 */
        ND_TCHECK2(pptr[0], sizeof(struct in6_addr));
        snprintf(pos, sizeof(addr), "%s", ip6addr_string(ndo, pptr));
        break;
    default:
        snprintf(pos, sizeof(addr), "bogus address length %u", addr_length);
        break;
    }
    pos += strlen(pos);

trunc:
    *(pos) = '\0';
    return (addr);
}

/* ---- print-bgp.c verbatim (bgp_vpn_sg_print) ---- */
static int
bgp_vpn_sg_print(netdissect_options *ndo,
                 const u_char *pptr, char *buf, u_int buflen)
{
    uint8_t addr_length;
    u_int total_length, offset;

    total_length = 0;

    /* Source address length, encoded in bits */
    ND_TCHECK2(pptr[0], 1);
    addr_length =  *pptr++;

    /* Source address */
    ND_TCHECK2(pptr[0], (addr_length >> 3));
    total_length += (addr_length >> 3) + 1;
    offset = strlen(buf);
    if (addr_length) {
        snprintf(buf + offset, buflen - offset, ", Source %s",
                 bgp_vpn_ip_print(ndo, pptr, addr_length));
        pptr += (addr_length >> 3);
    }

    /* Group address length, encoded in bits */
    ND_TCHECK2(pptr[0], 1);
    addr_length =  *pptr++;

    /* Group address */
    ND_TCHECK2(pptr[0], (addr_length >> 3));
    total_length += (addr_length >> 3) + 1;
    offset = strlen(buf);
    if (addr_length) {
        snprintf(buf + offset, buflen - offset, ", Group %s",
                 bgp_vpn_ip_print(ndo, pptr, addr_length));
        pptr += (addr_length >> 3);
    }

trunc:
    return (total_length);
}

/* ---- print-bgp.c verbatim (bgp_vpn_rd_print) ---- */
static char *
bgp_vpn_rd_print(netdissect_options *ndo,
                 const u_char *pptr)
{
   /* allocate space for the largest possible string */
    static char rd[sizeof("xxxxxxxxxx:xxxxx (xxx.xxx.xxx.xxx:xxxxx)")];
    char *pos = rd;

    /* ok lets load the RD format */
    switch (EXTRACT_16BITS(pptr)) {

        /* 2-byte-AS:number fmt*/
    case 0:
        snprintf(pos, sizeof(rd) - (pos - rd), "%u:%u (= %u.%u.%u.%u)",
                 EXTRACT_16BITS(pptr+2),
                 EXTRACT_32BITS(pptr+4),
                 *(pptr+4), *(pptr+5), *(pptr+6), *(pptr+7));
        break;
        /* IP-address:AS fmt*/

    case 1:
        snprintf(pos, sizeof(rd) - (pos - rd), "%u.%u.%u.%u:%u",
            *(pptr+2), *(pptr+3), *(pptr+4), *(pptr+5), EXTRACT_16BITS(pptr+6));
        break;

        /* 4-byte-AS:number fmt*/
    case 2:
	snprintf(pos, sizeof(rd) - (pos - rd), "%s:%u (%u.%u.%u.%u:%u)",
	    as_printf(ndo, astostr, sizeof(astostr), EXTRACT_32BITS(pptr+2)),
	    EXTRACT_16BITS(pptr+6), *(pptr+2), *(pptr+3), *(pptr+4),
	    *(pptr+5), EXTRACT_16BITS(pptr+6));
        break;
    default:
        snprintf(pos, sizeof(rd) - (pos - rd), "unknown RD format");
        break;
    }
    pos += strlen(pos);
    *(pos) = '\0';
    return (rd);
}

/* ---- target function, embedded VERBATIM from target/original_function.c,
 * with its real "static int" storage-class/return-type restored (the
 * frozen bundle file's byte-span starts at the identifier, dropping the
 * "static int" line that precedes it in print-bgp.c:906) ---- */
static int
decode_multicast_vpn(netdissect_options *ndo,
                     const u_char *pptr, char *buf, u_int buflen)
{
        uint8_t route_type, route_length, addr_length, sg_length;
        u_int offset;

	ND_TCHECK2(pptr[0], 2);
        route_type = *pptr++;
        route_length = *pptr++;

        snprintf(buf, buflen, "Route-Type: %s (%u), length: %u",
                 tok2str(bgp_multicast_vpn_route_type_values,
                         "Unknown", route_type),
                 route_type, route_length);

        switch(route_type) {
        case BGP_MULTICAST_VPN_ROUTE_TYPE_INTRA_AS_I_PMSI:
            ND_TCHECK2(pptr[0], BGP_VPN_RD_LEN);
            offset = strlen(buf);
            snprintf(buf + offset, buflen - offset, ", RD: %s, Originator %s",
                     bgp_vpn_rd_print(ndo, pptr),
                     bgp_vpn_ip_print(ndo, pptr + BGP_VPN_RD_LEN,
                                      (route_length - BGP_VPN_RD_LEN) << 3));
            break;
        case BGP_MULTICAST_VPN_ROUTE_TYPE_INTER_AS_I_PMSI:
            ND_TCHECK2(pptr[0], BGP_VPN_RD_LEN + 4);
            offset = strlen(buf);
	    snprintf(buf + offset, buflen - offset, ", RD: %s, Source-AS %s",
		bgp_vpn_rd_print(ndo, pptr),
		as_printf(ndo, astostr, sizeof(astostr),
		EXTRACT_32BITS(pptr + BGP_VPN_RD_LEN)));
            break;

        case BGP_MULTICAST_VPN_ROUTE_TYPE_S_PMSI:
            ND_TCHECK2(pptr[0], BGP_VPN_RD_LEN);
            offset = strlen(buf);
            snprintf(buf + offset, buflen - offset, ", RD: %s",
                     bgp_vpn_rd_print(ndo, pptr));
            pptr += BGP_VPN_RD_LEN;

            sg_length = bgp_vpn_sg_print(ndo, pptr, buf, buflen);
            addr_length =  route_length - sg_length;

            ND_TCHECK2(pptr[0], addr_length);
            offset = strlen(buf);
            snprintf(buf + offset, buflen - offset, ", Originator %s",
                     bgp_vpn_ip_print(ndo, pptr, addr_length << 3));
            break;

        case BGP_MULTICAST_VPN_ROUTE_TYPE_SOURCE_ACTIVE:
            ND_TCHECK2(pptr[0], BGP_VPN_RD_LEN);
            offset = strlen(buf);
            snprintf(buf + offset, buflen - offset, ", RD: %s",
                     bgp_vpn_rd_print(ndo, pptr));
            pptr += BGP_VPN_RD_LEN;

            bgp_vpn_sg_print(ndo, pptr, buf, buflen);
            break;

        case BGP_MULTICAST_VPN_ROUTE_TYPE_SHARED_TREE_JOIN: /* fall through */
        case BGP_MULTICAST_VPN_ROUTE_TYPE_SOURCE_TREE_JOIN:
            ND_TCHECK2(pptr[0], BGP_VPN_RD_LEN);
            offset = strlen(buf);
	    snprintf(buf + offset, buflen - offset, ", RD: %s, Source-AS %s",
		bgp_vpn_rd_print(ndo, pptr),
		as_printf(ndo, astostr, sizeof(astostr),
		EXTRACT_32BITS(pptr + BGP_VPN_RD_LEN)));
            pptr += BGP_VPN_RD_LEN;

            bgp_vpn_sg_print(ndo, pptr, buf, buflen);
            break;

            /*
             * no per route-type printing yet.
             */
        case BGP_MULTICAST_VPN_ROUTE_TYPE_INTRA_AS_SEG_LEAF:
        default:
            break;
        }

        return route_length + 2;

trunc:
	return -2;
}
/* ---- end verbatim target function ---- */

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) {
		perror("fopen");
		return 1;
	}
	if (fseek(fp, 0, SEEK_END) != 0) {
		perror("fseek");
		fclose(fp);
		return 1;
	}
	long len = ftell(fp);
	if (len < 0) {
		perror("ftell");
		fclose(fp);
		return 1;
	}
	rewind(fp);

	/* REQUIRED: heap buffer for the attacker-controlled packet bytes,
	 * sized EXACTLY to the file length (no slack) so ASan's redzone
	 * sits immediately after the real "captured packet" data -- mirrors
	 * tcpdump's real per-packet capture buffer. */
	size_t alloc_len = (size_t)len > 0 ? (size_t)len : 1;
	u_char *data = malloc(alloc_len);
	if (!data) {
		perror("malloc");
		fclose(fp);
		return 1;
	}
	if (len > 0 && fread(data, (size_t)len, 1, fp) != 1) {
		fprintf(stderr, "short read\n");
		fclose(fp);
		free(data);
		return 1;
	}
	fclose(fp);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_bflag = 0;
	/* Only the actual file bytes are "captured" -- matches the real
	 * caller, where ndo_snapend marks the end of what was captured off
	 * the wire/savefile. */
	ndo.ndo_snapend = data + len;

	/* Real caller (bgp_attr_print) local buffer size. */
	char buf[MAXHOSTNAMELEN + 100];

	int rc = decode_multicast_vpn(&ndo, data, buf, sizeof(buf));

	printf("decode_multicast_vpn rc=%d buf=%s\n", rc, buf);

	free(data);
	return 0;
}
