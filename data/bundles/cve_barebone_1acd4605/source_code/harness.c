/*
 * cve_1acd4605 direct-call crash harness for tcpdump's chdlc_print()
 * (CVE-2017-13687 / CWE-125 heap-buffer-overflow READ on the Cisco HDLC
 *  "ISO fudge byte" `*(p+1)` check, performed with NO length/snapend
 *  check at all).
 *
 * This file assembles:
 *   1. Minimal-but-faithful standalone re-declarations of the real
 *      tcpdump types/macros the function needs (struct tok,
 *      netdissect_options trimmed to the fields chdlc_print actually
 *      dereferences, ND_PRINT, the real EXTRACT_16BITS from extract.h --
 *      chdlc_print's own EXTRACT_16BITS(&p[2]) call is the OTHER
 *      unchecked read in this function, alongside the *(p+1) fudge-byte
 *      read that is the CVE's exact root cause).
 *   2. Minimal real-signature stand-ins for external symbols the
 *      (unmodified) function references but that live in other
 *      tcpdump source files not needed to exercise THIS bug: tok2str/
 *      tok2strbuf (copied verbatim from util-print.c -- cheap, and
 *      genuinely reachable when ndo_eflag is set), chdlc_cast_values
 *      (verbatim from print-chdlc.c -- the real 3-entry table),
 *      ethertype_values (stubbed to its real name + terminator only,
 *      per the ddiv directcall precedent: full contents live in
 *      print-ether.c, irrelevant to this bug), and no-op real-signature
 *      stand-ins for chdlc_slarp_print/ip_print/ip6_print/mpls_print/
 *      isoclns_print -- none of which contain the fault (it is entirely
 *      inside chdlc_print itself, before any of them would be called),
 *      so they are safe no-ops rather than full reimplementations.
 *   3. VERBATIM real tcpdump source: dataset/cve_1acd4605/target/
 *      original_function.c byte-for-byte (chdlc_print itself,
 *      UNCHANGED -- logic/names/signature untouched).
 *   4. main(): reads argv[1] (a file path) into a HEAP buffer (required
 *      so ASAN instruments it), sets ndo_snapend to the buffer's real
 *      end (no padding -- mirrors the real fuzz harness where the
 *      captured-packet buffer's length IS the snapshot length), and
 *      calls chdlc_print() directly, exactly once, with length == the
 *      buffer size (mirrors chdlc_if_print() passing h->len == h->caplen
 *      for a non-truncated capture).
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
 * netdissect_options, netdissect.h -- trimmed to the real fields
 * chdlc_print() actually dereferences: ndo_eflag, ndo_snapend,
 * ndo_printf. Real names/types; the dozens of other ndo_*flag knobs /
 * ndo_error/ndo_warning/ndo_default_print/ndo_if_printer/... are
 * omitted rather than fabricated, since they are never touched by this
 * function and would drag in unrelated typedefs.
 */
typedef struct netdissect_options netdissect_options;

