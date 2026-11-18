/*
 * cve_125c2871 -- CVE-2017-11665 direct-call ASAN harness for ffmpeg's
 * ff_amf_get_field_value() (libavformat/rtmppkt.c), a heap-buffer-overflow
 * READ (CWE-125).
 *
 * Root cause (visible in target/original_function.c, unchanged; confirmed
 * against the fix diff ffcc82219cef0928bed2d558b19ef6ea35634130):
 *   the initial scan loop
 *       while (*data != AMF_DATA_TYPE_OBJECT && data < data_end) { ... }
 *   dereferences `*data` BEFORE checking `data < data_end` (C evaluates the
 *   left `&&` operand first). The fix wraps the whole function in a
 *   GetByteContext (bytestream2) and adds an explicit `if (data >= data_end)
 *   return -1;` guard up front -- proof the missing check is exactly this
 *   read-before-bounds-check. Any input that makes `data` reach `data_end`
 *   (either on entry, or after one iteration's `ff_amf_tag_size` fallback
 *   `len = data_end - data; data += len;`) then has its NEXT loop-condition
 *   check dereference one byte past the buffer -> heap-buffer-overflow READ,
 *   inside ff_amf_get_field_value's own body.
 *
 * This file assembles, self-contained (compiles+links with only -lm):
 *   1. the real AMFDataType enum, verbatim from libavformat/flv.h;
 *   2. GetByteContext + the bytestream2/bytestream primitives
 *      ff_amf_get_field_value's own callee `ff_amf_tag_size` (and its static
 *      helper amf_tag_skip) need, verbatim from libavcodec/bytestream.h
 *      (the DEF() macro is copied as-is and instantiated for byte/be16/be32/
 *      be64 -- the only widths amf_tag_skip uses), backed by the portable
 *      (non-unaligned-fast-path) AV_RB8/16/32/64 + AV_WB8/16/32/64 macros
 *      from libavutil/intreadwrite.h (copied verbatim from that header's
 *      `#else` / no-fast-unaligned branch -- purely mechanical big-endian
 *      byte reads, not project logic);
 *   3. FFMIN, verbatim from libavutil/common.h; av_assert0, a faithful
 *      abort-on-false stand-in for libavutil/avassert.h's real assertion
 *      macro (never actually triggered by any crafted input here -- see
 *      below); av_int2double + `union av_intfloat64`, verbatim from
 *      libavutil/intfloat.h; av_strlcpy, verbatim from libavutil/avstring.c
 *      (all real callees the switch-statement branches of
 *      ff_amf_get_field_value reference -- unreached by every crafted input
 *      in this corpus, since every one either crashes or returns cleanly
 *      before locating a matching field, but must still be present/real for
 *      the function to compile as-is);
 *   4. ff_amf_tag_size() and its static helper amf_tag_skip() -- REAL
 *      callees directly on the crash path (ff_amf_get_field_value's scan
 *      loop calls ff_amf_tag_size on every iteration) -- pasted verbatim
 *      from source_code/libavformat/rtmppkt.c;
 *   5. the target function ff_amf_get_field_value() pasted BYTE-FOR-BYTE
 *      from target/original_function.c (unchanged);
 *   6. main(): reads argv[1] into a HEAP buffer sized EXACTLY to the file
 *      length (malloc(sz), no padding -- data_end must sit precisely at the
 *      ASAN redzone boundary for the check-after-use bug above to fault),
 *      then calls ff_amf_get_field_value(data, data_end, "duration", dst,
 *      sizeof(dst)).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- libavutil/attributes.h (verbatim, gcc/clang branch) ---- */
#define av_always_inline __attribute__((always_inline)) inline

/* ---- libavutil/common.h (verbatim) ---- */
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))

/* ---- faithful stand-in for libavutil/avassert.h's av_assert0. Real
 * ff_amf_tag_size() only reaches this line on ITS success path (ret>=0 &&
 * bytes-left>0); every crafted input in this corpus makes ff_amf_tag_size
 * return -1 (either amf_tag_skip fails outright, or it succeeds but leaves
 * 0 bytes -- see the two ff_amf_tag_size checks below), so this is
 * unreached by construction, not by luck. ---- */
