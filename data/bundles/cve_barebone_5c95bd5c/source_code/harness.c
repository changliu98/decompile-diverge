/*
 * Direct-call crash harness for CVE-2017-13050 (tcpdump, print-rpki-rtr.c:
 * rpki_rtr_pdu_print) -- Decompile-Diverge cve_barebone bundle cve_5c95bd5c.
 *
 * rpki_rtr_pdu_print() is embedded VERBATIM below (byte-for-byte from
 * target/original_function.c, spliced in programmatically by assemble.py --
 * same return type / signature / body / names, no retyping). Everything above
 * it is the minimal-but-real subset of tcpdump's netdissect.h / extract.h /
 * addrtoname.h+addrtoname.c / print-rpki-rtr.c that the function's call graph
 * actually references (real field / macro / function / table names, copied
 * from source_code/, nothing invented or renamed). Everything below it is the
 * harness-authored driver.
 *
 * Root cause (real CVE-2017-13050, upstream fix 83c64fce3a52 "RPKI-Router: add
 * a length check"): rpki_rtr_pdu_print() validates only the *declared* PDU
 * length --
 *     pdu_len = EXTRACT_32BITS(pdu_header->length);
 *     ND_TCHECK2(*tptr, pdu_len);
 * -- and then, for an IPv6-Prefix PDU (pdu_type == RPKI_RTR_IPV6_PREFIX_PDU),
 * unconditionally reinterprets tptr as a `rpki_rtr_pdu_ipv6_prefix` and prints
 *     ip6addr_string(ndo, pdu->prefix)
 * where `prefix` is a 16-byte field at offset 12 of that struct. ip6addr_string
 * is `#define ip6addr_string(ndo,p) getname6(ndo,(const u_char*)(p))`, and
 * getname6() opens with `memcpy(&addr, ap, sizeof(addr))` (sizeof == 16, the
 * size of `struct in6_addr`). When the captured packet is shorter than
 * 12 + 16 = 28 bytes (yet the declared pdu_len is small enough to pass the only
 * TCHECK), that 16-byte memcpy reads past the end of the heap-allocated packet
 * buffer -> heap-buffer-overflow READ (CWE-125) in __asan_memcpy, called from
 * getname6, called from rpki_rtr_pdu_print -- matching baseline dedup_token
 * "__asan_memcpy--getname6--rpki_rtr_pdu_print" and baseline.cwe CWE-125.
 * The upstream fix adds a per-PDU-type minimum-length check before the reads.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/* ---------------------------------------------------------------------
 * netdissect-stdinc.h: basic typedefs + TRUE/FALSE, copied verbatim.
 * --------------------------------------------------------------------- */
typedef unsigned char u_char;
typedef unsigned int u_int;
typedef unsigned short u_short;

#define TRUE 1
#define FALSE 0

/* ---------------------------------------------------------------------
 * extract.h: EXTRACT_16BITS / EXTRACT_32BITS, byte-at-a-time portable
 * form copied verbatim from source_code/extract.h.
 * --------------------------------------------------------------------- */
#define EXTRACT_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 0)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 1)) << 0)))
#define EXTRACT_32BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 0)) << 24) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 3)) << 0)))

/* ---------------------------------------------------------------------
 * netdissect.h: struct netdissect_options -- reduced to the fields
 * rpki_rtr_pdu_print's call graph actually touches: ndo_vflag (verbosity
 * gate around print_unknown_data), ndo_snapend (the bounds macros /
 * fn_printn end pointer), ndo_printf (the ND_PRINT output sink).
 * --------------------------------------------------------------------- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int ndo_vflag;
	const u_char *ndo_snapend;
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* netdissect.h: bounds-check macros, copied verbatim. */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TTEST(var) ND_TTEST2(var, sizeof(var))
#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

/* netdissect.h: ND_PRINT, copied verbatim. */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---------------------------------------------------------------------
 * netdissect.h: struct tok + util-print.c: tok2strbuf()/tok2str(),
 * copied verbatim. Pure string-table lookups -- never touch the packet
 * buffer, so they cannot mask or introduce a crash. Needed because the
 * unconditional header ND_PRINT(..."%s PDU"...) calls tok2str() for every
 * PDU, and the ERROR_REPORT branch calls it on rpki_rtr_error_codes.
 * --------------------------------------------------------------------- */
