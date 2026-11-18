/*
 * Direct-call crash harness for CVE-2017-13054 (tcpdump, print-lldp.c:
 * lldp_private_8023_print).
 *
 * Upstream fix: e6511cc1a950fe1566b2236329d6b4bd0826cc7a "CVE-2017-13054/LLDP:
 * add a missing length check". lldp_private_8023_print() dispatches on the
 * IEEE 802.3 organizationally-specific LLDP TLV subtype carried in
 * *(tptr+3). Every OTHER subtype case (MACPHY/MDIPOWER/LINKAGGR) guards its
 * reads with an explicit `if (tlv_len < N) return hexdump;` before touching
 * tptr beyond what the caller-declared tlv_len covers -- but the
 * LLDP_PRIVATE_8023_SUBTYPE_MTU (subtype 4, "Max frame size") case has NO
 * such guard:
 *
 *     case LLDP_PRIVATE_8023_SUBTYPE_MTU:
 *         ND_PRINT((ndo, "\n\t    MTU size %u", EXTRACT_16BITS(tptr + 4)));
 *         break;
 *
 * It unconditionally reads 2 bytes at tptr+4 regardless of tlv_len (the
 * function's only entry guard is `if (tlv_len < 4) return hexdump;`, which
 * lets tlv_len==4 or 5 through). The real caller, lldp_print(), only
 * guarantees `tlv_len` bytes are captured/allocated starting at tptr -- so a
 * TLV that declares tlv_len in {4,5} (enough to pass the top-of-function
 * check and to fetch the subtype byte at tptr+3) but is backed by an
 * allocation of only that many bytes makes EXTRACT_16BITS(tptr+4) read 1-2
 * bytes past the end of the allocation -- a heap-buffer-overflow READ
 * (CWE-125), attributed directly to lldp_private_8023_print (matches the
 * frozen baseline dedup_token
 * "EXTRACT_16BITS--lldp_private_8023_print--lldp_print", summary
 * "AddressSanitizer: heap-buffer-overflow ... extract.h:184:20 in
 * EXTRACT_16BITS", cwe CWE-125). The upstream fix adds
 * `if (tlv_len < 6) { return hexdump; }` immediately before this read.
 *
 * lldp_private_8023_print() is embedded VERBATIM below (byte-identical to
 * target/original_function.c -- verified programmatically: the exact
 * original bytes occur exactly once in this file). All preceding
 * type/macro/table definitions are copied VERBATIM (real names, real
 * bodies) from dataset/cve_de73540f/source_code/{netdissect.h,extract.h,
 * util-print.c,missing/strlcpy.c,print-lldp.c}:
 *   - struct tok; netdissect_options trimmed to the one field the function
 *     touches (ndo_printf, via ND_PRINT); ND_PRINT.
 *   - EXTRACT_16BITS/EXTRACT_32BITS (portable byte-at-a-time form -- the
 *     function uses EXTRACT_32BITS too, in the LINKAGGR case, so it must be
 *     defined for the verbatim body to compile even though our corpus never
 *     drives execution through that case for the crash itself).
 *   - LLDP_PRIVATE_8023_SUBTYPE_{MACPHY,MDIPOWER,LINKAGGR,MTU} and every
 *     other macro/struct-tok table the switch references
 *     (lldp_8023_subtype_values, lldp_8023_autonegotiation_values,
 *     lldp_pmd_capability_values, lldp_mau_types_values, lldp_mdi_values,
 *     lldp_mdi_power_pairs_values, lldp_mdi_power_class_values,
 *     lldp_aggregation_values, and their LLDP_MAU_PMD_, LLDP_MDI_,
 *     LLDP_AGGREGATION_ value macros) -- real names, real string tables,
 *     genuinely exercised by the SAFE corpus (MACPHY/MDIPOWER/LINKAGGR
 *     branches call tok2str()/bittok2str() with these tables for real).
 *   - TRUE/FALSE (netdissect-stdinc.h).
 *   - tok2str()/tok2strbuf()/bittok2str()/bittok2str_internal() (util-print.c,
 *     verbatim) and strlcpy() (missing/strlcpy.c, verbatim -- the build
 *     toolchain's glibc has no strlcpy(), exactly the situation
 *     `#ifndef HAVE_STRLCPY` in the real headers guards against).
 *
 * main() reads argv[1] as two parts: byte 0 is the attacker-declared
 * `tlv_len` (the TLV length subfield lldp_print() would have parsed out of
 * the packet's own TLV header -- a value that is NOT required to match how
 * much data was actually captured, which is the crux of the real bug); the
 * REST of the file (bytes 1..end) is copied into a HEAP buffer malloc'd to
 * EXACTLY that remaining length, mirroring the real captured-packet
 * allocation lldp_private_8023_print() is handed as `tptr`. It then calls
 * lldp_private_8023_print(&ndo, tptr, tlv_len) directly ONCE -- exactly the
 * `lldp_private_8023_print(ndo, tptr, tlv_len)` call lldp_print() makes at
 * print-lldp.c:1617, minus the outer LLDP-frame/TLV-walk this harness has no
 * dependency on. No stack/global buffer ever holds attacker data -- the
 * heap allocation's size is exactly the "captured" length, so ASAN's
 * redzone sits immediately after it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

/* ---- real BSD-ish typedefs used throughout tcpdump headers ---- */
typedef unsigned char  u_char;
typedef unsigned int   u_int;

