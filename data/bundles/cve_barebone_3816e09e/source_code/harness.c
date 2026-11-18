/*
 * Direct-call crash harness for ddiv bundle cve_3816e09e
 * (CVE-2017-13023, tcpdump print-mobility.c: mobility_opt_print()).
 *
 * Root cause: in the pre-fix mobility_opt_print() embedded verbatim below,
 * each mobility-header option is bounds-checked with a SINGLE-byte probe
 *
 *     if (i + 1 < len) { ND_TCHECK(bp[i + 1]); optlen = bp[i + 1] + 2; }
 *     ...
 *     if (i + optlen > len) goto trunc;
 *     ND_TCHECK(bp[i + optlen]);
 *
 * -- ND_TCHECK(bp[i + optlen]) only proves that the ONE byte immediately
 * after the option (offset i+optlen) was captured; it does not prove that
 * every byte the option's own per-type case is about to read was captured.
 * When the attacker sets the option's own length byte (bp[i+1]) to 0, an
 * IP6MOPT_REFRESH (2) or IP6MOPT_NONCEID (4) option gets optlen == 2, so
 * ND_TCHECK(bp[i+optlen]) == ND_TCHECK(bp[i+2]) validates only offset i+2.
 * But the REFRESH/NONCEID case then does
 *     EXTRACT_16BITS(&bp[i+2])
 * which loads BOTH bp[i+2] and bp[i+3] -- if the actual captured/allocated
 * buffer ends exactly at offset i+2 (i.e. its size is i+3), bp[i+3] is one
 * byte past the allocation -> heap-buffer-overflow READ (CWE-125), landing
 * in EXTRACT_16BITS, exactly matching the frozen baseline dedup_token
 * "EXTRACT_16BITS--mobility_opt_print--mobility_print" and summary
 * "AddressSanitizer: heap-buffer-overflow /work/./extract.h:184:20 in
 * EXTRACT_16BITS" (case.json). The `len` parameter mobility_opt_print()
 * receives is the mobility header's own DECLARED remaining length
 * (mhlen - hlen in the real caller mobility_print(), derived from the
 * attacker-controlled ip6m_len header byte, up to (255+1)*8 = 2048) --
 * completely decoupled from ndo_snapend, the true end of what was actually
 * captured. That decoupling (declared length >> captured length) is the
 * real-world precondition this bug depends on, reproduced below with a
 * harness-fixed large FIXED_LEN standing in for the declared length.
 *
 * This harness calls mobility_opt_print() DIRECTLY (as mobility_print()
 * does: `mobility_opt_print(ndo, &bp[hlen], mhlen - hlen)`), with `bp`
 * pointing at a HEAP buffer malloc'd to exactly the input file's length
 * and ndo_snapend set to that buffer's true end (no padding -- mirrors the
 * real capture-buffer / snapshot-length relationship).
 *
 * Supporting definitions below (netdissect_options trimmed to the two
 * fields the function touches, ND_TTEST2/ND_TCHECK2/ND_TCHECK/ND_PRINT,
 * EXTRACT_16BITS in the "processor natively handles unaligned loads"
 * variant, and the print-mobility.c IP6MOPT_* option constants) are copied
 * verbatim/reduced from dataset/cve_3816e09e/source_code/{netdissect.h,
 * extract.h,print-mobility.c}. ip6addr_string/getname6 (addrtoname.h /
 * addrtoname.c) is stubbed rather than embedded verbatim: the fault is NOT
 * inside it (no corpus input here ever takes the IP6MOPT_ALTCOA branch
 * that calls it), and its real implementation drags in a hostname-cache
 * dependency tree unrelated to this bug; it is provided only so the
 * verbatim switch statement that references it still links.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <arpa/inet.h>

/* ---- BSD-ish typedef used throughout tcpdump headers ---- */
typedef unsigned char u_char;

/*
 * netdissect_options, netdissect.h -- trimmed to the real fields
 * mobility_opt_print() actually dereferences: ndo_snapend (via the
 * ND_TCHECK / ND_TTEST family of macros) and ndo_printf (via ND_PRINT).
 */
typedef struct netdissect_options netdissect_options;

