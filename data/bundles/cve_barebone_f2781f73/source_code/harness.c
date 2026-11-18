/*
 * Direct-call crash harness for CVE-2018-14881 (tcpdump, print-bgp.c:
 * bgp_capabilities_print) -- Decompile-Diverge bundle cve_f2781f73.
 *
 * bgp_capabilities_print() is embedded VERBATIM below (byte-for-byte from
 * target/original_function.c, same signature/logic/names). Everything above
 * it is the minimal-but-real subset of tcpdump's netdissect.h / extract.h /
 * af.h / af.c / print-bgp.c / util-print.c that the function's body actually
 * references (real field/macro/function/table names, no invented
 * placeholders); everything below it is the harness-authored driver.
 *
 * Root cause (real CVE-2018-14881): while walking a BGP OPEN message's
 * capability TLVs, for BGP_CAPCODE_RESTART (64) the code does
 *   ND_TCHECK2(opt[i+2], cap_len);              // proves only cap_len bytes
 *   ...
 *   EXTRACT_16BITS(opt+i+2)                      // unconditionally reads 2
 * The TCHECK only proves that the ADVERTISED cap_len bytes are captured --
 * if cap_len is 0 or 1 (a malformed/truncated capability that happens to sit
 * at the very end of the captured packet), the TCHECK trivially passes (a
 * 0- or 1-byte proof) but EXTRACT_16BITS still reads a full 2 bytes at
 * opt[i+2], running past the end of the captured buffer -- a
 * heap-buffer-overflow READ (CWE-125). The upstream fix (86326e880d31)
 * added ND_TCHECK_16BITS(opt + i + 2) immediately before this read.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

/* ---------------------------------------------------------------------
 * netdissect.h: basic typedefs used throughout tcpdump printers.
 * --------------------------------------------------------------------- */
typedef unsigned char u_char;
typedef unsigned int u_int;

/* ---------------------------------------------------------------------
 * extract.h: EXTRACT_16BITS/EXTRACT_32BITS, native-unaligned-load path
 * (the LBL_ALIGN branch is not taken on x86_64, matching the real build).
 * Copied verbatim (modulo UNALIGNED_OK attribute spelling).
 * --------------------------------------------------------------------- */
#if defined(__has_attribute)
# if __has_attribute(no_sanitize)
#  define UNALIGNED_OK __attribute__((no_sanitize("undefined")))
# endif
#endif
#ifndef UNALIGNED_OK
# define UNALIGNED_OK
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

/* ---------------------------------------------------------------------
 * netdissect.h: struct netdissect_options -- reduced to the fields
 * bgp_capabilities_print's call graph actually touches: ndo_vflag (the
 * verbosity gates around print_unknown_data), ndo_bflag (as_printf's AS
 * number format flag), ndo_snapend (the bounds macros), ndo_printf (the
 * ND_PRINT output sink).
 * --------------------------------------------------------------------- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int ndo_vflag;
	int ndo_bflag;
	const u_char *ndo_snapend;
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* netdissect.h: bounds-check macros, copied verbatim. */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc

/* netdissect.h: ND_PRINT, copied verbatim. */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---------------------------------------------------------------------
 * netdissect.h: struct tok + util-print.c: tok2strbuf()/tok2str(),
 * copied verbatim. Pure string-table lookups against the static const
 * tables below -- never touch the packet buffer, so they cannot mask or
 * introduce a crash; they are here purely so the target function's
 * expressions compile and run exactly as in the real binary.
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
 * util-print.c: print_unknown_data() -- reduced-but-behaviorally-safe.
 * The real bounds logic (negative-length guard + clip to ndo_snapend) is
 * kept verbatim; the actual hex/ascii rendering (hex_print(), print-ascii.c)
 * is a no-op here since ndo_printf (below) is itself a no-op sink -- any
 * bytes it would render never reach observable output anyway, so skipping
 * the render cannot mask or introduce a memory access beyond what the real
 * function already bounds-checks.
 * --------------------------------------------------------------------- */
static int
print_unknown_data(netdissect_options *ndo, const u_char *cp, const char *ident, int len)
{
	if (len < 0) {
		return (0);
	}
	if (ndo->ndo_snapend - cp < len)
		len = (int)(ndo->ndo_snapend - cp);
	if (len < 0) {
		return (0);
	}
	/* real function: hex_print(ndo, ident, cp, len); -- no-op sink, see above */
	return (1);
}

