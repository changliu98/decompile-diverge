/* Direct-call crash harness for tcpdump ubik_print
 * (CVE-2017-13049, CWE-125, print-rx.c).
 *
 * ubik_print() reads the 4-byte RX/Ubik opcode with:
 *
 *     ubik_op = EXTRACT_32BITS(bp + sizeof(struct rx_header));
 *
 * with NO ND_TCHECK/ND_TCHECK2 guard of its own before this very first
 * read -- unlike every other read later in the function (all of which are
 * inside per-case macros -- INTOUT()/UINTOUT()/DATEOUT()/UBIK_VERSIONOUT()
 * -- that DO ND_TCHECK2() first). sizeof(struct rx_header) is 28 bytes, so
 * this unconditionally reads bytes [28..31] of the "packet" without ever
 * checking that 32 bytes were actually captured. If bp is a heap buffer
 * shorter than 32 bytes, this walks straight past the end of the
 * allocation -> heap-buffer-overflow READ inside EXTRACT_32BITS, matching
 * baseline dedup_token "EXTRACT_32BITS--ubik_print--prot_print" and
 * baseline.cwe CWE-125 exactly (this harness calls ubik_print directly,
 * so "prot_print" -- the whole-program caller -- is absent by design; the
 * fault frames EXTRACT_32BITS/ubik_print are identical).
 *
 * main() mimics the real caller's setup (prot_print()/vldb_print()/
 * kauth_print() in print-rx.c, which all just pass through the packet
 * pointer + ndo->ndo_snapend): it reads the whole input file into a
 * malloc'd heap buffer sized EXACTLY to the file length (no slack, so
 * ASAN's redzone sits immediately after the "captured packet" data,
 * mirroring the real capture buffer), sets ndo->ndo_snapend = data+len,
 * and calls ubik_print(&ndo, data) once, directly.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <time.h>
#include <arpa/inet.h>   /* ntohl/ntohs -- what tcpdump's netdissect-stdinc.h
                             includes for these */

/* ---- minimal but faithful type/macro defs the function needs ---- */
/* (real names verbatim from netdissect.h / extract.h / print-rx.c) */

typedef unsigned char u_char;
typedef unsigned int u_int;

typedef struct netdissect_options netdissect_options;

struct netdissect_options {
	/* pointer to end of current packet (during printing) -- the ONLY
	 * bounds primitive ND_TTEST2/ND_TCHECK2 uses */
	const u_char *ndo_snapend;

	/* pointer to function to do regular output -- what ND_PRINT() calls */
	int  (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* extract.h -- native (non-LBL_ALIGN) x86_64 unaligned-load variant
 * (verbatim; this is the branch that applies on x86_64, which is what
 * the ASAN build here runs on) */
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

static inline uint32_t UNALIGNED_OK
EXTRACT_32BITS(const void *p)
{
	return ((uint32_t)ntohl(*(const uint32_t *)(p)));
}

/* netdissect.h -- "l" bytes of "var" captured? (verbatim) */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

/* Bail if "l" bytes of "var" were not captured */
#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* print-rx.c -- struct rx_header (verbatim field-for-field; sizeof == 28
 * on this ABI, which is exactly the offset ubik_print's own unguarded
 * read is computed from) */
struct rx_header {
	uint32_t epoch;
	uint32_t cid;
	uint32_t callNumber;
	uint32_t seq;
	uint32_t serial;
	uint8_t type;
	uint8_t flags;
	uint8_t userStatus;
	uint8_t securityIndex;
	uint16_t spare;
	uint16_t serviceId;
};

/* netdissect.h -- struct tok + util-print.c -- tok2str/tok2strbuf
 * (verbatim; ubik_print calls tok2str() to format the opcode) */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

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

/* print-rx.c -- verbatim tables ubik_print references */
static const struct tok ubik_req[] = {
	{ 10000,	"vote-beacon" },
	{ 10001,	"vote-debug-old" },
	{ 10002,	"vote-sdebug-old" },
	{ 10003,	"vote-getsyncsite" },
	{ 10004,	"vote-debug" },
	{ 10005,	"vote-sdebug" },
	{ 10006,	"vote-xdebug" },
	{ 10007,	"vote-xsdebug" },
	{ 20000,	"disk-begin" },
	{ 20001,	"disk-commit" },
	{ 20002,	"disk-lock" },
	{ 20003,	"disk-write" },
	{ 20004,	"disk-getversion" },
	{ 20005,	"disk-getfile" },
	{ 20006,	"disk-sendfile" },
	{ 20007,	"disk-abort" },
	{ 20008,	"disk-releaselocks" },
	{ 20009,	"disk-truncate" },
	{ 20010,	"disk-probe" },
	{ 20011,	"disk-writev" },
	{ 20012,	"disk-interfaceaddr" },
	{ 20013,	"disk-setversion" },
	{ 0,		NULL },
};

static const struct tok ubik_lock_types[] = {
	{ 1,		"read" },
	{ 2,		"write" },
	{ 3,		"wait" },
	{ 0,		NULL },
};

/* print-rx.c -- verbatim macros ubik_print's body invokes */
#define INTOUT() { int _i; \
			ND_TCHECK2(bp[0], sizeof(int32_t)); \
			_i = (int) EXTRACT_32BITS(bp); \
			bp += sizeof(int32_t); \
			ND_PRINT((ndo, " %d", _i)); \
		}

