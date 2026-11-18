/*
 * Direct-call crash harness for CVE-2018-14880 (tcpdump, print-ospf6.c,
 * ospf6_print_lshdr()).
 *
 * Reproduces the heap-buffer-overflow READ (CWE-125) at
 * EXTRACT_16BITS(&lshp->ls_length) in print-ospf6.c.
 *
 * Root cause: ospf6_print_lshdr() is handed a `dataend` pointer that marks
 * the end of the DECLARED LSA block -- in the real caller chain this comes
 * from `ospf6_print()`'s `dataend = bp + datalen`, where `datalen` is read
 * straight out of the packet's own ospf6_len field and is only checked
 * against the packet's CLAIMED wire length (`length`), never against
 * `ndo->ndo_snapend` (the boundary of what was actually CAPTURED). So
 * `dataend` can legitimately point past the real captured buffer.
 *
 * ospf6_print_lshdr()'s own guard,
 *     if ((const u_char *)(lshp + 1) > dataend) goto trunc;
 * checks the header (sizeof(struct lsa6_hdr) == 20 bytes) against that
 * possibly-too-generous `dataend`, NOT against ndo_snapend. The two
 * ND_TCHECK()s that follow DO check against ndo_snapend, but only for
 * `lshp->ls_type` (offset 2..4) and `lshp->ls_seq` (offset 12..16) --
 * together they only prove the first 16 bytes of the 20-byte header were
 * captured. The very next statement unconditionally reads
 * `EXTRACT_16BITS(&lshp->ls_length)`, at offset 18..20 -- 2 bytes that are
 * NEVER bounds-checked against ndo_snapend at all. So whenever the real
 * captured buffer is between 16 and 19 bytes (inclusive) starting at lshp,
 * both ND_TCHECKs pass (16 <= captured) while the ls_length read (needs
 * captured >= 20) runs off the end of the allocation.
 *
 * struct lsa6_hdr layout (print-ospf6.c, verbatim, no padding -- 20 bytes):
 *   offset 0  ls_age     uint16_t
 *   offset 2  ls_type    uint16_t
 *   offset 4  ls_stateid rtrid_t (uint32_t)
 *   offset 8  ls_router  rtrid_t (uint32_t)
 *   offset 12 ls_seq     uint32_t
 *   offset 16 ls_chksum  uint16_t
 *   offset 18 ls_length  uint16_t   <-- the unchecked read
 *
 * All type/struct/macro/function definitions below are copied verbatim (or
 * minimally trimmed to the fields ospf6_print_lshdr()/ospf6_print_ls_type()
 * actually touch) from the real tcpdump headers/sources:
 *   - netdissect_options (trimmed: ndo_snapend/ndo_printf),
 *     ND_TTEST2/ND_TCHECK2/ND_TCHECK/ND_PRINT, struct tok  <- netdissect.h
 *   - EXTRACT_16BITS/EXTRACT_32BITS (native-unaligned-load variant, matches
 *     the frozen baseline crash site "extract.h:184:20 in EXTRACT_16BITS")
 *                                                            <- extract.h
 *   - rtrid_t, struct lsa6_hdr, LS_TYPE_.../LS_SCOPE_... defines,
 *     ospf6_lsa_values[]/ospf6_ls_scope_values[] tables,
 *     ospf6_print_ls_type() (real callee, embedded verbatim -- reached on
 *     every SAFE/in-bounds input, exercises tok2str()+ipaddr_string())
 *                                                            <- print-ospf6.c
 *   - tok2str()/tok2strbuf()/TOKBUFSIZE                      <- util-print.c
 *
 * Not on the fault path -> real-name/real-footprint stand-in (never
 * dereferences out of bounds; present only so the verbatim function body
 * compiles/links):
 *   - ipaddr_string(ndo, p): real macro is
 *     `#define ipaddr_string(ndo, p) getname(ndo, (const u_char *)(p))`
 *     (addrtoname.h), where getname() resolves a 4-byte router/link-state
 *     ID to a hostname/dotted-decimal string via a big DNS/hash-table
 *     machinery (addrtoname.c) unrelated to this CVE. Our stand-in reads
 *     the SAME 4 bytes (the same memory-safety footprint as getname()) and
 *     formats them as dotted decimal, without the caching/DNS machinery.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <netinet/in.h>   /* ntohs/ntohl */
