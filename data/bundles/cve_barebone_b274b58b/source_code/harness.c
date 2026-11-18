/* cve_barebone harness -- tcpdump print-fr.c:mfr_print()
 * heap-buffer-overflow READ (CWE-125). See gen_dc_cve_b274b58b.py's module docstring for the
 * full root-cause + crash-chain explanation.
 *
 * Sections below marked VERBATIM are copied byte-for-byte from source_code/ (real names, real
 * fields, real logic). Sections marked STUB are minimal faithful stand-ins for symbols
 * mfr_print()'s unmodified body (or a VERBATIM callee) references but that this specific
 * corpus never meaningfully executes.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <arpa/inet.h>   /* ntohl() for EXTRACT_32BITS */
#include <sys/time.h>    /* struct timeval, for the ts_print() stand-in */

/* ---- real BSD scalar typedefs (normally from netdissect-stdinc.h -> sys/types.h) ---- */
typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;

/* ---- netdissect.h: struct tok, VERBATIM ---- */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

typedef struct netdissect_options netdissect_options;

/* ---- netdissect_options, trimmed to the real fields mfr_print() and its real VERBATIM
 * callees on/around the crash path actually dereference (real names/types -- the dozen other
 * ndo_*flag knobs and ndo_error/ndo_warning/ndo_if_printer/... are omitted: mfr_print() and
 * none of the callees pulled in below ever touch them). ---- */
struct netdissect_options {
	int ndo_vflag;			/* verbosity level */
	const u_char *ndo_snapend;
	int  (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---- netdissect.h macros, VERBATIM ---- */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))
#define ND_TTEST(var) ND_TTEST2(var, sizeof(var))
#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- netdissect.h: ND_ISPRINT, VERBATIM ---- */
#define ND_ISPRINT(c)	((c) >= 0x20 && (c) <= 0x7E)

/* ---- extract.h, VERBATIM -- the "processor natively handles unaligned loads" branch, which
 * is what a real x86_64 build (LBL_ALIGN is `#undef`d in config.h.in, only set for
 * alignment-sensitive archs like alpha/mips) compiles. Only EXTRACT_32BITS is needed: it is
 * the ONLY EXTRACT_* macro mfr_print()'s body references, and it IS the faulting read. ---- */
static inline uint32_t
EXTRACT_32BITS(const void *p)
{
	return ((uint32_t)ntohl(*(const uint32_t *)(p)));
}

/* ---- print-fr.c: MFR_B_BIT/E_BIT/C_BIT/BEC_MASK/CTRL_FRAME/FRAG_FRAME + frf_flag_values[],
 * VERBATIM ---- */
/* FRF.15 / FRF.16 */
#define MFR_B_BIT 0x80
#define MFR_E_BIT 0x40
#define MFR_C_BIT 0x20
#define MFR_BEC_MASK    (MFR_B_BIT | MFR_E_BIT | MFR_C_BIT)
#define MFR_CTRL_FRAME  (MFR_B_BIT | MFR_E_BIT | MFR_C_BIT)
#define MFR_FRAG_FRAME  (MFR_B_BIT | MFR_E_BIT )

static const struct tok frf_flag_values[] = {
    { MFR_B_BIT, "Begin" },
    { MFR_E_BIT, "End" },
    { MFR_C_BIT, "Control" },
    { 0, NULL }
};

/* ---- print-fr.c: MFR_CTRL_MSG_x defines + mfr_ctrl_msg_values[] + MFR_CTRL_IE_x defines +
 * mfr_ctrl_ie_values[] + MFR_ID_STRING_MAXLEN + struct ie_tlv_header_t, VERBATIM ---- */
#define MFR_CTRL_MSG_ADD_LINK        1
#define MFR_CTRL_MSG_ADD_LINK_ACK    2
#define MFR_CTRL_MSG_ADD_LINK_REJ    3
#define MFR_CTRL_MSG_HELLO           4
#define MFR_CTRL_MSG_HELLO_ACK       5
#define MFR_CTRL_MSG_REMOVE_LINK     6
#define MFR_CTRL_MSG_REMOVE_LINK_ACK 7

