/*
 * Direct-call crash harness for CVE-2017-13002 (tcpdump, aodv_extension).
 *
 * Upstream bug: print-aodv.c:aodv_extension() reads `ep->type` in the very
 * first statement of the function body -- `switch (ep->type) {` -- with NO
 * bounds check whatsoever before it. Every other read in this function
 * (ND_TCHECK(*ah) for the AODV_EXT_HELLO branch) is guarded, but the switch
 * discriminant itself is not: `ep` is a pointer the CALLER computed from a
 * claimed/declared length (aodv_rreq/aodv_rrep do
 * `aodv_extension(ndo, (const struct aodv_ext *)(dat + sizeof(*ap)), i)`
 * where `i = length - sizeof(*ap)`, `length` being an AODV-header-declared
 * size, not necessarily <= the bytes actually captured/allocated). If the
 * declared length overstates the real buffer, `ep` lands past the end of
 * the allocation and `ep->type` is an out-of-bounds READ.
 *
 * This is the EXACT baseline crash: dedup_token
 * "aodv_extension--aodv_rrep--aodv_print",
 * "AddressSanitizer: heap-buffer-overflow /work/./print-aodv.c:181:14 in
 * aodv_extension" (line 181 relative to the frozen bundle == the `switch
 * (ep->type) {` line), access READ = CWE-125.
 *
 * aodv_extension() is embedded verbatim below (byte-identical to
 * target/original_function.c). The preceding definitions are the REAL
 * preamble of print-aodv.c (struct aodv_ext, struct aodv_hello,
 * AODV_EXT_HELLO, and struct aodv_rrep -- the real caller's header struct,
 * used ONLY in main() below to size the real call-site offset
 * `sizeof(*ap)`, exactly mirroring aodv_rrep()'s
 * `aodv_extension(ndo, (const struct aodv_ext *)(dat + sizeof(*ap)), i)`),
 * plus a minimal-but-real subset of netdissect.h/extract.h: the
 * ND_TCHECK2/ND_TTEST2/ND_PRINT macros, struct netdissect_options (only the
 * two fields aodv_extension touches: ndo_snapend, ndo_printf), and the
 * byte-at-a-time EXTRACT_32BITS macro. No callees need stubbing -- the
 * function's only callee is the ndo_printf function pointer, whose
 * memory-safety is irrelevant (a no-op sink is used).
 *
 * main() reads argv[1] into a HEAP buffer sized to the file length (this is
 * what lets ASAN's redzone catch a read past it), constructs `ep` at the
 * real call-site offset `buf + sizeof(struct aodv_rrep)` (== 20), sets
 * length = n - 20 the same way aodv_rrep() computes `i`, and sets
 * ndo_snapend = buf + n -- the honest end of what was actually allocated
 * (mirroring the real captured-packet bound). Whenever the input file is
 * <= 20 bytes, `ep` (buf+20) lands at or past the end of the allocation --
 * the switch's first read then runs off the buffer, reproducing the bug
 * with NO dependency on the rest of the project (no aodv_rrep/aodv_print,
 * no libpcap, no ip layer). Longer files (>20 bytes with enough trailing
 * data) keep `ep` in-bounds and exercise the function's non-crashing paths
 * (AODV_EXT_HELLO with a real interval read, the TCHECK-guarded truncation
 * path, and the default branch) for the SAFE half of the corpus.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/types.h>   /* u_char, u_int */

/* ---- extract.h (verbatim byte-at-a-time variant) ---- */

#define EXTRACT_32BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 0)) << 24) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 3)) << 0)))

/* ---- netdissect.h (verbatim subset: only fields aodv_extension uses) ---- */

typedef struct netdissect_options netdissect_options;

