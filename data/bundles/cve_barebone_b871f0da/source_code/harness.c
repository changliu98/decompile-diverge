/* Direct-call crash harness for tcpdump arp_print (CVE-2017-13013, CWE-125,
 * print-arp.c).
 *
 * Root cause (fix commit 13ab8d18617d616c7d343530f8a842e7143fb5cc, "CVE-2017-13013/
 * ARP: Add a couple of bounds checks"): arp_print() only bounds-checks that
 * PROTO_LEN(ap) (= ap->ar_pln, the attacker-controlled protocol-address-length
 * field) bytes are captured at the target-protocol-address offset:
 *
 *     if (!ND_TTEST2(*ar_tpa(ap), PROTO_LEN(ap))) { ...; return; }
 *     ...
 *     if ((pro != ETHERTYPE_IP && pro != ETHERTYPE_TRAIL) ||
 *         PROTO_LEN(ap) != 4 || HRD_LEN(ap) == 0 || ndo->ndo_vflag) {
 *         ND_PRINT(...);
 *         if (!ndo->ndo_vflag) goto out;   <- only bails out when NOT verbose
 *     }
 *     ...
 *     case ARPOP_REQUEST:
 *         ND_PRINT((ndo, "who-has %s", ipaddr_string(ndo, TPA(ap))));
 *
 * When -v is given (ndo_vflag != 0), execution falls through into the switch
 * even if PROTO_LEN(ap) != 4, i.e. even if fewer than 4 bytes were actually
 * bounds-checked at the target-protocol-address offset. ipaddr_string() is a
 * macro for getname() (addrtoname.c), which unconditionally does:
 *
 *     memcpy(&addr, ap, sizeof(addr));      // sizeof(addr) == 4, ALWAYS
 *
 * with NO bounds check of its own (by contract -- see the comment above
 * getname() in addrtoname.c: "ap is *NOT* necessarily part of the packet
 * data ... so you *CANNOT* use the ND_TCHECK{2}/ND_TTEST{2} macros on it";
 * callers must guarantee the 4 bytes are present). So whenever
 * PROTO_LEN(ap) < 4 and the captured buffer ends fewer than 4 bytes past the
 * target-protocol-address offset, getname()'s memcpy reads past the end of
 * the buffer -> heap-buffer-overflow READ, CWE-125. (The fix adds an
 * explicit `PROTO_LEN(ap) < 4` rejection before this can happen.)
 *
 * This harness embeds arp_print() VERBATIM (target/original_function.c,
 * byte-for-byte) together with every real type/macro/tok-table it
 * references, copied verbatim from source_code/print-arp.c (struct
 * arp_pkthdr, the ar_sha/ar_spa/ar_tha/ar_tpa/HRD/PRO/OP/HRD_LEN/PROTO_LEN/
 * SHA/SPA/THA/TPA macros, arpop_values[]/arphrd_values[], isnonzero(),
 * tstr[]), and its one real, self-contained fault-site callee getname()
 * (source_code/addrtoname.c, verbatim, together with its own real support:
 * struct hnamemem, HASHNAMESIZE, the static hnametable[] hash table,
 * f_netmask/f_localnet, intoa(), newhnamemem()) -- getname() IS the actual
 * fault site (its unchecked memcpy), so it is embedded verbatim rather than
 * stubbed, exactly like the EXTRACT_* helpers in other harnesses in this
 * corpus. netdissect.h contributes the ND_TTEST2/ND_TCHECK/ND_PRINT/
 * ND_DEFAULTPRINT macros and a minimal-but-faithful struct netdissect_options
 * subset (only the fields arp_print()/getname() actually touch); extract.h
 * contributes the native (non-LBL_ALIGN) x86_64 EXTRACT_16BITS. atmarp_print()
 * (arp_print's ARPHRD_ATM2225 branch) and linkaddr_string() (real signatures
 * from print-arp.c / addrtoname.h) are NOT on the fault path and are never
 * reached by this corpus (hrd is always ARPHRD_ETHER, and the crafted
 * "safe" inputs keep the target-hardware-address bytes all-zero so
 * isnonzero(THA(ap),...) short-circuits before any linkaddr_string() call)
 * -- they are given trivial, behaviourally-safe stub bodies with real
 * signatures purely so the translation unit links.
 *
 * main() reads argv[1] into a HEAP buffer malloc'd to EXACTLY the file
 * length (so ASAN's redzone sits immediately past the real "captured
 * packet" data, exactly like tcpdump's own per-packet capture buffer),
 * points ndo.ndo_snapend at data+len, sets ndo.ndo_vflag=1 (-v, required to
 * fall through into the switch even when PROTO_LEN(ap) != 4 -- see above)
 * and ndo.ndo_nflag=1 (-n, a completely standard/real tcpdump option that
 * makes getname() skip DNS/gethostbyaddr() and go straight to intoa(); this
 * is legitimate caller initialization, not a test rig -- the crash is
 * getname()'s FIRST statement, before the nflag check is ever reached, so
 * it plays no role in the trigger condition; it only keeps the harness
 * offline/deterministic once a "safe" input lets getname() run to
 * completion), then calls arp_print(&ndo, data, (u_int)len, (u_int)len)
 * directly, exactly once.
 *
 * Corpus design (byte 0-1 = ar_hrd = ARPHRD_ETHER(1) always, byte 2-3 =
 * ar_pro = ETHERTYPE_IP(0x0800) always, byte 4 = ar_hln, byte 5 = ar_pln,
 * byte 6-7 = ar_op = ARPOP_REQUEST(1) always -- so the ONLY call that can
 * ever fire is the single, unambiguous `ipaddr_string(ndo, TPA(ap))` in
 * "who-has %s", with no sibling function-call argument to create
 * evaluation-order ambiguity):
 *   Let tpa_off = 8 + 2*ar_hln + ar_pln (offset of the target protocol
 *   address, from the ar_tpa() macro).
 *   - TRIGGERING: ar_pln in {0,1,2,3} (so PROTO_LEN(ap) != 4, the outer
 *     `if` is taken, and since ndo_vflag=1 the function does NOT `goto out`)
 *     and file length N in [tpa_off+ar_pln, tpa_off+2] (still < tpa_off+4):
 *     the initial `ND_TTEST2(*ar_tpa(ap), PROTO_LEN(ap))` check passes
 *     (only ar_pln bytes are required there), but getname()'s unconditional
 *     4-byte memcpy at tpa_off then reads past the N-byte allocation.
 *   - SAFE (regime A1, header truncated): N in [1,7] -- fails the very
 *     first `ND_TCHECK(*ap)` (needs all 8 header bytes) -> `goto trunc`
 *     before even ar_hrd/ar_pro/ar_op are read.
 *   - SAFE (regime A2, target-protocol-address truncated): ar_hln/ar_pln
 *     chosen large enough that tpa_off+ar_pln > 8, with N in
 *     [8, tpa_off+ar_pln-1] -- passes the header check but fails
 *     `ND_TTEST2(*ar_tpa(ap), PROTO_LEN(ap))` -> early return via
 *     ND_DEFAULTPRINT, never reaches ipaddr_string() at all.
 *   - SAFE (regime B, fully in bounds): N >= tpa_off+4 (with slack 0-12
 *     bytes) -- getname()'s 4-byte read lands entirely inside the
 *     allocation; the target/hardware-address bytes in [8, tpa_off) are
 *     kept all-zero so isnonzero(THA(ap),...) is false and linkaddr_string()
 *     is never invoked; execution falls through to `out:` and returns
 *     cleanly.
 *   - SAFE (regime C, unmatched ar_op): ar_op set to an unhandled opcode
 *     (99) with N large enough to pass both initial checks -- falls into
 *     `default: ND_DEFAULTPRINT(...); return;`, never touching TPA/SPA at
 *     all.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <arpa/inet.h>   /* ntohs/ntohl -- what netdissect-stdinc.h pulls in */