#define av_assert0(cond) do { if (!(cond)) { fprintf(stderr, "assertion failed: %s\n", #cond); abort(); } } while (0)

/* ---- libavutil/intreadwrite.h (verbatim, the portable/no-fast-unaligned
 * branch -- mechanical big-endian byte reads, not project logic) ---- */
#define AV_RB8(x)     (((const uint8_t*)(x))[0])
#define AV_WB8(p, d)  do { ((uint8_t*)(p))[0] = (d); } while(0)

#define AV_RB16(x)                           \
    ((((const uint8_t*)(x))[0] << 8) |          \
      ((const uint8_t*)(x))[1])
#define AV_WB16(p, val) do {                 \
        uint16_t d = (val);                     \
        ((uint8_t*)(p))[1] = (d);               \
        ((uint8_t*)(p))[0] = (d)>>8;            \
    } while(0)

#define AV_RB32(x)                                \
    (((uint32_t)((const uint8_t*)(x))[0] << 24) |    \
               (((const uint8_t*)(x))[1] << 16) |    \
               (((const uint8_t*)(x))[2] <<  8) |    \
                ((const uint8_t*)(x))[3])
#define AV_WB32(p, val) do {                 \
        uint32_t d = (val);                     \
        ((uint8_t*)(p))[3] = (d);               \
        ((uint8_t*)(p))[2] = (d)>>8;            \
        ((uint8_t*)(p))[1] = (d)>>16;           \
        ((uint8_t*)(p))[0] = (d)>>24;           \
    } while(0)

#define AV_RB64(x)                                   \
    (((uint64_t)((const uint8_t*)(x))[0] << 56) |       \
     ((uint64_t)((const uint8_t*)(x))[1] << 48) |       \
     ((uint64_t)((const uint8_t*)(x))[2] << 40) |       \
     ((uint64_t)((const uint8_t*)(x))[3] << 32) |       \
     ((uint64_t)((const uint8_t*)(x))[4] << 24) |       \
     ((uint64_t)((const uint8_t*)(x))[5] << 16) |       \
     ((uint64_t)((const uint8_t*)(x))[6] <<  8) |       \
      (uint64_t)((const uint8_t*)(x))[7])
#define AV_WB64(p, val) do {                 \
        uint64_t d = (val);                     \
        ((uint8_t*)(p))[7] = (d);               \
        ((uint8_t*)(p))[6] = (d)>>8;            \
        ((uint8_t*)(p))[5] = (d)>>16;           \
        ((uint8_t*)(p))[4] = (d)>>24;           \
        ((uint8_t*)(p))[3] = (d)>>32;           \
        ((uint8_t*)(p))[2] = (d)>>40;           \
        ((uint8_t*)(p))[1] = (d)>>48;           \
        ((uint8_t*)(p))[0] = (d)>>56;           \
    } while(0)

/* ---- libavutil/intfloat.h (verbatim) ---- */
union av_intfloat64 {
    uint64_t i;
    double   f;
};

static av_always_inline double av_int2double(uint64_t i)
{
    union av_intfloat64 v;
    v.i = i;
    return v.f;
}

/* ---- libavutil/avstring.c (verbatim) ---- */
size_t av_strlcpy(char *dst, const char *src, size_t size)
{
    size_t len = 0;
    while (++len < size && *src)
        *dst++ = *src++;
    if (len <= size)
        *dst = 0;
    return len + strlen(src) - 1;
}

/* ---- libavcodec/bytestream.h (verbatim GetByteContext + DEF() macro,
 * instantiated for the widths amf_tag_skip/ff_amf_tag_size use: byte, be16,
 * be32, be64) ---- */
typedef struct GetByteContext {
    const uint8_t *buffer, *buffer_end, *buffer_start;
} GetByteContext;

