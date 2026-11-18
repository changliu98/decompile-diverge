/*
 * Direct-call crash harness for ddiv bundle cve_ac93a3b1
 * (CVE-2017-13040, tcpdump print-mptcp.c: mp_dss_print() / mp_dss_len()).
 *
 * Root cause (confirmed against the real upstream fix commit
 * 4c3aee4bb0294c232d56b6d34e9eeb74f630fe8c, "CVE-2017-13040/MPTCP: Clean up
 * printing DSS suboption."): in the pre-fix mp_dss_print() embedded
 * verbatim below,
 *
 *     const struct mp_dss *mdss = (const struct mp_dss *) opt;
 *     if ((opt_len != mp_dss_len(mdss, 1) &&
 *          opt_len != mp_dss_len(mdss, 0)) || flags & TH_SYN)
 *             return 0;
 *
 * calls mp_dss_len(mdss, 1) UNCONDITIONALLY as the very first thing the
 * function does (it is the left operand of the top-level `&&`, itself the
 * left operand of `||`, so C's evaluation order calls it before opt_len or
 * flags is even consulted). mp_dss_len() (also embedded verbatim below)
 * immediately dereferences `m->flags`, i.e. byte offset 3 of the `struct
 * mp_dss { uint8_t kind, len, sub, flags; }` overlaid on `opt` -- with NO
 * prior check that at least 4 bytes of option data are actually present.
 * If the caller's buffer/snapshot has fewer than 4 bytes, this is a
 * heap-buffer-overflow READ (CWE-125) inside mp_dss_len, called from
 * mp_dss_print, exactly matching the frozen baseline dedup_token
 * "mp_dss_len--mp_dss_print--mptcp_print" and summary "AddressSanitizer:
 * heap-buffer-overflow /work/./print-mptcp.c:244:16 in mp_dss_len"
 * (case.json; line 244 is `if (m->flags & MP_DSS_A) {`).
 *
 * The upstream fix replaces this whole idiom with an explicit
 * `if (opt_len < 4) return 0;` BEFORE any struct field is read, plus
 * per-field `opt_len` accounting for every subsequent EXTRACT_*BITS() call
 * later in the function (which, in the original code, has NO bounds
 * checking at all beyond the single opt_len/mp_dss_len equality test at
 * entry -- it fully trusts the caller-supplied opt_len to reflect how much
 * data is actually present).
 *
 * This harness calls mp_dss_print() DIRECTLY (exactly as mptcp_print()
 * does via `mptcp_options[subtype].print(ndo, cp, len, flags)`, dss being
 * one of the mptcp_options[] entries) with `opt` pointing at a HEAP buffer
 * malloc'd to exactly the input file's length, and `opt_len` set to that
 * same length -- mirroring the real invariant that the outer TCP
 * option-parsing loop only ever hands mp_dss_print() an `opt_len` it has
 * itself validated as the number of bytes actually captured/present (the
 * bug is precisely that mp_dss_len() does not re-derive its own minimum
 * 4-byte requirement from that guarantee before reading offset 3). `flags`
 * (the TCP header flags byte, unrelated to struct mp_dss's own `flags`
 * field) is fixed to 0 (no TH_SYN) throughout: the crash fires during the
 * unconditional first call to mp_dss_len() before `flags` is ever
 * consulted, and 0 lets every SAFE corpus input reach and safely exercise
 * the fully bounds-consistent deep-traversal branches of the function.
 *
 * Supporting definitions below (struct mp_dss + MP_DSS_* flag bits,
 * netdissect_options trimmed to the one field the function touches
 * (ndo_printf, via ND_PRINT), TH_SYN from tcp.h, EXTRACT_16/32/64BITS --
 * the "processor natively handles unaligned loads" variant, which is what
 * this project's extract.h compiles to on x86_64/LBL_ALIGN-undefined) are
 * copied verbatim/reduced from dataset/cve_ac93a3b1/source_code/
 * {netdissect.h,extract.h,tcp.h,print-mptcp.c}.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <inttypes.h>
#include <arpa/inet.h>

/* ---- real BSD-ish typedefs used throughout tcpdump headers ---- */
typedef unsigned char  u_char;
typedef unsigned int   u_int;

/*
 * netdissect_options, netdissect.h -- trimmed to the real field
 * mp_dss_print()/mp_dss_len() actually dereference: ndo_printf (via the
 * ND_PRINT macro). Real name/type; the many other ndo_*flag knobs, the
 * snapend pointer (unused by this function -- it has no ND_TCHECK/TTEST
 * calls at all, see the root-cause note above) and function pointers are
 * omitted rather than fabricated, since they are never touched here.
 */
typedef struct netdissect_options netdissect_options;