struct tok {
	u_int v;
	const char *s;
};

#define TOKBUFSIZE 128

static const char *
tok2strbuf(register const struct tok *lp, register const char *fmt,
	   register u_int v, char *buf, size_t bufsize)
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
tok2str(register const struct tok *lp, register const char *fmt,
	register u_int v)
{
	static char buf[4][TOKBUFSIZE];
	static int idx = 0;
	char *ret;

	ret = buf[idx];
	idx = (idx+1) & 3;
	return tok2strbuf(lp, fmt, v, ret, sizeof(buf[0]));
}

/* ---------------------------------------------------------------------
 * addrtoname.h: INET6_ADDRSTRLEN + ipaddr_string()/ip6addr_string()
 * macros -> getname()/getname6(). Real names / signatures / macro forms.
 * --------------------------------------------------------------------- */
#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN	46
#endif

#define ipaddr_string(ndo, p) getname(ndo, (const u_char *)(p))
#define ip6addr_string(ndo, p) getname6(ndo, (const u_char *)(p))

/*
 * addrtoname.c: getname() -- the IPv4 analog, reached only from the
 * RPKI_RTR_IPV4_PREFIX_PDU branch (safe inputs). The real getname() does a
 * hostname-cache/DNS lookup; that is irrelevant to the memory-safety of
 * rpki_rtr_pdu_print, so this is a minimal faithful rendering that reads
 * exactly the 4 address bytes the caller points it at (`p->prefix`, a
 * u_char[4]) and never past them.
 */
static const char *
getname(netdissect_options *ndo, const u_char *ap)
{
	(void)ndo;
	static char buf[32];
	uint32_t a = EXTRACT_32BITS(ap);
	snprintf(buf, sizeof(buf), "%u.%u.%u.%u",
		 (a >> 24) & 0xff, (a >> 16) & 0xff, (a >> 8) & 0xff, a & 0xff);
	return buf;
}

/*
 * addrtoname.c: getname6() -- the IPv6 address-to-name routine, reached
 * from the RPKI_RTR_IPV6_PREFIX_PDU branch. This is THE crash site: the
 * opening `memcpy(&addr, ap, sizeof(addr))` copies sizeof(struct in6_addr)
 * == 16 bytes out of the packet at `pdu->prefix`. The real getname6's tail
 * (hostname hash-table + gethostbyaddr()/addrtostr6() lookup) is
 * memory-cache infrastructure that never influences this bug and is never
 * reached once the memcpy overflows; it is rendered here as a faithful
 * inet_ntop() on the LOCAL copy (the real addrtostr6 formatting), keeping
 * the exact crashing statement and the exact `addr` union type from
 * addrtoname.c:296-311.
 */
static const char *
getname6(netdissect_options *ndo, const u_char *ap)
{
	union {
		struct in6_addr addr;
		struct for_hash_addr {
			char fill[14];
			uint16_t d;
		} addra;
	} addr;
	static char ntop_buf[INET6_ADDRSTRLEN];

	(void)ndo;
	memcpy(&addr, ap, sizeof(addr));
	inet_ntop(AF_INET6, &addr.addr, ntop_buf, sizeof(ntop_buf));
	return ntop_buf;
}

/* ---------------------------------------------------------------------
 * util-print.c: fn_printn() -- reached only from the RPKI_RTR_ERROR_REPORT
 * branch. Real name/signature; faithful minimal body that prints up to `n`
 * bytes but NEVER reads at or past `ep` (== ndo_snapend), exactly like the
 * real fn_printn's `while (n > 0 && (ep == NULL || s < ep))` bound. Returns
 * 1 on truncation (hit ep), 0 otherwise.
 * --------------------------------------------------------------------- */
static int
fn_printn(netdissect_options *ndo, const u_char *s, u_int n, const u_char *ep)
{
	(void)ndo;
	while (n > 0 && (ep == NULL || s < ep)) {
		n--;
		(void)*s;      /* real code emits the char; a bounded read only */
		s++;
	}
	return (n == 0) ? 0 : 1;
}

/* ---------------------------------------------------------------------
 * util-print.c: print_unknown_data() -- real bounds-clip logic kept
 * verbatim; the hex/ascii render (hex_print) is a no-op here because
 * ndo_printf is a no-op sink, and it never reads past the clipped length.
 * --------------------------------------------------------------------- */
