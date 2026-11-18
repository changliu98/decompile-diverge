/*
 * cve_6ecbfd19 direct-call crash harness for tcpdump's ieee802_11_print()
 * (CVE-2018-16227 / CWE-125 heap-buffer-overflow READ in the 802.11 mesh
 *  header length extraction).
 *
 * Root cause (visible directly in target/original_function.c, unchanged):
 *
 *   if (ndo->ndo_Hflag && FC_TYPE(fc) == T_DATA &&
 *       DATA_FRAME_IS_QOS(FC_SUBTYPE(fc))) {
 *           meshdrlen = extract_mesh_header_length(p+hdrlen);   <-- BUG
 *           hdrlen += meshdrlen;
 *   } else
 *           meshdrlen = 0;
 *
 *   if (caplen < hdrlen) {          -- the ONLY bounds check, and it runs
 *           ND_PRINT((ndo, "%s", tstr));            AFTER the read above --
 *           return hdrlen;
 *   }
 *
 *   extract_mesh_header_length() (print-802_11.c:1954, copied verbatim
 *   below) dereferences p[0] unconditionally:
 *
 *       static int
 *       extract_mesh_header_length(const u_char *p)
 *       {
 *           return (p[0] &~ 3) ? 0 : 6*(1 + (p[0] & 3));
 *       }
 *
 *   So when -H (ndo_Hflag) is set and the frame is a QoS Data frame,
 *   ieee802_11_print() reads p[hdrlen] with NO check that `caplen` (the
 *   number of bytes actually captured/available) covers byte `hdrlen` --
 *   the truncation check "if (caplen < hdrlen)" runs only AFTER this read.
 *   A frame whose captured length is <= hdrlen is therefore a
 *   heap-buffer-overflow READ of the byte at (or past) the buffer's end.
 *   The upstream fix (commit 4846b3c5d0a850e860baf4f07340495d29837d09)
 *   hoists an equivalent "caplen < hdrlen + 1" check to before the read.
 *
 * This file assembles:
 *   1. Minimal-but-faithful standalone re-declarations of the real tcpdump
 *      types/macros/struct fields ieee802_11_print() and its two small
 *      real callees need, copied verbatim from source_code/print-802_11.c,
 *      source_code/netdissect.h and source_code/extract.h (BSD scalar
 *      typedefs, a trimmed struct netdissect_options containing only the
 *      fields actually dereferenced -- ndo_snapend/ndo_Hflag/ndo_eflag/
 *      ndo_suppress_default_print/ndo_printf/ndo_default_print --,
 *      ND_PRINT/ND_DEFAULTPRINT, EXTRACT_LE_16BITS, the FC_x / DATA_FRAME_IS_x
 *      / T_x / CTRL_x_HDRLEN / IEEE802_11_x_LEN macros, struct lladdr_info,
 *      roundup2 and tstr exactly as they appear immediately above the
 *      target function in the real file).
 *   2. VERBATIM real tcpdump source for the two functions that actually
 *      compute `hdrlen` (and whose read is the CVE): extract_header_length()
 *      and extract_mesh_header_length() (print-802_11.c:1909-1957) -- the
 *      fault is inside extract_mesh_header_length(), called directly from
 *      ieee802_11_print().
 *   3. VERBATIM real tcpdump source: dataset/cve_6ecbfd19/target/
 *      original_function.c byte-for-byte (the target function itself,
 *      UNCHANGED -- no logic/name/signature edits).
 *   4. Inert stand-in definitions (never exercised by any corpus input --
 *      see io/manifest.json / the generator) for the OTHER callees
 *      ieee802_11_print() syntactically references but whose bodies are
 *      irrelevant to this CVE: ieee_802_11_hdr_print, get_mgmt_src_dst_mac,
 *      mgmt_body_print, ctrl_body_print, wep_print, get_data_src_dst_mac,
 *      llc_print, etheraddr_string. These exist ONLY so the translation
 *      unit links (the compiler cannot prove ndo->ndo_eflag / the switch
 *      target is unreachable at compile time, since ndo is a runtime
 *      pointer) -- every corpus input is crafted so control flow never
 *      actually reaches inside them with attacker data (the crashing
 *      inputs abort at the extract_mesh_header_length() read; the safe
 *      inputs are either truncated so the "caplen < hdrlen" check returns
 *      first, or -- for the handful that DO reach the switch -- the stubs
 *      are pure no-ops that touch no attacker memory, so reaching them is
 *      still genuinely crash-free, not a faked pass).
 *   5. main(): reads argv[1] into a HEAP buffer (required so ASAN
 *      instruments it), zero-inits a netdissect_options with ndo_Hflag=1
 *      (mirrors the real invocations required "-H" flag, matching
 *      io/manifest.json run_template "{tool} -H -c1 -v -nn -r {input}")
 *      and no-op ndo_printf/ndo_default_print, and calls
 *      ieee802_11_print() directly, exactly once, with
 *      length == orig_caplen == the number of bytes read, pad=0, fcslen=0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- real BSD scalar typedefs (normally from netdissect-stdinc.h) ---- */
typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;

/* ---- netdissect.h, verbatim: struct lladdr_info (lines 458-461) ---- */
typedef struct netdissect_options netdissect_options;

struct lladdr_info {
	const char *(*addr_string)(netdissect_options *, const u_char *);
	const u_char *addr;
};

/* ---- netdissect.h, trimmed to the fields ieee802_11_print() and its
 * callees actually dereference (ndo_snapend, ndo_Hflag, ndo_eflag,
 * ndo_suppress_default_print, ndo_printf, ndo_default_print) ---- */
struct netdissect_options {
	int ndo_eflag;			/* print ethernet header */
	int ndo_Hflag;			/* dissect 802.11s draft mesh standard */
	int ndo_suppress_default_print; /* don't use default_print() for unknown packet types */
	const u_char *ndo_snapend;	/* end of captured packet data */
	void (*ndo_default_print)(netdissect_options *,
				  const u_char *bp, u_int length);
	int  (*ndo_printf)(netdissect_options *,
			   const char *fmt, ...);
};

/* ---- netdissect.h macros, verbatim (lines 321-322) ---- */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF
#define ND_DEFAULTPRINT(ap, length) (*ndo->ndo_default_print)(ndo, ap, length)

/* ---- extract.h, verbatim (line 236-238) ---- */
#define EXTRACT_LE_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 1)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 0)) << 0)))

/* ---- print-802_11.c lines 42-107, verbatim: header-length macros,
 * frame-type/subtype constants and FC_* bit macros ---- */
#define	IEEE802_11_FC_LEN		2
#define	IEEE802_11_DUR_LEN		2
#define	IEEE802_11_DA_LEN		6
#define	IEEE802_11_SA_LEN		6
#define	IEEE802_11_BSSID_LEN		6
#define	IEEE802_11_RA_LEN		6
#define	IEEE802_11_TA_LEN		6
#define	IEEE802_11_ADDR1_LEN		6
#define	IEEE802_11_SEQ_LEN		2
#define	IEEE802_11_CTL_LEN		2
#define	IEEE802_11_CARRIED_FC_LEN	2
#define	IEEE802_11_HT_CONTROL_LEN	4
#define	IEEE802_11_IV_LEN		3
#define	IEEE802_11_KID_LEN		1

#define	IEEE802_11_FCS_LEN		4

#define	IEEE802_11_AID_LEN		2

#define	T_MGMT 0x0  /* management */
#define	T_CTRL 0x1  /* control */
#define	T_DATA 0x2 /* data */
#define	T_RESV 0x3  /* reserved */

#define CTRL_CONTROL_WRAPPER	0x7
#define	CTRL_BAR	0x8
#define	CTRL_BA		0x9
#define	CTRL_PS_POLL	0xA
#define	CTRL_RTS	0xB
#define	CTRL_CTS	0xC
#define	CTRL_ACK	0xD
#define	CTRL_CF_END	0xE
#define	CTRL_END_ACK	0xF