struct netdissect_options {
	int ndo_eflag;			/* print link-layer header */
	const u_char *ndo_snapend;	/* end of captured packet data */
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---- netdissect.h macro, verbatim ---- */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/*
 * extract.h, verbatim -- the "processor natively handles unaligned
 * loads" branch (no LBL_ALIGN), which is what a real x86_64 build
 * compiles. EXTRACT_16BITS(&p[2]) is chdlc_print's OWN unchecked read
 * of the proto field -- the same "no bounds check at all" pattern as
 * the *(p+1) fudge-byte read that is this CVE's documented root cause.
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

/* ---- chdlc.h, verbatim (the macros chdlc_print() and chdlc_cast_values
 * need; CHDLC_TYPE_CDP is unused -- its case is #if 0'd out in the real
 * function body) ---- */
#define CHDLC_HDRLEN 		4
#define CHDLC_UNICAST		0x0f
#define CHDLC_BCAST		0x8f
#define CHDLC_TYPE_SLARP	0x8035

/* ---- ethertype.h, verbatim values (the switch cases chdlc_print()
 * dispatches on) ---- */
#define ETHERTYPE_IP		0x0800
#define ETHERTYPE_IPV6		0x86dd
#define ETHERTYPE_MPLS		0x8847
#define ETHERTYPE_MPLS_MULTI	0x8848
#define ETHERTYPE_ISO           0xfefe  /* nonstandard - used in Cisco HDLC encapsulation */

/* print-chdlc.c, verbatim (the real 3-entry table) */
static const struct tok chdlc_cast_values[] = {
    { CHDLC_UNICAST, "unicast" },
    { CHDLC_BCAST, "bcast" },
    { 0, NULL}
};

/*
 * ethertype_values (print-ether.c): real symbol name required for
 * linkage (chdlc_print()'s ndo_eflag branch references it), stubbed to
 * just its real terminator entry -- its full contents (100+ entries)
 * live in a file outside this bug's call graph and this harness never
 * sets ndo_eflag, so the lookup is never even exercised at runtime.
 */
const struct tok ethertype_values[] = { { 0, NULL } };

/* util-print.c, verbatim */
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

/*
 * Real prototypes chdlc_print() references (print-chdlc.c's own
 * forward decl + netdissect.h's extern decls). Definitions (safe
 * no-ops) follow the target function -- none of these contain the
 * fault, which is entirely inside chdlc_print() itself, so full
 * reimplementations would add unrelated code without adding coverage
 * of THIS bug.
 */
static void chdlc_slarp_print(netdissect_options *, const u_char *, u_int);
extern void ip_print(netdissect_options *, const u_char *, u_int);
extern void ip6_print(netdissect_options *, const u_char *, u_int);
extern void isoclns_print(netdissect_options *, const u_char *, u_int, u_int);
extern void mpls_print(netdissect_options *, const u_char *, u_int);

/* ==================================================================
 * VERBATIM real tcpdump source begins here:
 *   dataset/cve_1acd4605/target/original_function.c byte-for-byte
 *   (chdlc_print itself, UNCHANGED).
 * ================================================================== */
u_int
chdlc_print(netdissect_options *ndo, register const u_char *p, u_int length)
{
	u_int proto;

	proto = EXTRACT_16BITS(&p[2]);
	if (ndo->ndo_eflag) {
                ND_PRINT((ndo, "%s, ethertype %s (0x%04x), length %u: ",
                       tok2str(chdlc_cast_values, "0x%02x", p[0]),
                       tok2str(ethertype_values, "Unknown", proto),
                       proto,
                       length));
	}

	length -= CHDLC_HDRLEN;
	p += CHDLC_HDRLEN;

	switch (proto) {
	case ETHERTYPE_IP:
		ip_print(ndo, p, length);
		break;
	case ETHERTYPE_IPV6:
		ip6_print(ndo, p, length);
		break;
	case CHDLC_TYPE_SLARP:
		chdlc_slarp_print(ndo, p, length);
		break;
#if 0
	case CHDLC_TYPE_CDP:
		chdlc_cdp_print(p, length);
		break;
#endif
        case ETHERTYPE_MPLS:
        case ETHERTYPE_MPLS_MULTI:
                mpls_print(ndo, p, length);
		break;
        case ETHERTYPE_ISO:
                /* is the fudge byte set ? lets verify by spotting ISO headers */
                if (*(p+1) == 0x81 ||
                    *(p+1) == 0x82 ||
                    *(p+1) == 0x83)
                    isoclns_print(ndo, p + 1, length - 1, ndo->ndo_snapend - p - 1);
                else
                    isoclns_print(ndo, p, length, ndo->ndo_snapend - p);
                break;
	default:
                if (!ndo->ndo_eflag)
                        ND_PRINT((ndo, "unknown CHDLC protocol (0x%04x)", proto));
                break;
	}

	return (CHDLC_HDRLEN);
}
/* ==================================================================
 * end of verbatim tcpdump source
 * ================================================================== */

/*
 * Safe no-op stand-ins for chdlc_print()'s real callees. None of them
 * contain this CVE's fault (the *(p+1) read that crashes happens in
 * the switch's case-selector expression itself, BEFORE isoclns_print()
 * is ever reached), so they only need to exist with the real signature
 * for linkage + never dereference p (so they can never introduce a
 * fake crash unrelated to chdlc_print()).
 *
 * IMPORTANT: a stub that is a pure no-op is PROVABLY side-effect-free
 * to the optimizer, which at -O1 let clang conclude that the
 * ETHERTYPE_ISO branch's outcome (and therefore the *(p+1) fudge-byte
 * read that selects it) was unobservable and dead-code-eliminate the
 * whole thing -- confirmed live: the exact-original 4-byte PoC
 * `0f 00 fe fe` produced RC=0 (no crash) until this fix. Folding each
 * stub's (pointer-only, never-dereferenced) arguments into a `volatile`
 * global gives them a real, argument-value-dependent side effect the
 * optimizer cannot prove away, which forces the branch -- and the
 * *(p+1) read that decides it -- to actually execute at runtime.
 */
static volatile unsigned long g_directcall_sink;

static void __attribute__((noinline))
chdlc_slarp_print(netdissect_options *ndo, const u_char *cp, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)cp ^ (unsigned long)length;
}

void __attribute__((noinline))
ip_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)bp ^ (unsigned long)length;
}

void __attribute__((noinline))
ip6_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)bp ^ (unsigned long)length;
}

void __attribute__((noinline))
mpls_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)bp ^ (unsigned long)length;
}

void __attribute__((noinline))
isoclns_print(netdissect_options *ndo, const u_char *p, u_int length, u_int caplen)
{
	g_directcall_sink ^= (unsigned long)(uintptr_t)ndo ^ (unsigned long)(uintptr_t)p
	                    ^ (unsigned long)length ^ (unsigned long)caplen;
}

/* no-op output function, per the direct-call harness recipe */
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

	/* attacker data MUST live on the heap so ASAN instruments it;
	 * allocate the EXACT captured size (no padding) so a read past
	 * the real packet bytes is a genuine heap-buffer-overflow, same
	 * as the real fuzz harness where the captured-packet buffer's
	 * length IS the snapshot length. */
	buf = (u_char *)malloc((size_t)fsz);
	if (fsz > 0 && !buf) { fclose(f); return 1; }

	n = fsz > 0 ? fread(buf, 1, (size_t)fsz, f) : 0;
	fclose(f);

	memset(&ndo_storage, 0, sizeof(ndo_storage));
	ndo->ndo_eflag = 0;		/* matches the real repro command: tcpdump -v -nn -r (no -e) */
	ndo->ndo_printf = null_printf;
	ndo->ndo_snapend = buf + n;

	(void)chdlc_print(ndo, buf, (u_int)n);

	free(buf);
	return 0;
}
