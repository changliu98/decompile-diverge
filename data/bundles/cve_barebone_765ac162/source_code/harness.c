/*
 * Direct-call crash harness for cve_765ac162 (CVE-2018-16451, tcpdump
 * print-smb.c, print_trans()). CWE-125 heap-buffer-overflow READ.
 *
 * Bug recap (matches baseline dedup_token
 * "__interceptor_strcmp--print_trans--print_smb" / summary
 * "AddressSanitizer: heap-buffer-overflow ... in __interceptor_strcmp"):
 * print_trans() dispatches an SMB Trans2 request/reply by comparing the
 * NUL-unchecked bytes at `data1 + 2` directly against two C string
 * literals with strcmp() (source print-smb.c:375 and :380, target/
 * original_function.c lines 41 and 46 here):
 *
 *     if (strcmp((const char *)(data1 + 2), "\\MAILSLOT\\BROWSE") == 0) ...
 *     if (strcmp((const char *)(data1 + 2), "\\PIPE\\LANMAN") == 0) ...
 *
 * strcmp() walks BOTH strings byte-by-byte until a mismatch or a NUL. If
 * the captured/attacker buffer at data1+2 matches a literal's prefix all
 * the way to the end of the captured buffer without ever hitting a NUL
 * byte, strcmp() reads one byte past the buffer's end -> heap-buffer-
 * overflow READ, exactly what ASan's `__interceptor_strcmp` frame shows
 * in the frozen baseline. This is independent of the surrounding SMB
 * word-count/param/data-offset accounting -- it only needs the two bytes
 * at data1 (the `bcc` byte count) to be nonzero and the packet to end
 * right inside a literal-prefix match starting at data1+2.
 *
 * print_trans() is embedded VERBATIM from target/original_function.c: no
 * logic/name/signature change. Its helper `smb_fdata()` (real prototype,
 * smb.h:122 / defined smbutil.c:795) is NOT the fault site -- the fault
 * is the strcmp() call directly inside print_trans() itself -- so it is
 * stubbed as a no-op that touches no memory and just returns its `buf`
 * argument, matching the real signature
 * `const u_char *smb_fdata(netdissect_options *, const u_char *, const
 * char *, const u_char *, int)`. print_browse()/print_ipc() (also real
 * print-smb.c callees, also not the fault site) are stubbed the same way,
 * purely so the corpus's two literal-EQUAL-match safe inputs (which
 * legitimately reach those calls in the real dispatcher) still link and
 * run cleanly.
 *
 * main() mimics the real caller chain (print_smb() -> print_trans(),
 * print-smb.c:863): it reads argv[1] into a HEAP buffer (malloc'd to
 * EXACTLY the file length, so ASan's redzone sits immediately past the
 * real data), sets `ndo->ndo_snapend` to the end of that buffer
 * (mirroring "everything in this buffer was captured"), lays out `words`
 * (a 17-byte SMB word-block header -- the minimum print_trans() needs to
 * pass its own ND_TCHECK2) and `data1` (2-byte bcc + the MAILSLOT/PIPE
 * path string) inside it, and calls
 * print_trans(ndo, words, data1, buf, maxbuf) ONCE, directly.
 */
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char u_char;
typedef unsigned int  u_int;

/* ---- minimal, faithful subset of netdissect.h ---- */

