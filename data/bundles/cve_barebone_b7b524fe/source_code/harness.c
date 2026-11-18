/*
 * cve_b7b524fe direct-call crash harness for tcpdump's ospf6_decode_v3()
 * (CVE-2017-13036 / CWE-125 heap-buffer-overflow READ via EXTRACT_32BITS
 *  on hello6->hello_options, read with NO ND_TCHECK guard at all before
 *  it -- the very first byte access into the OSPF_TYPE_HELLO payload).
 *
 * Upstream fix (88b2dac837e81cf56dce05e6e7b5989332c0092d) just inserts
 * `ND_TCHECK_32BITS(&hellop->hello_options);` immediately before this
 * read; every access after it in the HELLO case already has its own
 * ND_TCHECK, so this one unguarded read is the entire bug.
 *
 * This file assembles:
 *   1. Minimal-but-faithful standalone re-declarations of the real
 *      tcpdump types/macros the function needs (struct tok,
 *      netdissect_options trimmed to the fields actually dereferenced,
 *      ND_TTEST2/ND_TCHECK2/ND_TCHECK/ND_PRINT, and the real
 *      EXTRACT_16/32BITS from extract.h -- the "processor natively
 *      handles unaligned loads" branch, i.e. what a real x86_64 build
 *      compiles; EXTRACT_32BITS IS the literal faulting frame per
 *      case.json's baseline dedup_token
 *      "EXTRACT_32BITS--ospf6_decode_v3--ospf6_print").
 *   2. VERBATIM real tcpdump source from source_code/print-ospf6.c:
 *      the OSPF_TYPE_x, OSPF6HDR_LEN, OSPF6_OPTION_x, OSPF6_DB_x macros,
 *      typedef rtrid_t, struct lsa6_hdr/lsa6_prefix/lsa6/ospf6hdr/
 *      hello6/dd6/lsr6/lsu6, and the ospf6_option_values /
 *      ospf6_dd_flag_values tok tables -- every struct/macro/table the
 *      VERBATIM target function's body (all five switch cases) needs
 *      to resolve at compile time, then dataset/cve_b7b524fe/target/
 *      original_function.c byte-for-byte (the target function itself,
 *      UNCHANGED).
 *   3. Real-signature stand-ins for external symbols the function
 *      references but that live in other tcpdump source files not
 *      needed to exercise THIS bug: ospf6_print_lshdr/ospf6_print_lsa/
 *      ospf6_print_ls_type are stubs (only reachable via the DD/
 *      LS_REQ/LS_UPDATE/LS_ACK cases, which this corpus never selects
 *      -- every input is OSPF_TYPE_HELLO); ipaddr_string (-> getname)
 *      is a minimal real-signature stand-in (numeric, no DNS) that
 *      reads exactly sizeof(rtrid_t) bytes, matching the real
 *      implementation's memory-access footprint; bittok2str/
 *      bittok2str_internal/strlcpy are copied VERBATIM from
 *      util-print.c / missing/strlcpy.c (they ARE reached by the
 *      HELLO/DD Options-bitmask prints on the safe corpus, so their
 *      real logic matters for a faithful safe-path run).
 *   4. main(): reads argv[1] into a HEAP buffer (required so ASAN
 *      instruments it), sets ndo_snapend to the buffer's real end (no
 *      padding -- mirrors the real fuzz harness where the captured
 *      packet buffer's length IS the snapshot length), and calls
 *      ospf6_decode_v3() directly, exactly once, with dataend == the
 *      same buffer end (a plausible, in-range dataend -- the bug does
 *      not depend on dataend's value at all, only on ndo_snapend being
 *      shorter than the struct hello6 the code blindly indexes into).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* ---- real BSD scalar typedefs (normally from netdissect-stdinc.h) ---- */
typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;

/* ---- struct tok, netdissect.h, verbatim ---- */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