/* ---- netdissect-stdinc.h: TRUE/FALSE, verbatim ---- */
#define TRUE 1
#define FALSE 0

/* ---- extract.h: EXTRACT_16BITS/EXTRACT_32BITS, verbatim byte-at-a-time
 * ("have to do it a byte at a time") form -- portable, matches what the
 * real build uses on any target without a proven-safe unaligned-load path ---- */
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

/* ---- netdissect.h: netdissect_options (minimal: only the member
 * lldp_private_8023_print() actually touches -- ndo_printf, via
 * ND_PRINT -- real name/type) ---- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---- netdissect.h: ND_PRINT, verbatim ---- */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- missing/strlcpy.c, verbatim (the cvf-builder glibc has no
 * strlcpy(); the real headers guard the extern decl with
 * `#ifndef HAVE_STRLCPY` for exactly this case) ---- */
size_t
strlcpy(char *dst, const char *src, size_t siz)
{
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0 && --n != 0) {
		do {
			if ((*d++ = *s++) == 0)
				break;
		} while (--n != 0);
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);	/* count does not include NUL */
}

/* ---- util-print.c: tok2strbuf()/tok2str()/bittok2str_internal()/
 * bittok2str(), verbatim ---- */
#define TOKBUFSIZE 128

const char *
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

const char *
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

static char *
bittok2str_internal(register const struct tok *lp, register const char *fmt,
	   register u_int v, const char *sep)
{
        static char buf[1024+1]; /* our string buffer */
        char *bufp = buf;
        size_t space_left = sizeof(buf), string_size;
        register u_int rotbit; /* this is the bit we rotate through all bitpositions */
        register u_int tokval;
        const char * sepstr = "";

	while (lp != NULL && lp->s != NULL) {
            tokval=lp->v;   /* load our first value */
            rotbit=1;
            while (rotbit != 0) {
                /*
                 * lets AND the rotating bit with our token value
                 * and see if we have got a match
                 */
		if (tokval == (v&rotbit)) {
                    /* ok we have found something */
                    if (space_left <= 1)
                        return (buf); /* only enough room left for NUL, if that */
                    string_size = strlcpy(bufp, sepstr, space_left);
                    if (string_size >= space_left)
                        return (buf);    /* we ran out of room */
                    bufp += string_size;
                    space_left -= string_size;
                    if (space_left <= 1)
                        return (buf); /* only enough room left for NUL, if that */
                    string_size = strlcpy(bufp, lp->s, space_left);
                    if (string_size >= space_left)
                        return (buf);    /* we ran out of room */
                    bufp += string_size;
                    space_left -= string_size;
                    sepstr = sep;
                    break;
                }
                rotbit=rotbit<<1; /* no match - lets shift and try again */
            }
            lp++;
	}

        if (bufp == buf)
            /* bummer - lets print the "unknown" message as advised in the fmt string if we got one */
            (void)snprintf(buf, sizeof(buf), fmt == NULL ? "#%08x" : fmt, v);
        return (buf);
}