static const struct tok mfr_ctrl_msg_values[] = {
    { MFR_CTRL_MSG_ADD_LINK, "Add Link" },
    { MFR_CTRL_MSG_ADD_LINK_ACK, "Add Link ACK" },
    { MFR_CTRL_MSG_ADD_LINK_REJ, "Add Link Reject" },
    { MFR_CTRL_MSG_HELLO, "Hello" },
    { MFR_CTRL_MSG_HELLO_ACK, "Hello ACK" },
    { MFR_CTRL_MSG_REMOVE_LINK, "Remove Link" },
    { MFR_CTRL_MSG_REMOVE_LINK_ACK, "Remove Link ACK" },
    { 0, NULL }
};

#define MFR_CTRL_IE_BUNDLE_ID  1
#define MFR_CTRL_IE_LINK_ID    2
#define MFR_CTRL_IE_MAGIC_NUM  3
#define MFR_CTRL_IE_TIMESTAMP  5
#define MFR_CTRL_IE_VENDOR_EXT 6
#define MFR_CTRL_IE_CAUSE      7

static const struct tok mfr_ctrl_ie_values[] = {
    { MFR_CTRL_IE_BUNDLE_ID, "Bundle ID"},
    { MFR_CTRL_IE_LINK_ID, "Link ID"},
    { MFR_CTRL_IE_MAGIC_NUM, "Magic Number"},
    { MFR_CTRL_IE_TIMESTAMP, "Timestamp"},
    { MFR_CTRL_IE_VENDOR_EXT, "Vendor Extension"},
    { MFR_CTRL_IE_CAUSE, "Cause"},
    { 0, NULL }
};

#define MFR_ID_STRING_MAXLEN 50

struct ie_tlv_header_t {
    uint8_t ie_type;
    uint8_t ie_len;
};

/* ---- util-print.c: TOKBUFSIZE, VERBATIM ---- */
#define TOKBUFSIZE 128

/* ---- missing/strlcpy.c: the REAL portability shim tcpdump itself ships and links in on any
 * platform whose libc lacks strlcpy (config.h.in: `#undef HAVE_STRLCPY` by default) -- copied
 * verbatim (body only) and kept `static` purely to guarantee it binds to THIS definition even
 * if the build's glibc happens to also export one, never to change its behavior. ---- */
static size_t
strlcpy(char *dst, const char *src, size_t siz)
{
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0 && --n != 0) {
		do {
			if ((*d++ = *s++) == 0)
				break;
		} while (--n != 0);
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);	/* count does not include NUL */
}

/* ---- util-print.c: tok2strbuf()/tok2str(), VERBATIM ---- */
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

/* ---- util-print.c: bittok2str_internal()/bittok2str_nosep()/bittok2str(), VERBATIM ---- */
static char *
bittok2str_internal(register const struct tok *lp, register const char *fmt,
	   register u_int v, const char *sep)
{
        static char buf[1024+1]; /* our string buffer */
        char *bufp = buf;
        size_t space_left = sizeof(buf), string_size;
        register u_int rotbit; /* this is the bit we rotate through all bitpositions */
        register u_int tokval;
        const char * sepstr = "";

	while (lp != NULL && lp->s != NULL) {
            tokval=lp->v;   /* load our first value */
            rotbit=1;
            while (rotbit != 0) {
                /*
                 * lets AND the rotating bit with our token value
                 * and see if we have got a match
                 */
		if (tokval == (v&rotbit)) {
                    /* ok we have found something */
                    if (space_left <= 1)
                        return (buf); /* only enough room left for NUL, if that */
                    string_size = strlcpy(bufp, sepstr, space_left);
                    if (string_size >= space_left)
                        return (buf);    /* we ran out of room */
                    bufp += string_size;
                    space_left -= string_size;
                    if (space_left <= 1)
                        return (buf); /* only enough room left for NUL, if that */
                    string_size = strlcpy(bufp, lp->s, space_left);
                    if (string_size >= space_left)
                        return (buf);    /* we ran out of room */
                    bufp += string_size;
                    space_left -= string_size;
                    sepstr = sep;
                    break;
                }
                rotbit=rotbit<<1; /* no match - lets shift and try again */
            }
            lp++;
	}

        if (bufp == buf)
            /* bummer - lets print the "unknown" message as advised in the fmt string if we got one */
            (void)snprintf(buf, sizeof(buf), fmt == NULL ? "#%08x" : fmt, v);
        return (buf);
}

