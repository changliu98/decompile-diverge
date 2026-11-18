/*
 * Direct-call crash harness for CVE-2017-13005 (tcpdump, print-nfs.c: xid_map_enter).
 *
 * CWE-125 (out-of-bounds READ): xid_map_enter() only bounds-checks
 * rp->rm_call.cb_vers with ND_TTEST() before unconditionally reading
 * rp->rm_call.cb_proc (4 bytes further into the same struct) via the raw,
 * unchecked EXTRACT_32BITS() macro. If the captured packet is truncated
 * right after cb_vers, EXTRACT_32BITS(&rp->rm_call.cb_proc) reads past the
 * end of the packet buffer. (Fixed upstream by b45a9a167ca6a3ef2752ae9d48d
 * 56ac14b001bfd, which adds an ND_TTEST(cb_proc) check.)
 *
 * All type/macro definitions below are copied VERBATIM (trimmed to only
 * what xid_map_enter/its dependents need) from the real tcpdump headers
 * under source_code/: netdissect.h, netdissect-stdinc.h, extract.h, ip.h,
 * ip6.h, rpc_msg.h, rpc_auth.h. struct in6_addr is the real system type
 * from <netinet/in.h> (tcpdump itself relies on the platform header, it
 * does not define its own). The target function xid_map_enter() below is
 * byte-for-byte identical to target/original_function.c.
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>   /* struct in6_addr */
#include <arpa/inet.h>    /* ntohl */

typedef unsigned char u_char;
typedef unsigned int  u_int;

/* ---------------------------------------------------------------------
 * netdissect.h (trimmed)
 * ------------------------------------------------------------------- */

typedef unsigned char nd_uint8_t;
typedef signed char   nd_int8_t;
typedef unsigned char nd_uint16_t[2];

typedef struct {
	unsigned char bytes[4];
} nd_ipv4;

typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	/* global pointers to beginning and end of current packet (during printing) */
	const u_char *ndo_packetp;
	const u_char *ndo_snapend;
};

/*
 * Test in two parts to avoid these warnings:
 * comparison of unsigned expression >= 0 is always true [-Wtype-limits],
 * comparison is always true due to limited range of data type [-Wtype-limits].
 */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

/* True if "var" was captured */
#define ND_TTEST(var) ND_TTEST2(var, sizeof(var))

/* Bail if "l" bytes of "var" were not captured */
#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc

/* Bail if "var" was not captured */
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

/* x86-64: the processor natively handles unaligned loads, so UNALIGNED_MEMCPY
 * is plain memcpy() (see netdissect.h's #else branch, no LBL_ALIGN). */
#define UNALIGNED_MEMCPY(p, q, l)	memcpy((p), (q), (l))

/* ---------------------------------------------------------------------
 * netdissect-stdinc.h (trimmed)
 * ------------------------------------------------------------------- */
#define UNALIGNED	__attribute__((packed))

/* ---------------------------------------------------------------------
 * extract.h (trimmed: x86-64 "processor natively handles unaligned loads"
 * branch of EXTRACT_32BITS -- a raw, UNCHECKED pointer-cast + ntohl, exactly
 * as compiled in the real build). No bounds check happens inside this
 * function; that is the whole point of the CVE.
 * ------------------------------------------------------------------- */
#define UNALIGNED_OK

static inline uint32_t UNALIGNED_OK
EXTRACT_32BITS(const void *p)
{
	return ((uint32_t)ntohl(*(const uint32_t *)(p)));
}

/* ---------------------------------------------------------------------
 * ip.h (trimmed)
 * ------------------------------------------------------------------- */