char *
bittok2str(register const struct tok *lp, register const char *fmt,
	   register u_int v)
{
    return (bittok2str_internal(lp, fmt, v, ", "));
}

/* ================= print-lldp.c preamble, verbatim ================= */

#define LLDP_PRIVATE_8023_SUBTYPE_MACPHY        1
#define LLDP_PRIVATE_8023_SUBTYPE_MDIPOWER      2
#define LLDP_PRIVATE_8023_SUBTYPE_LINKAGGR      3
#define LLDP_PRIVATE_8023_SUBTYPE_MTU           4

static const struct tok lldp_8023_subtype_values[] = {
    { LLDP_PRIVATE_8023_SUBTYPE_MACPHY,	"MAC/PHY configuration/status"},
    { LLDP_PRIVATE_8023_SUBTYPE_MDIPOWER, "Power via MDI"},
    { LLDP_PRIVATE_8023_SUBTYPE_LINKAGGR, "Link aggregation"},
    { LLDP_PRIVATE_8023_SUBTYPE_MTU, "Max frame size"},
    { 0, NULL}
};

/*
 * From RFC 3636 - ifMauAutoNegCapAdvertisedBits
 */
#define	 LLDP_MAU_PMD_OTHER			(1 <<  15)
#define	 LLDP_MAU_PMD_10BASE_T			(1 <<  14)
#define	 LLDP_MAU_PMD_10BASE_T_FD		(1 <<  13)
#define	 LLDP_MAU_PMD_100BASE_T4		(1 <<  12)
#define	 LLDP_MAU_PMD_100BASE_TX		(1 <<  11)
#define	 LLDP_MAU_PMD_100BASE_TX_FD		(1 <<  10)
#define	 LLDP_MAU_PMD_100BASE_T2		(1 <<  9)
#define	 LLDP_MAU_PMD_100BASE_T2_FD		(1 <<  8)
#define	 LLDP_MAU_PMD_FDXPAUSE			(1 <<  7)
#define	 LLDP_MAU_PMD_FDXAPAUSE			(1 <<  6)
#define	 LLDP_MAU_PMD_FDXSPAUSE			(1 <<  5)
#define	 LLDP_MAU_PMD_FDXBPAUSE			(1 <<  4)
#define	 LLDP_MAU_PMD_1000BASE_X		(1 <<  3)
#define	 LLDP_MAU_PMD_1000BASE_X_FD		(1 <<  2)
#define	 LLDP_MAU_PMD_1000BASE_T		(1 <<  1)
#define	 LLDP_MAU_PMD_1000BASE_T_FD		(1 <<  0)

static const struct tok lldp_pmd_capability_values[] = {
    { LLDP_MAU_PMD_10BASE_T,		"10BASE-T hdx"},
    { LLDP_MAU_PMD_10BASE_T_FD,	        "10BASE-T fdx"},
    { LLDP_MAU_PMD_100BASE_T4,		"100BASE-T4"},
    { LLDP_MAU_PMD_100BASE_TX,		"100BASE-TX hdx"},
    { LLDP_MAU_PMD_100BASE_TX_FD,	"100BASE-TX fdx"},
    { LLDP_MAU_PMD_100BASE_T2,		"100BASE-T2 hdx"},
    { LLDP_MAU_PMD_100BASE_T2_FD,	"100BASE-T2 fdx"},
    { LLDP_MAU_PMD_FDXPAUSE,		"Pause for fdx links"},
    { LLDP_MAU_PMD_FDXAPAUSE,		"Asym PAUSE for fdx"},
    { LLDP_MAU_PMD_FDXSPAUSE,		"Sym PAUSE for fdx"},
    { LLDP_MAU_PMD_FDXBPAUSE,		"Asym and Sym PAUSE for fdx"},
    { LLDP_MAU_PMD_1000BASE_X,		"1000BASE-{X LX SX CX} hdx"},
    { LLDP_MAU_PMD_1000BASE_X_FD,	"1000BASE-{X LX SX CX} fdx"},
    { LLDP_MAU_PMD_1000BASE_T,		"1000BASE-T hdx"},
    { LLDP_MAU_PMD_1000BASE_T_FD,	"1000BASE-T fdx"},
    { 0, NULL}
};

