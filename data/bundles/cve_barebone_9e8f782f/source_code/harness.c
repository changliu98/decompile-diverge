/*
 * Direct-call crash harness for tcpdump print-isoclns.c:isoclns_print()
 * CVE-2017-12897 / CWE-125 (heap-buffer-overflow READ).
 *
 * Root cause (see dataset/cvf_9e8f782f/case.json baseline.dedup_token
 * "isoclns_print--handle_ppp--ppp_print" + baseline.summary
 * "AddressSanitizer: heap-buffer-overflow /work/./print-isoclns.c:684:10 in
 * isoclns_print"): isoclns_print()'s ONLY bounds check is
 * `if (caplen <= 1) return;` on its own `caplen` PARAMETER -- it never
 * consults ndo->ndo_snapend (unlike almost every other print-*.c function,
 * it has no ND_TCHECK at all). Its real caller, print-ppp.c:handle_ppp(),
 * hits the PPP_OSI case with
 *     isoclns_print(ndo, p, length, length);
 * i.e. it passes the PPP payload's on-wire `length` as BOTH `length` AND
 * `caplen`, so `caplen` is decoupled from how many bytes were actually
 * captured (ndo_snapend). When fewer bytes were really captured than
 * `length` claims, `caplen <= 1` wrongly evaluates false and
 * `switch (*p)` (print-isoclns.c:684) dereferences a `p` that is already
 * past the end of the captured buffer -> heap-buffer-overflow READ of 1
 * byte, entirely inside isoclns_print() itself (the switch's `*p` read
 * happens before any case body -- none of the sub-protocol printers it
 * calls are ever reached).
 *
 * The target function isoclns_print() is embedded VERBATIM below (byte-for-
 * byte identical to dataset/cvf_9e8f782f/target/original_function.c).
 * Everything above it is the minimal-but-faithful set of real type/macro
 * definitions (real names, from source_code/netdissect.h, source_code/
 * nlpid.h/nlpid.c) it needs to compile standalone, plus safe no-op stand-
 * ins (real names/signatures, from source_code/netdissect.h's extern
 * prototypes) for the sub-protocol printers it calls -- none of which is
 * where the fault is (the fault fires at the `switch (*p)` dispatch itself,
 * strictly before any of those callees would ever run), so each is a
 * pure no-op that never dereferences its pointer argument and so can never
 * introduce a fault of its own.
 *
 * main() reproduces the caller-side bug directly: it reads argv[1] as a
 * tiny record describing (a) how many bytes are ACTUALLY allocated on the
 * heap (the true "captured" length) and (b) the `caplen`/pointer-offset the
 * direct call passes to isoclns_print -- exactly the two independent
 * quantities handle_ppp() conflates in the real vulnerability. See the
 * comment above main() for the exact record layout.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/types.h>

typedef unsigned char u_char;
typedef unsigned int u_int;
typedef unsigned char uint8_t_local; /* unused, keeps intent explicit */

/* ---------------------------------------------------------------------
 * netdissect_options -- minimal-but-faithful subset (real field names /
 * types, from source_code/netdissect.h struct netdissect_options). Only
 * the fields isoclns_print() actually touches are kept: ndo_eflag
 * (controls the "-e" verbose NLPID banner) and ndo_printf (the ND_PRINT()
 * sink).
 * --------------------------------------------------------------------- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
    int ndo_eflag;                      /* print ethernet/link header info */
    int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---------------------------------------------------------------------
 * ND_PRINT -- verbatim from source_code/netdissect.h.
 * --------------------------------------------------------------------- */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---------------------------------------------------------------------
 * struct tok / tok2strbuf / tok2str -- verbatim from source_code/
 * netdissect.h (struct tok) and source_code/util-print.c (tok2strbuf/
 * tok2str: a trivial, self-contained, already-bounds-safe linear lookup +
 * snprintf fallback -- it only ever reads its OWN static token table and
 * writes to its OWN static buffer, never the packet buffer).
 * --------------------------------------------------------------------- */
struct tok {
        u_int v;                /* value */
        const char *s;          /* string */
};

#define TOKBUFSIZE 128

static const char *
tok2strbuf(const struct tok *lp, const char *fmt,
           u_int v, char *buf, size_t bufsize)
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
tok2str(const struct tok *lp, const char *fmt, u_int v)
{
        static char buf[4][TOKBUFSIZE];
        static int idx = 0;
        char *ret;

        ret = buf[idx];
        idx = (idx + 1) & 3;
        return tok2strbuf(lp, fmt, v, ret, sizeof(buf[0]));
}

