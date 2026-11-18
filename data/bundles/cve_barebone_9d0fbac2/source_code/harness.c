/*
 * cvf_9d0fbac2 direct-call crash harness for tcpdump's handle_ppp()
 * (CVE-2017-12897 / CWE-125 heap-buffer-overflow READ).
 *
 * Root cause (see fix commit 1dcd10aceabbc03bf571ea32b892c522cbe923de):
 * handle_ppp()'s PPP_OSI case calls `isoclns_print(ndo, p, length, length)`
 * -- passing the caller's `length` (the PPP payload's DECLARED length, not
 * derived from ndo_snapend) as BOTH the length AND the caplen argument.
 * isoclns_print()'s only "is there data?" guard is `if (caplen <= 1) return;`
 * -- it does NOT check `p` against ndo_snapend (the fix replaces this with
 * `if (!ND_TTEST(*p)) return;`). So whenever `p` itself already points at
 * or past the end of the actually-captured buffer (which can happen for
 * any reason unrelated to the value of `length`/`caplen` -- e.g. the
 * caller already consumed the whole buffer as header bytes before this
 * call), the very next statement `switch (*p) {` dereferences one byte
 * past the allocation: a genuine heap-buffer-overflow READ, exactly
 * matching this bundle's frozen baseline
 * (dedup_token "isoclns_print--handle_ppp--ppp_print", summary
 * "AddressSanitizer: heap-buffer-overflow /work/./print-isoclns.c:684:10
 * in isoclns_print" -- line 684 there is precisely `switch (*p) {`).
 *
 * This file assembles:
 *   1. Minimal-but-faithful standalone re-declarations of the real
 *      tcpdump types/macros/constants both functions need (struct tok,
 *      netdissect_options trimmed to the fields actually dereferenced,
 *      ND_PRINT, the PPP_/ETHERTYPE_/NLPID_ constants both switches
 *      dispatch on).
 *   2. Minimal real-signature stand-ins ("safe no-op" callees, see the
 *      big comment above their definitions below) for every OTHER
 *      external symbol either function references but that lives in a
 *      different tcpdump source file and does NOT contain this bug:
 *      ppp_hdlc/handle_ctrl_proto/handle_mlppp/handle_chap/handle_pap/
 *      handle_bap (print-ppp.c, other PPP sub-protocols), ip_print/
 *      ip6_print/ipx_print/mpls_print (print-ip.c/print-ip6.c/
 *      print-ipx.c/print-mpls.c), clnp_print/esis_print/isis_print/
 *      q933_print/ppp_print (isoclns_print's OWN callees -- unreachable
 *      for the crash anyway, since the fault fires at isoclns_print's
 *      very first statement, before ANY of them could be called),
 *      print_unknown_data (util-print.c). tok2str/tok2strbuf (also
 *      util-print.c) ARE implemented for real (see below) since
 *      handle_ppp's `default:` case calls tok2str() UNCONDITIONALLY
 *      (not behind ndo_eflag) and it is cheap + genuinely simple.
 *   3. VERBATIM real tcpdump source, byte-for-byte, unchanged:
 *        - handle_ppp() itself: dataset/cvf_9d0fbac2/target/
 *          original_function.c (== source_code/print-ppp.c:1443-1501).
 *        - isoclns_print(): source_code/print-isoclns.c:672-728 -- the
 *          real callee the fault is actually inside (per the
 *          ddiv directcall recipe's "embed real callees VERBATIM
 *          if the fault is inside one").
 *   4. main(): reads argv[1] into a HEAP buffer (`raw`, required so ASAN
 *      instruments it -- attacker data is NEVER put on the stack/in a
 *      global), then drives ONE of three scenarios selected by raw[0]
 *      (raw[0] is never itself an out-of-bounds read: main() only reads
 *      it when the file is non-empty, and defaults to the TRIGGER
 *      scenario for an empty file):
 *        sel==0 (or empty file): TRIGGER. proto=PPP_OSI, p = raw+n (one
 *          byte past the END of the SAME heap allocation -- 0 valid
 *          bytes remain there), length=64 (>1, so isoclns_print's
 *          `caplen<=1` guard is bypassed) -- reproduces the exact bug:
 *          p invalid, length/caplen totally disconnected from that
 *          fact. Works for any n>=0 (n=0 = malloc(0), still ASAN-
 *          instrumented with a 0-byte usable region).
 *        sel==1: SAFE, in-bounds PPP_OSI. p = raw+1, length = n-1
 *          (requires n>=3 so length>1); raw[1] is the NLPID byte
 *          isoclns_print's OWN switch reads -- varying it across the
 *          generated corpus exercises every one of isoclns_print's
 *          cases (NULLNS/CLNP/ESIS/ISIS/Q933/IP/IP6/PPP/unknown-
 *          default), all safely (p is genuinely in-bounds: raw has
 *          n>=3 live bytes and p=raw+1 only ever needs raw[1] to be
 *          valid).
 *        sel==2: SAFE, non-OSI proto. proto = (raw[1]<<8)|raw[2] (a
 *          16-bit big-endian field the generator sets to one of
 *          handle_ppp's OTHER recognized PPP_/ETHERTYPE_ constants,
 *          or an unrecognized value to hit the `default:` case);
 *          p = raw+3, length = n-3 (requires n>=3; length may be 0,
 *          which is fine -- none of the stub callees ever dereference
 *          p, so any length is safe here). The proto values used are
 *          all chosen to avoid the `(proto & 0xff00) == 0x7e00` HDLC-
 *          escape-code path (ppp_hdlc), which is unrelated to this bug.
 *      main() calls handle_ppp() exactly once per input, with
 *      ndo_snapend set to the real end of the SAME allocation used for
 *      `p` (mirrors the real capture-buffer model: the malloc'd
 *      buffer's length IS the snapshot length) and ndo_eflag=0 (matches
 *      the frozen baseline's repro flags "-v -nn", no "-e").
 *
 * Compiler-DCE note (load-bearing, see the `vb_escape()`/sink comments
 * below): at -O1, if every one of isoclns_print's/handle_ppp's callees
 * were a PURE no-op with no observable effect, clang can prove the
 * entire chain of calls (and hence the `switch(*p)`/`switch(proto)`
 * selector reads that pick among them) has no observable outcome and
 * dead-code-eliminate it -- silently turning the real overflow into a
 * no-op (this exact failure mode is documented, live-confirmed, in
 * this project's OTHER direct-call harnesses, e.g. cve_1acd4605's
 * chdlc_print). Every stub callee below therefore folds its own
 * arguments into a shared `volatile` global sink, giving each
 * branch/case a real, argument-value-dependent side effect the
 * optimizer cannot prove away -- forcing the selector reads (INCLUDING
 * the crashing one) to actually execute at runtime. `raw` itself is
 * additionally escaped via `vb_escape()` before the call.
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

/* ---- struct tok, netdissect.h, verbatim ---- */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