/*
 * From RFC 3636 - dot3MauType
 */
#define		LLDP_MAU_TYPE_UNKNOWN		0
#define		LLDP_MAU_TYPE_AUI		1
#define		LLDP_MAU_TYPE_10BASE_5		2
#define		LLDP_MAU_TYPE_FOIRL		3
#define		LLDP_MAU_TYPE_10BASE_2		4
#define		LLDP_MAU_TYPE_10BASE_T		5
#define		LLDP_MAU_TYPE_10BASE_FP		6
#define		LLDP_MAU_TYPE_10BASE_FB		7
#define		LLDP_MAU_TYPE_10BASE_FL		8
#define		LLDP_MAU_TYPE_10BROAD36		9
#define		LLDP_MAU_TYPE_10BASE_T_HD	10
#define		LLDP_MAU_TYPE_10BASE_T_FD	11
#define		LLDP_MAU_TYPE_10BASE_FL_HD	12
#define		LLDP_MAU_TYPE_10BASE_FL_FD	13
#define		LLDP_MAU_TYPE_100BASE_T4	14
#define		LLDP_MAU_TYPE_100BASE_TX_HD	15
#define		LLDP_MAU_TYPE_100BASE_TX_FD	16
#define		LLDP_MAU_TYPE_100BASE_FX_HD	17
#define		LLDP_MAU_TYPE_100BASE_FX_FD	18
#define		LLDP_MAU_TYPE_100BASE_T2_HD	19
#define		LLDP_MAU_TYPE_100BASE_T2_FD	20
#define		LLDP_MAU_TYPE_1000BASE_X_HD	21
#define		LLDP_MAU_TYPE_1000BASE_X_FD	22
#define		LLDP_MAU_TYPE_1000BASE_LX_HD	23
#define		LLDP_MAU_TYPE_1000BASE_LX_FD	24
#define		LLDP_MAU_TYPE_1000BASE_SX_HD	25
#define		LLDP_MAU_TYPE_1000BASE_SX_FD	26
#define		LLDP_MAU_TYPE_1000BASE_CX_HD	27
#define		LLDP_MAU_TYPE_1000BASE_CX_FD	28
#define		LLDP_MAU_TYPE_1000BASE_T_HD	29
#define		LLDP_MAU_TYPE_1000BASE_T_FD	30
#define		LLDP_MAU_TYPE_10GBASE_X		31
#define		LLDP_MAU_TYPE_10GBASE_LX4	32
#define		LLDP_MAU_TYPE_10GBASE_R		33
#define		LLDP_MAU_TYPE_10GBASE_ER	34
#define		LLDP_MAU_TYPE_10GBASE_LR	35
#define		LLDP_MAU_TYPE_10GBASE_SR	36
#define		LLDP_MAU_TYPE_10GBASE_W		37
#define		LLDP_MAU_TYPE_10GBASE_EW	38
#define		LLDP_MAU_TYPE_10GBASE_LW	39
#define		LLDP_MAU_TYPE_10GBASE_SW	40