#include <netdb.h>       /* struct hostent / gethostbyaddr -- referenced (but,
                            with ndo_nflag=1, never executed) inside the
                            verbatim getname() body */

/* ---- minimal but faithful type/macro defs the function(s) need ---- */
/* (real names verbatim from netdissect.h / extract.h / addrtoname.h /
 *  addrtoname.c / print-arp.c) */

typedef unsigned char u_char;
typedef unsigned int u_int;
typedef unsigned short u_short;

typedef struct netdissect_options netdissect_options;

/* netdissect.h: struct tok + tok2str (real signature; "tok2str is
 * deprecated" per netdissect.h but still the one actually linked/used). */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

static const char *
tok2str(const struct tok *lp, const char *fmt, u_int v)
{
	static char buf[128];
	while (lp != NULL && lp->s != NULL) {
		if (lp->v == v)
			return lp->s;
		lp++;
	}
	if (fmt == NULL)
		fmt = "#%d";
	snprintf(buf, sizeof(buf), fmt, v);
	return buf;
}

/* netdissect.h struct netdissect_options -- minimal but faithful subset:
 * only the fields arp_print()/getname() actually touch. */
struct netdissect_options {
	int ndo_vflag;			/* verbosity level */
	int ndo_eflag;			/* print ethernet header */
	int ndo_nflag;			/* leave addresses as numbers */
	int ndo_Nflag;			/* remove domains from printed host names */
	const u_char *ndo_packetp;	/* beginning of current packet */
	const u_char *ndo_snapend;	/* end of current packet */
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
	void (*ndo_default_print)(netdissect_options *, const u_char *bp, u_int length);
	void (*ndo_error)(netdissect_options *, const char *fmt, ...);
};