#include <arpa/inet.h>
#include <sys/types.h>    /* u_char, u_int */

/* ---- netdissect.h (verbatim subset: only fields/macros the target uses) ---- */

typedef struct netdissect_options netdissect_options;

struct netdissect_options {
	const u_char *ndo_snapend;	/* end of captured/allocated packet */
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- extract.h (verbatim, native-unaligned-load variant: no LBL_ALIGN;
 * matches the frozen baseline crash site "extract.h:184:20 in EXTRACT_16BITS") ---- */

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

/* ---- util-print.c (verbatim: tok2str family) ---- */

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

/* ---- addrtoname.h: ipaddr_string == getname(), real-footprint stand-in ---- */

static const char *
ipaddr_string(netdissect_options *ndo, const void *vp)
{
	/* real macro: #define ipaddr_string(ndo, p) getname(ndo, (const
	 * u_char *)(p)) -- the explicit cast is why this takes `const void *`
	 * (both `const rtrid_t *` and `const u_char *` call sites exist in
	 * the verbatim target/callee below). */
	const u_char *p = (const u_char *)vp;
	static char buf[4][32];
	static int idx = 0;
	char *b;
	(void)ndo;
	b = buf[idx];
	idx = (idx + 1) & 3;
	/* getname() resolves a 4-byte router/link-state ID (addrtoname.c); we
	 * read the same 4 bytes and format them as dotted decimal, no
	 * DNS/hash-table. */
	snprintf(b, sizeof(buf[0]), "%u.%u.%u.%u", p[0], p[1], p[2], p[3]);
	return b;
}

/* ---- print-ospf6.c (verbatim: types/tables/callee the target references) ---- */

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

/* ls_type	*/
#define	LS_TYPE_ROUTER		1   /* router link */
#define	LS_TYPE_NETWORK		2   /* network link */
#define	LS_TYPE_INTER_AP	3   /* Inter-Area-Prefix */
#define	LS_TYPE_INTER_AR	4   /* Inter-Area-Router */
#define	LS_TYPE_ASE		5   /* ASE */
#define	LS_TYPE_GROUP		6   /* Group membership */
#define	LS_TYPE_NSSA		7   /* NSSA */
#define	LS_TYPE_LINK		8   /* Link LSA */
#define	LS_TYPE_INTRA_AP	9   /* Intra-Area-Prefix */
#define LS_TYPE_INTRA_ATE       10  /* Intra-Area-TE */
#define LS_TYPE_GRACE           11  /* Grace LSA */
#define LS_TYPE_RI		12  /* Router information */
#define LS_TYPE_INTER_ASTE	13  /* Inter-AS-TE */
#define LS_TYPE_L1VPN		14  /* L1VPN */
#define LS_TYPE_MASK		0x1fff

#define LS_SCOPE_LINKLOCAL	0x0000
#define LS_SCOPE_AREA		0x2000
#define LS_SCOPE_AS		0x4000
#define LS_SCOPE_MASK		0x6000
#define LS_SCOPE_U              0x8000

static const struct tok ospf6_lsa_values[] = {
	{ LS_TYPE_ROUTER,       "Router" },
	{ LS_TYPE_NETWORK,      "Network" },
	{ LS_TYPE_INTER_AP,     "Inter-Area Prefix" },
	{ LS_TYPE_INTER_AR,     "Inter-Area Router" },
	{ LS_TYPE_ASE,          "External" },
	{ LS_TYPE_GROUP,        "Deprecated" },
	{ LS_TYPE_NSSA,         "NSSA" },
	{ LS_TYPE_LINK,         "Link" },
	{ LS_TYPE_INTRA_AP,     "Intra-Area Prefix" },
        { LS_TYPE_INTRA_ATE,    "Intra-Area TE" },
        { LS_TYPE_GRACE,        "Grace" },
	{ LS_TYPE_RI,           "Router Information" },
	{ LS_TYPE_INTER_ASTE,   "Inter-AS-TE" },
	{ LS_TYPE_L1VPN,        "Layer 1 VPN" },
	{ 0,			NULL }
};

static const struct tok ospf6_ls_scope_values[] = {
	{ LS_SCOPE_LINKLOCAL,   "Link Local" },
	{ LS_SCOPE_AREA,        "Area Local" },
	{ LS_SCOPE_AS,          "Domain Wide" },
	{ 0,			NULL }
};

static void
ospf6_print_ls_type(netdissect_options *ndo,
                    register u_int ls_type, register const rtrid_t *ls_stateid)
{
        ND_PRINT((ndo, "\n\t    %s LSA (%d), %s Scope%s, LSA-ID %s",
               tok2str(ospf6_lsa_values, "Unknown", ls_type & LS_TYPE_MASK),
               ls_type & LS_TYPE_MASK,
               tok2str(ospf6_ls_scope_values, "Unknown", ls_type & LS_SCOPE_MASK),
               ls_type &0x8000 ? ", transitive" : "", /* U-bit */
               ipaddr_string(ndo, ls_stateid)));
}

/* ================= target function, embedded verbatim ================= */

static int
ospf6_print_lshdr(netdissect_options *ndo,
                  register const struct lsa6_hdr *lshp, const u_char *dataend)
{
	if ((const u_char *)(lshp + 1) > dataend)
		goto trunc;
	ND_TCHECK(lshp->ls_type);
	ND_TCHECK(lshp->ls_seq);

	ND_PRINT((ndo, "\n\t  Advertising Router %s, seq 0x%08x, age %us, length %u",
               ipaddr_string(ndo, &lshp->ls_router),
               EXTRACT_32BITS(&lshp->ls_seq),
               EXTRACT_16BITS(&lshp->ls_age),
               EXTRACT_16BITS(&lshp->ls_length)-(u_int)sizeof(struct lsa6_hdr)));

	ospf6_print_ls_type(ndo, EXTRACT_16BITS(&lshp->ls_type), &lshp->ls_stateid);

	return (0);
trunc:
	return (1);
}

/* ============================= harness main ============================= */

/* ndo_printf stand-in: routes every formatted-print call through a REAL,
 * opaque libc call that actually consumes its varargs, so the optimizer
 * cannot prove the call has no observable effect and fold away/DCE the
 * surrounding statement (including the crashing
 * EXTRACT_16BITS(&lshp->ls_length) argument evaluation feeding it). */
static int
stub_printf(netdissect_options *ndo, const char *fmt, ...)
{
	char buf[256];
	va_list ap;
	int rc;
	(void)ndo;
	va_start(ap, fmt);
	rc = vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	return rc;
}

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