struct ip {
	nd_uint8_t	ip_vhl;		/* header length, version */
#define IP_V(ip)	(((ip)->ip_vhl & 0xf0) >> 4)
#define IP_HL(ip)	((ip)->ip_vhl & 0x0f)
	nd_uint8_t	ip_tos;		/* type of service */
	nd_uint16_t	ip_len;		/* total length */
	nd_uint16_t	ip_id;		/* identification */
	nd_uint16_t	ip_off;		/* fragment offset field */
	nd_uint8_t	ip_ttl;		/* time to live */
	nd_uint8_t	ip_p;		/* protocol */
	nd_uint16_t	ip_sum;		/* checksum */
	nd_ipv4		ip_src, ip_dst;	/* source and dest address */
};

/* ---------------------------------------------------------------------
 * ip6.h (trimmed)
 * ------------------------------------------------------------------- */
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

/* ---------------------------------------------------------------------
 * rpc_auth.h (trimmed)
 * ------------------------------------------------------------------- */
struct sunrpc_opaque_auth {
	uint32_t oa_flavor;		/* flavor of auth */
	uint32_t oa_len;		/* length of opaque body */
	/* zero or more bytes of body */
};

/* ---------------------------------------------------------------------
 * rpc_msg.h (verbatim)
 * ------------------------------------------------------------------- */
struct sunrpc_rejected_reply {
	uint32_t		 rj_stat;	/* enum reject_stat */
	union {
		struct {
			uint32_t low;
			uint32_t high;
		} RJ_versions;
		uint32_t RJ_why;  /* enum auth_stat - why authentication did not work */
	} ru;
#define	rj_vers	ru.RJ_versions
#define	rj_why	ru.RJ_why
};

struct sunrpc_reply_body {
	uint32_t	rp_stat;		/* enum reply_stat */
	struct sunrpc_rejected_reply rp_reject;	/* if rejected */
};

struct sunrpc_call_body {
	uint32_t cb_rpcvers;	/* must be equal to two */
	uint32_t cb_prog;
	uint32_t cb_vers;
	uint32_t cb_proc;
	struct sunrpc_opaque_auth cb_cred;
	/* followed by opaque verifier */
};

struct sunrpc_msg {
	uint32_t		rm_xid;
	uint32_t		rm_direction;	/* enum msg_type */
	union {
		struct sunrpc_call_body RM_cmb;
		struct sunrpc_reply_body RM_rmb;
	} ru;
#define	rm_call		ru.RM_cmb
#define	rm_reply	ru.RM_rmb
};

/* ---------------------------------------------------------------------
 * print-nfs.c file-scope state that xid_map_enter() reads/writes
 * (verbatim, from immediately above the function at print-nfs.c:843-862).
 * ------------------------------------------------------------------- */
struct xid_map_entry {
	uint32_t	xid;		/* transaction ID (net order) */
	int ipver;			/* IP version (4 or 6) */
	struct in6_addr	client;		/* client IP address (net order) */
	struct in6_addr	server;		/* server IP address (net order) */
	uint32_t	proc;		/* call proc number (host order) */
	uint32_t	vers;		/* program version (host order) */
};

#define	XIDMAPSIZE	64

static struct xid_map_entry xid_map[XIDMAPSIZE];

static int xid_map_next = 0;

/* =======================================================================
 * TARGET FUNCTION -- byte-for-byte identical to target/original_function.c
 * ======================================================================= */
static int
xid_map_enter(netdissect_options *ndo,
              const struct sunrpc_msg *rp, const u_char *bp)
{
	const struct ip *ip = NULL;
	const struct ip6_hdr *ip6 = NULL;
	struct xid_map_entry *xmep;

	if (!ND_TTEST(rp->rm_call.cb_vers))
		return (0);
	switch (IP_V((const struct ip *)bp)) {
	case 4:
		ip = (const struct ip *)bp;
		break;
	case 6:
		ip6 = (const struct ip6_hdr *)bp;
		break;
	default:
		return (1);
	}

	xmep = &xid_map[xid_map_next];

	if (++xid_map_next >= XIDMAPSIZE)
		xid_map_next = 0;

	UNALIGNED_MEMCPY(&xmep->xid, &rp->rm_xid, sizeof(xmep->xid));
	if (ip) {
		xmep->ipver = 4;
		UNALIGNED_MEMCPY(&xmep->client, &ip->ip_src, sizeof(ip->ip_src));
		UNALIGNED_MEMCPY(&xmep->server, &ip->ip_dst, sizeof(ip->ip_dst));
	}
	else if (ip6) {
		xmep->ipver = 6;
		UNALIGNED_MEMCPY(&xmep->client, &ip6->ip6_src, sizeof(ip6->ip6_src));
		UNALIGNED_MEMCPY(&xmep->server, &ip6->ip6_dst, sizeof(ip6->ip6_dst));
	}
	xmep->proc = EXTRACT_32BITS(&rp->rm_call.cb_proc);
	xmep->vers = EXTRACT_32BITS(&rp->rm_call.cb_vers);
	return (1);
}
/* ================= end target function ================= */

