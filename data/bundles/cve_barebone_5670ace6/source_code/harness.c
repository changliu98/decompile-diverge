/* Direct-call crash harness for tcpdump vrrp_print (CVE-2019-15167, CWE-125,
 * print-vrrp.c).
 *
 * Root cause: in the "ndo->ndo_vflag" (-v) block of vrrp_print(), for a VRRPv3
 * packet whose checksum verification fails, the code does:
 *
 *     if (version == 3 && ND_TTEST2(bp[0], len)) {
 *         uint16_t cksum = nextproto4_cksum(ndo, (const struct ip *)bp2, bp,
 *             len, len, IPPROTO_VRRP);
 *         if (cksum)
 *             ND_PRINT((ndo, ", (bad vrrp cksum %x)",
 *                 EXTRACT_16BITS(&bp[6])));
 *     }
 *
 * ND_TTEST2(bp[0], len) only proves that the FIRST `len` bytes starting at bp
 * are captured (i.e. bp+len <= ndo_snapend) -- it says nothing about whether
 * byte offset 6..7 (the fixed VRRP checksum-field offset EXTRACT_16BITS reads)
 * is within that captured region. If the caller passes a `len` smaller than 8
 * (very common: `len` here is the VRRP payload length claimed by the wrapping
 * IP header, not tied to offset 6 in any way) *and* fewer than 8 bytes were
 * actually captured, ND_TTEST2 passes on the short `len` while
 * EXTRACT_16BITS(&bp[6]) reads 2 bytes starting at offset 6, straight past the
 * end of the captured/allocated buffer -> heap-buffer-overflow READ, CWE-125.
 * (The parallel version==2 branch a few lines above already has the missing
 * `ND_TCHECK_16BITS(&bp[6])` guard; the fix commit a152aebfd1114376ba266ed30
 * 416be596ef9d806 ("VRRP: Add a missing bounds check") adds the same guard to
 * the version==3 branch.) This matches the baseline's own crash site exactly:
 * dedup EXTRACT_16BITS--vrrp_print--ip_print_demux, summary "AddressSanitizer:
 * heap-buffer-overflow .../extract.h:184:20 in EXTRACT_16BITS".
 *
 * This harness embeds vrrp_print() VERBATIM (target/original_function.c,
 * byte-for-byte) plus every real type/macro/tok-table it references, taken
 * verbatim from print-vrrp.c / netdissect.h / extract.h / ip.h / ipproto.h in
 * source_code/. vrrp_print has no other in-file callees. Out-of-file callees
 * (tok2str, in_cksum, nextproto4_cksum, ipaddr_string/getname, fn_printn) are
 * given trivial, behaviourally-safe stub bodies with their REAL signatures --
 * none of them is the fault site, and the crafted corpus below is designed so
 * none of them is ever reached with attacker-controlled out-of-bounds data
 * (nextproto4_cksum in particular is deliberately made to always report a
 * "bad" checksum, deterministically, without touching memory -- exactly the
 * `ip_print` volatile-sink pattern used by the icmp_print direct-call harness
 * to defeat -O1 dead-code-elimination of an argument whose only use is inside
 * a stubbed-out callee).
 *
 * main() reads argv[1] into a HEAP buffer malloc'd to EXACTLY the file length
 * (so ASAN's redzone sits immediately past the real "captured packet" data,
 * mirroring tcpdump's own per-packet capture buffer), sets
 * ndo.ndo_snapend = data + len (== "this many bytes were captured"),
 * ndo.ndo_vflag = 1 (-v, required to reach the checksum block), and calls
 * vrrp_print(&ndo, data, (u_int)len, data, 64) directly, exactly once, with
 * `len` (the VRRP payload-length argument) passed as the SAME value as the
 * captured/allocated size -- i.e. ND_TTEST2(bp[0], len) always evaluates at
 * the exact boundary bp+len == snapend, so it depends only on where the
 * fixed offset-6 read falls relative to that one boundary.
 *
 * Corpus design (byte0 = (version<<4)|type; version must be 3, type must be
 * VRRP_TYPE_ADVERTISEMENT(1) -> byte0 = 0x31; bytes 1..5 = vrid/prio/naddrs/
 * intvl-hi/intvl-lo, freely variable, they only affect *printed* text, never
 * the crash; longer inputs zero-pad remaining structure):
 *   - TRIGGERING: file length (== captured == len) in {6, 7}. This is enough
 *     to pass the earlier `ND_TCHECK(bp[5])` (needs >=6 captured) and enter
 *     the -v/version==3 block, but leaves offset 6..7 (the checksum field
 *     EXTRACT_16BITS reads) 1-2 bytes past the end of the allocation.
 *   - SAFE (regime A, "too short to even reach the block"): length in
 *     {0,1,2} (fails the very first `ND_TCHECK(bp[0])` or the version/type
 *     decode never matches ADVERTISEMENT) or {3,4,5} (passes bp[0] checks but
 *     fails `ND_TCHECK(bp[2])`/`ND_TCHECK(bp[5])` -> `goto trunc`).
 *   - SAFE (regime B, "wrong type/version"): length >= 6 but byte0 encodes a
 *     version outside [2,3] or a type != ADVERTISEMENT -> early `return`
 *     before the vulnerable block is ever reached.
 *   - SAFE (regime C, "in bounds"): length >= 8 -> the same version==3 +
 *     checksum-block code path runs, EXTRACT_16BITS(&bp[6]) executes, but
 *     offset 6..7 is now fully inside the allocation -- exercises the exact
 *     same branch as TRIGGERING, just safely. naddrs byte (index 3) is kept 0
 *     in these inputs so the following address-printing loop is a no-op and
 *     never reaches the (stubbed, unimplemented-for-real) ipaddr_string.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <arpa/inet.h>   /* ntohs/ntohl -- what netdissect-stdinc.h pulls in */