	/* HEAP buffer for the attacker-controlled bytes, sized EXACTLY to the
	 * input file length (min 1 byte for malloc, but ndo_snapend still
	 * tracks the true `n`, so a 0-byte input's true bound is `buf+0`). */
	size_t alloc = (n > 0) ? (size_t)n : 1;
	unsigned char *buf = (unsigned char *)malloc(alloc);
	if (!buf) { fclose(f); return 1; }

	size_t got = (n > 0) ? fread(buf, 1, (size_t)n, f) : 0;
	fclose(f);
	if ((long)got != n) { free(buf); return 1; }

	netdissect_options ndo_s;
	memset(&ndo_s, 0, sizeof(ndo_s));	/* zero-init unused fields */
	ndo_s.ndo_printf = stub_printf;
	ndo_s.ndo_snapend = buf + n;		/* end of the ACTUALLY captured/allocated packet */

	/* `dataend` simulates the DECLARED end of the LSA block that the real
	 * caller ospf6_print() computes from a length field read straight out
	 * of the packet (`dataend = bp + datalen`), checked only against the
	 * packet's claimed wire length -- never against ndo_snapend. Fixing it
	 * at exactly one lsa6_hdr's worth past the header start reproduces
	 * that real-world mismatch: the declared boundary says "the whole
	 * header is here", independent of how many bytes (`n`) were actually
	 * captured into `buf`. */
	const u_char *dataend = buf + sizeof(struct lsa6_hdr);

	ospf6_print_lshdr(&ndo_s, (const struct lsa6_hdr *)buf, dataend);

	free(buf);
	return 0;
}
