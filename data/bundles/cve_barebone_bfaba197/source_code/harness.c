/* cve_bfaba197 -- pjmedia_rtcp_fb_build_sli direct-call ASAN harness
 *
 * Bug: pjmedia_rtcp_fb_build_sli computes the required output-buffer size as
 *   len = (3 + sli_cnt) * 4;
 * with `sli_cnt` an attacker/caller-controlled `unsigned`. When sli_cnt is
 * within 3 of UINT_MAX (0xFFFFFFFD..0xFFFFFFFF), the addition wraps around
 * 2^32 and `len` becomes a small value (0, 4 or 8), so the guard
 *   if (len > *length) return PJ_ETOOSMALL;
 * passes even though `*length` (the caller-supplied buffer capacity) is far
 * too small for the real number of FCI entries the subsequent loop
 *   for (i = 0; i < sli_cnt; ++i) { ... write 4 bytes at p ... }
 * is about to emit (billions of iterations). The very first few iterations
 * already walk `p` straight off the end of the heap buffer -> heap-based
 * buffer overflow WRITE (CWE-787), entirely inside the target function's
 * own body, reachable purely via its (session, buf, length, sli_cnt, sli)
 * arguments -- no elaborate object state, no deep callees.
 *
 * This is a real, unpatched defect in pjmedia_rtcp_fb_build_sli's own
 * integer-overflow-guard logic: fix commit 11559e49e65 (mapped to this
 * candidate) touches the header-struct type used by this function but does
 * NOT touch the len computation/guard shown above, so the overflow is
 * present verbatim in target/original_function.c and reproduced here
 * byte-for-byte.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <assert.h>

/* ---- real pjlib type definitions (pjlib/include/pj/types.h) ---- */
typedef unsigned int   pj_uint32_t;
typedef unsigned short pj_uint16_t;
typedef unsigned char  pj_uint8_t;
typedef size_t         pj_size_t;
typedef int            pj_status_t;

/* ---- real pjlib macros (pjlib/include/pj/config.h, assert.h, errno.h) ---- */
#define PJ_DEF(type)    type
#define pj_assert(expr) assert(expr)
#define PJ_ASSERT_RETURN(expr,retval)    \
            do { \
                if (!(expr)) { pj_assert(expr); return retval; } \
            } while (0)
#define PJ_SUCCESS      0
#define PJ_EINVAL       70004
#define PJ_ETOOSMALL    70019

/* ---- real pjlib inline helpers (pjlib/include/pj/string.h, sock_bsd.c) ---- */
static void *pj_memcpy(void *dst, const void *src, pj_size_t size)
{
    return memcpy(dst, src, size);
}
static pj_uint16_t pj_htons(pj_uint16_t hostshort)
{
    return htons(hostshort);
}

/* ---- real pjmedia RTCP structs (pjmedia/include/pjmedia/rtcp.h) ---- */
typedef struct pjmedia_rtcp_common
{
    unsigned        count:5;   /**< varies by payload type */
    unsigned        p:1;       /**< padding flag           */
    unsigned        version:2; /**< packet type            */
    unsigned        pt:8;      /**< payload type           */
    unsigned        length:16; /**< packet length          */
    pj_uint32_t     ssrc;      /**< SSRC identification    */
} pjmedia_rtcp_common;

typedef struct pjmedia_rtcp_rr
{
    pj_uint32_t     ssrc;          /**< SSRC identification.           */
    pj_uint32_t     fract_lost:8;  /**< Fraction lost.                 */
    pj_uint32_t     total_lost_2:8;/**< Total lost, bit 0-7.           */
    pj_uint32_t     total_lost_1:8;/**< Total lost, bit 8-15.          */
    pj_uint32_t     total_lost_0:8;/**< Total lost, bit 16-23.         */
    pj_uint32_t     last_seq;      /**< Last sequence number.          */
    pj_uint32_t     jitter;        /**< Jitter.                        */
    pj_uint32_t     lsr;           /**< NTP ts in last SR received.    */
    pj_uint32_t     dlsr;          /**< Delay since last SR.           */
} pjmedia_rtcp_rr;

typedef struct pjmedia_rtcp_rr_pkt
{
    pjmedia_rtcp_common  common;   /**< Common header.         */
    pjmedia_rtcp_rr      rr;       /**< variable-length list   */
} pjmedia_rtcp_rr_pkt;

/* Minimal pjmedia_rtcp_session: only the field pjmedia_rtcp_fb_build_sli's
 * own body dereferences (session->rtcp_rr_pkt.common) -- real field name
 * and real type, matching pjmedia/include/pjmedia/rtcp.h. */
typedef struct pjmedia_rtcp_session
{
    pjmedia_rtcp_rr_pkt     rtcp_rr_pkt;   /**< Cached RTCP RR packet. */
} pjmedia_rtcp_session;

/* ---- real pjmedia RTCP-FB struct (pjmedia/include/pjmedia/rtcp_fb.h) ---- */
typedef struct pjmedia_rtcp_fb_sli
{
    pj_uint16_t          first;    /**< First lost macroblock     */
    pj_uint16_t          number;   /**< The number of lost macroblocks
                                         packets                    */
    pj_uint8_t           pict_id;  /**< Picture ID (temporal ref)  */
} pjmedia_rtcp_fb_sli;

/* ---- real RTCP-FB payload-type constant (pjmedia/src/pjmedia/rtcp_fb.c) ---- */
#define RTCP_PSFB      206

/* forward-declare noinline so the crash frame keeps the real function name
 * in the ASAN report; the definition below is byte-identical to
 * target/original_function.c (verbatim, not touched by this prototype). */