/*
 * netdissect_options, netdissect.h -- trimmed to the real fields
 * handle_ppp()/isoclns_print() actually dereference: ndo_eflag (read by
 * isoclns_print, and by handle_ppp's real callees which we've stubbed
 * out) and ndo_printf (ND_PRINT). ndo_snapend is included and set for
 * parity with the real caller/struct layout, even though THIS
 * (pre-fix, vulnerable) revision of isoclns_print does not itself
 * consult it -- that check is exactly what the fix commit adds.
 */
typedef struct netdissect_options netdissect_options;

struct netdissect_options {
	int ndo_eflag;			/* print link-layer header */
	const u_char *ndo_snapend;	/* end of captured packet data */
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---- netdissect.h macro, verbatim ---- */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- ppp.h, verbatim constants -- handle_ppp()'s own switch(proto) ---- */
#define PPP_IP		0x0021	/* Raw IP */
#define PPP_OSI		0x0023	/* OSI Network Layer */
#define PPP_IPX		0x002b	/* Novell IPX */
#define PPP_VJNC	0x002f	/* Van Jacobson Uncompressed TCP/IP */
#define PPP_ML          0x003d  /* Multi-Link PPP */
#define PPP_IPV6	0x0057	/* IPv6 */
#define	PPP_COMP	0x00fd	/* Compressed Datagram */
#define PPP_MPLS_UCAST  0x0281  /* rfc 3032 */
#define PPP_MPLS_MCAST  0x0283  /* rfc 3022 */
#define PPP_IPCP	0x8021	/* IP Control Protocol */
#define PPP_OSICP	0x8023	/* OSI Network Layer Control Protocol */
#define PPP_IPV6CP	0x8057	/* IPv6 Control Protocol */
#define PPP_CCP		0x80fd	/* Compress Control Protocol */
#define PPP_MPLSCP      0x8281  /* rfc 3022 */
#define PPP_LCP		0xc021	/* Link Control Protocol */
#define PPP_PAP		0xc023	/* Password Authentication Protocol */
#define PPP_CHAP	0xc223	/* Challenge Handshake Authentication Protocol */
#define PPP_BACP	0xc02b	/* Bandwidth Allocation Control Protocol */
#define PPP_BAP		0xc02d	/* BAP */

/* ---- ethertype.h, verbatim values -- also handle_ppp()'s switch(proto) ---- */
#define ETHERTYPE_IP		0x0800
#define ETHERTYPE_IPV6		0x86dd
#define ETHERTYPE_IPX		0x8137

/* ---- nlpid.h, verbatim -- isoclns_print()'s OWN switch(*p) ---- */
#define	NLPID_NULLNS	0x00
#define NLPID_Q933      0x08
#define	NLPID_CLNP	0x81
#define	NLPID_ESIS	0x82
#define	NLPID_ISIS	0x83
#define NLPID_IP        0xcc
#define NLPID_PPP       0xcf
#define NLPID_IP6       0x8e

/*
 * print-ppp.c, real symbol name required for linkage (handle_ppp's
 * `default:` case references it UNCONDITIONALLY via tok2str()) --
 * contents stubbed to just the real terminator entry, per the
 * ddiv directcall precedent (see e.g. cve_1acd4605's
 * `ethertype_values`): the full ~35-entry table lives entirely outside
 * this bug's call graph and only feeds a discarded ND_PRINT (this
 * harness's ndo_printf is a no-op).
 */
static const struct tok ppptype2str[] = { { 0, NULL } };

/*
 * nlpid.h, real symbol name -- isoclns_print() only reads it behind
 * `if (ndo->ndo_eflag)`, which this harness never sets (matches the
 * frozen baseline's repro flags "-v -nn", no "-e"), so its contents
 * are irrelevant; stubbed the same way as ppptype2str above.
 */
const struct tok nlpid_values[] = { { 0, NULL } };

/*
 * Forward declarations (real names + real signatures) for every
 * external symbol handle_ppp()/isoclns_print() reference. NONE of these
 * contain either function's fault (isoclns_print's own `switch (*p)`
 * selector read, which fires -- when it fires -- before any of them
 * could possibly be reached), so per the ddiv directcall
 * precedent they are safe real-signature no-op stand-ins rather than
 * full reimplementations. Definitions follow main().
 */
static void handle_ctrl_proto(netdissect_options *, u_int proto, const u_char *pptr, int length);
static void handle_mlppp(netdissect_options *, const u_char *p, int length);
static void handle_chap(netdissect_options *, const u_char *p, int length);
static void handle_pap(netdissect_options *, const u_char *p, int length);
static void handle_bap(netdissect_options *, const u_char *p, int length);
static void ppp_hdlc(netdissect_options *, const u_char *p, int length);
extern void ip_print(netdissect_options *, const u_char *, u_int);
extern void ip6_print(netdissect_options *, const u_char *, u_int);
extern void ipx_print(netdissect_options *, const u_char *, u_int);
extern void mpls_print(netdissect_options *, const u_char *, u_int);
extern int  print_unknown_data(netdissect_options *, const u_char *, const char *, int);
extern const char *tok2strbuf(const struct tok *, const char *, u_int, char *, size_t);
extern const char *tok2str(const struct tok *, const char *, u_int);
extern void isoclns_print(netdissect_options *, const uint8_t *, u_int, u_int);

/* isoclns_print()'s OWN real callees (print-isoclns.c/print-fr.c/print-ppp.c) */
static int   clnp_print(netdissect_options *, const uint8_t *, u_int);
static void  esis_print(netdissect_options *, const uint8_t *, u_int);
static int   isis_print(netdissect_options *, const uint8_t *, u_int);
extern void  q933_print(netdissect_options *, const u_char *, u_int);
extern u_int ppp_print(netdissect_options *, const u_char *, u_int);

/* ==================================================================
 * VERBATIM real tcpdump source begins here:
 *   dataset/cvf_9d0fbac2/target/original_function.c byte-for-byte
 *   (== source_code/print-ppp.c:1443-1501, handle_ppp() itself,
 *   UNCHANGED -- logic/names/signature untouched).
 * ================================================================== */
static void
handle_ppp(netdissect_options *ndo,
           u_int proto, const u_char *p, int length)
{
	if ((proto & 0xff00) == 0x7e00) { /* is this an escape code ? */
		ppp_hdlc(ndo, p - 1, length);
		return;
	}

	switch (proto) {
	case PPP_LCP: /* fall through */
	case PPP_IPCP:
	case PPP_OSICP:
	case PPP_MPLSCP:
	case PPP_IPV6CP:
	case PPP_CCP:
	case PPP_BACP:
		handle_ctrl_proto(ndo, proto, p, length);
		break;
	case PPP_ML:
		handle_mlppp(ndo, p, length);
		break;
	case PPP_CHAP:
		handle_chap(ndo, p, length);
		break;
	case PPP_PAP:
		handle_pap(ndo, p, length);
		break;
	case PPP_BAP:		/* XXX: not yet completed */
		handle_bap(ndo, p, length);
		break;
	case ETHERTYPE_IP:	/*XXX*/
        case PPP_VJNC:
	case PPP_IP:
		ip_print(ndo, p, length);
		break;
	case ETHERTYPE_IPV6:	/*XXX*/
	case PPP_IPV6:
		ip6_print(ndo, p, length);
		break;
	case ETHERTYPE_IPX:	/*XXX*/
	case PPP_IPX:
		ipx_print(ndo, p, length);
		break;
	case PPP_OSI:
		isoclns_print(ndo, p, length, length);
		break;
	case PPP_MPLS_UCAST:
	case PPP_MPLS_MCAST:
		mpls_print(ndo, p, length);
		break;
	case PPP_COMP:
		ND_PRINT((ndo, "compressed PPP data"));
		break;
	default:
		ND_PRINT((ndo, "%s ", tok2str(ppptype2str, "unknown PPP protocol (0x%04x)", proto)));
		print_unknown_data(ndo, p, "\n\t", length);
		break;
	}
}
/* ==================================================================
 * end of verbatim handle_ppp
 * ================================================================== */

/* ==================================================================
 * VERBATIM real tcpdump source begins here:
 *   source_code/print-isoclns.c:672-728 (isoclns_print() itself,
 *   UNCHANGED) -- the real callee handle_ppp()'s PPP_OSI case dispatches
 *   straight into (`isoclns_print(ndo, p, length, length)`, no offset)
 *   and the ACTUAL fault (the unchecked `switch (*p)` selector read) is
 *   inside. Per the ddiv directcall recipe ("embed real callees
 *   VERBATIM if the fault is inside one") this function is reproduced
 *   byte-for-byte from source_code/, not stubbed.
 * ================================================================== */
void
isoclns_print(netdissect_options *ndo,
              const uint8_t *p, u_int length, u_int caplen)
{
	if (caplen <= 1) { /* enough bytes on the wire ? */
		ND_PRINT((ndo, "|OSI"));
		return;
	}

	if (ndo->ndo_eflag)
		ND_PRINT((ndo, "OSI NLPID %s (0x%02x): ", tok2str(nlpid_values, "Unknown", *p), *p));

	switch (*p) {

	case NLPID_CLNP:
		if (!clnp_print(ndo, p, length))
			print_unknown_data(ndo, p, "\n\t", caplen);
		break;

	case NLPID_ESIS:
		esis_print(ndo, p, length);
		return;

	case NLPID_ISIS:
		if (!isis_print(ndo, p, length))
			print_unknown_data(ndo, p, "\n\t", caplen);
		break;

	case NLPID_NULLNS:
		ND_PRINT((ndo, "%slength: %u", ndo->ndo_eflag ? "" : ", ", length));
		break;

	case NLPID_Q933:
		q933_print(ndo, p + 1, length - 1);
		break;

	case NLPID_IP:
		ip_print(ndo, p + 1, length - 1);
		break;

	case NLPID_IP6:
		ip6_print(ndo, p + 1, length - 1);
		break;

	case NLPID_PPP:
		ppp_print(ndo, p + 1, length - 1);
		break;

	default:
		if (!ndo->ndo_eflag)
			ND_PRINT((ndo, "OSI NLPID 0x%02x unknown", *p));
		ND_PRINT((ndo, "%slength: %u", ndo->ndo_eflag ? "" : ", ", length));
		if (caplen > 1)
			print_unknown_data(ndo, p, "\n\t", caplen);
		break;
	}
}
/* ==================================================================
 * end of verbatim isoclns_print
 * ================================================================== */

/*
 * Safe no-op stand-ins for handle_ppp()'s and isoclns_print()'s real
 * callees (see the big header comment for the full rationale + the
 * DCE gotcha). Every one folds its own arguments into a shared
 * `volatile` global sink so its call site has a real, argument-value-
 * dependent observable effect -- this is what forces the compiler to
 * actually evaluate the `switch(*p)`/`switch(proto)` selector reads
 * (crash-causing one included) at runtime instead of proving the whole
 * dispatch dead and eliminating it.
 */
static volatile unsigned long g_directcall_sink;

static void __attribute__((noinline))
handle_ctrl_proto(netdissect_options *ndo, u_int proto, const u_char *pptr, int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)proto
	                    ^ (unsigned long)(uintptr_t)pptr ^ (unsigned long)(long)length;
}

