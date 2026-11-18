/*
 * Direct-call crash harness for cvf_fe7391b4 (CVE-2017-13015, tcpdump
 * print-eap.c, eap_print()). CWE-125 heap-buffer-overflow READ.
 *
 * Bug recap (matches baseline dedup_token
 * "EXTRACT_16BITS--eap_print--ethertype_print" / summary "AddressSanitizer:
 * heap-buffer-overflow /work/./extract.h:184:20 in EXTRACT_16BITS", fixed
 * upstream by 985122081165753c7442bd7824c473eb9ff56308 "CVE-2017-13015/EAP:
 * Add more bounds checks."):
 *
 * eap_print() first ND_TCHECK(*eap)s the 4-byte eap_frame_t header
 * (original_function.c:161) -- that's the ONLY bounds check before the
 * EAP_FRAME_TYPE_PACKET arm starts dereferencing bytes past it:
 *
 *     type = *(tptr);                    (:187, tptr[0] -- unchecked)
 *     len  = EXTRACT_16BITS(tptr+2);     (:188, tptr[2..3] -- unchecked)
 *     ND_PRINT((ndo, ..., *(tptr+1), len));   (:189-193, tptr[1] -- unchecked)
 *     ND_TCHECK2(*tptr, len);            (:195 -- the FIRST real check,
 *                                          AFTER the three reads above)
 *     if (type <= 2) {
 *         subtype = *(tptr+4);           (:198, tptr[4] -- STILL unchecked;
 *                                          not covered by the `len` above)
 *         switch (subtype) {
 *         ...
 *         case EAP_TYPE_TTLS: case EAP_TYPE_TLS: case EAP_TYPE_FAST:
 *             ... *(tptr+5) ...          (tptr[5] -- unchecked)
 *             if (EAP_TLS_EXTRACT_BIT_L(*(tptr+5)))
 *                 EXTRACT_32BITS(tptr+6);        (tptr[6..9] -- unchecked)
 *
 * So there are FIVE independent unguarded reads past the 4-byte header,
 * gated only by how much is actually captured (ndo->ndo_snapend), never by
 * the on-wire `len` field: tptr[0], tptr[2..3] (the original PoC's crash
 * site -- EXTRACT_16BITS at extract.h:184), tptr[4], tptr[5], and
 * tptr[6..9]. All five are heap-buffer-overflow READs inside eap_print
 * itself (CWE-125) and are exercised by the corpus via the truncation
 * length of the heap buffer.
 *
 * eap_print() is embedded VERBATIM from target/original_function.c. Its
 * real callees (tok2str/tok2strbuf/bittok2str/bittok2str_internal/
 * bittok2str_nosep + strlcpy, and safeputs/safeputchar) are embedded
 * VERBATIM from source_code/util-print.c and source_code/missing/strlcpy.c
 * -- none of them are on the fault path (tok2str* only formats an already-
 * read integer; safeputs's `len` argument is always <= what ND_TCHECK2
 * already validated against snapend, so it's memory-safe by construction)
 * but they DO touch real packet bytes (safeputs) or run before the crash
 * on the same statement (tok2str), so they are kept real rather than
 * stubbed. The static token tables / #defines are copied verbatim from
 * print-eap.c.
 *
 * main() reads argv[1] into a HEAP buffer (malloc'd to EXACTLY the file
 * length -- ASan's redzone sits immediately past the real data, mirroring
 * "captured packet" truncation) and calls eap_print(&ndo, p, length) ONCE,
 * directly, with ndo->ndo_vflag=1 (REQUIRED -- the whole EAP_FRAME_TYPE_PACKET
 * arm, and hence every crash site, is only reached in verbose mode; matches
 * the real `tcpdump -v` invocation this CVE requires) and
 * ndo->ndo_snapend = p + length (the captured-length boundary the bug reads
 * past).
 */

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;

/* ---- netdissect.h, netdissect_options trimmed to the real fields this
 * function (and the macros it uses) actually touch: ndo_vflag (verbosity),
 * ndo_snapend (captured-data boundary, used by ND_TTEST2/ND_TCHECK2),
 * ndo_printf (the ND_PRINT sink). Real names/types. ---- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int ndo_vflag;				/* verbosity level */
	const u_char *ndo_snapend;		/* end of captured data */
	int  (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* netdissect.h macros, verbatim */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))
#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))
#define ND_TTEST(var) ND_TTEST2(var, sizeof(var))
#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

#define ND_ISPRINT(c)	((c) >= 0x20 && (c) <= 0x7E)

/* extract.h, verbatim (byte-at-a-time big-endian form -- portable, no
 * alignment/strict-aliasing assumptions). */
#define EXTRACT_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 0)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 1)) << 0)))
#define EXTRACT_32BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 0)) << 24) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 3)) << 0)))