#define	DATA_QOS_DATA			0x8

#define DATA_FRAME_IS_CF_ACK(x)		((x) & 0x01)
#define DATA_FRAME_IS_CF_POLL(x)	((x) & 0x02)
#define DATA_FRAME_IS_NULL(x)		((x) & 0x04)
#define DATA_FRAME_IS_QOS(x)		((x) & 0x08)

#define	FC_VERSION(fc)		((fc) & 0x3)
#define	FC_TYPE(fc)		(((fc) >> 2) & 0x3)
#define	FC_SUBTYPE(fc)		(((fc) >> 4) & 0xF)
#define	FC_TO_DS(fc)		((fc) & 0x0100)
#define	FC_FROM_DS(fc)		((fc) & 0x0200)
#define	FC_MORE_FLAG(fc)	((fc) & 0x0400)
#define	FC_RETRY(fc)		((fc) & 0x0800)
#define	FC_POWER_MGMT(fc)	((fc) & 0x1000)
#define	FC_MORE_DATA(fc)	((fc) & 0x2000)
#define	FC_PROTECTED(fc)	((fc) & 0x4000)
#define	FC_ORDER(fc)		((fc) & 0x8000)

#define	MGMT_HDRLEN	(IEEE802_11_FC_LEN+IEEE802_11_DUR_LEN+\
			 IEEE802_11_DA_LEN+IEEE802_11_SA_LEN+\
			 IEEE802_11_BSSID_LEN+IEEE802_11_SEQ_LEN)

#define	CTRL_CONTROL_WRAPPER_HDRLEN	(IEEE802_11_FC_LEN+IEEE802_11_DUR_LEN+\
					 IEEE802_11_ADDR1_LEN+\
					 IEEE802_11_CARRIED_FC_LEN+\
					 IEEE802_11_HT_CONTROL_LEN)
#define	CTRL_RTS_HDRLEN	(IEEE802_11_FC_LEN+IEEE802_11_DUR_LEN+\
			 IEEE802_11_RA_LEN+IEEE802_11_TA_LEN)
#define	CTRL_CTS_HDRLEN	(IEEE802_11_FC_LEN+IEEE802_11_DUR_LEN+IEEE802_11_RA_LEN)
#define	CTRL_ACK_HDRLEN	(IEEE802_11_FC_LEN+IEEE802_11_DUR_LEN+IEEE802_11_RA_LEN)
#define	CTRL_PS_POLL_HDRLEN	(IEEE802_11_FC_LEN+IEEE802_11_AID_LEN+\
				 IEEE802_11_BSSID_LEN+IEEE802_11_TA_LEN)
#define	CTRL_END_HDRLEN	(IEEE802_11_FC_LEN+IEEE802_11_DUR_LEN+\
			 IEEE802_11_RA_LEN+IEEE802_11_BSSID_LEN)
#define	CTRL_END_ACK_HDRLEN	(IEEE802_11_FC_LEN+IEEE802_11_DUR_LEN+\
				 IEEE802_11_RA_LEN+IEEE802_11_BSSID_LEN)
#define	CTRL_BA_HDRLEN	(IEEE802_11_FC_LEN+IEEE802_11_DUR_LEN+IEEE802_11_RA_LEN)
#define	CTRL_BAR_HDRLEN		(IEEE802_11_FC_LEN+IEEE802_11_DUR_LEN+\
				 IEEE802_11_RA_LEN+IEEE802_11_TA_LEN+\
				 IEEE802_11_CTL_LEN+IEEE802_11_SEQ_LEN)

/* ---- forward declarations for the OTHER real callees ieee802_11_print()
 * syntactically references (definitions -- inert stand-ins -- follow
 * AFTER the verbatim target function; see the comment block there). C
 * requires these be declared before use, so the prototypes (matching the
 * real signatures in source_code/print-802_11.c and source_code/
 * addrtoname.h exactly) go here, ahead of the verbatim code. ---- */
static void ieee_802_11_hdr_print(netdissect_options *, uint16_t,
    const u_char *, u_int, u_int);