#define UINTOUT() { unsigned long _i; \
			ND_TCHECK2(bp[0], sizeof(int32_t)); \
			_i = EXTRACT_32BITS(bp); \
			bp += sizeof(int32_t); \
			ND_PRINT((ndo, " %lu", _i)); \
		}

#define DATEOUT() { time_t _t; struct tm *tm; char str[256]; \
			ND_TCHECK2(bp[0], sizeof(int32_t)); \
			_t = (time_t) EXTRACT_32BITS(bp); \
			bp += sizeof(int32_t); \
			tm = localtime(&_t); \
			strftime(str, 256, "%Y/%m/%d %H:%M:%S", tm); \
			ND_PRINT((ndo, " %s", str)); \
		}

#define UBIK_VERSIONOUT() {int32_t epoch; int32_t counter; \
			ND_TCHECK2(bp[0], sizeof(int32_t) * 2); \
			epoch = EXTRACT_32BITS(bp); \
			bp += sizeof(int32_t); \
			counter = EXTRACT_32BITS(bp); \
			bp += sizeof(int32_t); \
			ND_PRINT((ndo, " %d.%d", epoch, counter)); \
		}

/* ndo_printf stub: must actually CONSUME its varargs via vsnprintf (an
 * opaque libc call), not silently discard them -- with a truly no-op
 * body, clang can prove the EXTRACT_32BITS()/tok2str() argument values
 * feeding ND_PRINT() are never observed and elide the reads that produce
 * them entirely, hiding the bug (see cve_299f4da7's harness for the same
 * gotcha in a sibling tcpdump print-*.c function). */
static int
ndo_printf_stub(netdissect_options *ndo, const char *fmt, ...)
{
	char buf[512];
	va_list ap;
	va_start(ap, fmt);
	int n = vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	(void)ndo;
	return n;
}

/* ---- verbatim target function (target/original_function.c), unchanged ---- */
static void
ubik_print(netdissect_options *ndo,
           register const u_char *bp)
{
	int ubik_op;
	int32_t temp;

	/*
	 * Print out the afs call we're invoking.  The table used here was
	 * gleaned from ubik/ubik_int.xg
	 */

	ubik_op = EXTRACT_32BITS(bp + sizeof(struct rx_header));

	ND_PRINT((ndo, " ubik call %s", tok2str(ubik_req, "op#%d", ubik_op)));

	/*
	 * Decode some of the arguments to the Ubik calls
	 */

	bp += sizeof(struct rx_header) + 4;

	switch (ubik_op) {
		case 10000:		/* Beacon */
			ND_TCHECK2(bp[0], 4);
			temp = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			ND_PRINT((ndo, " syncsite %s", temp ? "yes" : "no"));
			ND_PRINT((ndo, " votestart"));
			DATEOUT();
			ND_PRINT((ndo, " dbversion"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			break;
		case 10003:		/* Get sync site */
			ND_PRINT((ndo, " site"));
			UINTOUT();
			break;
		case 20000:		/* Begin */
		case 20001:		/* Commit */
		case 20007:		/* Abort */
		case 20008:		/* Release locks */
		case 20010:		/* Writev */
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			break;
		case 20002:		/* Lock */
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " file"));
			INTOUT();
			ND_PRINT((ndo, " pos"));
			INTOUT();
			ND_PRINT((ndo, " length"));
			INTOUT();
			temp = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			tok2str(ubik_lock_types, "type %d", temp);
			break;
		case 20003:		/* Write */
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " file"));
			INTOUT();
			ND_PRINT((ndo, " pos"));
			INTOUT();
			break;
		case 20005:		/* Get file */
			ND_PRINT((ndo, " file"));
			INTOUT();
			break;
		case 20006:		/* Send file */
			ND_PRINT((ndo, " file"));
			INTOUT();
			ND_PRINT((ndo, " length"));
			INTOUT();
			ND_PRINT((ndo, " dbversion"));
			UBIK_VERSIONOUT();
			break;
		case 20009:		/* Truncate */
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " file"));
			INTOUT();
			ND_PRINT((ndo, " length"));
			INTOUT();
			break;
		case 20012:		/* Set version */
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " oldversion"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " newversion"));
			UBIK_VERSIONOUT();
			break;
		default:
			;
	}

	return;

trunc:
	ND_PRINT((ndo, " [|ubik]"));
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
	 * mirrors the real capture buffer tcpdump allocates per-packet, and
	 * the ndo_snapend semantics its own callers set up. */
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
	/* Only the actual file bytes are "captured" -- matches the real
	 * caller, where ndo_snapend marks the end of what was captured off
	 * the wire/savefile, which may be far short of any length field
	 * encoded inside the packet. */
	ndo.ndo_snapend = data + len;
	ndo.ndo_printf = ndo_printf_stub;

	ubik_print(&ndo, data);

	printf("ubik_print done, len=%ld\n", len);

	free(data);
	return 0;
}