static void __attribute__((noinline))
handle_mlppp(netdissect_options *ndo, const u_char *p, int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)p ^ (unsigned long)(long)length;
}

static void __attribute__((noinline))
handle_chap(netdissect_options *ndo, const u_char *p, int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)p ^ (unsigned long)(long)length ^ 1;
}

static void __attribute__((noinline))
handle_pap(netdissect_options *ndo, const u_char *p, int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)p ^ (unsigned long)(long)length ^ 2;
}

static void __attribute__((noinline))
handle_bap(netdissect_options *ndo, const u_char *p, int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)p ^ (unsigned long)(long)length ^ 3;
}

static void __attribute__((noinline))
ppp_hdlc(netdissect_options *ndo, const u_char *p, int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)p ^ (unsigned long)(long)length ^ 4;
}

void __attribute__((noinline))
ip_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)bp ^ (unsigned long)length ^ 5;
}

void __attribute__((noinline))
ip6_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)bp ^ (unsigned long)length ^ 6;
}

void __attribute__((noinline))
ipx_print(netdissect_options *ndo, const u_char *p, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)p ^ (unsigned long)length ^ 7;
}

void __attribute__((noinline))
mpls_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)bp ^ (unsigned long)length ^ 8;
}

int __attribute__((noinline))
print_unknown_data(netdissect_options *ndo, const u_char *cp, const char *ident, int len)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)cp
	                    ^ (unsigned long)(uintptr_t)ident ^ (unsigned long)(long)len ^ 9;
	return 1;
}

