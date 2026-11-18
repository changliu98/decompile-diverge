/* cve_13d96ac1 -- pjproject print_media_desc() SDP "m=" line overflow.
 *
 * The vulnerable function checks buf length only against media.slen +
 * transport.slen + 12 + 24 before writing the "m=<media> <port>[/<port_count>]
 * <transport>" prefix, but the subsequent per-format-string loop
 * (`for (i=0;i<m->desc.fmt_count;++i) { *p++=' '; pj_memcpy(p, fmt[i].ptr,
 * fmt[i].slen); p += fmt[i].slen; }`) writes an UNBOUNDED number of bytes
 * with NO check against `end` (buf+len) at all. Supplying a small output
 * buffer plus a handful of long/many "fmt" strings overflows the heap
 * buffer passed by the caller. The fix (commit 560a1346) adds an
 * `if (end-p > m->desc.fmt[i].slen)` guard around that loop and around the
 * trailing "\r\n" write.
 *
 * This harness constructs a pjmedia_sdp_media object directly from the
 * input file bytes and calls print_media_desc() on it in isolation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- minimal pjlib type defs (verbatim names/widths from pjlib/include/pj/types.h) ---- */
typedef int            pj_int32_t;
typedef unsigned int   pj_uint32_t;
typedef short          pj_int16_t;
typedef unsigned short pj_uint16_t;
typedef size_t         pj_size_t;
typedef long           pj_ssize_t;   /* non-PJ_WIN64 branch */
typedef int            pj_status_t;

/* pjlib/include/pj/types.h: struct pj_str_t */
struct pj_str_t
{
    char       *ptr;
    pj_ssize_t  slen;
};
typedef struct pj_str_t pj_str_t;

/* pjmedia/include/pjmedia/sdp.h limits */
#define PJMEDIA_MAX_SDP_FMT     32
#define PJMEDIA_MAX_SDP_BANDW   4
#define PJMEDIA_MAX_SDP_ATTR    (PJMEDIA_MAX_SDP_FMT*2 + 4)

/* Only pointers to these are used by print_media_desc's own body on the
 * crash path we exercise (m->conn stays NULL, bandw_count/attr_count stay
 * 0), so incomplete forward-declared structs suffice for the real type. */
struct pjmedia_sdp_conn
{
    pj_str_t    net_type;
    pj_str_t    addr_type;
    pj_str_t    addr;
};
typedef struct pjmedia_sdp_conn pjmedia_sdp_conn;

typedef struct pjmedia_sdp_bandw
{
    pj_str_t    modifier;
    pj_uint32_t value;
} pjmedia_sdp_bandw;

struct pjmedia_sdp_attr
{
    pj_str_t    name;
    pj_str_t    value;
};
typedef struct pjmedia_sdp_attr pjmedia_sdp_attr;

/* pjmedia/include/pjmedia/sdp.h: struct pjmedia_sdp_media (verbatim) */
struct pjmedia_sdp_media
{
    /** Media descriptor line ("m=" line) */
    struct
    {
	pj_str_t    media;		/**< Media type ("audio", "video")  */
	pj_uint16_t port;		/**< Port number.		    */
	unsigned    port_count;		/**< Port count, used only when >2  */
	pj_str_t    transport;		/**< Transport ("RTP/AVP")	    */
	unsigned    fmt_count;		/**< Number of formats.		    */
	pj_str_t    fmt[PJMEDIA_MAX_SDP_FMT];       /**< Media formats.	    */
    } desc;

    pjmedia_sdp_conn   *conn;		/**< Optional connection info.	    */
    unsigned	        bandw_count;	/**< Number of bandwidth info.	    */
    pjmedia_sdp_bandw  *bandw[PJMEDIA_MAX_SDP_BANDW]; /**< Bandwidth info.  */
    unsigned	        attr_count;	/**< Number of attributes.	    */
    pjmedia_sdp_attr   *attr[PJMEDIA_MAX_SDP_ATTR];   /**< Attributes.	    */

};
typedef struct pjmedia_sdp_media pjmedia_sdp_media;

/* pjlib/include/pj/string.h: pj_memcpy (verbatim body, memcpy wrapper) */
#define PJ_INLINE(t) static inline t
PJ_INLINE(void*) pj_memcpy(void *dst, const void *src, pj_size_t size)
{
    return memcpy(dst, src, size);
}