/* ---------------------------------------------------------------------
 * nlpid.h / nlpid.c -- verbatim (real NLPID_* constants + the real
 * nlpid_values token table isoclns_print() switches on and prints via
 * tok2str()).
 * --------------------------------------------------------------------- */
#define	NLPID_NULLNS	  0x00
#define NLPID_Q933      0x08 /* ANSI T1.617 Annex D or ITU-T Q.933 Annex A */
#define NLPID_LMI       0x09 /* The original, aka Cisco, aka Gang of Four */
#define NLPID_SNAP      0x80
#define	NLPID_CLNP	    0x81 /* iso9577 */
#define	NLPID_ESIS	    0x82 /* iso9577 */
#define	NLPID_ISIS	    0x83 /* iso9577 */
#define NLPID_CONS      0x84
#define NLPID_IDRP      0x85
#define NLPID_MFR       0xb1 /* FRF.15 */
#define NLPID_SPB       0xc1 /* IEEE 802.1aq/D4.5 */
#define NLPID_IP        0xcc
#define NLPID_PPP       0xcf
#define NLPID_X25_ESIS  0x8a
#define NLPID_IP6       0x8e

static const struct tok nlpid_values[] = {
    { NLPID_NULLNS, "NULL" },
    { NLPID_Q933, "Q.933" },
    { NLPID_LMI, "LMI" },
    { NLPID_SNAP, "SNAP" },
    { NLPID_CLNP, "CLNP" },
    { NLPID_ESIS, "ES-IS" },
    { NLPID_ISIS, "IS-IS" },
    { NLPID_CONS, "CONS" },
    { NLPID_IDRP, "IDRP" },
    { NLPID_SPB, "ISIS_SPB" },
    { NLPID_MFR, "FRF.15" },
    { NLPID_IP, "IPv4" },
    { NLPID_PPP, "PPP" },
    { NLPID_X25_ESIS, "X25 ES-IS" },
    { NLPID_IP6, "IPv6" },
    { 0, NULL }
};

/* ---------------------------------------------------------------------
 * uint8_t -- isoclns_print()'s `p` parameter is `const uint8_t *`.
 * --------------------------------------------------------------------- */
#include <stdint.h>

/* ---------------------------------------------------------------------
 * Sub-protocol printer callees -- real names/signatures (extern
 * prototypes verbatim from source_code/netdissect.h / static prototypes
 * from source_code/print-isoclns.c), each a pure no-op stand-in. NONE of
 * these ever runs on the crashing path: the fault fires at the
 * `switch (*p)` dispatch itself (or, when ndo_eflag is set, at the *p
 * read a few lines earlier), i.e. before dispatch even selects a case
 * body. They are kept as genuine no-ops (never dereference their pointer
 * argument) purely so the callers below still link, and so they can never
 * mask or fabricate an unrelated fault of their own.
 * --------------------------------------------------------------------- */
static int
clnp_print(netdissect_options *ndo, const uint8_t *pptr, u_int length)
{
        (void)ndo; (void)pptr; (void)length;
        return 1; /* "packet recognized" -> real code skips print_unknown_data */
}

static void
esis_print(netdissect_options *ndo, const uint8_t *pptr, u_int length)
{
        (void)ndo; (void)pptr; (void)length;
}

static int
isis_print(netdissect_options *ndo, const uint8_t *pptr, u_int length)
{
        (void)ndo; (void)pptr; (void)length;
        return 1;
}

static void
q933_print(netdissect_options *ndo, const u_char *p, u_int length)
{
        (void)ndo; (void)p; (void)length;
}

void
ip_print(netdissect_options *ndo, const u_char *p, u_int length)
{
        (void)ndo; (void)p; (void)length;
}

void
ip6_print(netdissect_options *ndo, const u_char *p, u_int length)
{
        (void)ndo; (void)p; (void)length;
}

u_int
ppp_print(netdissect_options *ndo, register const u_char *p, u_int length)
{
        (void)ndo; (void)p; (void)length;
        return 0;
}

static int
print_unknown_data(netdissect_options *ndo, const u_char *cp,
                    const char *ident, int len)
{
        (void)ndo; (void)cp; (void)ident; (void)len;
        return 1;
}

/* =======================================================================
 * TARGET FUNCTION -- VERBATIM, byte-for-byte identical to
 * dataset/cvf_9e8f782f/target/original_function.c. Do not edit.
 * ======================================================================= */
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
/* ======================================================================= */