static int __attribute__((noinline))
clnp_print(netdissect_options *ndo, const uint8_t *pptr, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)pptr ^ (unsigned long)length ^ 10;
	return (int)(g_directcall_sink & 1); /* varies at runtime; keeps the caller's `if (!clnp_print(...))` branch live too */
}

static void __attribute__((noinline))
esis_print(netdissect_options *ndo, const uint8_t *pptr, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)pptr ^ (unsigned long)length ^ 11;
}

static int __attribute__((noinline))
isis_print(netdissect_options *ndo, const uint8_t *p, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)p ^ (unsigned long)length ^ 12;
	return (int)(g_directcall_sink & 1);
}

void __attribute__((noinline))
q933_print(netdissect_options *ndo, const u_char *p, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)p ^ (unsigned long)length ^ 13;
}

u_int __attribute__((noinline))
ppp_print(netdissect_options *ndo, const u_char *p, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)p ^ (unsigned long)length ^ 14;
	return 0;
}

/* util-print.c, verbatim (small, self-contained, genuinely cheap --
 * handle_ppp's `default:` case calls tok2str() UNCONDITIONALLY, not
 * behind ndo_eflag, so unlike the other callees above it is implemented
 * for real rather than stubbed). */
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

/* no-op output function (per the direct-call harness recipe), with a
 * sink write so ND_PRINT() call sites (e.g. isoclns_print's
 * NLPID_NULLNS/default cases, which call NOTHING else) stay observable
 * too. */