static int
print_unknown_data(netdissect_options *ndo, const u_char *cp, const char *ident, int len)
{
	(void)ident;
	if (len < 0) {
		return (0);
	}
	if (ndo->ndo_snapend - cp < len)
		len = (int)(ndo->ndo_snapend - cp);
	if (len < 0) {
		return (0);
	}
	/* real function: hex_print(ndo, ident, cp, len); -- no-op sink */
	return (1);
}

/* ---------------------------------------------------------------------
 * print-rpki-rtr.c: PDU structs, type codes and value tables -- copied
 * VERBATIM from source_code/print-rpki-rtr.c (real names / values / order).
 * --------------------------------------------------------------------- */
typedef struct rpki_rtr_pdu_ {
    u_char version;		/* Version number */
    u_char pdu_type;		/* PDU type */
    union {
	u_char session_id[2];	/* Session id */
	u_char error_code[2];	/* Error code */
    } u;
    u_char length[4];
} rpki_rtr_pdu;

typedef struct rpki_rtr_pdu_ipv4_prefix_ {
    rpki_rtr_pdu pdu_header;
    u_char flags;
    u_char prefix_length;
    u_char max_length;
    u_char zero;
    u_char prefix[4];
    u_char as[4];
} rpki_rtr_pdu_ipv4_prefix;

typedef struct rpki_rtr_pdu_ipv6_prefix_ {
    rpki_rtr_pdu pdu_header;
    u_char flags;
    u_char prefix_length;
    u_char max_length;
    u_char zero;
    u_char prefix[16];
    u_char as[4];
} rpki_rtr_pdu_ipv6_prefix;

typedef struct rpki_rtr_pdu_error_report_ {
    rpki_rtr_pdu pdu_header;
    u_char encapsulated_pdu_length[4]; /* Encapsulated PDU length */
} rpki_rtr_pdu_error_report;

#define RPKI_RTR_SERIAL_NOTIFY_PDU	0
#define RPKI_RTR_SERIAL_QUERY_PDU	1
#define RPKI_RTR_RESET_QUERY_PDU	2
#define RPKI_RTR_CACHE_RESPONSE_PDU	3
#define RPKI_RTR_IPV4_PREFIX_PDU	4
#define RPKI_RTR_IPV6_PREFIX_PDU	6
#define RPKI_RTR_END_OF_DATA_PDU	7
#define RPKI_RTR_CACHE_RESET_PDU	8
#define RPKI_RTR_ERROR_REPORT_PDU	10

static const struct tok rpki_rtr_pdu_values[] = {
    { RPKI_RTR_SERIAL_NOTIFY_PDU, "Serial Notify" },
    { RPKI_RTR_SERIAL_QUERY_PDU, "Serial Query" },
    { RPKI_RTR_RESET_QUERY_PDU, "Reset Query" },
    { RPKI_RTR_CACHE_RESPONSE_PDU, "Cache Response" },
    { RPKI_RTR_IPV4_PREFIX_PDU, "IPV4 Prefix" },
    { RPKI_RTR_IPV6_PREFIX_PDU, "IPV6 Prefix" },
    { RPKI_RTR_END_OF_DATA_PDU, "End of Data" },
    { RPKI_RTR_CACHE_RESET_PDU, "Cache Reset" },
    { RPKI_RTR_ERROR_REPORT_PDU, "Error Report" },
    { 0, NULL}
};

static const struct tok rpki_rtr_error_codes[] = {
    { 0, "Corrupt Data" },
    { 1, "Internal Error" },
    { 2, "No Data Available" },
    { 3, "Invalid Request" },
    { 4, "Unsupported Protocol Version" },
    { 5, "Unsupported PDU Type" },
    { 6, "Withdrawal of Unknown Record" },
    { 7, "Duplicate Announcement Received" },
    { 0, NULL}
};

/* ---------------------------------------------------------------------
 * print-rpki-rtr.c: indent_string() -- copied VERBATIM. Writes into a
 * static buffer only; never touches the packet buffer.
 * --------------------------------------------------------------------- */