static const struct tok lldp_mau_types_values[] = {
    { LLDP_MAU_TYPE_UNKNOWN,            "Unknown"},
    { LLDP_MAU_TYPE_AUI,                "AUI"},
    { LLDP_MAU_TYPE_10BASE_5,           "10BASE_5"},
    { LLDP_MAU_TYPE_FOIRL,              "FOIRL"},
    { LLDP_MAU_TYPE_10BASE_2,           "10BASE2"},
    { LLDP_MAU_TYPE_10BASE_T,           "10BASET duplex mode unknown"},
    { LLDP_MAU_TYPE_10BASE_FP,          "10BASEFP"},
    { LLDP_MAU_TYPE_10BASE_FB,          "10BASEFB"},
    { LLDP_MAU_TYPE_10BASE_FL,          "10BASEFL duplex mode unknown"},
    { LLDP_MAU_TYPE_10BROAD36,          "10BROAD36"},
    { LLDP_MAU_TYPE_10BASE_T_HD,        "10BASET hdx"},
    { LLDP_MAU_TYPE_10BASE_T_FD,        "10BASET fdx"},
    { LLDP_MAU_TYPE_10BASE_FL_HD,       "10BASEFL hdx"},
    { LLDP_MAU_TYPE_10BASE_FL_FD,       "10BASEFL fdx"},
    { LLDP_MAU_TYPE_100BASE_T4,         "100BASET4"},
    { LLDP_MAU_TYPE_100BASE_TX_HD,      "100BASETX hdx"},
    { LLDP_MAU_TYPE_100BASE_TX_FD,      "100BASETX fdx"},
    { LLDP_MAU_TYPE_100BASE_FX_HD,      "100BASEFX hdx"},
    { LLDP_MAU_TYPE_100BASE_FX_FD,      "100BASEFX fdx"},
    { LLDP_MAU_TYPE_100BASE_T2_HD,      "100BASET2 hdx"},
    { LLDP_MAU_TYPE_100BASE_T2_FD,      "100BASET2 fdx"},
    { LLDP_MAU_TYPE_1000BASE_X_HD,      "1000BASEX hdx"},
    { LLDP_MAU_TYPE_1000BASE_X_FD,      "1000BASEX fdx"},
    { LLDP_MAU_TYPE_1000BASE_LX_HD,     "1000BASELX hdx"},
    { LLDP_MAU_TYPE_1000BASE_LX_FD,     "1000BASELX fdx"},
    { LLDP_MAU_TYPE_1000BASE_SX_HD,     "1000BASESX hdx"},
    { LLDP_MAU_TYPE_1000BASE_SX_FD,     "1000BASESX fdx"},
    { LLDP_MAU_TYPE_1000BASE_CX_HD,     "1000BASECX hdx"},
    { LLDP_MAU_TYPE_1000BASE_CX_FD,     "1000BASECX fdx"},
    { LLDP_MAU_TYPE_1000BASE_T_HD,      "1000BASET hdx"},
    { LLDP_MAU_TYPE_1000BASE_T_FD,      "1000BASET fdx"},
    { LLDP_MAU_TYPE_10GBASE_X,          "10GBASEX"},
    { LLDP_MAU_TYPE_10GBASE_LX4,        "10GBASELX4"},
    { LLDP_MAU_TYPE_10GBASE_R,          "10GBASER"},
    { LLDP_MAU_TYPE_10GBASE_ER,         "10GBASEER"},
    { LLDP_MAU_TYPE_10GBASE_LR,         "10GBASELR"},
    { LLDP_MAU_TYPE_10GBASE_SR,         "10GBASESR"},
    { LLDP_MAU_TYPE_10GBASE_W,          "10GBASEW"},
    { LLDP_MAU_TYPE_10GBASE_EW,         "10GBASEEW"},
    { LLDP_MAU_TYPE_10GBASE_LW,         "10GBASELW"},
    { LLDP_MAU_TYPE_10GBASE_SW,         "10GBASESW"},
    { 0, NULL}
};

#define LLDP_8023_AUTONEGOTIATION_SUPPORT       (1 <<  0)
#define LLDP_8023_AUTONEGOTIATION_STATUS        (1 <<  1)

static const struct tok lldp_8023_autonegotiation_values[] = {
    { LLDP_8023_AUTONEGOTIATION_SUPPORT, "supported"},
    { LLDP_8023_AUTONEGOTIATION_STATUS, "enabled"},
    { 0, NULL}
};