/* ---------------------------------------------------------------------
 * af.h / af.c: AFNUM_* + af_values[], copied verbatim.
 * --------------------------------------------------------------------- */
#define AFNUM_INET	1
#define AFNUM_INET6	2
#define AFNUM_NSAP	3
#define AFNUM_HDLC	4
#define AFNUM_BBN1822	5
#define AFNUM_802	6
#define AFNUM_E163	7
#define AFNUM_E164	8
#define AFNUM_F69	9
#define AFNUM_X121	10
#define AFNUM_IPX	11
#define AFNUM_ATALK	12
#define AFNUM_DECNET	13
#define AFNUM_BANYAN	14
#define AFNUM_E164NSAP	15
#define AFNUM_VPLS      25
#define AFNUM_L2VPN     196

static const struct tok af_values[] = {
    { 0,                      "Reserved"},
    { AFNUM_INET,             "IPv4"},
    { AFNUM_INET6,            "IPv6"},
    { AFNUM_NSAP,             "NSAP"},
    { AFNUM_HDLC,             "HDLC"},
    { AFNUM_BBN1822,          "BBN 1822"},
    { AFNUM_802,              "802"},
    { AFNUM_E163,             "E.163"},
    { AFNUM_E164,             "E.164"},
    { AFNUM_F69,              "F.69"},
    { AFNUM_X121,             "X.121"},
    { AFNUM_IPX,              "Novell IPX"},
    { AFNUM_ATALK,            "Appletalk"},
    { AFNUM_DECNET,           "Decnet IV"},
    { AFNUM_BANYAN,           "Banyan Vines"},
    { AFNUM_E164NSAP,         "E.164 with NSAP subaddress"},
    { AFNUM_L2VPN,            "Layer-2 VPN"},
    { AFNUM_VPLS,             "VPLS"},
    { 0, NULL},
};

/* ---------------------------------------------------------------------
 * print-bgp.c: BGP_CAP_HEADER_SIZE, BGP_CAPCODE_*, bgp_capcode_values[],
 * SAFNUM_*, bgp_safi_values[], bgp_add_path_recvsend[], astostr/as_printf,
 * all copied verbatim.
 * --------------------------------------------------------------------- */
#define BGP_CAP_HEADER_SIZE	2	/* some compilers may pad to 4 bytes */

#define BGP_CAPCODE_MP                  1 /* RFC2858 */
#define BGP_CAPCODE_RR                  2 /* RFC2918 */
#define BGP_CAPCODE_ORF                 3 /* RFC5291 */
#define BGP_CAPCODE_MR                  4 /* RFC3107 */
#define BGP_CAPCODE_EXT_NH              5 /* RFC5549 */
#define BGP_CAPCODE_RESTART            64 /* RFC4724  */
#define BGP_CAPCODE_AS_NEW             65 /* RFC6793 */
#define BGP_CAPCODE_DYN_CAP            67 /* draft-ietf-idr-dynamic-cap */
#define BGP_CAPCODE_MULTISESS          68 /* draft-ietf-idr-bgp-multisession */
#define BGP_CAPCODE_ADD_PATH           69 /* RFC7911 */
#define BGP_CAPCODE_ENH_RR             70 /* draft-keyur-bgp-enhanced-route-refresh */
#define BGP_CAPCODE_RR_CISCO          128

static const struct tok bgp_capcode_values[] = {
    { BGP_CAPCODE_MP,           "Multiprotocol Extensions"},
    { BGP_CAPCODE_RR,           "Route Refresh"},
    { BGP_CAPCODE_ORF,          "Cooperative Route Filtering"},
    { BGP_CAPCODE_MR,           "Multiple Routes to a Destination"},
    { BGP_CAPCODE_EXT_NH,       "Extended Next Hop Encoding"},
    { BGP_CAPCODE_RESTART,      "Graceful Restart"},
    { BGP_CAPCODE_AS_NEW,       "32-Bit AS Number"},
    { BGP_CAPCODE_DYN_CAP,      "Dynamic Capability"},
    { BGP_CAPCODE_MULTISESS,    "Multisession BGP"},
    { BGP_CAPCODE_ADD_PATH,     "Multiple Paths"},
    { BGP_CAPCODE_ENH_RR,       "Enhanced Route Refresh"},
    { BGP_CAPCODE_RR_CISCO,     "Route Refresh (Cisco)"},
    { 0, NULL}
};