struct netdissect_options {
	const u_char *ndo_snapend;	/* end of captured/allocated packet */
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TTEST(var) ND_TTEST2(var, sizeof(var))
#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ================= real print-aodv.c preamble, verbatim ================= */

struct aodv_rrep {
	uint8_t		rrep_type;	/* AODV message type (2) */
	uint8_t		rrep_flags;	/* various flags */
	uint8_t		rrep_ps;	/* prefix size */
	uint8_t		rrep_hops;	/* number of hops from o to d */
	uint32_t	rrep_da;	/* destination IPv4 address */
	uint32_t	rrep_ds;	/* destination sequence number */
	uint32_t	rrep_oa;	/* originator IPv4 address */
	uint32_t	rrep_life;	/* lifetime of this route */
};

struct aodv_ext {
	uint8_t		type;		/* extension type */
	uint8_t		length;		/* extension length */
};

struct aodv_hello {
	struct	aodv_ext	eh;		/* extension header */
	uint8_t			interval[4];	/* expect my next hello in
						 * (n) ms
						 * NOTE: this is not aligned */
};

#define	AODV_EXT_HELLO	1

/* ================= target function, embedded VERBATIM (byte-identical to
 * target/original_function.c) ================= */

static void
aodv_extension(netdissect_options *ndo,
               const struct aodv_ext *ep, u_int length)
{
	const struct aodv_hello *ah;

	switch (ep->type) {
	case AODV_EXT_HELLO:
		ah = (const struct aodv_hello *)(const void *)ep;
		ND_TCHECK(*ah);
		if (length < sizeof(struct aodv_hello))
			goto trunc;
		ND_PRINT((ndo, "\n\text HELLO %ld ms",
		    (unsigned long)EXTRACT_32BITS(&ah->interval)));
		break;

	default:
		ND_PRINT((ndo, "\n\text %u %u", ep->type, ep->length));
		break;
	}
	return;

trunc:
	ND_PRINT((ndo, " [|hello]"));
}

/* ============================= harness main ============================= */

/* Sink for ndo_printf. We don't care about the formatted text (it's
 * discarded like the real tool's -q/quiet output would be), only the
 * memory-safety of the parse -- BUT it must perform a REAL, opaque,
 * externally-visible I/O side effect (an actual vfprintf), not silently
 * ignore its varargs. aodv_extension() is `static` with a single call site
 * and tiny; a no-op sink lets the optimizer prove (after inlining
 * aodv_extension AND devirtualizing/inlining the sink itself, since
 * ndo_printf is provably always this one function) that NO branch of the
 * switch has any observable effect at all, which licenses removing the
 * whole computation -- including the very switch(ep->type) read this
 * harness exists to exercise -- as dead code. A genuine vfprintf() call is
 * a libc I/O side effect the compiler must preserve, which keeps every
 * argument expression (ep->type, ep->length, the EXTRACT_32BITS read) a
 * real, unelidable memory access. (Verified empirically: the no-op sink
 * silently produced RC=0/no crash on every input; this fix reproduces the
 * crash reliably.) */
static int
stub_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	va_start(ap, fmt);
	int r = vfprintf(stderr, fmt, ap);
	va_end(ap);
	return r;
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
	 * input file length -- this is what lets a call-site offset computed
	 * from a declared-but-not-actually-captured length run off the end of
	 * the allocation, matching real ASAN heap-buffer-overflow semantics. */
	unsigned char *buf = (unsigned char *)malloc((size_t)n > 0 ? (size_t)n : 1);
	if (n > 0) {
		if (!buf) { fclose(f); return 1; }
		size_t got = fread(buf, 1, (size_t)n, f);
		fclose(f);
		if (got != (size_t)n) { free(buf); return 1; }
	} else {
		fclose(f);
	}

	netdissect_options ndo_s;
	memset(&ndo_s, 0, sizeof(ndo_s));	/* zero-init unused fields */
	ndo_s.ndo_printf = stub_printf;	/* stub output function pointer */
	ndo_s.ndo_snapend = buf + n;		/* honest end of the captured/allocated packet */

	/* Mirror the REAL call site in aodv_rrep():
	 *     i = length - sizeof(*ap);
	 *     if (i >= sizeof(struct aodv_ext))
	 *         aodv_extension(ndo, (const struct aodv_ext *)(dat + sizeof(*ap)), i);
	 * Here `dat` == buf and the outer "length" == n (the whole file IS the
	 * claimed AODV RREP message). `ep` therefore lands at buf +
	 * sizeof(struct aodv_rrep) (== 20) exactly as it would in the real
	 * decode -- and if the file is <= 20 bytes, that offset is past the
	 * end of what was actually allocated, exactly the real bug (a claimed
	 * length exceeding the actually captured/allocated bytes). */
	const struct aodv_ext *ep = (const struct aodv_ext *)(buf + sizeof(struct aodv_rrep));
	u_int length = (n > (long)sizeof(struct aodv_rrep))
	    ? (u_int)(n - (long)sizeof(struct aodv_rrep)) : 0;

	aodv_extension(&ndo_s, ep, length);

	free(buf);
	return 0;
}