#define DEF(type, name, bytes, read, write)                                  \
static av_always_inline type bytestream_get_ ## name(const uint8_t **b)        \
{                                                                              \
    (*b) += bytes;                                                             \
    return read(*b - bytes);                                                   \
}                                                                              \
static av_always_inline void bytestream_put_ ## name(uint8_t **b,              \
                                                     const type value)         \
{                                                                              \
    write(*b, value);                                                          \
    (*b) += bytes;                                                             \
}                                                                              \
static av_always_inline type bytestream2_get_ ## name ## u(GetByteContext *g)  \
{                                                                              \
    return bytestream_get_ ## name(&g->buffer);                                \
}                                                                              \
static av_always_inline type bytestream2_get_ ## name(GetByteContext *g)       \
{                                                                              \
    if (g->buffer_end - g->buffer < bytes) {                                   \
        g->buffer = g->buffer_end;                                             \
        return 0;                                                              \
    }                                                                          \
    return bytestream2_get_ ## name ## u(g);                                   \
}

DEF(uint64_t,     be64, 8, AV_RB64, AV_WB64)
DEF(unsigned int, be32, 4, AV_RB32, AV_WB32)
DEF(unsigned int, be16, 2, AV_RB16, AV_WB16)
DEF(unsigned int, byte, 1, AV_RB8 , AV_WB8)

static av_always_inline void bytestream2_init(GetByteContext *g,
                                              const uint8_t *buf,
                                              int buf_size)
{
    av_assert0(buf_size >= 0);
    g->buffer       = buf;
    g->buffer_start = buf;
    g->buffer_end   = buf + buf_size;
}

static av_always_inline unsigned int bytestream2_get_bytes_left(GetByteContext *g)
{
    return g->buffer_end - g->buffer;
}

static av_always_inline void bytestream2_skip(GetByteContext *g,
                                              unsigned int size)
{
    g->buffer += FFMIN(g->buffer_end - g->buffer, size);
}

static av_always_inline int bytestream2_tell(GetByteContext *g)
{
    return (int)(g->buffer - g->buffer_start);
}

/* ==================================================================== *
 * libavformat/flv.h -- verbatim AMFDataType enum
 * ==================================================================== */
typedef enum {
    AMF_DATA_TYPE_NUMBER      = 0x00,
    AMF_DATA_TYPE_BOOL        = 0x01,
    AMF_DATA_TYPE_STRING      = 0x02,
    AMF_DATA_TYPE_OBJECT      = 0x03,
    AMF_DATA_TYPE_NULL        = 0x05,
    AMF_DATA_TYPE_UNDEFINED   = 0x06,
    AMF_DATA_TYPE_REFERENCE   = 0x07,
    AMF_DATA_TYPE_MIXEDARRAY  = 0x08,
    AMF_DATA_TYPE_OBJECT_END  = 0x09,
    AMF_DATA_TYPE_ARRAY       = 0x0a,
    AMF_DATA_TYPE_DATE        = 0x0b,
    AMF_DATA_TYPE_LONG_STRING = 0x0c,
    AMF_DATA_TYPE_UNSUPPORTED = 0x0d,
} AMFDataType;

/* ==================================================================== *
 * libavformat/rtmppkt.c -- verbatim real callees on the crash path
 * (ff_amf_get_field_value calls ff_amf_tag_size every scan iteration)
 * ==================================================================== */
static int amf_tag_skip(GetByteContext *gb)
{
    AMFDataType type;
    unsigned nb   = -1;
    int parse_key = 1;

    if (bytestream2_get_bytes_left(gb) < 1)
        return -1;

    type = bytestream2_get_byte(gb);
    switch (type) {
    case AMF_DATA_TYPE_NUMBER:
        bytestream2_get_be64(gb);
        return 0;
    case AMF_DATA_TYPE_BOOL:
        bytestream2_get_byte(gb);
        return 0;
    case AMF_DATA_TYPE_STRING:
        bytestream2_skip(gb, bytestream2_get_be16(gb));
        return 0;
    case AMF_DATA_TYPE_LONG_STRING:
        bytestream2_skip(gb, bytestream2_get_be32(gb));
        return 0;
    case AMF_DATA_TYPE_NULL:
        return 0;
    case AMF_DATA_TYPE_DATE:
        bytestream2_skip(gb, 10);
        return 0;
    case AMF_DATA_TYPE_ARRAY:
        parse_key = 0;
    case AMF_DATA_TYPE_MIXEDARRAY:
        nb = bytestream2_get_be32(gb);
    case AMF_DATA_TYPE_OBJECT:
        while (nb-- > 0 || type != AMF_DATA_TYPE_ARRAY) {
            int t;
            if (parse_key) {
                int size = bytestream2_get_be16(gb);
                if (!size) {
                    bytestream2_get_byte(gb);
                    break;
                }
                bytestream2_skip(gb, size);
            }
            t = amf_tag_skip(gb);
            if (t < 0 || bytestream2_get_bytes_left(gb) <= 0)
                return -1;
        }
        return 0;
    case AMF_DATA_TYPE_OBJECT_END:  return 0;
    default:                        return -1;
    }
}