pj_status_t pjmedia_rtcp_fb_build_sli(
                    pjmedia_rtcp_session *session,
                    void *buf,
                    pj_size_t *length,
                    unsigned sli_cnt,
                    const pjmedia_rtcp_fb_sli sli[]) __attribute__((noinline));

/* ============ VERBATIM target function begins ============ */
PJ_DEF(pj_status_t) pjmedia_rtcp_fb_build_sli(
					pjmedia_rtcp_session *session, 
					void *buf,
					pj_size_t *length,
					unsigned sli_cnt,
					const pjmedia_rtcp_fb_sli sli[])
{
    pjmedia_rtcp_common *hdr;
    pj_uint8_t *p;
    unsigned len, i;

    PJ_ASSERT_RETURN(session && buf && length && sli_cnt && sli, PJ_EINVAL);

    len = (3 + sli_cnt) * 4;
    if (len > *length)
	return PJ_ETOOSMALL;

    /* Build RTCP-FB SLI header */
    hdr = (pjmedia_rtcp_common*)buf;
    pj_memcpy(hdr, &session->rtcp_rr_pkt.common,  sizeof(*hdr));
    hdr->pt = RTCP_PSFB;
    hdr->count = 2; /* FMT = 2 */
    hdr->length = pj_htons((pj_uint16_t)(len/4 - 1));

    /* Build RTCP-FB SLI FCI */
    p = (pj_uint8_t*)hdr + sizeof(*hdr);
    for (i = 0; i < sli_cnt; ++i) {
	/* 'first' takes 13 bit */
	*p++  = (pj_uint8_t)((sli[i].first >> 5) & 0xFF);   /* 8 MSB bits */
	*p    = (pj_uint8_t)((sli[i].first & 31) << 3);	    /* 5 LSB bits */
	/* 'number' takes 13 bit */
	*p++ |= (pj_uint8_t)((sli[i].number >> 10) & 7);    /* 3 MSB bits */
	*p++  = (pj_uint8_t)((sli[i].number >> 2) & 0xFF);  /* 8 mid bits */
	*p    = (pj_uint8_t)((sli[i].number & 3) << 6);	    /* 2 LSB bits */
	/* 'pict_id' takes 6 bit */
	*p++ |= (sli[i].pict_id & 63);
    }

    /* Finally */
    *length = len;

    return PJ_SUCCESS;
}/* ============ VERBATIM target function ends ============ */

#define BUF_LEN   64u   /* caller-supplied output-buffer capacity / *length */
#define SLI_CAP   64u   /* room for the FCI-source array; loop crashes on the
                           tiny `buf` write within the first few iterations,
                           well before it could ever read past SLI_CAP */

int main(int argc, char **argv)
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
    fseek(f, 0, SEEK_END);
    long fsz = ftell(f);
    if (fsz < 0) fsz = 0;
    fseek(f, 0, SEEK_SET);

    /* heap-allocate the raw file bytes (ASAN-guarded) */
    unsigned char *filebuf = (unsigned char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
    if (!filebuf) { fclose(f); return 1; }
    size_t got = fsz > 0 ? fread(filebuf, 1, (size_t)fsz, f) : 0;
    fclose(f);

    /* first 4 bytes of the input = attacker-controlled sli_cnt (LE u32),
       zero-padded if the file is shorter. */
    unsigned char cntbytes[4] = {0, 0, 0, 0};
    for (size_t i = 0; i < 4 && i < got; ++i) cntbytes[i] = filebuf[i];
    pj_uint32_t sli_cnt = (pj_uint32_t)cntbytes[0]
                        | ((pj_uint32_t)cntbytes[1] << 8)
                        | ((pj_uint32_t)cntbytes[2] << 16)
                        | ((pj_uint32_t)cntbytes[3] << 24);

    /* build a modest, always-valid FCI source array from the remaining
       input bytes (or zero-filled); its size is unrelated to sli_cnt and
       never actually gets walked far because the tiny `buf` write is what
       overflows first when sli_cnt has wrapped `len`. */
    pjmedia_rtcp_fb_sli sli_arr[SLI_CAP];
    memset(sli_arr, 0, sizeof(sli_arr));
    for (unsigned i = 0; i < SLI_CAP; ++i) {
        size_t off = 4 + (size_t)i * 5;
        if (off + 5 <= got) {
            sli_arr[i].first   = (pj_uint16_t)(filebuf[off] | (filebuf[off+1] << 8));
            sli_arr[i].number  = (pj_uint16_t)(filebuf[off+2] | (filebuf[off+3] << 8));
            sli_arr[i].pict_id = filebuf[off+4];
        }
    }

    /* real session object: zero-initialised is a perfectly valid
       pjmedia_rtcp_session (its rtcp_rr_pkt.common is just the memcpy
       source used by the target function). */
    pjmedia_rtcp_session sess;
    memset(&sess, 0, sizeof(sess));

    /* caller-supplied output buffer, heap-allocated to EXACTLY the
       capacity advertised via `length` -- a fully spec-compliant caller. */
    void *buf = malloc(BUF_LEN);
    if (!buf) { free(filebuf); return 1; }
    pj_size_t length = BUF_LEN;

    pj_status_t rc = pjmedia_rtcp_fb_build_sli(&sess, buf, &length, sli_cnt, sli_arr);

    free(buf);
    free(filebuf);
    fprintf(stderr, "rc=%d sli_cnt=%u length_out=%zu\n", rc, sli_cnt, (size_t)length);
    return 0;
}