static void get_mgmt_src_dst_mac(const u_char *, const uint8_t **,
    const uint8_t **);
static int mgmt_body_print(netdissect_options *, uint16_t, const uint8_t *,
    const u_char *, u_int);
static int ctrl_body_print(netdissect_options *, uint16_t, const u_char *);
static int wep_print(netdissect_options *, const u_char *);
static void get_data_src_dst_mac(uint16_t, const u_char *,
    const uint8_t **, const uint8_t **);
static int llc_print(netdissect_options *, const u_char *, u_int, u_int,
    const struct lladdr_info *, const struct lladdr_info *);
static const char *etheraddr_string(netdissect_options *, const u_char *);

/* ==================================================================
 * print-802_11.c:1909-1957, verbatim: the two real helpers that compute
 * hdrlen. extract_mesh_header_length() is the CVE's actual fault site.
 * ================================================================== */
static int
extract_header_length(netdissect_options *ndo,
                      uint16_t fc)
{
	int len;

	switch (FC_TYPE(fc)) {
	case T_MGMT:
		return MGMT_HDRLEN;
	case T_CTRL:
		switch (FC_SUBTYPE(fc)) {
		case CTRL_CONTROL_WRAPPER:
			return CTRL_CONTROL_WRAPPER_HDRLEN;
		case CTRL_BAR:
			return CTRL_BAR_HDRLEN;
		case CTRL_BA:
			return CTRL_BA_HDRLEN;
		case CTRL_PS_POLL:
			return CTRL_PS_POLL_HDRLEN;
		case CTRL_RTS:
			return CTRL_RTS_HDRLEN;
		case CTRL_CTS:
			return CTRL_CTS_HDRLEN;
		case CTRL_ACK:
			return CTRL_ACK_HDRLEN;
		case CTRL_CF_END:
			return CTRL_END_HDRLEN;
		case CTRL_END_ACK:
			return CTRL_END_ACK_HDRLEN;
		default:
			ND_PRINT((ndo, "unknown 802.11 ctrl frame subtype (%d)", FC_SUBTYPE(fc)));
			return 0;
		}
	case T_DATA:
		len = (FC_TO_DS(fc) && FC_FROM_DS(fc)) ? 30 : 24;
		if (DATA_FRAME_IS_QOS(FC_SUBTYPE(fc)))
			len += 2;
		return len;
	default:
		ND_PRINT((ndo, "unknown 802.11 frame type (%d)", FC_TYPE(fc)));
		return 0;
	}
}

static int
extract_mesh_header_length(const u_char *p)
{
	return (p[0] &~ 3) ? 0 : 6*(1 + (p[0] & 3));
}
/* ==================================================================
 * end of verbatim helpers
 * ================================================================== */

/* ---- print-802_11.c lines 2016-2020, verbatim (immediately precede the
 * target function in the real file) ---- */
#ifndef roundup2
#define	roundup2(x, y)	(((x)+((y)-1))&(~((y)-1))) /* if y is powers of two */
#endif

static const char tstr[] = "[|802.11]";

/* ==================================================================
 * verbatim target function -- dataset/cve_6ecbfd19/target/original_function.c
 * ================================================================== */