static int
null_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	g_directcall_sink ^= (unsigned long)(uintptr_t)fmt ^ 15;
	return 0;
}

/* Compiler-escape barrier (harness-only helper, does NOT touch either
 * target function): forces the compiler to assume `p` may be read by
 * unknown code, so it cannot conclude the heap buffer is otherwise
 * unobserved and fold away accesses that depend on its contents/extent. */
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
	u_char *raw;
	u_char sel;
	netdissect_options ndo_storage;
	netdissect_options *ndo = &ndo_storage;
	const u_char *p;
	int length;
	u_int proto;

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

	/* attacker data MUST live on the heap so ASAN instruments it; the
	 * TRIGGER scenario below needs `raw+n` (one byte past the
	 * allocation) to be a genuine ASAN redzone, so allocate EXACTLY
	 * the input size -- no padding -- even for n==0 (malloc(0) is
	 * still ASAN-instrumented: any deref of it is an overflow). */
	raw = (u_char *)malloc((size_t)fsz);
	if (fsz > 0 && !raw) { fclose(f); return 1; }

	n = fsz > 0 ? fread(raw, 1, (size_t)fsz, f) : 0;
	fclose(f);

	memset(&ndo_storage, 0, sizeof(ndo_storage));
	ndo->ndo_eflag = 0;		/* matches the frozen baseline's repro flags: -v -nn (no -e) */
	ndo->ndo_printf = null_printf;
	ndo->ndo_snapend = raw + n;	/* real capture-buffer model: buffer length IS the snapshot length */

	sel = (n >= 1) ? raw[0] : 0;

	if (sel == 1 && n >= 3) {
		/* SAFE: in-bounds PPP_OSI. p/length stay genuinely inside
		 * the [raw, raw+n) allocation; raw[1] (the NLPID byte
		 * isoclns_print's own switch reads) varies across the
		 * generated corpus to exercise each of its cases safely. */
		proto = PPP_OSI;
		p = raw + 1;
		length = (int)(n - 1);
	} else if (sel == 2 && n >= 3) {
		/* SAFE: non-OSI proto, taken verbatim from the input
		 * (generator picks values that are either one of
		 * handle_ppp's other recognized constants, or deliberately
		 * unrecognized to hit `default:` -- never the 0x7e00 HDLC-
		 * escape pattern, which is unrelated to this bug). */
		proto = ((u_int)raw[1] << 8) | (u_int)raw[2];
		p = raw + 3;
		length = (int)(n - 3);
	} else {
		/* TRIGGER (sel==0, or a malformed/too-short sel1/sel2 file
		 * falls back here too): p = raw+n is one byte past the END
		 * of the allocation -- 0 valid bytes remain there -- while
		 * length/caplen (64, fixed, >1) are totally disconnected
		 * from that fact, exactly reproducing CVE-2017-12897:
		 * isoclns_print's `caplen<=1` guard is bypassed, then its
		 * very next statement `switch (*p)` reads one byte past
		 * the allocation. */
		proto = PPP_OSI;
		p = raw + n;
		length = 64;
	}

	vb_escape(raw);
	handle_ppp(ndo, proto, p, length);
	vb_escape(raw);

	free(raw);
	return 0;
}