struct netdissect_options {
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---- netdissect.h macro, verbatim ---- */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- tcp.h, verbatim (only the bit mp_dss_print() references) ---- */
#define TH_SYN	   0x02

/*
 * extract.h, verbatim -- the "processor natively handles unaligned loads"
 * branch (LBL_ALIGN undefined; this project's config.h.in shows LBL_ALIGN
 * is only #defined for specific alignment-requiring targets, not compiled
 * for on x86_64).
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

static inline uint64_t UNALIGNED_OK
EXTRACT_64BITS(const void *p)
{
	return ((uint64_t)(((uint64_t)ntohl(*((const uint32_t *)(p) + 0))) << 32 |
		((uint64_t)ntohl(*((const uint32_t *)(p) + 1))) << 0));
}

/*
 * print-mptcp.c, verbatim -- struct mp_dss and its MP_DSS_* flag bits,
 * exactly as declared (lines 103-114 of dataset/cve_ac93a3b1/source_code/
 * print-mptcp.c).
 */
struct mp_dss {
	uint8_t        kind;
	uint8_t        len;
	uint8_t        sub;
	uint8_t        flags;
};

#define MP_DSS_F                        0x10
#define MP_DSS_m                        0x08
#define MP_DSS_M                        0x04
#define MP_DSS_a                        0x02
#define MP_DSS_A                        0x01

/* ==================================================================
 * REAL CALLEE -- embedded VERBATIM from dataset/cve_ac93a3b1/source_code/
 * print-mptcp.c lines 239-265. This is the function whose read of
 * `m->flags` (line 244) is the actual faulting instruction -- the top
 * frame of the baseline's dedup_token "mp_dss_len--mp_dss_print--
 * mptcp_print".
 * ================================================================== */
static u_int mp_dss_len(const  struct mp_dss *m, int csum)
{
        u_int len;

        len = 4;
        if (m->flags & MP_DSS_A) {
                /* Ack present - 4 or 8 octets */
                len += (m->flags & MP_DSS_a) ? 8 : 4;
        }
        if (m->flags & MP_DSS_M) {
                /*
                 * Data Sequence Number (DSN), Subflow Sequence Number (SSN),
                 * Data-Level Length present, and Checksum possibly present.
                 * All but the Checksum are 10 bytes if the m flag is
                 * clear (4-byte DSN) and 14 bytes if the m flag is set
                 * (8-byte DSN).
                 */
                len += (m->flags & MP_DSS_m) ? 14 : 10;

                /*
                 * The Checksum is present only if negotiated.
                 */
                if (csum)
                        len += 2;
	}
	return len;
}
/* ================================================================== */

/* ==================================================================
 * TARGET FUNCTION -- embedded VERBATIM from
 * dataset/cve_ac93a3b1/target/original_function.c. Do not modify.
 * ================================================================== */
static int
mp_dss_print(netdissect_options *ndo,
             const u_char *opt, u_int opt_len, u_char flags)
{
        const struct mp_dss *mdss = (const struct mp_dss *) opt;

        if ((opt_len != mp_dss_len(mdss, 1) &&
             opt_len != mp_dss_len(mdss, 0)) || flags & TH_SYN)
                return 0;

        if (mdss->flags & MP_DSS_F)
                ND_PRINT((ndo, " fin"));

        opt += 4;
        if (mdss->flags & MP_DSS_A) {
                ND_PRINT((ndo, " ack "));
                if (mdss->flags & MP_DSS_a) {
                        ND_PRINT((ndo, "%" PRIu64, EXTRACT_64BITS(opt)));
                        opt += 8;
                } else {
                        ND_PRINT((ndo, "%u", EXTRACT_32BITS(opt)));
                        opt += 4;
                }
        }

        if (mdss->flags & MP_DSS_M) {
                ND_PRINT((ndo, " seq "));
                if (mdss->flags & MP_DSS_m) {
                        ND_PRINT((ndo, "%" PRIu64, EXTRACT_64BITS(opt)));
                        opt += 8;
                } else {
                        ND_PRINT((ndo, "%u", EXTRACT_32BITS(opt)));
                        opt += 4;
                }
                ND_PRINT((ndo, " subseq %u", EXTRACT_32BITS(opt)));
                opt += 4;
                ND_PRINT((ndo, " len %u", EXTRACT_16BITS(opt)));
                opt += 2;

                if (opt_len == mp_dss_len(mdss, 1))
                        ND_PRINT((ndo, " csum 0x%x", EXTRACT_16BITS(opt)));
        }
        return 1;
}
/* ================================================================== */

/*
 * Harness-authored: the ndo_printf output function pointer, stubbed to
 * discard its formatted output (real tcpdump wires this to a
 * vfprintf(stdout, ...) wrapper; we format into a scratch buffer and drop
 * it instead of writing to stdout). It must actually CONSUME the varargs
 * via vsnprintf() -- an opaque libc call -- rather than silently ignore
 * them: with a truly no-op body, clang -O1 can prove some ND_PRINT
 * arguments are dead and elide the load entirely (this exact gotcha is
 * documented in the sibling cve_42e8b6f8/cve_299f4da7 harnesses for the
 * same project/macro).
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
	 * and catches mp_dss_len()'s `m->flags` (offset 3) read running past
	 * it whenever the file is shorter than 4 bytes. malloc(0) is avoided
	 * (glibc still returns a valid unique pointer for it, but keep
	 * semantics obvious -- 1-byte-minimum files are enough to reach
	 * every OOB size we need). */
	size_t alloc_sz = (sz > 0) ? (size_t)sz : 1;
	u_char *buf = (u_char *)malloc(alloc_sz);
	if (!buf) { fclose(f); return 1; }

	size_t n = fread(buf, 1, (size_t)sz, f);
	fclose(f);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_printf = noop_printf;

	/* Direct call: exactly how mptcp_print() invokes it via
	 * `mptcp_options[subtype].print(ndo, cp, len, flags)` -- `opt` points
	 * at the option bytes and `opt_len` is the caller-validated length of
	 * that data, which we set to the true size of the heap allocation
	 * (n): this is the realistic invariant the bug depends on (the caller
	 * guarantees opt_len bytes are present, but mp_dss_len() reads a
	 * 4th byte regardless of whether opt_len said fewer than 4 were
	 * there). `flags` (TCP header flags, not struct mp_dss's own field)
	 * is fixed at 0 -- TH_SYN is never involved in the crash path (it is
	 * only consulted, if at all, AFTER the always-executed first call to
	 * mp_dss_len() has already returned or crashed). */
	(void)mp_dss_print(&ndo, buf, (u_int)n, (u_char)0);

	free(buf);
	return 0;
}