static char *
indent_string (u_int indent)
{
    static char buf[20];
    u_int idx;

    idx = 0;
    buf[idx] = '\0';

    /*
     * Does the static buffer fit ?
     */
    if (sizeof(buf) < ((indent/8) + (indent %8) + 2)) {
	return buf;
    }

    /*
     * Heading newline.
     */
    buf[idx] = '\n';
    idx++;

    while (indent >= 8) {
	buf[idx] = '\t';
	idx++;
	indent -= 8;
    }

    while (indent > 0) {
	buf[idx] = ' ';
	idx++;
	indent--;
    }

    /*
     * Trailing zero.
     */
    buf[idx] = '\0';

    return buf;
}

/* ---------------------------------------------------------------------
 * TARGET FUNCTION -- VERBATIM copy of target/original_function.c, spliced
 * in programmatically (assemble.py). Do not modify logic, names, signature.
 * --------------------------------------------------------------------- */
static int
rpki_rtr_pdu_print (netdissect_options *ndo, const u_char *tptr, u_int indent)
{
    const rpki_rtr_pdu *pdu_header;
    u_int pdu_type, pdu_len, hexdump;
    const u_char *msg;

    pdu_header = (const rpki_rtr_pdu *)tptr;
    pdu_type = pdu_header->pdu_type;
    pdu_len = EXTRACT_32BITS(pdu_header->length);
    ND_TCHECK2(*tptr, pdu_len);
    hexdump = FALSE;

    ND_PRINT((ndo, "%sRPKI-RTRv%u, %s PDU (%u), length: %u",
	   indent_string(8),
	   pdu_header->version,
	   tok2str(rpki_rtr_pdu_values, "Unknown", pdu_type),
	   pdu_type, pdu_len));

    switch (pdu_type) {

	/*
	 * The following PDUs share the message format.
	 */
    case RPKI_RTR_SERIAL_NOTIFY_PDU:
    case RPKI_RTR_SERIAL_QUERY_PDU:
    case RPKI_RTR_END_OF_DATA_PDU:
        msg = (const u_char *)(pdu_header + 1);
	ND_PRINT((ndo, "%sSession ID: 0x%04x, Serial: %u",
	       indent_string(indent+2),
	       EXTRACT_16BITS(pdu_header->u.session_id),
	       EXTRACT_32BITS(msg)));
	break;

	/*
	 * The following PDUs share the message format.
	 */
    case RPKI_RTR_RESET_QUERY_PDU:
    case RPKI_RTR_CACHE_RESET_PDU:

	/*
	 * Zero payload PDUs.
	 */
	break;

    case RPKI_RTR_CACHE_RESPONSE_PDU:
	ND_PRINT((ndo, "%sSession ID: 0x%04x",
	       indent_string(indent+2),
	       EXTRACT_16BITS(pdu_header->u.session_id)));
	break;

    case RPKI_RTR_IPV4_PREFIX_PDU:
	{
	    const rpki_rtr_pdu_ipv4_prefix *pdu;

	    pdu = (const rpki_rtr_pdu_ipv4_prefix *)tptr;
	    ND_PRINT((ndo, "%sIPv4 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",
		   indent_string(indent+2),
		   ipaddr_string(ndo, pdu->prefix),
		   pdu->prefix_length, pdu->max_length,
		   EXTRACT_32BITS(pdu->as), pdu->flags));
	}
	break;

    case RPKI_RTR_IPV6_PREFIX_PDU:
	{
	    const rpki_rtr_pdu_ipv6_prefix *pdu;

	    pdu = (const rpki_rtr_pdu_ipv6_prefix *)tptr;
	    ND_PRINT((ndo, "%sIPv6 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",
		   indent_string(indent+2),
		   ip6addr_string(ndo, pdu->prefix),
		   pdu->prefix_length, pdu->max_length,
		   EXTRACT_32BITS(pdu->as), pdu->flags));
	}
	break;

    case RPKI_RTR_ERROR_REPORT_PDU:
	{
	    const rpki_rtr_pdu_error_report *pdu;
	    u_int encapsulated_pdu_length, text_length, tlen, error_code;

	    pdu = (const rpki_rtr_pdu_error_report *)tptr;
	    encapsulated_pdu_length = EXTRACT_32BITS(pdu->encapsulated_pdu_length);
	    ND_TCHECK2(*tptr, encapsulated_pdu_length);
	    tlen = pdu_len;

	    error_code = EXTRACT_16BITS(pdu->pdu_header.u.error_code);
	    ND_PRINT((ndo, "%sError code: %s (%u), Encapsulated PDU length: %u",
		   indent_string(indent+2),
		   tok2str(rpki_rtr_error_codes, "Unknown", error_code),
		   error_code, encapsulated_pdu_length));

	    tptr += sizeof(*pdu);
	    tlen -= sizeof(*pdu);

	    /*
	     * Recurse if there is an encapsulated PDU.
	     */
	    if (encapsulated_pdu_length &&
		(encapsulated_pdu_length <= tlen)) {
		ND_PRINT((ndo, "%s-----encapsulated PDU-----", indent_string(indent+4)));
		if (rpki_rtr_pdu_print(ndo, tptr, indent+2))
			goto trunc;
	    }

	    tptr += encapsulated_pdu_length;
	    tlen -= encapsulated_pdu_length;

	    /*
	     * Extract, trail-zero and print the Error message.
	     */
	    text_length = 0;
	    if (tlen > 4) {
		text_length = EXTRACT_32BITS(tptr);
		tptr += 4;
		tlen -= 4;
	    }
	    ND_TCHECK2(*tptr, text_length);
	    if (text_length && (text_length <= tlen )) {
		ND_PRINT((ndo, "%sError text: ", indent_string(indent+2)));
		if (fn_printn(ndo, tptr, text_length, ndo->ndo_snapend))
			goto trunc;
	    }
	}
	break;

    default:

	/*
	 * Unknown data, please hexdump.
	 */
	hexdump = TRUE;
    }

    /* do we also want to see a hex dump ? */
    if (ndo->ndo_vflag > 1 || (ndo->ndo_vflag && hexdump)) {
	print_unknown_data(ndo,tptr,"\n\t  ", pdu_len);
    }
    return 0;

trunc:
    return 1;
}