/* ---- util-print.c, verbatim (real callees; none on the fault path). ---- */
#define TOKBUFSIZE 128

struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

/* missing/strlcpy.c, verbatim. */
static size_t
strlcpy(char *dst, const char *src, size_t siz)
{
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;

	if (n != 0 && --n != 0) {
		do {
			if ((*d++ = *s++) == 0)
				break;
		} while (--n != 0);
	}

	if (n == 0) {
		if (siz != 0)
			*d = '\0';
		while (*s++)
			;
	}

	return(s - src - 1);
}

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

static char *
bittok2str_internal(register const struct tok *lp, register const char *fmt,
	   register u_int v, const char *sep)
{
        static char buf[1024+1];
        char *bufp = buf;
        size_t space_left = sizeof(buf), string_size;
        register u_int rotbit;
        register u_int tokval;
        const char * sepstr = "";

	while (lp != NULL && lp->s != NULL) {
            tokval=lp->v;
            rotbit=1;
            while (rotbit != 0) {
		if (tokval == (v&rotbit)) {
                    if (space_left <= 1)
                        return (buf);
                    string_size = strlcpy(bufp, sepstr, space_left);
                    if (string_size >= space_left)
                        return (buf);
                    bufp += string_size;
                    space_left -= string_size;
                    if (space_left <= 1)
                        return (buf);
                    string_size = strlcpy(bufp, lp->s, space_left);
                    if (string_size >= space_left)
                        return (buf);
                    bufp += string_size;
                    space_left -= string_size;
                    sepstr = sep;
                    break;
                }
                rotbit=rotbit<<1;
            }
            lp++;
	}

        if (bufp == buf)
            (void)snprintf(buf, sizeof(buf), fmt == NULL ? "#%08x" : fmt, v);
        return (buf);
}

char *
bittok2str_nosep(register const struct tok *lp, register const char *fmt,
	   register u_int v)
{
    return (bittok2str_internal(lp, fmt, v, ""));
}

char *
bittok2str(register const struct tok *lp, register const char *fmt,
	   register u_int v)
{
    return (bittok2str_internal(lp, fmt, v, ", "));
}

static void
safeputchar(netdissect_options *ndo, const u_char c)
{
	ND_PRINT((ndo, (c < 0x80 && ND_ISPRINT(c)) ? "%c" : "\\0x%02x", c));
}

void
safeputs(netdissect_options *ndo,
         const u_char *s, const u_int maxlen)
{
	u_int idx = 0;

	while (idx < maxlen && *s) {
		safeputchar(ndo, *s);
		idx++;
		s++;
	}
}

/* ---- print-eap.c file-scope statics eap_print() reads directly, verbatim
 * (source_code/print-eap.c lines 32-138). ---- */
#define	EAP_FRAME_TYPE_PACKET		0
#define	EAP_FRAME_TYPE_START		1
#define	EAP_FRAME_TYPE_LOGOFF		2
#define	EAP_FRAME_TYPE_KEY		3
#define	EAP_FRAME_TYPE_ENCAP_ASF_ALERT	4

struct eap_frame_t {
    unsigned char   version;
    unsigned char   type;
    unsigned char   length[2];
};

static const struct tok eap_frame_type_values[] = {
    { EAP_FRAME_TYPE_PACKET,      	"EAP packet" },
    { EAP_FRAME_TYPE_START,    		"EAPOL start" },
    { EAP_FRAME_TYPE_LOGOFF,      	"EAPOL logoff" },
    { EAP_FRAME_TYPE_KEY,      		"EAPOL key" },
    { EAP_FRAME_TYPE_ENCAP_ASF_ALERT, 	"Encapsulated ASF alert" },
    { 0, NULL}
};

#define		EAP_REQUEST	1
#define		EAP_RESPONSE	2
#define		EAP_SUCCESS	3
#define		EAP_FAILURE	4

static const struct tok eap_code_values[] = {
    { EAP_REQUEST,	"Request" },
    { EAP_RESPONSE,	"Response" },
    { EAP_SUCCESS,	"Success" },
    { EAP_FAILURE,	"Failure" },
    { 0, NULL}
};

#define		EAP_TYPE_NO_PROPOSED	0
#define		EAP_TYPE_IDENTITY	1
#define		EAP_TYPE_NOTIFICATION	2
#define		EAP_TYPE_NAK		3
#define		EAP_TYPE_MD5_CHALLENGE	4
#define		EAP_TYPE_OTP		5
#define		EAP_TYPE_GTC		6
#define		EAP_TYPE_TLS		13		/* RFC 2716 */
#define		EAP_TYPE_SIM		18		/* RFC 4186 */
#define		EAP_TYPE_TTLS		21		/* draft-funk-eap-ttls-v0-01.txt */
#define		EAP_TYPE_AKA		23		/* RFC 4187 */
#define		EAP_TYPE_FAST		43		/* RFC 4851 */
#define		EAP_TYPE_EXPANDED_TYPES	254
#define		EAP_TYPE_EXPERIMENTAL	255