/*
 * netdissect_options, netdissect.h -- trimmed to the real fields this
 * function actually dereferences: ndo_vflag, ndo_snapend, ndo_printf.
 * Real names/types; the dozen other ndo_*flag knobs and the
 * ndo_error/ndo_warning/ndo_default_print/ndo_if_printer pointers are
 * omitted rather than fabricated (they'd drag in struct pcap_pkthdr /
 * if_printer, irrelevant to this bug and never touched by
 * ospf6_decode_v3 or its stand-in callees).
 */
typedef struct netdissect_options netdissect_options;

struct netdissect_options {
	int ndo_vflag;			/* verbosity level */
	const u_char *ndo_snapend;	/* end of captured packet data */
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---- netdissect.h macros, verbatim ---- */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TTEST(var) ND_TTEST2(var, sizeof(var))

#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/*
 * extract.h, verbatim -- the "processor natively handles unaligned
 * loads" branch (no LBL_ALIGN), which is what a real x86_64 build
 * compiles. EXTRACT_32BITS is the literal faulting frame in
 * case.json's baseline dedup_token
 * ("EXTRACT_32BITS--ospf6_decode_v3--ospf6_print").
 */
#if defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 409)
#define UNALIGNED_OK	__attribute__((no_sanitize_undefined))
#elif defined(__has_attribute) && __has_attribute(no_sanitize)
#define UNALIGNED_OK	__attribute__((no_sanitize("undefined")))
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

/* ==================================================================
 * VERBATIM real tcpdump source: source_code/print-ospf6.c
 * (OSPF_TYPE_* / OSPF6HDR_LEN / OSPF6_OPTION_* / OSPF6_DB_* macros,
 * typedef rtrid_t, struct lsa6_hdr/lsa6_prefix/lsa6/ospf6hdr/hello6/
 * dd6/lsr6/lsu6, ospf6_option_values / ospf6_dd_flag_values)
 * ================================================================== */

#define	OSPF_TYPE_HELLO         1	/* Hello */
#define	OSPF_TYPE_DD            2	/* Database Description */
#define	OSPF_TYPE_LS_REQ        3	/* Link State Request */
#define	OSPF_TYPE_LS_UPDATE     4	/* Link State Update */
#define	OSPF_TYPE_LS_ACK        5	/* Link State Ack */

/* Options *_options	*/
#define OSPF6_OPTION_V6	0x01	/* V6 bit: A bit for peeping tom */
#define OSPF6_OPTION_E	0x02	/* E bit: External routes advertised	*/
#define OSPF6_OPTION_MC	0x04	/* MC bit: Multicast capable */
#define OSPF6_OPTION_N	0x08	/* N bit: For type-7 LSA */
#define OSPF6_OPTION_R	0x10	/* R bit: Router bit */
#define OSPF6_OPTION_DC	0x20	/* DC bit: Demand circuits */
/* The field is actually 24-bit (RFC5340 Section A.2). */
#define OSPF6_OPTION_AF	0x0100	/* AF bit: Multiple address families */
#define OSPF6_OPTION_L	0x0200	/* L bit: Link-local signaling (LLS) */
#define OSPF6_OPTION_AT	0x0400	/* AT bit: Authentication trailer */

/* db_flags	*/
#define	OSPF6_DB_INIT		0x04	    /*	*/
#define	OSPF6_DB_MORE		0x02
#define	OSPF6_DB_MASTER		0x01
#define	OSPF6_DB_M6		0x10  /* IPv6 MTU */

typedef uint32_t rtrid_t;

/* link state advertisement header */
struct lsa6_hdr {
    uint16_t ls_age;
    uint16_t ls_type;
    rtrid_t ls_stateid;
    rtrid_t ls_router;
    uint32_t ls_seq;
    uint16_t ls_chksum;
    uint16_t ls_length;
};

/* Length of an IPv6 address, in bytes. */
#define IPV6_ADDR_LEN_BYTES (128/8)

struct lsa6_prefix {
    uint8_t lsa_p_len;
    uint8_t lsa_p_opt;
    uint16_t lsa_p_metric;
    uint8_t lsa_p_prefix[IPV6_ADDR_LEN_BYTES]; /* maximum length */
};

/* link state advertisement */
struct lsa6 {
    struct lsa6_hdr ls_hdr;