/* extract.h -- native (non-LBL_ALIGN) x86_64 unaligned-load variant (the
 * one x86_64 builds use). Only EXTRACT_16BITS is needed by arp_print(). */
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

/* netdissect.h -- "l" bytes of "var" captured? (verbatim) */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TTEST(var) ND_TTEST2(var, sizeof(var))
#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF
#define ND_DEFAULTPRINT(ap, length) (*ndo->ndo_default_print)(ndo, ap, length)

/* ---- addrtoname.h (verbatim macro + real prototypes of the two
 * out-of-file callees arp_print() references) ---- */
extern const char *getname(netdissect_options *, const u_char *);
#define ipaddr_string(ndo, p) getname(ndo, (const u_char *)(p))
extern const char *linkaddr_string(netdissect_options *, const u_char *, const unsigned int, const unsigned int);

enum {
    LINKADDR_ETHER,
    LINKADDR_FRELAY,
    LINKADDR_IEEE1394,
    LINKADDR_ATM
};

/* ---- addrtoname.c, verbatim: the real fault-site helper getname() plus
 * its own real support (struct hnamemem / HASHNAMESIZE / hnametable[] /
 * f_netmask / f_localnet / intoa() / newhnamemem()). ---- */

#define HASHNAMESIZE 4096

struct hnamemem {
	uint32_t addr;
	const char *name;
	struct hnamemem *nxt;
};

static struct hnamemem hnametable[HASHNAMESIZE];

static uint32_t f_netmask;
static uint32_t f_localnet;

#ifndef NTOHL
#define NTOHL(x)	(x) = ntohl(x)
#endif

/*
 * A faster replacement for inet_ntoa(). (addrtoname.c intoa(), verbatim)
 */