static const struct tok eap_type_values[] = {
    { EAP_TYPE_NO_PROPOSED,	"No proposed" },
    { EAP_TYPE_IDENTITY,	"Identity" },
    { EAP_TYPE_NOTIFICATION,    "Notification" },
    { EAP_TYPE_NAK,      	"Nak" },
    { EAP_TYPE_MD5_CHALLENGE,   "MD5-challenge" },
    { EAP_TYPE_OTP,      	"OTP" },
    { EAP_TYPE_GTC,      	"GTC" },
    { EAP_TYPE_TLS,      	"TLS" },
    { EAP_TYPE_SIM,      	"SIM" },
    { EAP_TYPE_TTLS,      	"TTLS" },
    { EAP_TYPE_AKA,      	"AKA" },
    { EAP_TYPE_FAST,      	"FAST" },
    { EAP_TYPE_EXPANDED_TYPES,  "Expanded types" },
    { EAP_TYPE_EXPERIMENTAL,    "Experimental" },
    { 0, NULL}
};

#define EAP_TLS_EXTRACT_BIT_L(x) 	(((x)&0x80)>>7)

#define EAP_TLS_FLAGS_LEN_INCLUDED		(1 << 7)
#define EAP_TLS_FLAGS_MORE_FRAGMENTS		(1 << 6)
#define EAP_TLS_FLAGS_START			(1 << 5)

static const struct tok eap_tls_flags_values[] = {
	{ EAP_TLS_FLAGS_LEN_INCLUDED, "L bit" },
	{ EAP_TLS_FLAGS_MORE_FRAGMENTS, "More fragments bit"},
	{ EAP_TLS_FLAGS_START, "Start bit"},
	{ 0, NULL}
};

#define EAP_TTLS_VERSION(x)		((x)&0x07)

#define EAP_AKA_CHALLENGE		1
#define EAP_AKA_AUTH_REJECT		2
#define EAP_AKA_SYNC_FAILURE		4
#define EAP_AKA_IDENTITY		5
#define EAP_SIM_START			10
#define EAP_SIM_CHALLENGE		11
#define EAP_AKA_NOTIFICATION		12
#define EAP_AKA_REAUTH			13
#define EAP_AKA_CLIENT_ERROR		14

static const struct tok eap_aka_subtype_values[] = {
    { EAP_AKA_CHALLENGE,	"Challenge" },
    { EAP_AKA_AUTH_REJECT,	"Auth reject" },
    { EAP_AKA_SYNC_FAILURE,	"Sync failure" },
    { EAP_AKA_IDENTITY,		"Identity" },
    { EAP_SIM_START,		"Start" },
    { EAP_SIM_CHALLENGE,	"Challenge" },
    { EAP_AKA_NOTIFICATION,	"Notification" },
    { EAP_AKA_REAUTH,		"Reauth" },
    { EAP_AKA_CLIENT_ERROR,	"Client error" },
    { 0, NULL}
};

/* ---- target function, embedded VERBATIM from target/original_function.c
 * (byte-for-byte identical -- diffed during validation). ---- */