#define	LLDP_MDI_PORT_CLASS			(1 <<  0)
#define	LLDP_MDI_POWER_SUPPORT			(1 <<  1)
#define LLDP_MDI_POWER_STATE			(1 <<  2)
#define LLDP_MDI_PAIR_CONTROL_ABILITY		(1 <<  3)

static const struct tok lldp_mdi_values[] = {
    { LLDP_MDI_PORT_CLASS, 		"PSE"},
    { LLDP_MDI_POWER_SUPPORT, 		"supported"},
    { LLDP_MDI_POWER_STATE, 		"enabled"},
    { LLDP_MDI_PAIR_CONTROL_ABILITY, 	"can be controlled"},
    { 0, NULL}
};

#define LLDP_MDI_PSE_PORT_POWER_PAIRS_SIGNAL	1
#define LLDP_MDI_PSE_PORT_POWER_PAIRS_SPARE	2

static const struct tok lldp_mdi_power_pairs_values[] = {
    { LLDP_MDI_PSE_PORT_POWER_PAIRS_SIGNAL,	"signal"},
    { LLDP_MDI_PSE_PORT_POWER_PAIRS_SPARE,	"spare"},
    { 0, NULL}
};

#define LLDP_MDI_POWER_CLASS0		1
#define LLDP_MDI_POWER_CLASS1		2
#define LLDP_MDI_POWER_CLASS2		3
#define LLDP_MDI_POWER_CLASS3		4
#define LLDP_MDI_POWER_CLASS4		5

static const struct tok lldp_mdi_power_class_values[] = {
    { LLDP_MDI_POWER_CLASS0,     "class0"},
    { LLDP_MDI_POWER_CLASS1,     "class1"},
    { LLDP_MDI_POWER_CLASS2,     "class2"},
    { LLDP_MDI_POWER_CLASS3,     "class3"},
    { LLDP_MDI_POWER_CLASS4,     "class4"},
    { 0, NULL}
};

#define LLDP_AGGREGATION_CAPABILTIY     (1 <<  0)
#define LLDP_AGGREGATION_STATUS         (1 <<  1)

static const struct tok lldp_aggregation_values[] = {
    { LLDP_AGGREGATION_CAPABILTIY, "supported"},
    { LLDP_AGGREGATION_STATUS, "enabled"},
    { 0, NULL}
};

/* ================= target function, embedded VERBATIM from
 * dataset/cve_de73540f/target/original_function.c. Do not modify. ========= */
static int
lldp_private_8023_print(netdissect_options *ndo,
                        const u_char *tptr, u_int tlv_len)
{
    int subtype, hexdump = FALSE;

    if (tlv_len < 4) {
        return hexdump;
    }
    subtype = *(tptr+3);

    ND_PRINT((ndo, "\n\t  %s Subtype (%u)",
           tok2str(lldp_8023_subtype_values, "unknown", subtype),
           subtype));

    switch (subtype) {
    case LLDP_PRIVATE_8023_SUBTYPE_MACPHY:
        if (tlv_len < 9) {
            return hexdump;
        }
        ND_PRINT((ndo, "\n\t    autonegotiation [%s] (0x%02x)",
               bittok2str(lldp_8023_autonegotiation_values, "none", *(tptr+4)),
               *(tptr + 4)));
        ND_PRINT((ndo, "\n\t    PMD autoneg capability [%s] (0x%04x)",
               bittok2str(lldp_pmd_capability_values,"unknown", EXTRACT_16BITS(tptr+5)),
               EXTRACT_16BITS(tptr + 5)));
        ND_PRINT((ndo, "\n\t    MAU type %s (0x%04x)",
               tok2str(lldp_mau_types_values, "unknown", EXTRACT_16BITS(tptr+7)),
               EXTRACT_16BITS(tptr + 7)));
        break;

    case LLDP_PRIVATE_8023_SUBTYPE_MDIPOWER:
        if (tlv_len < 7) {
            return hexdump;
        }
        ND_PRINT((ndo, "\n\t    MDI power support [%s], power pair %s, power class %s",
               bittok2str(lldp_mdi_values, "none", *(tptr+4)),
               tok2str(lldp_mdi_power_pairs_values, "unknown", *(tptr+5)),
               tok2str(lldp_mdi_power_class_values, "unknown", *(tptr + 6))));
        break;

    case LLDP_PRIVATE_8023_SUBTYPE_LINKAGGR:
        if (tlv_len < 9) {
            return hexdump;
        }
        ND_PRINT((ndo, "\n\t    aggregation status [%s], aggregation port ID %u",
               bittok2str(lldp_aggregation_values, "none", *(tptr+4)),
               EXTRACT_32BITS(tptr + 5)));
        break;

    case LLDP_PRIVATE_8023_SUBTYPE_MTU:
        ND_PRINT((ndo, "\n\t    MTU size %u", EXTRACT_16BITS(tptr + 4)));
        break;

    default:
        hexdump = TRUE;
        break;
    }

    return hexdump;
}
/* ================================================================== */

