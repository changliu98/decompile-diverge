/*
 * Direct-call crash harness for CVE-2018-14467 (tcpdump, print-bgp.c:
 * bgp_capabilities_print).
 *
 * Upstream fix: e3f3b445e2d20ac5d5b7fcb7559ce6beb55da0c9 "(for 4.9.3)
 * CVE-2018-14467/BGP: Fix BGP_CAPCODE_MP." bgp_capabilities_print() walks a
 * caller-supplied list of BGP OPEN capability options. For a
 * BGP_CAPCODE_MP (Multiprotocol Extensions, type 1) capability, the code
 * ND_TCHECK2()s only `cap_len` bytes at opt[i+2] (the capability's declared
 * body length) before unconditionally reading a 16-bit AFI at opt[i+2] via
 * EXTRACT_16BITS *and* an 8-bit SAFI at opt[i+5] -- 3 bytes further into
 * the body than the TCHECK covers whenever cap_len < 4. The fix adds an
 * explicit `ND_TCHECK_8BITS(opt + i + 5)` immediately before the SAFI
 * read/print. With cap_len in {2,3} and the captured/allocated buffer
 * ending exactly at the declared body (no bytes beyond opt[i+2+cap_len-1]),
 * the SAFI read at opt[i+5] runs past the end of the allocation ->
 * heap-buffer-overflow READ (CWE-125), attributed directly to
 * bgp_capabilities_print (baseline dedup_token
 * "bgp_capabilities_print--bgp_open_print--bgp_header_print"; this
 * direct-call harness drops the two whole-program caller frames and calls
 * bgp_capabilities_print() itself, so the crashing frame is exactly the
 * target function).
 *
 * bgp_capabilities_print() is embedded VERBATIM below (byte-identical to
 * target/original_function.c). All type/macro/table definitions that
 * precede it -- struct tok, struct netdissect_options (trimmed to the
 * fields the function actually touches: ndo_bflag/ndo_vflag/ndo_snapend/
 * ndo_printf), ND_TTEST2/ND_TCHECK2/ND_TCHECK_16BITS/ND_PRINT,
 * EXTRACT_16BITS/EXTRACT_32BITS (byte-at-a-time form), BGP_CAP_HEADER_SIZE
 * and every BGP_CAPCODE_/AFNUM_/SAFNUM_ constant plus the
 * bgp_capcode_values/af_values/bgp_safi_values/bgp_add_path_recvsend
 * tok tables, astostr + as_printf(), and tok2str()/tok2strbuf() -- are
 * copied VERBATIM (real names, real bodies) from
 * dataset/cve_f6ec1976/source_code/{netdissect.h,extract.h,af.h,af.c,
 * util-print.c,print-bgp.c}. The one callee that is NOT on the fault path,
 * print_unknown_data() (util-print.c), is only reached from
 * bgp_capabilities_print()'s default/unknown-capability branch and the
 * trailing `ndo_vflag>1` hexdump branch -- neither of which the trigger
 * corpus ever exercises with vflag=1 fixed -- so it is a minimal,
 * memory-safe stand-in (same real prototype, self-clamps to ndo_snapend
 * like the real one, never manufactures a crash).
 *
 * main() reads argv[1] into a HEAP buffer malloc'd to EXACTLY the file's
 * length (so ASAN's redzone sits immediately after the attacker bytes,
 * matching the real captured-packet-buffer boundary bgp_capabilities_print
 * must respect), sets ndo_snapend = buf+n, ndo_vflag = 1 (the "fully
 * decode it" verbosity level real callers use), ndo_bflag = 0, and calls
 * bgp_capabilities_print(&ndo, buf, n) directly -- exactly the
 * `bgp_capabilities_print(ndo, &opt[i+BGP_OPT_SIZE], bgpopt.bgpopt_len)`
 * call bgp_open_print() makes at print-bgp.c:2474, minus the outer
 * BGP-message/TLV-option framing this harness has no dependency on.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

/* ---- real BSD-ish typedefs used throughout tcpdump headers ---- */
typedef unsigned char  u_char;
typedef unsigned int   u_int;

/* ---- extract.h: EXTRACT_16BITS/EXTRACT_32BITS, verbatim byte-at-a-time
 * variant (the portable "have to do it a byte at a time" form) ---- */
#define EXTRACT_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 0)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 1)) << 0)))
#define EXTRACT_32BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 0)) << 24) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 3)) << 0)))

/* ---- netdissect.h: struct tok ---- */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