void
eap_print(netdissect_options *ndo,
          register const u_char *cp,
          u_int length)
{
    const struct eap_frame_t *eap;
    const u_char *tptr;
    u_int tlen, type, subtype;
    int count=0, len;

    tptr = cp;
    tlen = length;
    eap = (const struct eap_frame_t *)cp;
    ND_TCHECK(*eap);

    /* in non-verbose mode just lets print the basic info */
    if (ndo->ndo_vflag < 1) {
	ND_PRINT((ndo, "%s (%u) v%u, len %u",
               tok2str(eap_frame_type_values, "unknown", eap->type),
               eap->type,
               eap->version,
               EXTRACT_16BITS(eap->length)));
	return;
    }

    ND_PRINT((ndo, "%s (%u) v%u, len %u",
           tok2str(eap_frame_type_values, "unknown", eap->type),
           eap->type,
           eap->version,
           EXTRACT_16BITS(eap->length)));

    tptr += sizeof(const struct eap_frame_t);
    tlen -= sizeof(const struct eap_frame_t);

    switch (eap->type) {
    case EAP_FRAME_TYPE_PACKET:
        type = *(tptr);
        len = EXTRACT_16BITS(tptr+2);
        ND_PRINT((ndo, ", %s (%u), id %u, len %u",
               tok2str(eap_code_values, "unknown", type),
               type,
               *(tptr+1),
               len));

        ND_TCHECK2(*tptr, len);

        if (type <= 2) { /* For EAP_REQUEST and EAP_RESPONSE only */
            subtype = *(tptr+4);
            ND_PRINT((ndo, "\n\t\t Type %s (%u)",
                   tok2str(eap_type_values, "unknown", *(tptr+4)),
                   *(tptr + 4)));

            switch (subtype) {
            case EAP_TYPE_IDENTITY:
                if (len - 5 > 0) {
                    ND_PRINT((ndo, ", Identity: "));
                    safeputs(ndo, tptr + 5, len - 5);
                }
                break;

            case EAP_TYPE_NOTIFICATION:
                if (len - 5 > 0) {
                    ND_PRINT((ndo, ", Notification: "));
                    safeputs(ndo, tptr + 5, len - 5);
                }
                break;

            case EAP_TYPE_NAK:
                count = 5;

                /*
                 * one or more octets indicating
                 * the desired authentication
                 * type one octet per type
                 */
                while (count < len) {
                    ND_PRINT((ndo, " %s (%u),",
                           tok2str(eap_type_values, "unknown", *(tptr+count)),
                           *(tptr + count)));
                    count++;
                }
                break;

            case EAP_TYPE_TTLS:
                ND_PRINT((ndo, " TTLSv%u",
                       EAP_TTLS_VERSION(*(tptr + 5)))); /* fall through */
            case EAP_TYPE_TLS:
                ND_PRINT((ndo, " flags [%s] 0x%02x,",
                       bittok2str(eap_tls_flags_values, "none", *(tptr+5)),
                       *(tptr + 5)));

                if (EAP_TLS_EXTRACT_BIT_L(*(tptr+5))) {
		    ND_PRINT((ndo, " len %u", EXTRACT_32BITS(tptr + 6)));
                }
                break;

            case EAP_TYPE_FAST:
                ND_PRINT((ndo, " FASTv%u",
                       EAP_TTLS_VERSION(*(tptr + 5))));
                ND_PRINT((ndo, " flags [%s] 0x%02x,",
                       bittok2str(eap_tls_flags_values, "none", *(tptr+5)),
                       *(tptr + 5)));

                if (EAP_TLS_EXTRACT_BIT_L(*(tptr+5))) {
                    ND_PRINT((ndo, " len %u", EXTRACT_32BITS(tptr + 6)));
                }

                /* FIXME - TLV attributes follow */
                break;

            case EAP_TYPE_AKA:
            case EAP_TYPE_SIM:
                ND_PRINT((ndo, " subtype [%s] 0x%02x,",
                       tok2str(eap_aka_subtype_values, "unknown", *(tptr+5)),
                       *(tptr + 5)));

                /* FIXME - TLV attributes follow */
                break;

            case EAP_TYPE_MD5_CHALLENGE:
            case EAP_TYPE_OTP:
            case EAP_TYPE_GTC:
            case EAP_TYPE_EXPANDED_TYPES:
            case EAP_TYPE_EXPERIMENTAL:
            default:
                break;
            }
        }
        break;

    case EAP_FRAME_TYPE_LOGOFF:
    case EAP_FRAME_TYPE_ENCAP_ASF_ALERT:
    default:
        break;
    }
    return;

 trunc:
    ND_PRINT((ndo, "\n\t[|EAP]"));
}
/* ---- end verbatim target function ---- */

static int
nd_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	int r;
	va_start(ap, fmt);
	r = vprintf(fmt, ap);
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
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	long len = ftell(f);
	if (len < 0) { fclose(f); return 1; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* REQUIRED: heap buffer for attacker-controlled bytes, malloc'd to
	 * EXACTLY the file length, so ASan's redzone sits immediately past
	 * the real data (mirrors the "captured packet" buffer -- caplen IS
	 * the file length, no padding). */
	u_char *buf = NULL;
	if (len > 0) {
		buf = malloc((size_t)len);
		if (!buf) { fclose(f); return 1; }
		size_t rd = fread(buf, 1, (size_t)len, f);
		fclose(f);
		if (rd != (size_t)len) { free(buf); return 1; }
	} else {
		fclose(f);
		/* len == 0: still exercise the function with a non-NULL,
		 * zero-size heap allocation -- ndo_snapend is set to
		 * buf+0 below so the function's own ND_TCHECK(*eap) trips
		 * on the very first line. */
		buf = malloc(1);
		if (!buf) return 1;
		len = 0;
	}

	netdissect_options ndo_storage;
	memset(&ndo_storage, 0, sizeof(ndo_storage));
	netdissect_options *ndo = &ndo_storage;
	ndo->ndo_printf = nd_printf;
	ndo->ndo_vflag = 1;		/* REQUIRED: every crash site is only reached
					 * in verbose mode (mirrors `tcpdump -v`) */
	ndo->ndo_snapend = buf + len;	/* captured-data boundary the bug reads past */

	eap_print(ndo, buf, (u_int)len);

	printf("\neap_print returned (len=%ld)\n", len);

	free(buf);
	return 0;
}