/* debug macro used by pj_utoa_pad; no-op stub (not part of the memory bug) */
#define PJ_CHECK_STACK()

/* pjlib/src/pj/string.c: pj_utoa / pj_utoa_pad (verbatim bodies) */
static int pj_utoa_pad( unsigned long val, char *buf, int min_dig, int pad)
{
    char *p;
    int len;

    PJ_CHECK_STACK();

    p = buf;
    do {
        unsigned long digval = (unsigned long) (val % 10);
        val /= 10;
        *p++ = (char) (digval + '0');
    } while (val > 0);

    len = (int)(p-buf);
    while (len < min_dig) {
	*p++ = (char)pad;
	++len;
    }
    *p-- = '\0';

    do {
        char temp = *p;
        *p = *buf;
        *buf = temp;
        --p;
        ++buf;
    } while (buf < p);

    return len;
}

static int pj_utoa(unsigned long val, char *buf)
{
    return pj_utoa_pad(val, buf, 0, 0);
}

/* pjmedia/src/pjmedia/sdp.c: print_connection_info / print_bandw / print_attr
 * are called from print_media_desc's body but are never reached on the path
 * we drive it through here (m->conn == NULL, bandw_count == 0,
 * attr_count == 0) -- minimal stubs so the translation unit links; they are
 * NOT on the crash path. */
static int print_connection_info( pjmedia_sdp_conn *c, char *buf, int len)
{
    (void)c; (void)buf; (void)len;
    return -1;
}

static pj_ssize_t print_bandw(const pjmedia_sdp_bandw *bandw, char *buf, pj_size_t len)
{
    (void)bandw; (void)buf; (void)len;
    return -1;
}

static pj_ssize_t print_attr(const pjmedia_sdp_attr *attr, char *buf, pj_size_t len)
{
    (void)attr; (void)buf; (void)len;
    return -1;
}

/* ==== BEGIN verbatim copy of data_cve/cve_13d96ac1/target/original_function.c ==== */
static int print_media_desc(const pjmedia_sdp_media *m, char *buf, pj_size_t len)
{
    char *p = buf;
    char *end = buf+len;
    unsigned i;
    int printed;

    /* check length for the "m=" line. */
    if (len < (pj_size_t)m->desc.media.slen+m->desc.transport.slen+12+24) {
	return -1;
    }
    *p++ = 'm';	    /* m= */
    *p++ = '=';
    pj_memcpy(p, m->desc.media.ptr, m->desc.media.slen);
    p += m->desc.media.slen;
    *p++ = ' ';
    printed = pj_utoa(m->desc.port, p);
    p += printed;
    if (m->desc.port_count > 1) {
	*p++ = '/';
	printed = pj_utoa(m->desc.port_count, p);
	p += printed;
    }
    *p++ = ' ';
    pj_memcpy(p, m->desc.transport.ptr, m->desc.transport.slen);
    p += m->desc.transport.slen;
    for (i=0; i<m->desc.fmt_count; ++i) {
	*p++ = ' ';
	pj_memcpy(p, m->desc.fmt[i].ptr, m->desc.fmt[i].slen);
	p += m->desc.fmt[i].slen;
    }
    *p++ = '\r';
    *p++ = '\n';

    /* print connection info, if present. */
    if (m->conn) {
	printed = print_connection_info(m->conn, p, (int)(end-p));
	if (printed < 0) {
	    return -1;
	}
	p += printed;
    }
    
    /* print optional bandwidth info. */
    for (i=0; i<m->bandw_count; ++i) {
	printed = (int)print_bandw(m->bandw[i], p, end-p);
	if (printed < 0) {
	    return -1;
	}
	p += printed;
    }

    /* print attributes. */
    for (i=0; i<m->attr_count; ++i) {
	printed = (int)print_attr(m->attr[i], p, end-p);
	if (printed < 0) {
	    return -1;
	}
	p += printed;
    }

    return (int)(p-buf);
}
/* ==== END verbatim copy of original_function.c ==== */