/* ---------------------------------------------------------------------
 * harness plumbing
 * --------------------------------------------------------------------- */
static int
harness_printf(netdissect_options *ndo, const char *fmt, ...)
{
        (void)ndo;
        (void)fmt;
        return 0;
}

/*
 * Input record layout (raw bytes, read from argv[1]):
 *
 *   byte 0        : eflag        (0 or nonzero -> ndo->ndo_eflag)
 *   byte 1        : real_n       (0..250) -- number of bytes ACTUALLY
 *                                 malloc()'d and filled ("truly captured").
 *   byte 2        : caplen_lo    \_ caplen argument passed to
 *   byte 3        : caplen_hi    /  isoclns_print(), 16-bit little-endian.
 *                                 This is the value the buggy real caller
 *                                 (handle_ppp -> isoclns_print(ndo,p,len,len))
 *                                 conflates with the on-wire length INSTEAD
 *                                 of the true captured length -- here it is
 *                                 an independent, directly-controlled field,
 *                                 exactly modelling that conflation.
 *   byte 4        : p_offset     (0..250) -- offset from the start of the
 *                                 real_n-byte heap buffer at which `p`
 *                                 itself points. offset == real_n (or
 *                                 beyond) means `p` points AT/PAST the end
 *                                 of the actual allocation -> the read of
 *                                 `*p` inside isoclns_print is a
 *                                 heap-buffer-overflow READ, exactly
 *                                 reproducing the CVE-2017-12897 fault.
 *                                 offset < real_n means `p` points at a
 *                                 valid byte -> no overflow.
 *   bytes 5..     : payload, copied into the real_n-byte heap buffer
 *                                 (truncated/zero-padded to real_n bytes).
 *                                 `length` (the 2nd arg) is passed equal to
 *                                 caplen, mirroring the real
 *                                 isoclns_print(ndo,p,length,length) call.
 */
int
main(int argc, char **argv)
{
        FILE *f;
        long sz;
        unsigned char *raw;
        size_t n;
        u_char *buf;
        unsigned real_n, p_offset;
        uint16_t caplen;
        netdissect_options ndo_storage;
        netdissect_options *ndo = &ndo_storage;

        if (argc < 2) {
                fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
                return 1;
        }

        f = fopen(argv[1], "rb");
        if (!f) {
                fprintf(stderr, "cannot open %s\n", argv[1]);
                return 1;
        }
        if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
        sz = ftell(f);
        if (sz < 0) { fclose(f); return 1; }
        rewind(f);

        raw = (unsigned char *)malloc((size_t)sz > 0 ? (size_t)sz : 1);
        if (!raw) { fclose(f); return 1; }
        n = (sz > 0) ? fread(raw, 1, (size_t)sz, f) : 0;
        fclose(f);

        if (n < 5) {
                /* Too short to hold a full record -- nothing meaningful to
                 * do; exit clean (this is not itself a test of the fault). */
                free(raw);
                return 0;
        }

        memset(&ndo_storage, 0, sizeof(ndo_storage));
        ndo->ndo_eflag = raw[0] & 1;
        real_n = raw[1];
        if (real_n > 250) real_n = 250;
        caplen = (uint16_t)(raw[2] | (raw[3] << 8));
        p_offset = raw[4];
        if (p_offset > 250) p_offset = 250;

        /* HEAP buffer sized EXACTLY to real_n -- required so ASAN's redzone
         * sits immediately after it and an over-read past it is caught.
         * real_n == 0 is intentionally malloc(0) (a valid zero-size ASAN
         * allocation, NOT malloc(1)): any read at offset 0 of an empty
         * allocation must itself be flagged as a heap-buffer-overflow. */
        buf = (u_char *)malloc(real_n);
        if (!buf && real_n > 0) { free(raw); return 1; }
        {
                size_t avail = (n > 5) ? (n - 5) : 0;
                size_t cpy = avail < real_n ? avail : real_n;
                if (cpy > 0)
                        memcpy(buf, raw + 5, cpy);
                if (cpy < real_n)
                        memset(buf + cpy, 0, real_n - cpy);
        }
        free(raw);

        ndo->ndo_printf = harness_printf;

        /* p is (buf + p_offset). If p_offset >= real_n, p points at or past
         * the end of the real_n-byte allocation -- ASAN will flag the very
         * first byte isoclns_print() reads from it as a heap-buffer-overflow
         * READ, in isoclns_print() itself, matching the baseline crash. */
        isoclns_print(ndo, (const uint8_t *)(buf + p_offset), caplen, caplen);

        free(buf);
        return 0;
}