/* ---- netdissect.h: netdissect_options (minimal: only the members
 * bgp_capabilities_print()/its real callees actually touch, real
 * names/types) ---- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int ndo_bflag;		/* print 4 byte ASes in ASDOT notation (as_printf) */
	int ndo_vflag;		/* verbosity level */
	const u_char *ndo_snapend;	/* end of captured/allocated packet */
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---- netdissect.h: ND_TTEST2/ND_TCHECK2/ND_PRINT, verbatim ---- */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- extract.h: ND_TCHECK_16BITS, verbatim ---- */
#define ND_TCHECK_16BITS(p) ND_TCHECK2(*(p), 2)

/* ---- util-print.c: tok2strbuf()/tok2str(), verbatim ---- */
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

/* ---- util-print.c: print_unknown_data() -- real prototype, memory-safe
 * stand-in. bgp_capabilities_print() reaches this only from its
 * default/unknown-capability branch (vflag<=1) and the trailing
 * "vflag>1 && cap_len>0" hexdump branch; this harness fixes ndo_vflag=1,
 * so neither call site is ever exercised by the corpus below (the
 * BGP_CAPCODE_MP trigger path never enters either), but the stand-in
 * stays memory-safe (self-clamps to ndo_snapend exactly like the real
 * print_unknown_data(), then just touches a volatile sink instead of
 * hex_print()'s I/O-formatting machinery) so it can never itself
 * manufacture or mask a crash. */
static volatile unsigned long g_sink;

static int
print_unknown_data(netdissect_options *ndo, const u_char *cp, const char *ident, int len)
{
	(void)ident;
	if (len < 0)
		return 0;
	if (ndo->ndo_snapend - cp < len)
		len = (int)(ndo->ndo_snapend - cp);
	if (len < 0)
		return 0;
	for (int k = 0; k < len; k++)
		g_sink += cp[k];
	return 1;
}

/* ================= real print-bgp.c preamble, verbatim ================= */

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

/* ---- af.h/af.c: AFNUM_*, af_values[], verbatim ---- */
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

/* ---- print-bgp.c: SAFNUM_*, bgp_safi_values[], verbatim ---- */
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

/* ---- print-bgp.c: bgp_add_path_recvsend[], verbatim ---- */
static const struct tok bgp_add_path_recvsend[] = {
  { 1, "Receive" },
  { 2, "Send" },
  { 3, "Both" },
  { 0, NULL },
};

/* ---- print-bgp.c: astostr/as_printf(), verbatim ---- */
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

/* ================= target function, embedded VERBATIM from
 * dataset/cve_f6ec1976/target/original_function.c. Do not modify. ========= */
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
                    /* Restart Flags (4 bits), Restart Time in seconds (12 bits) */
                    ND_TCHECK_16BITS(opt + i + 2);
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
}/* ================================================================== */

/* Harness-authored: the ndo_printf output function pointer, stubbed to
 * discard its formatted output (real tcpdump wires this to a
 * vfprintf(stdout, ...) wrapper; we format into a scratch buffer and drop
 * it). It must actually CONSUME the varargs via vsnprintf(), not silently
 * ignore them: bgp_capabilities_print() is `static` and called exactly
 * once (from main(), non-inlined callers gone), so with a truly no-op
 * ndo_printf body clang -O1 can prove every ND_PRINT(...) argument
 * (including the tok2str(bgp_safi_values,...,opt[i+5]) SAFI read that IS
 * the bug) is unobserved and dead-code-eliminate the load entirely --
 * silently optimizing the vulnerability away instead of just stubbing
 * "output" (this exact failure mode was hit and fixed in the sibling
 * cve_299f4da7 harness). Routing through vsnprintf (an opaque libc call)
 * forces the real heap read to happen, exactly as it would when the real
 * ndo_printf formats the string for output. */
static int
noop_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	char scratch[512];
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

	/* HEAP buffer sized EXACTLY to the input file -- required so ASAN's
	 * redzone sits immediately after the attacker-controlled capability
	 * bytes and catches bgp_capabilities_print()'s SAFI read
	 * (opt[i+5]) when it runs past the declared+present body. */
	size_t alloc_sz = (sz > 0) ? (size_t)sz : 1;
	u_char *buf = (u_char *)malloc(alloc_sz);
	if (!buf) { fclose(f); return 1; }

	size_t n = (sz > 0) ? fread(buf, 1, (size_t)sz, f) : 0;
	fclose(f);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_bflag = 0;
	ndo.ndo_vflag = 1;		/* real callers decode capabilities only when vflag>=1 */
	ndo.ndo_printf = noop_printf;
	ndo.ndo_snapend = buf + n;	/* end of the captured/allocated packet */

	/* Direct call: exactly how bgp_open_print() invokes
	 * bgp_capabilities_print() at print-bgp.c:2474 --
	 * (ndo, options-pointer, options-length). Here the WHOLE heap
	 * buffer IS the capabilities option data; caps_len = n. */
	bgp_capabilities_print(&ndo, buf, (int)n);

	free(buf);
	return 0;
}