/*
 * Convert a bit token value to a string; use "fmt" if not found.
 * this is useful for parsing bitfields, the output strings are not seperated.
 */
char *
bittok2str_nosep(register const struct tok *lp, register const char *fmt,
	   register u_int v)
{
    return (bittok2str_internal(lp, fmt, v, ""));
}

/*
 * Convert a bit token value to a string; use "fmt" if not found.
 * this is useful for parsing bitfields, the output strings are comma seperated.
 */
char *
bittok2str(register const struct tok *lp, register const char *fmt,
	   register u_int v)
{
    return (bittok2str_internal(lp, fmt, v, ", "));
}

/* ---- util-print.c: safeputchar(), VERBATIM ---- */
void
safeputchar(netdissect_options *ndo,
            const u_char c)
{
	ND_PRINT((ndo, (c < 0x80 && ND_ISPRINT(c)) ? "%c" : "\\0x%02x", c));
}

/* hex_print: minimal faithful stand-in for the real multi-column hex/ASCII dumper
 * (print-ascii.c). print_unknown_data() (VERBATIM immediately below) has ALREADY clamped
 * `len` to the verified [cp, ndo->ndo_snapend) range before calling this, so this stand-in
 * carries no memory-safety role of its own; it only needs to consume exactly the already-
 * verified `len` bytes without doing anything unsafe, which a plain byte loop satisfies.
 * Real prototype (netdissect.h): void hex_print(netdissect_options *, const char *ident,
 * const u_char *cp, u_int). */
static void
hex_print(netdissect_options *ndo, const char *ident, const u_char *cp, u_int len)
{
	u_int i;
	ND_PRINT((ndo, "%s", ident));
	for (i = 0; i < len; i++)
		ND_PRINT((ndo, "%02x", cp[i]));
}

/* ---- util-print.c: print_unknown_data(), VERBATIM (its own bounds-clamp against
 * ndo->ndo_snapend is real; only hex_print() above, its formatting-only callee, is stubbed) ---- */
int
print_unknown_data(netdissect_options *ndo, const u_char *cp,const char *ident,int len)
{
	if (len < 0) {
          ND_PRINT((ndo,"%sDissector error: print_unknown_data called with negative length",
		    ident));
		return(0);
	}
	if (ndo->ndo_snapend - cp < len)
		len = ndo->ndo_snapend - cp;
	if (len < 0) {
          ND_PRINT((ndo,"%sDissector error: print_unknown_data called with pointer past end of packet",
		    ident));
		return(0);
	}
        hex_print(ndo, ident,cp,len);
	return(1); /* everything is ok */
}

/* ts_print: minimal faithful stand-in. The real implementation (util-print.c) formats *tvp
 * against ndo->ndo_tflag / a static "first packet" reference timestamp / thiszone -- none of
 * which mfr_print() exposes or this corpus varies (ts_print is reached, at all, only when an
 * IE's ADJUSTED length equals sizeof(struct timeval); it is purely cosmetic printing and does
 * not gate any further bounds check inside mfr_print() itself). This stand-in reads the SAME
 * real fields (tv_sec/tv_usec) from the SAME already-ND_TCHECK2-verified pointer and prints
 * them, preserving the real memory-access shape without the unrelated timezone/precision
 * formatting machinery. */