/* Subsequent address family identifier, RFC2283 section 7 */
#define SAFNUM_RES                      0
#define SAFNUM_UNICAST                  1
#define SAFNUM_MULTICAST                2
#define SAFNUM_UNIMULTICAST             3       /* deprecated now */
#define SAFNUM_LABUNICAST               4
#define SAFNUM_MULTICAST_VPN            5
#define SAFNUM_TUNNEL                   64
#define SAFNUM_VPLS                     65
#define SAFNUM_MDT                      66
#define SAFNUM_VPNUNICAST               128
#define SAFNUM_VPNMULTICAST             129
#define SAFNUM_VPNUNIMULTICAST          130     /* deprecated now */
#define SAFNUM_RT_ROUTING_INFO          132

static const struct tok bgp_safi_values[] = {
    { SAFNUM_RES,               "Reserved"},
    { SAFNUM_UNICAST,           "Unicast"},
    { SAFNUM_MULTICAST,         "Multicast"},
    { SAFNUM_UNIMULTICAST,      "Unicast+Multicast"},
    { SAFNUM_LABUNICAST,        "labeled Unicast"},
    { SAFNUM_TUNNEL,            "Tunnel"},
    { SAFNUM_VPLS,              "VPLS"},
    { SAFNUM_MDT,               "MDT"},
    { SAFNUM_VPNUNICAST,        "labeled VPN Unicast"},
    { SAFNUM_VPNMULTICAST,      "labeled VPN Multicast"},
    { SAFNUM_VPNUNIMULTICAST,   "labeled VPN Unicast+Multicast"},
    { SAFNUM_RT_ROUTING_INFO,   "Route Target Routing Information"},
    { SAFNUM_MULTICAST_VPN,     "Multicast VPN"},
    { 0, NULL }
};

/* ADD-PATH Send/Receive field values */
static const struct tok bgp_add_path_recvsend[] = {
  { 1, "Receive" },
  { 2, "Send" },
  { 3, "Both" },
  { 0, NULL },
};

static char astostr[20];

/*
 * as_printf
 *
 * Convert an AS number into a string and return string pointer.
 *
 * Depending on bflag is set or not, AS number is converted into ASDOT notation
 * or plain number notation.
 *
 */
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

/* ---------------------------------------------------------------------
 * TARGET FUNCTION -- VERBATIM copy of target/original_function.c.
 * Do not modify logic, names, or signature.
 * --------------------------------------------------------------------- */