typedef unsigned char u_char;
typedef unsigned int u_int;
typedef unsigned short u_short;

typedef struct netdissect_options netdissect_options;

/* netdissect.h: struct tok + tok2str (real signature) */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};
extern const char *tok2str(const struct tok *, const char *, u_int);

/* netdissect.h struct netdissect_options -- minimal but faithful subset:
 * only the fields vrrp_print() actually touches. */
struct netdissect_options {
	int ndo_vflag;			/* verbosity level */
	const u_char *ndo_packetp;	/* beginning of current packet */
	const u_char *ndo_snapend;	/* end of current packet */
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* extract.h -- native (non-LBL_ALIGN) x86_64 unaligned-load variant, the
 * exact one x86_64 builds use (matches the baseline's own
 * "extract.h:184:20 in EXTRACT_16BITS" crash site). */
#if defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 409)
#define UNALIGNED_OK	__attribute__((no_sanitize_undefined))
#elif defined(__has_attribute)
#if __has_attribute(no_sanitize)
#define UNALIGNED_OK	__attribute__((no_sanitize("undefined")))
#else
#define UNALIGNED_OK
#endif
#else
#define UNALIGNED_OK
#endif

static inline uint16_t UNALIGNED_OK
EXTRACT_16BITS(const void *p)
{
	return ((uint16_t)ntohs(*(const uint16_t *)(p)));
}

/* netdissect.h -- "l" bytes of "var" captured? (verbatim) */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TTEST(var) ND_TTEST2(var, sizeof(var))
#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))
/* extract.h -- used only in the version==2 branch (real signature, never
 * exercised by this version==3-only corpus -- see file header). */
#define ND_TCHECK_16BITS(p) ND_TCHECK2(*(p), 2)

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ip.h: struct ip is only ever used opaquely here (cast-and-pass-through to
 * the stubbed nextproto4_cksum, never dereferenced) -- an incomplete type is
 * faithful enough and avoids dragging in nd_uint-typed checksum-layout
 * details that vrrp_print() itself never touches. */
struct ip;

/* ipproto.h (verbatim) */
#ifndef IPPROTO_VRRP
#define IPPROTO_VRRP		112
#endif

/* netdissect.h: struct cksum_vec + in_cksum() (real signatures; version==2-
 * only code path, never exercised by this corpus -- see file header). */
struct cksum_vec {
	const uint8_t	*ptr;
	int		len;
};
extern uint16_t in_cksum(const struct cksum_vec *, int);

/* netdissect.h: nextproto4_cksum() (real signature). Out-of-file callee, not
 * the fault site -- see file header for why the stub always reports "bad". */
extern int nextproto4_cksum(netdissect_options *, const struct ip *, const uint8_t *, u_int, u_int, u_int);

/* addrtoname.h: ipaddr_string is a MACRO to getname() in the real headers --
 * kept as the real macro name/expansion, getname() stubbed below. */
extern const char *getname(netdissect_options *, const u_char *);
#define ipaddr_string(ndo, p) getname(ndo, (const u_char *)(p))

/* netdissect.h (real signature); version==2-simple-auth-only, never
 * exercised by this corpus. */
extern int fn_printn(netdissect_options *, const u_char *, u_int, const u_char *);

/* ---- print-vrrp.c, verbatim (RFC-diagram comments omitted, tables kept) ---- */

/* Type */
#define	VRRP_TYPE_ADVERTISEMENT	1

static const struct tok type2str[] = {
	{ VRRP_TYPE_ADVERTISEMENT,	"Advertisement"	},
	{ 0,				NULL		}
};

/* Auth Type */
#define	VRRP_AUTH_NONE		0
#define	VRRP_AUTH_SIMPLE	1
#define	VRRP_AUTH_AH		2

static const struct tok auth2str[] = {
	{ VRRP_AUTH_NONE,		"none"		},
	{ VRRP_AUTH_SIMPLE,		"simple"	},
	{ VRRP_AUTH_AH,			"ah"		},
	{ 0,				NULL		}
};

/* ---- trivial, behaviourally-safe stubs for the out-of-file callees.
 * None of these is the fault site, and (see file header) our corpus is
 * crafted so none of them ever touches attacker-controlled out-of-bounds
 * data; they just need to exist, with real signatures, for the TU to link. ---- */

const char *
tok2str(const struct tok *lp, const char *fmt, u_int v)
{
	static char buf[128];
	while (lp != NULL && lp->s != NULL) {
		if (lp->v == v)
			return lp->s;
		lp++;
	}
	if (fmt == NULL)
		fmt = "#%d";
	snprintf(buf, sizeof(buf), fmt, v);
	return buf;
}

uint16_t
in_cksum(const struct cksum_vec *vec, int veclen)
{
	(void)vec; (void)veclen;
	return 0;
}

/* volatile sink: forces the compiler to actually materialize (and thus
 * actually PERFORM) the call + its arguments at every call site -- mirrors
 * the icmp_print direct-call harness's `ip_print_sink` trick, which found
 * (and fixed) a real -O1 dead-code-elimination hazard for exactly this shape
 * of stub. Deliberately, deterministically reports "bad checksum" (nonzero)
 * without dereferencing any of its pointer arguments -- it is not the fault
 * site under test; see the file header for why. */
static volatile u_int nextproto4_cksum_sink;

__attribute__((noinline)) int
nextproto4_cksum(netdissect_options *ndo, const struct ip *ip, const uint8_t *ptr,
    u_int len, u_int covlen, u_int next_proto)
{
	(void)ndo; (void)ip;
	nextproto4_cksum_sink = (u_int)(uintptr_t)ptr + len + covlen + next_proto;
	return 1;
}

const char *
getname(netdissect_options *ndo, const u_char *ap)
{
	(void)ndo;
	static char buf[32];
	snprintf(buf, sizeof(buf), "%u.%u.%u.%u", ap[0], ap[1], ap[2], ap[3]);
	return buf;
}

int
fn_printn(netdissect_options *ndo, const u_char *s, u_int n, const u_char *ep)
{
	(void)ndo; (void)s; (void)n; (void)ep;
	return 0;
}

static int
harness_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	va_start(ap, fmt);
	int r = vfprintf(stderr, fmt, ap);
	va_end(ap);
	return r;
}