    /* Link state types */
    union {
	/* Router links advertisements */
	struct {
	    union {
		uint8_t flg;
		uint32_t opt;
	    } rla_flgandopt;
#define rla_flags	rla_flgandopt.flg
#define rla_options	rla_flgandopt.opt
	    struct rlalink6 {
		uint8_t link_type;
		uint8_t link_zero[1];
		uint16_t link_metric;
		uint32_t link_ifid;
		uint32_t link_nifid;
		rtrid_t link_nrtid;
	    } rla_link[1];		/* may repeat	*/
	} un_rla;

	/* Network links advertisements */
	struct {
	    uint32_t nla_options;
	    rtrid_t nla_router[1];	/* may repeat	*/
	} un_nla;

	/* Inter Area Prefix LSA */
	struct {
	    uint32_t inter_ap_metric;
	    struct lsa6_prefix inter_ap_prefix[1];
	} un_inter_ap;

	/* AS external links advertisements */
	struct {
	    uint32_t asla_metric;
	    struct lsa6_prefix asla_prefix[1];
	    /* some optional fields follow */
	} un_asla;

	/* Type 7 LSA */

	/* Link LSA */
	struct llsa {
	    union {
		uint8_t pri;
		uint32_t opt;
	    } llsa_priandopt;
#define llsa_priority	llsa_priandopt.pri
#define llsa_options	llsa_priandopt.opt
	    struct in6_addr llsa_lladdr;
	    uint32_t llsa_nprefix;
	    struct lsa6_prefix llsa_prefix[1];
	} un_llsa;