/* ---------------------------------------------------------------------
 * Harness-authored: no-op sink for ndo_printf. We only care about the
 * memory-safety of rpki_rtr_pdu_print's own reads of the packet buffer;
 * the human-readable RPKI-RTR dump it would normally produce is irrelevant.
 * ND_PRINT((ndo, fmt, ...)) still evaluates every argument expression
 * (including ip6addr_string(ndo,pdu->prefix) -> getname6()'s memcpy and the
 * EXTRACT_*BITS reads) before this sink is called -- exactly as the real
 * vfprintf-based ndo_printf would -- so the out-of-bounds read still happens.
 * --------------------------------------------------------------------- */
static int
noop_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	(void)fmt;
	return 0;
}

/* ---------------------------------------------------------------------
 * Direct-call driver: read argv[1] into a HEAP buffer sized EXACTLY to the
 * bytes read, so the ASAN redzone sits immediately after the packet. Mirror
 * how the real caller (rpki_rtr_print, print-rpki-rtr.c) invokes
 * rpki_rtr_pdu_print: tptr = the packet bytes at the start of the PDU,
 * indent = 8, ndo_snapend = one-past-the-end of what was captured. The bytes
 * of the file ARE the PDU wire image: [0]=version, [1]=pdu_type, [2..3]=
 * session/error id, [4..7]=length (big-endian, the only value TCHECK'd), and
 * for an IPv6-Prefix PDU [8]=flags,[9]=prefix_length,[10]=max_length,
 * [11]=zero,[12..27]=prefix,[28..31]=as. A file shorter than 28 bytes whose
 * declared length still passes ND_TCHECK2 drives getname6's 16-byte memcpy of
 * pdu->prefix past ndo_snapend == the heap boundary.
 * --------------------------------------------------------------------- */
int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 1;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	fseek(f, 0, SEEK_END);
	long sz = ftell(f);
	if (sz < 0)
		sz = 0;
	fseek(f, 0, SEEK_SET);

	size_t alloc_sz = (size_t)sz > 0 ? (size_t)sz : 1;
	u_char *data = (u_char *)malloc(alloc_sz);
	if (!data) {
		fclose(f);
		return 1;
	}
	size_t got = sz > 0 ? fread(data, 1, (size_t)sz, f) : 0;
	fclose(f);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_vflag = 1;		/* like tcpdump -v; harmless for known PDUs */
	ndo.ndo_snapend = data + got;	/* exactly the captured/heap region */
	ndo.ndo_printf = noop_printf;

	int rv = rpki_rtr_pdu_print(&ndo, data, 8);
	fprintf(stderr, "rpki_rtr_pdu_print returned %d, len=%zu\n", rv, got);

	free(data);
	return 0;
}