/*
 * main(): read argv[1] into a HEAP buffer sized exactly to the file's
 * length, and call xid_map_enter() ONCE with pointers into that buffer:
 *
 *   bp (2nd real-caller arg, the packet-start pointer) = buf + 0
 *       -- room for either a 20-byte IPv4 header or a 40-byte IPv6 header.
 *   rp (the RPC message pointer)                       = buf + RP_OFF (40)
 *
 * ndo->ndo_snapend = buf + <file length>, i.e. EXACTLY the end of this
 * malloc() allocation -- the same role ndo_snapend plays in the real
 * tool (end of the captured/snapshotted bytes of the packet). Any
 * EXTRACT_32BITS/memcpy inside xid_map_enter that reads past that point
 * reads past the actual heap allocation, which ASAN's redzone catches as
 * a genuine heap-buffer-overflow READ -- not a fabricated stack/global
 * overflow. The corpus (see gen_corpus.py) controls ONLY the file's
 * length and byte content; RP_OFF is fixed by this harness, matching how
 * a real capture buffer's length determines how "chatty" it is.
 */
#define RP_OFF 40

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
	if (fseek(f, 0, SEEK_END) != 0) {
		fclose(f);
		return 1;
	}
	long sz = ftell(f);
	if (sz < 0) {
		fclose(f);
		return 1;
	}
	rewind(f);

	size_t alloc_sz = (size_t)(sz > 0 ? sz : 1);
	u_char *buf = (u_char *)malloc(alloc_sz);
	if (!buf) {
		fclose(f);
		return 1;
	}
	size_t got = (sz > 0) ? fread(buf, 1, (size_t)sz, f) : 0;
	fclose(f);
	if ((long)got != sz) {
		free(buf);
		return 1;
	}

	netdissect_options ndo_storage;
	netdissect_options *ndo = &ndo_storage;
	ndo->ndo_packetp = buf;
	ndo->ndo_snapend = buf + sz;	/* exactly the end of the heap allocation */

	const u_char *bp = buf;
	const struct sunrpc_msg *rp = (const struct sunrpc_msg *)(buf + RP_OFF);

	int ret = xid_map_enter(ndo, rp, bp);

	/*
	 * xid_map[] is otherwise never read again in this translation unit,
	 * so an optimizing compiler can prove the stores inside
	 * xid_map_enter() (xmep->proc/vers/xid/client/server) are dead --
	 * and, transitively, eliminate the very EXTRACT_32BITS()/memcpy()
	 * reads that trigger the OOB, silently vanishing the crash. Force
	 * those writes observable via a volatile sink, exactly the way a
	 * real caller (nfsreq_print_noaddr) goes on to consume proc/vers.
	 * This does NOT touch xid_map_enter() itself.
	 */
	volatile uint32_t sink = 0;
	for (int k = 0; k < XIDMAPSIZE; k++) {
		sink ^= xid_map[k].xid ^ (uint32_t)xid_map[k].ipver ^
		        xid_map[k].proc ^ xid_map[k].vers;
	}

	printf("xid_map_enter returned %d (input length=%ld) sink=%u\n", ret, sz, sink);

	free(buf);
	return 0;
}