	/* Intra-Area-Prefix */
	struct {
	    uint16_t intra_ap_nprefix;
	    uint16_t intra_ap_lstype;
	    rtrid_t intra_ap_lsid;
	    rtrid_t intra_ap_rtid;
	    struct lsa6_prefix intra_ap_prefix[1];
	} un_intra_ap;
    } lsa_un;
};

/*
 * the main header
 */
struct ospf6hdr {
    uint8_t ospf6_version;
    uint8_t ospf6_type;
    uint16_t ospf6_len;
    rtrid_t ospf6_routerid;
    rtrid_t ospf6_areaid;
    uint16_t ospf6_chksum;
    uint8_t ospf6_instanceid;
    uint8_t ospf6_rsvd;
};

/*
 * The OSPF6 header length is 16 bytes, regardless of how your compiler
 * might choose to pad the above structure.
 */
#define OSPF6HDR_LEN    16

/* Hello packet */
struct hello6 {
    uint32_t hello_ifid;
    union {
	uint8_t pri;
	uint32_t opt;
    } hello_priandopt;
#define hello_priority	hello_priandopt.pri
#define hello_options	hello_priandopt.opt
    uint16_t hello_helloint;
    uint16_t hello_deadint;
    rtrid_t hello_dr;
    rtrid_t hello_bdr;
    rtrid_t hello_neighbor[1]; /* may repeat	*/
};

/* Database Description packet */
struct dd6 {
    uint32_t db_options;
    uint16_t db_mtu;
    uint8_t db_mbz;
    uint8_t db_flags;
    uint32_t db_seq;
    struct lsa6_hdr db_lshdr[1]; /* may repeat	*/
};

/* Link State Request */
struct lsr6 {
    uint16_t ls_mbz;
    uint16_t ls_type;
    rtrid_t ls_stateid;
    rtrid_t ls_router;
};

/* Link State Update */
struct lsu6 {
    uint32_t lsu_count;
    struct lsa6 lsu_lsa[1]; /* may repeat	*/
};

static const struct tok ospf6_option_values[] = {
	{ OSPF6_OPTION_V6,	"V6" },
	{ OSPF6_OPTION_E,	"External" },
	{ OSPF6_OPTION_MC,	"Deprecated" },
	{ OSPF6_OPTION_N,	"NSSA" },
	{ OSPF6_OPTION_R,	"Router" },
	{ OSPF6_OPTION_DC,	"Demand Circuit" },
	{ OSPF6_OPTION_AF,	"AFs Support" },
	{ OSPF6_OPTION_L,	"LLS" },
	{ OSPF6_OPTION_AT,	"Authentication Trailer" },
	{ 0,			NULL }
};

static const struct tok ospf6_dd_flag_values[] = {
	{ OSPF6_DB_INIT,	"Init" },
	{ OSPF6_DB_MORE,	"More" },
	{ OSPF6_DB_MASTER,	"Master" },
	{ OSPF6_DB_M6,		"IPv6 MTU" },
	{ 0,			NULL }
};

/* ==================================================================
 * end of verbatim print-ospf6.c struct/macro/table block
 * ================================================================== */

/*
 * Real-signature stand-ins for the three callees ospf6_decode_v3()
 * invokes (DD/LS_ACK, LS_REQ, LS_UPDATE cases). Not reached by this
 * corpus (every input is OSPF_TYPE_HELLO), so their real bodies --
 * which live in the same print-ospf6.c and pull in more tables/
 * structs unrelated to this bug -- are not needed; only the real
 * name+signature is needed so the VERBATIM target function's other
 * switch cases still resolve at compile time.
 */
static void
ospf6_print_ls_type(netdissect_options *ndo, u_int ls_type, const rtrid_t *ls_stateid)
{
	(void)ndo; (void)ls_type; (void)ls_stateid;
}

static int
ospf6_print_lshdr(netdissect_options *ndo, const struct lsa6_hdr *lshp, const u_char *dataend)
{
	(void)ndo; (void)lshp; (void)dataend;
	return 0;
}

static int
ospf6_print_lsa(netdissect_options *ndo, const struct lsa6 *lsap, const u_char *dataend)
{
	(void)ndo; (void)lsap; (void)dataend;
	return 0;
}

/*
 * missing/strlcpy.c, verbatim (real compat shim tcpdump ships for
 * non-BSD libcs; bittok2str_internal below needs it).
 */
static size_t
strlcpy(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;

	if (n != 0 && --n != 0) {
		do {
			if ((*d++ = *s++) == 0)
				break;
		} while (--n != 0);
	}

	if (n == 0) {
		if (siz != 0)
			*d = '\0';
		while (*s++)
			;
	}

	return(s - src - 1);
}

/* util-print.c, verbatim (reached by the HELLO/DD Options bitmask
 * prints on the safe corpus, so the real bit-formatting logic
 * matters for a faithful safe-path run). */
static char *
bittok2str_internal(const struct tok *lp, const char *fmt,
	   u_int v, const char *sep)
{
        static char buf[1024+1];
        char *bufp = buf;
        size_t space_left = sizeof(buf), string_size;
        u_int rotbit;
        u_int tokval;
        const char * sepstr = "";

	while (lp != NULL && lp->s != NULL) {
            tokval=lp->v;
            rotbit=1;
            while (rotbit != 0) {
		if (tokval == (v&rotbit)) {
                    if (space_left <= 1)
                        return (buf);
                    string_size = strlcpy(bufp, sepstr, space_left);
                    if (string_size >= space_left)
                        return (buf);
                    bufp += string_size;
                    space_left -= string_size;
                    if (space_left <= 1)
                        return (buf);
                    string_size = strlcpy(bufp, lp->s, space_left);
                    if (string_size >= space_left)
                        return (buf);
                    bufp += string_size;
                    space_left -= string_size;
                    sepstr = sep;
                    break;
                }
                rotbit=rotbit<<1;
            }
            lp++;
	}

        if (bufp == buf)
            (void)snprintf(buf, sizeof(buf), fmt == NULL ? "#%08x" : fmt, v);
        return (buf);
}

static char *
bittok2str(const struct tok *lp, const char *fmt, u_int v)
{
    return (bittok2str_internal(lp, fmt, v, ", "));
}

/*
 * addrtoname.h real macro -> getname (addrtoname.c). Real signature,
 * simplified numeric-only body (no hostname resolution -- this
 * harness always runs numeric, no network); reads exactly
 * sizeof(rtrid_t) bytes from p, same as the real implementation's
 * memory-access footprint.
 */
#define ipaddr_string(ndo, p) getname(ndo, (const u_char *)(p))

static const char *
getname(netdissect_options *ndo, const u_char *p)
{
	static char buf[INET_ADDRSTRLEN];
	struct in_addr in;
	(void)ndo;
	memcpy(&in, p, sizeof(in));
	return inet_ntop(AF_INET, &in, buf, sizeof(buf));
}

/* ==================================================================
 * VERBATIM real tcpdump source begins here:
 *   dataset/cve_b7b524fe/target/original_function.c, byte-for-byte,
 *   the target function itself, UNCHANGED.
 * ================================================================== */

static int
ospf6_decode_v3(netdissect_options *ndo,
                register const struct ospf6hdr *op,
                register const u_char *dataend)
{
	register const rtrid_t *ap;
	register const struct lsr6 *lsrp;
	register const struct lsa6_hdr *lshp;
	register const struct lsa6 *lsap;
	register int i;

	switch (op->ospf6_type) {

	case OSPF_TYPE_HELLO: {
		register const struct hello6 *hellop = (const struct hello6 *)((const uint8_t *)op + OSPF6HDR_LEN);

		ND_PRINT((ndo, "\n\tOptions [%s]",
		          bittok2str(ospf6_option_values, "none",
		          EXTRACT_32BITS(&hellop->hello_options))));

		ND_TCHECK(hellop->hello_deadint);
		ND_PRINT((ndo, "\n\t  Hello Timer %us, Dead Timer %us, Interface-ID %s, Priority %u",
		          EXTRACT_16BITS(&hellop->hello_helloint),
		          EXTRACT_16BITS(&hellop->hello_deadint),
		          ipaddr_string(ndo, &hellop->hello_ifid),
		          hellop->hello_priority));

		ND_TCHECK(hellop->hello_dr);
		if (EXTRACT_32BITS(&hellop->hello_dr) != 0)
			ND_PRINT((ndo, "\n\t  Designated Router %s",
			    ipaddr_string(ndo, &hellop->hello_dr)));
		ND_TCHECK(hellop->hello_bdr);
		if (EXTRACT_32BITS(&hellop->hello_bdr) != 0)
			ND_PRINT((ndo, ", Backup Designated Router %s",
			    ipaddr_string(ndo, &hellop->hello_bdr)));
		if (ndo->ndo_vflag > 1) {
			ND_PRINT((ndo, "\n\t  Neighbor List:"));
			ap = hellop->hello_neighbor;
			while ((const u_char *)ap < dataend) {
				ND_TCHECK(*ap);
				ND_PRINT((ndo, "\n\t    %s", ipaddr_string(ndo, ap)));
				++ap;
			}
		}
		break;	/* HELLO */
	}

	case OSPF_TYPE_DD: {
		register const struct dd6 *ddp = (const struct dd6 *)((const uint8_t *)op + OSPF6HDR_LEN);

		ND_TCHECK(ddp->db_options);
		ND_PRINT((ndo, "\n\tOptions [%s]",
		          bittok2str(ospf6_option_values, "none",
		          EXTRACT_32BITS(&ddp->db_options))));
		ND_TCHECK(ddp->db_flags);
		ND_PRINT((ndo, ", DD Flags [%s]",
		          bittok2str(ospf6_dd_flag_values,"none",ddp->db_flags)));

		ND_TCHECK(ddp->db_seq);
		ND_PRINT((ndo, ", MTU %u, DD-Sequence 0x%08x",
                       EXTRACT_16BITS(&ddp->db_mtu),
                       EXTRACT_32BITS(&ddp->db_seq)));
		if (ndo->ndo_vflag > 1) {
			/* Print all the LS adv's */
			lshp = ddp->db_lshdr;
			while ((const u_char *)lshp < dataend) {
				if (ospf6_print_lshdr(ndo, lshp++, dataend))
					goto trunc;
			}
		}
		break;
	}

	case OSPF_TYPE_LS_REQ:
		if (ndo->ndo_vflag > 1) {
			lsrp = (const struct lsr6 *)((const uint8_t *)op + OSPF6HDR_LEN);
			while ((const u_char *)lsrp < dataend) {
				ND_TCHECK(*lsrp);
				ND_PRINT((ndo, "\n\t  Advertising Router %s",
				          ipaddr_string(ndo, &lsrp->ls_router)));
				ospf6_print_ls_type(ndo, EXTRACT_16BITS(&lsrp->ls_type),
                                                    &lsrp->ls_stateid);
				++lsrp;
			}
		}
		break;

	case OSPF_TYPE_LS_UPDATE:
		if (ndo->ndo_vflag > 1) {
			register const struct lsu6 *lsup = (const struct lsu6 *)((const uint8_t *)op + OSPF6HDR_LEN);

			ND_TCHECK(lsup->lsu_count);
			i = EXTRACT_32BITS(&lsup->lsu_count);
			lsap = lsup->lsu_lsa;
			while ((const u_char *)lsap < dataend && i--) {
				if (ospf6_print_lsa(ndo, lsap, dataend))
					goto trunc;
				lsap = (const struct lsa6 *)((const u_char *)lsap +
				    EXTRACT_16BITS(&lsap->ls_hdr.ls_length));
			}
		}
		break;

	case OSPF_TYPE_LS_ACK:
		if (ndo->ndo_vflag > 1) {
			lshp = (const struct lsa6_hdr *)((const uint8_t *)op + OSPF6HDR_LEN);
			while ((const u_char *)lshp < dataend) {
				if (ospf6_print_lshdr(ndo, lshp++, dataend))
					goto trunc;
			}
		}
		break;

	default:
		break;
	}
	return (0);
trunc:
	return (1);
}

/* ==================================================================
 * end of verbatim target function
 * ================================================================== */

/* no-op output function pointer, per the direct-call harness recipe */
static int
null_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo; (void)fmt;
	return 0;
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
	struct ospf6hdr *op;

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
	ndo->ndo_vflag = 2;		/* max verbosity, like the real fuzz target */
	ndo->ndo_printf = null_printf;
	/* snapend = exact end of the heap allocation -- no padding, so a
	 * read that runs past the declared object body but still inside
	 * a shorter-than-full-struct object is a genuine heap-buffer-
	 * overflow, exactly as in the real fuzz harness where the
	 * captured-packet buffer IS the snapshot length. */
	ndo->ndo_snapend = buf + n;

	/* op = the packet buffer itself, exactly as the real caller
	 * ospf6_print() does: op = (const struct ospf6hdr *)bp. */
	op = (struct ospf6hdr *)buf;

	/* dataend: the real caller derives this from the *attacker-
	 * declared* ospf6_len field, which can be <= or > the real
	 * snapend. The bug this harness reproduces does not depend on
	 * dataend's value at all (the faulting read has no ND_TCHECK at
	 * all), so a plausible in-range dataend == snapend is used. */
	(void)ospf6_decode_v3(ndo, op, buf + n);

	free(buf);
	return 0;
}