const char *
intoa(uint32_t addr)
{
	register char *cp;
	register u_int byte;
	register int n;
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

/* Return a zero'ed hnamemem struct and cuts down on calloc() overhead.
 * (addrtoname.c newhnamemem(), verbatim) */
struct hnamemem *
newhnamemem(netdissect_options *ndo)
{
	register struct hnamemem *p;
	static struct hnamemem *ptr = NULL;
	static u_int num = 0;

	if (num  <= 0) {
		num = 64;
		ptr = (struct hnamemem *)calloc(num, sizeof (*ptr));
		if (ptr == NULL)
			(*ndo->ndo_error)(ndo, "newhnamemem: calloc");
	}
	--num;
	p = ptr++;
	return (p);
}

/*
 * Return a name for the IP address pointed to by ap.  This address
 * is assumed to be in network byte order.
 *
 * NOTE: ap is *NOT* necessarily part of the packet data (not even if
 * this is being called with the "ipaddr_string()" macro), so you
 * *CANNOT* use the ND_TCHECK{2}/ND_TTEST{2} macros on it. Furthermore,
 * even in cases where it *is* part of the packet data, the caller
 * would still have to check for a null return value, even if it's
 * just printing the return value with "%s" - not all versions of
 * printf print "(null)" with "%s" and a null pointer, some of them
 * don't check for a null pointer and crash in that case.
 *
 * The callers of this routine should, before handing this routine
 * a pointer to packet data, be sure that the data is present in
 * the packet buffer.  They should probably do those checks anyway,
 * as other data at that layer might not be IP addresses, and it
 * also needs to check whether they're present in the packet buffer.
 *
 * (addrtoname.c getname(), verbatim -- THIS is the fault site: the
 * memcpy below is unconditional and is exactly what arp_print()'s
 * caller-side bounds check (PROTO_LEN(ap) < 4) is supposed to prevent.)
 */
const char *
getname(netdissect_options *ndo, const u_char *ap)
{
	register struct hostent *hp;
	uint32_t addr;
	struct hnamemem *p;

	memcpy(&addr, ap, sizeof(addr));
	p = &hnametable[addr & (HASHNAMESIZE-1)];
	for (; p->nxt; p = p->nxt) {
		if (p->addr == addr)
			return (p->name);
	}
	p->addr = addr;
	p->nxt = newhnamemem(ndo);

	/*
	 * Print names unless:
	 *	(1) -n was given.
	 *      (2) Address is foreign and -f was given. (If -f was not
	 *	    given, f_netmask and f_localnet are 0 and the test
	 *	    evaluates to true)
	 */
	if (!ndo->ndo_nflag &&
	    (addr & f_netmask) == f_localnet) {
		hp = gethostbyaddr((char *)&addr, 4, AF_INET);
		if (hp) {
			char *dotp;

			p->name = strdup(hp->h_name);
			if (p->name == NULL)
				(*ndo->ndo_error)(ndo,
						  "getname: strdup(hp->h_name)");
			if (ndo->ndo_Nflag) {
				/* Remove domain qualifications */
				dotp = strchr(p->name, '.');
				if (dotp)
					*dotp = '\0';
			}
			return (p->name);
		}
	}
	p->name = strdup(intoa(addr));
	if (p->name == NULL)
		(*ndo->ndo_error)(ndo, "getname: strdup(intoa(addr))");
	return (p->name);
}

/* ---- trivial, behaviourally-safe stub for the one out-of-file callee
 * that is NOT the fault site (real signature; never actually invoked by
 * this corpus -- see file header). ---- */
const char *
linkaddr_string(netdissect_options *ndo, const u_char *ep, const unsigned int type, const unsigned int len)
{
	(void)ndo; (void)type;
	static char buf[BUFSIZ];
	unsigned int i;
	char *cp = buf;
	for (i = 0; i < len && (size_t)(cp - buf) < sizeof(buf) - 4; i++) {
		if (i != 0)
			*cp++ = ':';
		cp += snprintf(cp, sizeof(buf) - (cp - buf), "%02x", ep[i]);
	}
	*cp = '\0';
	return buf;
}

/* ---- print-arp.c, verbatim (struct arp_pkthdr + its field-access macros,
 * lines 50-97 of source_code/print-arp.c) ---- */

struct  arp_pkthdr {
        u_short ar_hrd;         /* format of hardware address */
#define ARPHRD_ETHER    1       /* ethernet hardware format */
#define ARPHRD_IEEE802  6       /* token-ring hardware format */
#define ARPHRD_ARCNET   7       /* arcnet hardware format */
#define ARPHRD_FRELAY   15      /* frame relay hardware format */
#define ARPHRD_ATM2225  19      /* ATM (RFC 2225) */
#define ARPHRD_STRIP    23      /* Ricochet Starmode Radio hardware format */
#define ARPHRD_IEEE1394 24      /* IEEE 1394 (FireWire) hardware format */
        u_short ar_pro;         /* format of protocol address */
        u_char  ar_hln;         /* length of hardware address */
        u_char  ar_pln;         /* length of protocol address */
        u_short ar_op;          /* one of: */
#define ARPOP_REQUEST   1       /* request to resolve address */
#define ARPOP_REPLY     2       /* response to previous request */
#define ARPOP_REVREQUEST 3      /* request protocol address given hardware */
#define ARPOP_REVREPLY  4       /* response giving protocol address */
#define ARPOP_INVREQUEST 8      /* request to identify peer */
#define ARPOP_INVREPLY  9       /* response identifying peer */
#define ARPOP_NAK       10      /* NAK - only valif for ATM ARP */

#define ar_sha(ap)	(((const u_char *)((ap)+1))+0)
#define ar_spa(ap)	(((const u_char *)((ap)+1))+  (ap)->ar_hln)
#define ar_tha(ap)	(((const u_char *)((ap)+1))+  (ap)->ar_hln+(ap)->ar_pln)
#define ar_tpa(ap)	(((const u_char *)((ap)+1))+2*(ap)->ar_hln+(ap)->ar_pln)
};

#define ARP_HDRLEN	8

#define HRD(ap) EXTRACT_16BITS(&(ap)->ar_hrd)
#define HRD_LEN(ap) ((ap)->ar_hln)
#define PROTO_LEN(ap) ((ap)->ar_pln)
#define OP(ap)  EXTRACT_16BITS(&(ap)->ar_op)
#define PRO(ap) EXTRACT_16BITS(&(ap)->ar_pro)
#define SHA(ap) (ar_sha(ap))
#define SPA(ap) (ar_spa(ap))
#define THA(ap) (ar_tha(ap))
#define TPA(ap) (ar_tpa(ap))

static const char tstr[] = "[|ARP]";

/* ethertype.h (real macros) + a minimal real subset of print-ether.c's
 * ethertype_values[] (display-only, not on the fault path). */
#ifndef ETHERTYPE_IP
#define	ETHERTYPE_IP		0x0800
#endif
#ifndef ETHERTYPE_TRAIL
#define ETHERTYPE_TRAIL	0x1000
#endif

static const struct tok ethertype_values[] = {
    { ETHERTYPE_IP,		"IPv4" },
    { 0, NULL }
};

/* print-arp.c arpop_values[]/arphrd_values[], verbatim. */
static const struct tok arpop_values[] = {
    { ARPOP_REQUEST, "Request" },
    { ARPOP_REPLY, "Reply" },
    { ARPOP_REVREQUEST, "Reverse Request" },
    { ARPOP_REVREPLY, "Reverse Reply" },
    { ARPOP_INVREQUEST, "Inverse Request" },
    { ARPOP_INVREPLY, "Inverse Reply" },
    { ARPOP_NAK, "NACK Reply" },
    { 0, NULL }
};

static const struct tok arphrd_values[] = {
    { ARPHRD_ETHER, "Ethernet" },
    { ARPHRD_IEEE802, "TokenRing" },
    { ARPHRD_ARCNET, "ArcNet" },
    { ARPHRD_FRELAY, "FrameRelay" },
    { ARPHRD_STRIP, "Strip" },
    { ARPHRD_IEEE1394, "IEEE 1394" },
    { ARPHRD_ATM2225, "ATM" },
    { 0, NULL }
};

/* print-arp.c isnonzero(), verbatim (lines 180-190). */
static int
isnonzero(const u_char *a, size_t len)
{
	while (len > 0) {
		if (*a != 0)
			return (1);
		a++;
		len--;
	}
	return (0);
}

/* print-arp.c atmarp_print() -- NOT the fault site, and (see file header)
 * this corpus never sets ar_hrd == ARPHRD_ATM2225, so it is never actually
 * invoked; trivial safe stub with the real (static) signature so the
 * translation unit links. */
static void
atmarp_print(netdissect_options *ndo, const u_char *bp, u_int length, u_int caplen)
{
	(void)ndo; (void)bp; (void)length; (void)caplen;
}

/* ---- I/O stubs (real signatures) ---- */

static int
harness_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	va_start(ap, fmt);
	int r = vfprintf(stderr, fmt, ap);
	va_end(ap);
	return r;
}