/* Harness-authored: the ndo_printf output function pointer, stubbed to
 * discard its formatted output (real tcpdump wires this to a
 * vfprintf(stdout, ...) wrapper; we format into a scratch buffer and drop
 * it). It must actually CONSUME the varargs via vsnprintf(), not silently
 * ignore them: lldp_private_8023_print() is `static` and called exactly
 * once (from main(), no other non-inlined callers), so with a truly no-op
 * ndo_printf body clang -O1 could prove the MTU case's
 * EXTRACT_16BITS(tptr+4) argument (the read that IS the bug) is unobserved
 * and dead-code-eliminate the load, silently optimizing the vulnerability
 * away (this exact failure mode was hit in sibling direct-call harnesses).
 * Routing through vsnprintf (an opaque libc call) forces the real heap read
 * to happen, exactly as it would when the real ndo_printf formats the
 * string for output. */
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

	u_char *filebuf = NULL;
	size_t fn = 0;
	if (sz > 0) {
		filebuf = (u_char *)malloc((size_t)sz);
		if (!filebuf) { fclose(f); return 1; }
		fn = fread(filebuf, 1, (size_t)sz, f);
	}
	fclose(f);

	/*
	 * Input format (harness-defined, documented here):
	 *   byte 0       = the attacker-declared TLV length (tlv_len). This is
	 *                  the value lldp_print() would have parsed out of the
	 *                  TLV's own 9-bit length subfield in the packet -- a
	 *                  value the real bug never validates against how much
	 *                  data was actually captured/allocated.
	 *   bytes 1..end = the "captured" TLV value bytes -- exactly what
	 *                  lldp_private_8023_print() receives as `tptr`. This
	 *                  is copied into a HEAP buffer allocated to EXACTLY
	 *                  that many bytes (fn ? fn-1 : 0), so tlv_len and the
	 *                  real allocation size are independent, just like the
	 *                  real caller's declared-length-vs-captured-length
	 *                  mismatch.
	 */
	u_int tlv_len = (fn >= 1) ? filebuf[0] : 0;
	size_t payload_len = (fn >= 1) ? (fn - 1) : 0;

	/* HEAP buffer sized EXACTLY to the "captured" payload -- required so
	 * ASAN's redzone sits immediately after it and catches
	 * lldp_private_8023_print()'s MTU-case EXTRACT_16BITS(tptr+4) read
	 * whenever tlv_len claims more bytes than were actually captured. */
	u_char *tptr = (u_char *)malloc(payload_len);
	if (payload_len > 0 && !tptr) { free(filebuf); return 1; }
	if (payload_len > 0)
		memcpy(tptr, filebuf + 1, payload_len);
	free(filebuf);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_printf = noop_printf;

	/* Direct call: exactly how lldp_print() invokes
	 * lldp_private_8023_print() at print-lldp.c:1617 --
	 * (ndo, tptr, tlv_len). */
	lldp_private_8023_print(&ndo, tptr, tlv_len);

	free(tptr);
	return 0;
}