/*
 * main(): read argv[1] into a heap buffer, decode a small fixed layout out
 * of the first bytes into the fields of a pjmedia_sdp_media object, then
 * call print_media_desc() on a freshly heap-allocated output buffer whose
 * size is also attacker-controlled. All string fields (`media`, `transport`,
 * `fmt[i]`) point into a separate, generously-sized heap "content" buffer
 * (safe to read from), so any crash below can only come from
 * print_media_desc()'s OWN unchecked writes into the (small) output buffer.
 *
 * Input layout (all raw bytes, no endianness games -- everything is a
 * single byte or derived from one):
 *   [0]              out_len        -- size of the destination buffer passed to
 *                                       print_media_desc (0..255)
 *   [1]              fmt_count      -- number of desc.fmt[] entries (0..32, clamped)
 *   [2]              media_slen     -- desc.media.slen (0..64, clamped)
 *   [3]              transport_slen -- desc.transport.slen (0..64, clamped)
 *   [4]              port_lo        -- desc.port low byte
 *   [5]              port_count     -- desc.port_count (0..255)
 *   [6 .. 6+fmt_count-1]            -- per-fmt slen byte (0..255 each)
 *   [rest]                          -- ignored (content buffer is independently seeded)
 */
int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) { fprintf(stderr, "open failed\n"); return 1; }
    fseek(f, 0, SEEK_END);
    long fsz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (fsz < 6) fsz = 6;
    unsigned char *raw = (unsigned char*)malloc((size_t)fsz);
    if (!raw) { fclose(f); return 1; }
    memset(raw, 0x41, (size_t)fsz);
    fseek(f, 0, SEEK_SET);
    size_t got = fread(raw, 1, (size_t)fsz, f);
    fclose(f);
    (void)got;

    unsigned char b0 = raw[0];                     /* out_len */
    unsigned char b1 = raw[1];                      /* fmt_count raw */
    unsigned char b2 = raw[2];                      /* media_slen raw */
    unsigned char b3 = raw[3];                      /* transport_slen raw */
    unsigned char b4 = raw[4];                      /* port low byte */
    unsigned char b5 = raw[5];                      /* port_count */

    unsigned fmt_count = b1 % (PJMEDIA_MAX_SDP_FMT + 1);   /* 0..32 */
    long media_slen = b2 % 65;                              /* 0..64 */
    long transport_slen = b3 % 65;                           /* 0..64 */

    /* Big content buffer: every pj_str_t.ptr below points at its start, so
     * reads of up to `content_sz` bytes from offset 0 are always in-bounds
     * regardless of the slen values chosen -- reads never crash, only the
     * output buffer's bounded writes can. */
    size_t content_sz = 8192;
    char *content = (char*)malloc(content_sz);
    if (!content) return 1;
    for (size_t i = 0; i < content_sz; ++i) {
        content[i] = (char)('a' + (int)((raw[i % (size_t)fsz] + i) % 26));
    }

    pjmedia_sdp_media m;
    memset(&m, 0, sizeof(m));
    m.desc.media.ptr = content;
    m.desc.media.slen = media_slen;
    m.desc.port = (pj_uint16_t)b4;
    m.desc.port_count = (unsigned)b5;
    m.desc.transport.ptr = content;
    m.desc.transport.slen = transport_slen;
    m.desc.fmt_count = fmt_count;

    size_t off = 6;
    for (unsigned i = 0; i < fmt_count; ++i) {
        unsigned char sb = (off < (size_t)fsz) ? raw[off] : 0x40;
        off++;
        m.desc.fmt[i].ptr = content;
        m.desc.fmt[i].slen = (long)sb;   /* 0..255, deliberately unbounded by out_len */
    }
    m.conn = NULL;         /* never dereferenced: keeps print_connection_info off the path */
    m.bandw_count = 0;     /* keeps print_bandw off the path */
    m.attr_count = 0;      /* keeps print_attr off the path */

    pj_size_t out_len = (pj_size_t)b0;
    char *outbuf = (char*)malloc(out_len ? out_len : 1);
    if (!outbuf) return 1;

    int rc = print_media_desc(&m, outbuf, out_len);
    fprintf(stderr, "print_media_desc rc=%d out_len=%zu fmt_count=%u\n",
            rc, (size_t)out_len, fmt_count);

    free(outbuf);
    free(content);
    free(raw);
    return 0;
}