static u_int
ieee802_11_print(netdissect_options *ndo,
                 const u_char *p, u_int length, u_int orig_caplen, int pad,
                 u_int fcslen)
{
	uint16_t fc;
	u_int caplen, hdrlen, meshdrlen;
	struct lladdr_info src, dst;
	int llc_hdrlen;

	caplen = orig_caplen;
	/* Remove FCS, if present */
	if (length < fcslen) {
		ND_PRINT((ndo, "%s", tstr));
		return caplen;
	}
	length -= fcslen;
	if (caplen > length) {
		/* Amount of FCS in actual packet data, if any */
		fcslen = caplen - length;
		caplen -= fcslen;
		ndo->ndo_snapend -= fcslen;
	}

	if (caplen < IEEE802_11_FC_LEN) {
		ND_PRINT((ndo, "%s", tstr));
		return orig_caplen;
	}

	fc = EXTRACT_LE_16BITS(p);
	hdrlen = extract_header_length(ndo, fc);
	if (hdrlen == 0) {
		/* Unknown frame type or control frame subtype; quit. */
		return (0);
	}
	if (pad)
		hdrlen = roundup2(hdrlen, 4);
	if (ndo->ndo_Hflag && FC_TYPE(fc) == T_DATA &&
	    DATA_FRAME_IS_QOS(FC_SUBTYPE(fc))) {
		meshdrlen = extract_mesh_header_length(p+hdrlen);
		hdrlen += meshdrlen;
	} else
		meshdrlen = 0;

	if (caplen < hdrlen) {
		ND_PRINT((ndo, "%s", tstr));
		return hdrlen;
	}

	if (ndo->ndo_eflag)
		ieee_802_11_hdr_print(ndo, fc, p, hdrlen, meshdrlen);

	/*
	 * Go past the 802.11 header.
	 */
	length -= hdrlen;
	caplen -= hdrlen;
	p += hdrlen;

	src.addr_string = etheraddr_string;
	dst.addr_string = etheraddr_string;
	switch (FC_TYPE(fc)) {
	case T_MGMT:
		get_mgmt_src_dst_mac(p - hdrlen, &src.addr, &dst.addr);
		if (!mgmt_body_print(ndo, fc, src.addr, p, length)) {
			ND_PRINT((ndo, "%s", tstr));
			return hdrlen;
		}
		break;
	case T_CTRL:
		if (!ctrl_body_print(ndo, fc, p - hdrlen)) {
			ND_PRINT((ndo, "%s", tstr));
			return hdrlen;
		}
		break;
	case T_DATA:
		if (DATA_FRAME_IS_NULL(FC_SUBTYPE(fc)))
			return hdrlen;	/* no-data frame */
		/* There may be a problem w/ AP not having this bit set */
		if (FC_PROTECTED(fc)) {
			ND_PRINT((ndo, "Data"));
			if (!wep_print(ndo, p)) {
				ND_PRINT((ndo, "%s", tstr));
				return hdrlen;
			}
		} else {
			get_data_src_dst_mac(fc, p - hdrlen, &src.addr, &dst.addr);
			llc_hdrlen = llc_print(ndo, p, length, caplen, &src, &dst);
			if (llc_hdrlen < 0) {
				/*
				 * Some kinds of LLC packet we cannot
				 * handle intelligently
				 */
				if (!ndo->ndo_suppress_default_print)
					ND_DEFAULTPRINT(p, caplen);
				llc_hdrlen = -llc_hdrlen;
			}
			hdrlen += llc_hdrlen;
		}
		break;
	default:
		/* We shouldn't get here - we should already have quit */
		break;
	}

	return hdrlen;
}
/* ==================================================================
 * end of verbatim target function
 * ================================================================== */

/* ------------------------------------------------------------------
 * Inert stand-ins for the OTHER real callees ieee802_11_print()
 * syntactically references (declared/defined so the TU links -- the
 * compiler cannot statically prove these call sites are unreachable,
 * since ndo->ndo_eflag / the FC_TYPE switch target are runtime values).
 * Every corpus input is crafted so these bodies are never entered with
 * attacker data still in play in a way that could crash or fake a
 * result: they touch no attacker memory and perform no unbounded
 * access -- pure no-ops/constant returns. The real fault lives entirely
 * inside extract_mesh_header_length() above, which IS verbatim.
 * ------------------------------------------------------------------ */
static void
ieee_802_11_hdr_print(netdissect_options *ndo, uint16_t fc, const u_char *p,
                      u_int hdrlen, u_int meshdrlen)
{
	(void)ndo; (void)fc; (void)p; (void)hdrlen; (void)meshdrlen;
}

static void
get_mgmt_src_dst_mac(const u_char *p, const uint8_t **srcp, const uint8_t **dstp)
{
	(void)p;
	if (srcp) *srcp = NULL;
	if (dstp) *dstp = NULL;
}