/* ---- verbatim target function (target/original_function.c, byte-for-byte) ---- */
void
vrrp_print(netdissect_options *ndo,
           register const u_char *bp, register u_int len,
           register const u_char *bp2, int ttl)
{
	int version, type, auth_type = VRRP_AUTH_NONE; /* keep compiler happy */
	const char *type_s;

	ND_TCHECK(bp[0]);
	version = (bp[0] & 0xf0) >> 4;
	type = bp[0] & 0x0f;
	type_s = tok2str(type2str, "unknown type (%u)", type);
	ND_PRINT((ndo, "VRRPv%u, %s", version, type_s));
	if (ttl != 255)
		ND_PRINT((ndo, ", (ttl %u)", ttl));
	if (version < 2 || version > 3 || type != VRRP_TYPE_ADVERTISEMENT)
		return;
	ND_TCHECK(bp[2]);
	ND_PRINT((ndo, ", vrid %u, prio %u", bp[1], bp[2]));
	ND_TCHECK(bp[5]);

	if (version == 2) {
		auth_type = bp[4];
		ND_PRINT((ndo, ", authtype %s", tok2str(auth2str, NULL, auth_type)));
		ND_PRINT((ndo, ", intvl %us, length %u", bp[5], len));
	} else { /* version == 3 */
		uint16_t intvl = (bp[4] & 0x0f) << 8 | bp[5];
		ND_PRINT((ndo, ", intvl %ucs, length %u", intvl, len));
	}

	if (ndo->ndo_vflag) {
		int naddrs = bp[3];
		int i;
		char c;

		if (version == 2 && ND_TTEST2(bp[0], len)) {
			struct cksum_vec vec[1];

			vec[0].ptr = bp;
			vec[0].len = len;
			if (in_cksum(vec, 1)) {
				ND_TCHECK_16BITS(&bp[6]);
				ND_PRINT((ndo, ", (bad vrrp cksum %x)",
					EXTRACT_16BITS(&bp[6])));
			}
		}

		if (version == 3 && ND_TTEST2(bp[0], len)) {
			uint16_t cksum = nextproto4_cksum(ndo, (const struct ip *)bp2, bp,
				len, len, IPPROTO_VRRP);
			if (cksum)
				ND_PRINT((ndo, ", (bad vrrp cksum %x)",
					EXTRACT_16BITS(&bp[6])));
		}

		ND_PRINT((ndo, ", addrs"));
		if (naddrs > 1)
			ND_PRINT((ndo, "(%d)", naddrs));
		ND_PRINT((ndo, ":"));
		c = ' ';
		bp += 8;
		for (i = 0; i < naddrs; i++) {
			ND_TCHECK(bp[3]);
			ND_PRINT((ndo, "%c%s", c, ipaddr_string(ndo, bp)));
			c = ',';
			bp += 4;
		}
		if (version == 2 && auth_type == VRRP_AUTH_SIMPLE) { /* simple text password */
			ND_TCHECK(bp[7]);
			ND_PRINT((ndo, " auth \""));
			if (fn_printn(ndo, bp, 8, ndo->ndo_snapend)) {
				ND_PRINT((ndo, "\""));
				goto trunc;
			}
			ND_PRINT((ndo, "\""));
		}
	}
	return;
trunc:
	ND_PRINT((ndo, "[|vrrp]"));
}
/* ---- end verbatim target function ---- */

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) {
		perror("fopen");
		return 1;
	}
	if (fseek(fp, 0, SEEK_END) != 0) {
		perror("fseek");
		fclose(fp);
		return 1;
	}
	long len = ftell(fp);
	if (len < 0) {
		perror("ftell");
		fclose(fp);
		return 1;
	}
	rewind(fp);

	/* Heap buffer, sized to EXACTLY the file length (no slack) so ASAN's
	 * redzone sits immediately after the real "captured packet" data --
	 * mirrors the real per-packet capture buffer tcpdump allocates. */
	size_t alloc_len = (size_t)len > 0 ? (size_t)len : 1;
	u_char *data = malloc(alloc_len);
	if (!data) {
		perror("malloc");
		fclose(fp);
		return 1;
	}
	if (len > 0 && fread(data, (size_t)len, 1, fp) != 1) {
		fprintf(stderr, "short read\n");
		fclose(fp);
		free(data);
		return 1;
	}
	fclose(fp);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_vflag = 1;		/* -v, required to reach the checksum block */
	ndo.ndo_packetp = data;
	/* Only the actual file bytes are "captured" -- matches the real caller,
	 * where ndo_snapend marks the end of what was captured off the
	 * wire/savefile, independent of any length field encoded inside the
	 * packet itself. */
	ndo.ndo_snapend = data + len;
	ndo.ndo_printf = harness_printf;

	/* `len` (the VRRP payload-length argument) is passed as the SAME value
	 * as the captured/allocated size, so ND_TTEST2(bp[0], len) always
	 * evaluates at the exact boundary bp+len == snapend (see file header
	 * for the corpus-design rationale). bp2 points at the same valid
	 * buffer (matches the real caller: bp2 is the enclosing IP header,
	 * typically earlier in the same captured packet); it is never
	 * dereferenced by any code path this corpus reaches (nextproto4_cksum
	 * is stubbed and ignores it). ttl=64 is an arbitrary in-range value,
	 * irrelevant to the crash. */
	vrrp_print(&ndo, data, (u_int)len, data, 64);

	free(data);
	return 0;
}