void
ts_print(netdissect_options *ndo, const struct timeval *tvp)
{
	ND_PRINT((ndo, "%ld.%06ld ", (long)tvp->tv_sec, (long)tvp->tv_usec));
}

/* fr_print: STUB. Real callee (also defined in print-fr.c), but only reached from
 * mfr_print()'s OTHER top-level branch -- the FRF.16 FRAGMENTATION frame
 * ((p[0]&MFR_BEC_MASK) == MFR_FRAG_FRAME or MFR_B_BIT). Every input this corpus generates
 * sets the CONTROL-frame bits instead ((p[0]&MFR_BEC_MASK)==MFR_CTRL_FRAME, p[1]==0), so this
 * is never executed; it must merely link. mfr_print() discards its return value at the one
 * call site regardless. */
u_int
fr_print(netdissect_options *ndo, register const u_char *p, u_int length)
{
	(void)ndo; (void)p; (void)length;
	return 0;
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) ================= */
u_int
mfr_print(netdissect_options *ndo,
          register const u_char *p, u_int length)
{
    u_int tlen,idx,hdr_len = 0;
    uint16_t sequence_num;
    uint8_t ie_type,ie_len;
    const uint8_t *tptr;


/*
 * FRF.16 Link Integrity Control Frame
 *
 *      7    6    5    4    3    2    1    0
 *    +----+----+----+----+----+----+----+----+
 *    | B  | E  | C=1| 0    0    0    0  | EA |
 *    +----+----+----+----+----+----+----+----+
 *    | 0    0    0    0    0    0    0    0  |
 *    +----+----+----+----+----+----+----+----+
 *    |              message type             |
 *    +----+----+----+----+----+----+----+----+
 */

    ND_TCHECK2(*p, 4); /* minimum frame header length */

    if ((p[0] & MFR_BEC_MASK) == MFR_CTRL_FRAME && p[1] == 0) {
        ND_PRINT((ndo, "FRF.16 Control, Flags [%s], %s, length %u",
               bittok2str(frf_flag_values,"none",(p[0] & MFR_BEC_MASK)),
               tok2str(mfr_ctrl_msg_values,"Unknown Message (0x%02x)",p[2]),
               length));
        tptr = p + 3;
        tlen = length -3;
        hdr_len = 3;

        if (!ndo->ndo_vflag)
            return hdr_len;

        while (tlen>sizeof(struct ie_tlv_header_t)) {
            ND_TCHECK2(*tptr, sizeof(struct ie_tlv_header_t));
            ie_type=tptr[0];
            ie_len=tptr[1];

            ND_PRINT((ndo, "\n\tIE %s (%u), length %u: ",
                   tok2str(mfr_ctrl_ie_values,"Unknown",ie_type),
                   ie_type,
                   ie_len));

            /* infinite loop check */
            if (ie_type == 0 || ie_len <= sizeof(struct ie_tlv_header_t))
                return hdr_len;

            ND_TCHECK2(*tptr, ie_len);
            tptr+=sizeof(struct ie_tlv_header_t);
            /* tlv len includes header */
            ie_len-=sizeof(struct ie_tlv_header_t);
            tlen-=sizeof(struct ie_tlv_header_t);

            switch (ie_type) {

            case MFR_CTRL_IE_MAGIC_NUM:
                ND_PRINT((ndo, "0x%08x", EXTRACT_32BITS(tptr)));
                break;

            case MFR_CTRL_IE_BUNDLE_ID: /* same message format */
            case MFR_CTRL_IE_LINK_ID:
                for (idx = 0; idx < ie_len && idx < MFR_ID_STRING_MAXLEN; idx++) {
                    if (*(tptr+idx) != 0) /* don't print null termination */
                        safeputchar(ndo, *(tptr + idx));
                    else
                        break;
                }
                break;

            case MFR_CTRL_IE_TIMESTAMP:
                if (ie_len == sizeof(struct timeval)) {
                    ts_print(ndo, (const struct timeval *)tptr);
                    break;
                }
                /* fall through and hexdump if no unix timestamp */

                /*
                 * FIXME those are the defined IEs that lack a decoder
                 * you are welcome to contribute code ;-)
                 */

            case MFR_CTRL_IE_VENDOR_EXT:
            case MFR_CTRL_IE_CAUSE:

            default:
                if (ndo->ndo_vflag <= 1)
                    print_unknown_data(ndo, tptr, "\n\t  ", ie_len);
                break;
            }

            /* do we want to see a hexdump of the IE ? */
            if (ndo->ndo_vflag > 1 )
                print_unknown_data(ndo, tptr, "\n\t  ", ie_len);

            tlen-=ie_len;
            tptr+=ie_len;
        }
        return hdr_len;
    }
/*
 * FRF.16 Fragmentation Frame
 *
 *      7    6    5    4    3    2    1    0
 *    +----+----+----+----+----+----+----+----+
 *    | B  | E  | C=0|seq. (high 4 bits) | EA  |
 *    +----+----+----+----+----+----+----+----+
 *    |        sequence  (low 8 bits)         |
 *    +----+----+----+----+----+----+----+----+
 *    |        DLCI (6 bits)        | CR | EA  |
 *    +----+----+----+----+----+----+----+----+
 *    |   DLCI (4 bits)   |FECN|BECN| DE | EA |
 *    +----+----+----+----+----+----+----+----+
 */

    sequence_num = (p[0]&0x1e)<<7 | p[1];
    /* whole packet or first fragment ? */
    if ((p[0] & MFR_BEC_MASK) == MFR_FRAG_FRAME ||
        (p[0] & MFR_BEC_MASK) == MFR_B_BIT) {
        ND_PRINT((ndo, "FRF.16 Frag, seq %u, Flags [%s], ",
               sequence_num,
               bittok2str(frf_flag_values,"none",(p[0] & MFR_BEC_MASK))));
        hdr_len = 2;
        fr_print(ndo, p+hdr_len,length-hdr_len);
        return hdr_len;
    }

    /* must be a middle or the last fragment */
    ND_PRINT((ndo, "FRF.16 Frag, seq %u, Flags [%s]",
           sequence_num,
           bittok2str(frf_flag_values,"none",(p[0] & MFR_BEC_MASK))));
    print_unknown_data(ndo, p, "\n\t", length);

    return hdr_len;

 trunc:
    ND_PRINT((ndo, "[|mfr]"));
    return length;
}
/* ==================================================================
 * end of verbatim / minimally-stubbed tcpdump source
 * ================================================================== */