static int
mgmt_body_print(netdissect_options *ndo, uint16_t fc, const uint8_t *src,
                const u_char *p, u_int length)
{
	(void)ndo; (void)fc; (void)src; (void)p; (void)length;
	return 1; /* "handled" */
}

static int
ctrl_body_print(netdissect_options *ndo, uint16_t fc, const u_char *p)
{
	(void)ndo; (void)fc; (void)p;
	return 1; /* "handled" */
}

static int
wep_print(netdissect_options *ndo, const u_char *p)
{
	(void)ndo; (void)p;
	return 1; /* "handled" */
}

static void
get_data_src_dst_mac(uint16_t fc, const u_char *p, const uint8_t **srcp,
                     const uint8_t **dstp)
{
	(void)fc; (void)p;
	if (srcp) *srcp = NULL;
	if (dstp) *dstp = NULL;
}

static int
llc_print(netdissect_options *ndo, const u_char *p, u_int length,
         u_int caplen, const struct lladdr_info *src,
         const struct lladdr_info *dst)
{
	(void)ndo; (void)p; (void)length; (void)caplen; (void)src; (void)dst;
	return 0; /* non-negative: "handled", no default-print fallback */
}

static const char *
etheraddr_string(netdissect_options *ndo, const u_char *ap)
{
	(void)ndo; (void)ap;
	return "";
}

/* no-op ndo_printf / ndo_default_print -- the harness doesn't care about
 * the printed text, only about the memory-safety of the target function */
static int
vb_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo; (void)fmt;
	return 0;
}

static void
vb_default_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	(void)ndo; (void)bp; (void)length;
}

/* Compiler-escape barrier (harness-only helper, does NOT touch the target
 * function): forces the compiler to assume `p` may be read by unknown
 * code, so the heap buffer is never proven dead / hoisted away before the
 * call. */
static void
vb_escape(void *p)
{
	__asm__ __volatile__("" : : "g"(p) : "memory");
}

int
main(int argc, char **argv)
{
	FILE *f;
	long fsz;
	size_t n;
	u_char *buf;
	netdissect_options ndo_storage;
	netdissect_options *ndo = &ndo_storage;
	volatile u_int result;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	fsz = ftell(f);
	if (fsz < 0) fsz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* attacker data MUST live on the heap so ASAN instruments it */
	buf = (u_char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if (!buf) { fclose(f); return 1; }

	n = fsz > 0 ? fread(buf, 1, (size_t)fsz, f) : 0;
	fclose(f);

	memset(&ndo_storage, 0, sizeof(ndo_storage));
	ndo->ndo_printf = vb_printf;
	ndo->ndo_default_print = vb_default_print;
	/* mirrors the real invocation's required "-H" flag (see
	 * io/manifest.json run_template "{tool} -H -c1 -v -nn -r {input}")
	 * -- without it the vulnerable mesh-header branch is dead code. */
	ndo->ndo_Hflag = 1;
	ndo->ndo_eflag = 0;
	ndo->ndo_suppress_default_print = 0;
	/* snapend = exact end of the heap allocation -- no padding, so a
	 * read that runs past the declared header boundary but still inside
	 * the malloc'd chunk is genuinely a heap-buffer-overflow, matching
	 * the real capture-buffer model. Unused by this function's own logic
	 * unless caplen > length, but set faithfully regardless. */
	ndo->ndo_snapend = buf + n;

	vb_escape(buf);
	/* length == orig_caplen == bytes actually supplied: no additional
	 * pcap-level truncation on top of what the corpus file itself
	 * encodes; pad=0, fcslen=0 keep hdrlen a direct function of the
	 * frame-control field and the (crafted) mesh-header length byte. */
	result = ieee802_11_print(ndo, buf, (u_int)n, (u_int)n, 0, 0);
	vb_escape(buf);

	/* use the result so the whole call can never be proven dead */
	fprintf(stderr, "hdrlen=%u\n", (unsigned)result);

	free(buf);
	return 0;
}