int ff_amf_tag_size(const uint8_t *data, const uint8_t *data_end)
{
    GetByteContext gb;
    int ret;

    if (data >= data_end)
        return -1;

    bytestream2_init(&gb, data, data_end - data);

    ret = amf_tag_skip(&gb);
    if (ret < 0 || bytestream2_get_bytes_left(&gb) <= 0)
        return -1;
    av_assert0(bytestream2_tell(&gb) >= 0 && bytestream2_tell(&gb) <= data_end - data);
    return bytestream2_tell(&gb);
}

/* ==================================================================== *
 * TARGET FUNCTION -- verbatim from target/original_function.c (unchanged)
 * ==================================================================== */
int ff_amf_get_field_value(const uint8_t *data, const uint8_t *data_end,
                           const uint8_t *name, uint8_t *dst, int dst_size)
{
    int namelen = strlen(name);
    int len;

    while (*data != AMF_DATA_TYPE_OBJECT && data < data_end) {
        len = ff_amf_tag_size(data, data_end);
        if (len < 0)
            len = data_end - data;
        data += len;
    }
    if (data_end - data < 3)
        return -1;
    data++;
    for (;;) {
        int size = bytestream_get_be16(&data);
        if (!size)
            break;
        if (size < 0 || size >= data_end - data)
            return -1;
        data += size;
        if (size == namelen && !memcmp(data-size, name, namelen)) {
            switch (*data++) {
            case AMF_DATA_TYPE_NUMBER:
                snprintf(dst, dst_size, "%g", av_int2double(AV_RB64(data)));
                break;
            case AMF_DATA_TYPE_BOOL:
                snprintf(dst, dst_size, "%s", *data ? "true" : "false");
                break;
            case AMF_DATA_TYPE_STRING:
                len = bytestream_get_be16(&data);
                av_strlcpy(dst, data, FFMIN(len+1, dst_size));
                break;
            default:
                return -1;
            }
            return 0;
        }
        len = ff_amf_tag_size(data, data_end);
        if (len < 0 || len >= data_end - data)
            return -1;
        data += len;
    }
    return -1;
}
/* ==== end verbatim ==== */

/* ==================================================================== *
 * FDP driver
 *
 * Heap-allocate the raw file content EXACTLY (no slack): data = buf,
 * data_end = buf + n. `name` is a fixed, ordinary field name -- not
 * attacker-controlled and irrelevant to the bug (the crash lives entirely
 * in the initial scan loop, before any name comparison happens).
 * ==================================================================== */
int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f)
        return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* HEAP-allocate exactly `sz` bytes (including sz==0 -- ASAN's malloc(0)
     * always returns a valid, uniquely-redzoned pointer) so data_end sits
     * precisely on the redzone boundary. */
    uint8_t *buf = (uint8_t *)malloc((size_t)sz);
    if (sz > 0 && !buf) { fclose(f); return 0; }
    size_t n = sz > 0 ? fread(buf, 1, (size_t)sz, f) : 0;
    fclose(f);

    const uint8_t *data     = buf;
    const uint8_t *data_end = buf + n;
    const uint8_t *name     = (const uint8_t *)"duration";
    uint8_t dst[256];

    int ret = ff_amf_get_field_value(data, data_end, name, dst, sizeof(dst));
    fprintf(stderr, "ret=%d\n", ret);

    free(buf);
    return 0;
}