static int
nd_printf(netdissect_options *ndo, const char *fmt, ...)
{
	va_list ap;
	int ret;
	(void)ndo;
	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
	va_end(ap);
	return ret;
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

	/* attacker packet data MUST live on the heap, and ndo_snapend MUST be exactly
	 * buf + (bytes actually read) so that an over-length EXTRACT_32BITS() read walks off the
	 * real allocation -- exactly the CWE-125 over-read, reproduced with a real heap
	 * allocation rather than a synthetic offset. */
	buf = (u_char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if (!buf) { fclose(f); return 1; }

	n = fsz > 0 ? fread(buf, 1, (size_t)fsz, f) : 0;
	fclose(f);

	memset(&ndo_storage, 0, sizeof(ndo_storage));
	ndo->ndo_vflag = 1;             /* -> the IE loop is entered (real `tcpdump -v`) */
	ndo->ndo_snapend = buf + n;     /* real snapshot-length semantics: exactly the alloc */
	ndo->ndo_printf = nd_printf;

	/* volatile function pointer: forbids the compiler from inlining mfr_print() into
	 * main(), so it stays a real, separately-named stack frame in the ASAN backtrace. */
	u_int (*volatile call_mfr)(netdissect_options *, const u_char *, u_int) = mfr_print;
	call_mfr(ndo, buf, (u_int)n);

	free(buf);
	return 0;
}