static void
bgp_capabilities_print(netdissect_options *ndo,
                       const u_char *opt, int caps_len)
{
	int cap_type, cap_len, tcap_len, cap_offset;
        int i = 0;

        while (i < caps_len) {
                ND_TCHECK2(opt[i], BGP_CAP_HEADER_SIZE);
                cap_type=opt[i];
                cap_len=opt[i+1];
                tcap_len=cap_len;
                ND_PRINT((ndo, "\n\t      %s (%u), length: %u",
                       tok2str(bgp_capcode_values, "Unknown",
                                  cap_type),
                       cap_type,
                       cap_len));
                ND_TCHECK2(opt[i+2], cap_len);
                switch (cap_type) {
                case BGP_CAPCODE_MP:
                    ND_PRINT((ndo, "\n\t\tAFI %s (%u), SAFI %s (%u)",
                           tok2str(af_values, "Unknown",
                                      EXTRACT_16BITS(opt+i+2)),
                           EXTRACT_16BITS(opt+i+2),
                           tok2str(bgp_safi_values, "Unknown",
                                      opt[i+5]),
                           opt[i+5]));
                    break;
                case BGP_CAPCODE_RESTART:
                    ND_PRINT((ndo, "\n\t\tRestart Flags: [%s], Restart Time %us",
                           ((opt[i+2])&0x80) ? "R" : "none",
                           EXTRACT_16BITS(opt+i+2)&0xfff));
                    tcap_len-=2;
                    cap_offset=4;
                    while(tcap_len>=4) {
                        ND_PRINT((ndo, "\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding state preserved: %s",
                               tok2str(af_values,"Unknown",
                                          EXTRACT_16BITS(opt+i+cap_offset)),
                               EXTRACT_16BITS(opt+i+cap_offset),
                               tok2str(bgp_safi_values,"Unknown",
                                          opt[i+cap_offset+2]),
                               opt[i+cap_offset+2],
                               ((opt[i+cap_offset+3])&0x80) ? "yes" : "no" ));
                        tcap_len-=4;
                        cap_offset+=4;
                    }
                    break;
                case BGP_CAPCODE_RR:
                case BGP_CAPCODE_RR_CISCO:
                    break;
                case BGP_CAPCODE_AS_NEW:

                    /*
                     * Extract the 4 byte AS number encoded.
                     */
                    if (cap_len == 4) {
                        ND_PRINT((ndo, "\n\t\t 4 Byte AS %s",
                            as_printf(ndo, astostr, sizeof(astostr),
                            EXTRACT_32BITS(opt + i + 2))));
                    }
                    break;
                case BGP_CAPCODE_ADD_PATH:
                    cap_offset=2;
                    if (tcap_len == 0) {
                        ND_PRINT((ndo, " (bogus)")); /* length */
                        break;
                    }
                    while (tcap_len > 0) {
                        if (tcap_len < 4) {
                            ND_PRINT((ndo, "\n\t\t(invalid)"));
                            break;
                        }
                        ND_PRINT((ndo, "\n\t\tAFI %s (%u), SAFI %s (%u), Send/Receive: %s",
                                  tok2str(af_values,"Unknown",EXTRACT_16BITS(opt+i+cap_offset)),
                                  EXTRACT_16BITS(opt+i+cap_offset),
                                  tok2str(bgp_safi_values,"Unknown",opt[i+cap_offset+2]),
                                  opt[i+cap_offset+2],
                                  tok2str(bgp_add_path_recvsend,"Bogus (0x%02x)",opt[i+cap_offset+3])
                        ));
                        tcap_len-=4;
                        cap_offset+=4;
                    }
                    break;
                default:
                    ND_PRINT((ndo, "\n\t\tno decoder for Capability %u",
                           cap_type));
                    if (ndo->ndo_vflag <= 1)
                        print_unknown_data(ndo, &opt[i+2], "\n\t\t", cap_len);
                    break;
                }
                if (ndo->ndo_vflag > 1 && cap_len > 0) {
                    print_unknown_data(ndo, &opt[i+2], "\n\t\t", cap_len);
                }
                i += BGP_CAP_HEADER_SIZE + cap_len;
        }
        return;

trunc:
	ND_PRINT((ndo, "[|BGP]"));
}

/* ---------------------------------------------------------------------
 * Harness-authored: no-op sink for ndo_printf. We only care about the
 * memory-safety of bgp_capabilities_print's own reads of the packet
 * buffer; the formatted human-readable BGP dump it would normally produce
 * on stdout is irrelevant to that. ND_PRINT((ndo, fmt, ...)) still
 * evaluates every argument expression (including the EXTRACT_16BITS/
 * EXTRACT_32BITS/opt[...] reads) before calling this sink -- exactly as it
 * would when the real ndo_printf (vfprintf-based) is invoked -- so the
 * out-of-bounds read still happens.
 * --------------------------------------------------------------------- */
static int
noop_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	(void)fmt;
	return 0;
}

/* ---------------------------------------------------------------------
 * Direct-call driver: read argv[1] into a HEAP buffer, mirror how the real
 * caller (bgp_open_print, print-bgp.c) invokes bgp_capabilities_print: opt
 * = the packet bytes at the start of the OPEN message's capability options,
 * caps_len = the remaining captured option length, ndo_snapend = one-past-
 * the-end of what was actually captured. We bound ndo_snapend to EXACTLY
 * the malloc'd+read region so an out-of-bounds parse lands in the ASAN
 * redzone right after the heap allocation, not on unrelated heap memory.
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
	ndo.ndo_vflag = 1;		/* matches the real PoC run template: tcpdump -v */
	ndo.ndo_bflag = 0;
	ndo.ndo_snapend = data + got;	/* exactly the captured/heap region */
	ndo.ndo_printf = noop_printf;

	bgp_capabilities_print(&ndo, data, (int)got);
	fprintf(stderr, "bgp_capabilities_print returned normally, len=%zu\n", got);

	free(data);
	return 0;
}