static void
harness_default_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	(void)ndo; (void)bp; (void)length;
}

static void
harness_error(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputc('\n', stderr);
	exit(1);
}

/* ---- verbatim target function (target/original_function.c, byte-for-byte) ---- */
void
arp_print(netdissect_options *ndo,
	  const u_char *bp, u_int length, u_int caplen)
{
	const struct arp_pkthdr *ap;
	u_short pro, hrd, op, linkaddr;

	ap = (const struct arp_pkthdr *)bp;
	ND_TCHECK(*ap);

	hrd = HRD(ap);
	pro = PRO(ap);
	op = OP(ap);


        /* if its ATM then call the ATM ARP printer
           for Frame-relay ARP most of the fields
           are similar to Ethernet so overload the Ethernet Printer
           and set the linkaddr type for linkaddr_string(ndo, ) accordingly */

        switch(hrd) {
        case ARPHRD_ATM2225:
            atmarp_print(ndo, bp, length, caplen);
            return;
        case ARPHRD_FRELAY:
            linkaddr = LINKADDR_FRELAY;
            break;
        default:
            linkaddr = LINKADDR_ETHER;
            break;
	}

	if (!ND_TTEST2(*ar_tpa(ap), PROTO_LEN(ap))) {
		ND_PRINT((ndo, "%s", tstr));
		ND_DEFAULTPRINT((const u_char *)ap, length);
		return;
	}

        if (!ndo->ndo_eflag) {
            ND_PRINT((ndo, "ARP, "));
        }

        /* print hardware type/len and proto type/len */
        if ((pro != ETHERTYPE_IP && pro != ETHERTYPE_TRAIL) ||
	    PROTO_LEN(ap) != 4 ||
            HRD_LEN(ap) == 0 ||
            ndo->ndo_vflag) {
            ND_PRINT((ndo, "%s (len %u), %s (len %u)",
                      tok2str(arphrd_values, "Unknown Hardware (%u)", hrd),
                      HRD_LEN(ap),
                      tok2str(ethertype_values, "Unknown Protocol (0x%04x)", pro),
                      PROTO_LEN(ap)));

            /* don't know know about the address formats */
            if (!ndo->ndo_vflag) {
                goto out;
            }
	}

        /* print operation */
        ND_PRINT((ndo, "%s%s ",
               ndo->ndo_vflag ? ", " : "",
               tok2str(arpop_values, "Unknown (%u)", op)));

	switch (op) {

	case ARPOP_REQUEST:
		ND_PRINT((ndo, "who-has %s", ipaddr_string(ndo, TPA(ap))));
		if (isnonzero((const u_char *)THA(ap), HRD_LEN(ap)))
			ND_PRINT((ndo, " (%s)",
				  linkaddr_string(ndo, THA(ap), linkaddr, HRD_LEN(ap))));
		ND_PRINT((ndo, " tell %s", ipaddr_string(ndo, SPA(ap))));
		break;

	case ARPOP_REPLY:
		ND_PRINT((ndo, "%s is-at %s",
                          ipaddr_string(ndo, SPA(ap)),
                          linkaddr_string(ndo, SHA(ap), linkaddr, HRD_LEN(ap))));
		break;

	case ARPOP_REVREQUEST:
		ND_PRINT((ndo, "who-is %s tell %s",
			  linkaddr_string(ndo, THA(ap), linkaddr, HRD_LEN(ap)),
			  linkaddr_string(ndo, SHA(ap), linkaddr, HRD_LEN(ap))));
		break;

	case ARPOP_REVREPLY:
		ND_PRINT((ndo, "%s at %s",
			  linkaddr_string(ndo, THA(ap), linkaddr, HRD_LEN(ap)),
			  ipaddr_string(ndo, TPA(ap))));
		break;

	case ARPOP_INVREQUEST:
		ND_PRINT((ndo, "who-is %s tell %s",
			  linkaddr_string(ndo, THA(ap), linkaddr, HRD_LEN(ap)),
			  linkaddr_string(ndo, SHA(ap), linkaddr, HRD_LEN(ap))));
		break;

	case ARPOP_INVREPLY:
		ND_PRINT((ndo,"%s at %s",
			  linkaddr_string(ndo, SHA(ap), linkaddr, HRD_LEN(ap)),
			  ipaddr_string(ndo, SPA(ap))));
		break;

	default:
		ND_DEFAULTPRINT((const u_char *)ap, caplen);
		return;
	}

 out:
        ND_PRINT((ndo, ", length %u", length));

	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}
/* ---- end verbatim target function ---- */

int main(int argc, char **argv)
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

	/* Heap buffer, sized to EXACTLY the file length (no slack) so ASAN's
	 * redzone sits immediately after the real "captured packet" data --
	 * mirrors the real per-packet capture buffer tcpdump allocates. */
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
	ndo.ndo_vflag = 1;		/* -v, required to fall through the PROTO_LEN!=4 branch */
	ndo.ndo_nflag = 1;		/* -n, skip DNS lookups in getname() (standard tcpdump option) */
	ndo.ndo_packetp = data;
	/* Only the actual file bytes are "captured" -- matches the real
	 * caller, where ndo_snapend marks the end of what was captured off
	 * the wire/savefile. */
	ndo.ndo_snapend = data + len;
	ndo.ndo_printf = harness_printf;
	ndo.ndo_default_print = harness_default_print;
	ndo.ndo_error = harness_error;

	arp_print(&ndo, data, (u_int)len, (u_int)len);

	free(data);
	return 0;
}