struct netdissect_options {
	const u_char *ndo_snapend;	/* end of captured/allocated packet */
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
 * extract.h, verbatim -- the "processor natively handles unaligned loads"
 * branch (LBL_ALIGN undefined on x86_64), the literal faulting frame in
 * case.json's baseline dedup_token / summary ("extract.h:184:20 in
 * EXTRACT_16BITS" -- matches this project's real extract.h line 184).
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

/* addrtoname.h, verbatim macro */
#define ip6addr_string(ndo, p) getname6(ndo, (const u_char *)(p))

/* Minimal stub -- see file header comment. Never exercised by this
 * harness's corpus (no input ever hits the IP6MOPT_ALTCOA case). */
static const char *
getname6(netdissect_options *ndo, const u_char *p)
{
	(void)ndo; (void)p;
	return "::";
}

/* print-mobility.c, Mobility Header Options constants -- verbatim */
#define IP6MOPT_MINLEN		2
#define IP6MOPT_PAD1          0x0	/* Pad1 */
#define IP6MOPT_PADN          0x1	/* PadN */
#define IP6MOPT_REFRESH	      0x2	/* Binding Refresh Advice */
#define IP6MOPT_REFRESH_MINLEN  4
#define IP6MOPT_ALTCOA        0x3	/* Alternate Care-of Address */
#define IP6MOPT_ALTCOA_MINLEN  18
#define IP6MOPT_NONCEID       0x4	/* Nonce Indices */
#define IP6MOPT_NONCEID_MINLEN  6
#define IP6MOPT_AUTH          0x5	/* Binding Authorization Data */
#define IP6MOPT_AUTH_MINLEN    12

/* ==================================================================
 * TARGET FUNCTION -- embedded VERBATIM from
 * dataset/cve_3816e09e/target/original_function.c. Do not modify.
 * ================================================================== */
static int
mobility_opt_print(netdissect_options *ndo,
                   const u_char *bp, const unsigned len)
{
	unsigned i, optlen;

	for (i = 0; i < len; i += optlen) {
		ND_TCHECK(bp[i]);
		if (bp[i] == IP6MOPT_PAD1)
			optlen = 1;
		else {
			if (i + 1 < len) {
				ND_TCHECK(bp[i + 1]);
				optlen = bp[i + 1] + 2;
			}
			else
				goto trunc;
		}
		if (i + optlen > len)
			goto trunc;
		ND_TCHECK(bp[i + optlen]);

		switch (bp[i]) {
		case IP6MOPT_PAD1:
			ND_PRINT((ndo, "(pad1)"));
			break;
		case IP6MOPT_PADN:
			if (len - i < IP6MOPT_MINLEN) {
				ND_PRINT((ndo, "(padn: trunc)"));
				goto trunc;
			}
			ND_PRINT((ndo, "(padn)"));
			break;
		case IP6MOPT_REFRESH:
			if (len - i < IP6MOPT_REFRESH_MINLEN) {
				ND_PRINT((ndo, "(refresh: trunc)"));
				goto trunc;
			}
			/* units of 4 secs */
			ND_PRINT((ndo, "(refresh: %u)",
				EXTRACT_16BITS(&bp[i+2]) << 2));
			break;
		case IP6MOPT_ALTCOA:
			if (len - i < IP6MOPT_ALTCOA_MINLEN) {
				ND_PRINT((ndo, "(altcoa: trunc)"));
				goto trunc;
			}
			ND_PRINT((ndo, "(alt-CoA: %s)", ip6addr_string(ndo, &bp[i+2])));
			break;
		case IP6MOPT_NONCEID:
			if (len - i < IP6MOPT_NONCEID_MINLEN) {
				ND_PRINT((ndo, "(ni: trunc)"));
				goto trunc;
			}
			ND_PRINT((ndo, "(ni: ho=0x%04x co=0x%04x)",
				EXTRACT_16BITS(&bp[i+2]),
				EXTRACT_16BITS(&bp[i+4])));
			break;
		case IP6MOPT_AUTH:
			if (len - i < IP6MOPT_AUTH_MINLEN) {
				ND_PRINT((ndo, "(auth: trunc)"));
				goto trunc;
			}
			ND_PRINT((ndo, "(auth)"));
			break;
		default:
			if (len - i < IP6MOPT_MINLEN) {
				ND_PRINT((ndo, "(sopt_type %u: trunc)", bp[i]));
				goto trunc;
			}
			ND_PRINT((ndo, "(type-0x%02x: len=%u)", bp[i], bp[i + 1]));
			break;
		}
	}
	return 0;

trunc:
	return 1;
}
/* ================================================================== */

/*
 * Harness-authored: the ndo_printf output function pointer, stubbed to
 * discard its formatted output but still actually CONSUME the varargs
 * via vsnprintf() (an opaque libc call) -- with a truly no-op body clang
 * -O1 can prove a printf-only argument like EXTRACT_16BITS(&bp[i+2]) is
 * dead and elide the load entirely, silently optimizing the bug away.
 */
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

/*
 * Fixed "declared remaining mobility-option-area length" the real
 * mobility_print() would compute as `mhlen - hlen` from the packet's own
 * attacker-controlled ip6m_len header byte -- not attacker/ASAN-visible
 * memory, just a scalar bound, decoupled from how many bytes were
 * actually captured (that's what ndo_snapend tracks, set below to the
 * real end of the heap allocation). Large enough that the len-based
 * "trunc" checks in the switch never gate the corpus.
 */
#define FIXED_LEN 65535u

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

	/* HEAP buffer sized exactly to the input file -- required so ASAN's
	 * heap redzone sits immediately after the attacker-controlled bytes
	 * and catches mobility_opt_print()'s EXTRACT_16BITS() 2-byte load
	 * running past it. malloc(0) is avoided (glibc still returns a
	 * valid unique pointer for it, but keep semantics obvious). */
	size_t alloc_sz = (sz > 0) ? (size_t)sz : 1;
	u_char *buf = (u_char *)malloc(alloc_sz);
	if (!buf) { fclose(f); return 1; }

	size_t n = fread(buf, 1, (size_t)sz, f);
	fclose(f);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_printf = noop_printf;
	/* ndo_snapend = the real end of the captured/allocated region --
	 * mirrors the real fuzz harness where the captured-packet buffer
	 * length IS the snapshot length. No padding: this is exactly the
	 * boundary EXTRACT_16BITS(&bp[i+2]) must not cross. */
	ndo.ndo_snapend = buf + n;

	/* Direct call: exactly how mobility_print() invokes
	 * mobility_opt_print() -- `mobility_opt_print(ndo, &bp[hlen], mhlen
	 * - hlen)` -- with bp pointing at the option-area bytes and len the
	 * caller's declared remaining length. */
	(void)mobility_opt_print(&ndo, buf, FIXED_LEN);

	free(buf);
	return 0;
}