/* Real struct from netdissect.h; only the fields print_trans() (and the
 * macros/callees it uses) actually touch are kept. */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
    const u_char *ndo_snapend;
    int  (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif

/* netdissect.h verbatim */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* extract.h verbatim (only the LE 16-bit accessor print_trans() uses) */
#define EXTRACT_LE_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 1)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 0)) << 0)))

/* print-smb.c file-scope statics print_trans() reads directly (not
 * parameters) -- same names/types/defaults as source print-smb.c:25-26. */
static int request = 0;
static int unicodestr = 0;
static const char tstr[] = "[|SMB]";

/* smb.h verbatim prototype; smb_fdata()/print_browse()/print_ipc() are
 * real print-smb.c/smbutil.c callees but NOT the fault site (the fault is
 * the strcmp() call directly inside print_trans()) -- stubbed as no-ops
 * that touch NO caller memory, per the harness convention, so the
 * function compiles/links standalone with no dependency on the rest of
 * tcpdump.
 *
 * Each stub still writes to a `volatile` sink. This is NOT semantically
 * meaningful -- it exists purely to give the stub an observable side
 * effect the optimizer cannot prove equivalent across the taken/not-taken
 * branches. Without it, at -O1 the whole `if (bcc > 0) { ... }` block in
 * print_trans() (every branch of which -- match-MAILSLOT, match-PIPE, or
 * no-match -- ends in one of these truly-no-op stubs) is providably
 * side-effect-free and dead-code-eliminated *whole*, which silently
 * deletes the vulnerable strcmp() calls along with it (verified: without
 * the sink writes, none of the 25 crafted triggering inputs crashed).
 * The sink forces the compiler to actually evaluate strcmp()'s result to
 * decide whether to perform the (fake) side effect, so the real
 * strcmp()-induced heap OOB read on the way to that decision survives
 * optimization -- exactly as it does in the full linked tcpdump binary,
 * where smb_fdata()/print_browse()/print_ipc() have real effects (they
 * print packet fields) that the optimizer likewise cannot discard. */
static volatile unsigned g_sink;

static const u_char *
smb_fdata(netdissect_options *ndo, const u_char *buf, const char *fmt,
          const u_char *maxbuf, int unicode)
{
    (void)ndo; (void)fmt; (void)maxbuf; (void)unicode;
    g_sink++;
    return buf;
}

static void
print_browse(netdissect_options *ndo, const u_char *param, int paramlen,
             const u_char *data, int datalen)
{
    (void)ndo; (void)param; (void)paramlen; (void)data; (void)datalen;
    g_sink += 2;
}

static void
print_ipc(netdissect_options *ndo, const u_char *param, int paramlen,
          const u_char *data, int datalen)
{
    (void)ndo; (void)param; (void)paramlen; (void)data; (void)datalen;
    g_sink += 3;
}

/* ---- target function, embedded VERBATIM from target/original_function.c ---- */
static void
print_trans(netdissect_options *ndo,
            const u_char *words, const u_char *data1, const u_char *buf, const u_char *maxbuf)
{
    u_int bcc;
    const char *f1, *f2, *f3, *f4;
    const u_char *data, *param;
    const u_char *w = words + 1;
    int datalen, paramlen;

    if (request) {
	ND_TCHECK2(w[12 * 2], 2);
	paramlen = EXTRACT_LE_16BITS(w + 9 * 2);
	param = buf + EXTRACT_LE_16BITS(w + 10 * 2);
	datalen = EXTRACT_LE_16BITS(w + 11 * 2);
	data = buf + EXTRACT_LE_16BITS(w + 12 * 2);
	f1 = "TotParamCnt=[d] \nTotDataCnt=[d] \nMaxParmCnt=[d] \nMaxDataCnt=[d]\nMaxSCnt=[d] \nTransFlags=[w] \nRes1=[w] \nRes2=[w] \nRes3=[w]\nParamCnt=[d] \nParamOff=[d] \nDataCnt=[d] \nDataOff=[d] \nSUCnt=[d]\n";
	f2 = "|Name=[S]\n";
	f3 = "|Param ";
	f4 = "|Data ";
    } else {
	ND_TCHECK2(w[7 * 2], 2);
	paramlen = EXTRACT_LE_16BITS(w + 3 * 2);
	param = buf + EXTRACT_LE_16BITS(w + 4 * 2);
	datalen = EXTRACT_LE_16BITS(w + 6 * 2);
	data = buf + EXTRACT_LE_16BITS(w + 7 * 2);
	f1 = "TotParamCnt=[d] \nTotDataCnt=[d] \nRes1=[d]\nParamCnt=[d] \nParamOff=[d] \nRes2=[d] \nDataCnt=[d] \nDataOff=[d] \nRes3=[d]\nLsetup=[d]\n";
	f2 = "|Unknown ";
	f3 = "|Param ";
	f4 = "|Data ";
    }

    smb_fdata(ndo, words + 1, f1, min(words + 1 + 2 * words[0], maxbuf),
        unicodestr);

    ND_TCHECK2(*data1, 2);
    bcc = EXTRACT_LE_16BITS(data1);
    ND_PRINT((ndo, "smb_bcc=%u\n", bcc));
    if (bcc > 0) {
	smb_fdata(ndo, data1 + 2, f2, maxbuf - (paramlen + datalen), unicodestr);

	if (strcmp((const char *)(data1 + 2), "\\MAILSLOT\\BROWSE") == 0) {
	    print_browse(ndo, param, paramlen, data, datalen);
	    return;
	}

	if (strcmp((const char *)(data1 + 2), "\\PIPE\\LANMAN") == 0) {
	    print_ipc(ndo, param, paramlen, data, datalen);
	    return;
	}

	if (paramlen)
	    smb_fdata(ndo, param, f3, min(param + paramlen, maxbuf), unicodestr);
	if (datalen)
	    smb_fdata(ndo, data, f4, min(data + datalen, maxbuf), unicodestr);
    }
    return;
trunc:
    ND_PRINT((ndo, "%s", tstr));
}
/* ---- end verbatim target function ---- */

static int
nd_printf(netdissect_options *ndo, const char *fmt, ...)
{
    (void)ndo;
    va_list ap;
    va_start(ap, fmt);
    int r = vprintf(fmt, ap);
    va_end(ap);
    return r;
}

/* SMB word-block header size print_trans() needs before data1: w=words+1,
 * and the request==0 branch's furthest access is w[7*2] i.e. words[15],
 * ND_TCHECK2'd for 2 bytes -> words[15] and words[16] must be in-bounds,
 * i.e. 17 header bytes (indices 0..16) minimum. */
#define HDR_LEN 17

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
    if (len < HDR_LEN + 2) {
        /* too short to even reach the bcc field -- nothing to dissect */
        fclose(f);
        return 0;
    }

    /* REQUIRED: heap buffer for attacker-controlled bytes, malloc'd to
     * EXACTLY the file length, so ASan's redzone sits immediately past
     * the real data (mirrors the captured-packet buffer in tcpdump). */
    u_char *buf = malloc((size_t)len);
    if (!buf) { fclose(f); return 1; }
    size_t rd = fread(buf, 1, (size_t)len, f);
    fclose(f);
    if (rd != (size_t)len) { free(buf); return 1; }

    netdissect_options ndo_storage;
    memset(&ndo_storage, 0, sizeof(ndo_storage));
    netdissect_options *ndo = &ndo_storage;
    ndo->ndo_printf = nd_printf;
    ndo->ndo_snapend = buf + len;   /* everything in the file is "captured" */

    request = 0;      /* reply path -- same branch the original PoC drives */
    unicodestr = 0;

    const u_char *words  = buf;               /* 17-byte word-block header */
    const u_char *data1  = buf + HDR_LEN;      /* bcc(2) + path string      */
    const u_char *pbuf   = buf;
    const u_char *maxbuf = buf + len;

    print_trans(ndo, words, data1, pbuf, maxbuf);

    printf("print_trans returned (len=%ld) sink=%u\n", len, g_sink);

    free(buf);
    return 0;
}
