/*
 * Direct-call ASAN harness for CVE fixed by ffmpeg commit
 * ca09d8a0dcd82e3128e62463231296aaf63ae6f7 ("avcodec/jpegxl_parser: Fix integer
 * overflow in skip_boxes()").
 *
 * Bug: in libavcodec/jpegxl_parser.c, skip_boxes() accumulates an ISOBMFF box
 * "size" (attacker-controlled, up to 2^64-1) into ctx->skip, which is a plain
 * `int`:
 *
 *     ctx->skip += size;
 *
 * The addition is performed in 64-bit (usual arithmetic conversions promote
 * `ctx->skip` to uint64_t), but the *store* back into the 32-bit `int` field
 * truncates the value. A crafted box size can therefore make ctx->skip wrap
 * to a small NEGATIVE int. skip_boxes() itself never re-derives a pointer
 * from ctx->skip after that (it only accumulates it across loop iterations,
 * using the *local* GetByteContext for further reads), so the corruption is
 * benign until skip_boxes() is invoked AGAIN on the same JXLParseContext
 * (exactly how the real caller, jpegxl_parse()/try_parse(), uses it across
 * successive calls before ctx->skip is reset). On that second call:
 *
 *     if (ctx->skip > buf_size)              // -8 > buf_size is FALSE -> passes
 *         return AVERROR_BUFFER_TOO_SMALL;
 *     buf      += ctx->skip;                 // buf - 8  (walks BEFORE the buffer)
 *     buf_size -= ctx->skip;                 // buf_size + 8 (end pointer unchanged)
 *     bytestream2_init(&gb, buf, buf_size);
 *     ...
 *     bytestream2_peek_le16(&gb)              // reads *(buf - 8) -> OOB READ
 *
 * The fix adds `|| size > INT_MAX - ctx->skip` to the invalid-size guard so
 * the accumulation can never overflow `ctx->skip` in the first place.
 *
 * This harness calls the REAL, byte-for-byte skip_boxes() TWICE against the
 * SAME (heap-allocated, zero-initialized) JXLParseContext, exactly mirroring
 * the two-call pattern the real parser exercises across parse invocations:
 *   - call #1 parses a crafted ISOBMFF box header out of a first heap buffer
 *     and (for triggering inputs) overflows ctx->skip to a small negative
 *     value;
 *   - call #2 re-enters skip_boxes() on a SECOND, independently malloc()'d
 *     heap buffer, whose start ASAN has surrounded with a redzone; if
 *     ctx->skip is corrupted, call #2 reads a few bytes to the LEFT of that
 *     buffer -> ASan heap-buffer-overflow READ (CWE-125).
 *
 * Everything skip_boxes() touches (the JXLParseContext.skip field, the
 * GetByteContext type + bytestream2_* accessors, the AV_R{B,L}{16,32,64}
 * byte-order readers, FFMIN, the AVERROR_* / FF_JPEGXL_*_SIGNATURE_LE
 * constants) is reproduced here with its REAL name and REAL behavior,
 * copied/ported verbatim from libavutil/{intreadwrite,error,macros}.h,
 * libavcodec/{bytestream.h,jpegxl.h} in data_cve/cve_a809f261/source_code.
 * JXLParseContext itself is trimmed to just the one field skip_boxes()
 * actually touches (`int skip`) -- the real struct also embeds ParseContext/
 * JXLCodestream, which skip_boxes() never references.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- libavutil/macros.h (verbatim) ---- */
#define MKTAG(a,b,c,d)   ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))

/* ---- libavutil/error.h (verbatim, only the two tags skip_boxes returns) ---- */
#define FFERRTAG(a, b, c, d) (-(int)MKTAG(a, b, c, d))
#define AVERROR_BUFFER_TOO_SMALL   FFERRTAG( 'B','U','F','S')
#define AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A')

/* ---- libavcodec/jpegxl.h (verbatim) ---- */
#define FF_JPEGXL_CODESTREAM_SIGNATURE_LE 0x0aff
#define FF_JPEGXL_CONTAINER_SIGNATURE_LE 0x204c584a0c000000

/* ---- libavutil/intreadwrite.h, portable fallback path (verbatim) ---- */
#define AV_RB32(x)                                \
    (((uint32_t)((const uint8_t*)(x))[0] << 24) |    \
               (((const uint8_t*)(x))[1] << 16) |    \
               (((const uint8_t*)(x))[2] <<  8) |    \
                ((const uint8_t*)(x))[3])
#define AV_RB64(x)                                   \
    (((uint64_t)((const uint8_t*)(x))[0] << 56) |       \
     ((uint64_t)((const uint8_t*)(x))[1] << 48) |       \
     ((uint64_t)((const uint8_t*)(x))[2] << 40) |       \
     ((uint64_t)((const uint8_t*)(x))[3] << 32) |       \
     ((uint64_t)((const uint8_t*)(x))[4] << 24) |       \
     ((uint64_t)((const uint8_t*)(x))[5] << 16) |       \
     ((uint64_t)((const uint8_t*)(x))[6] <<  8) |       \
      (uint64_t)((const uint8_t*)(x))[7])
#define AV_RL16(x)                           \
    ((((const uint8_t*)(x))[1] << 8) |          \
      ((const uint8_t*)(x))[0])
#define AV_RL64(x)                                   \
    (((uint64_t)((const uint8_t*)(x))[7] << 56) |       \
     ((uint64_t)((const uint8_t*)(x))[6] << 48) |       \
     ((uint64_t)((const uint8_t*)(x))[5] << 40) |       \
     ((uint64_t)((const uint8_t*)(x))[4] << 32) |       \
     ((uint64_t)((const uint8_t*)(x))[3] << 24) |       \
     ((uint64_t)((const uint8_t*)(x))[2] << 16) |       \
     ((uint64_t)((const uint8_t*)(x))[1] <<  8) |       \
      (uint64_t)((const uint8_t*)(x))[0])

/* ---- libavcodec/bytestream.h (verbatim behavior, only the functions
 * skip_boxes() calls: init / get_bytes_left / skip / get_be32 / get_be64 /
 * peek_le16 / peek_le64. Bodies match the DEF() macro expansion + the
 * hand-written functions in the real header exactly. ---- */
typedef struct GetByteContext {
    const uint8_t *buffer, *buffer_end, *buffer_start;
} GetByteContext;

static inline void bytestream2_init(GetByteContext *g, const uint8_t *buf, int buf_size)
{
    g->buffer       = buf;
    g->buffer_start = buf;
    g->buffer_end   = buf + buf_size;
}

static inline int bytestream2_get_bytes_left(GetByteContext *g)
{
    return g->buffer_end - g->buffer;
}

static inline void bytestream2_skip(GetByteContext *g, unsigned int size)
{
    g->buffer += FFMIN(g->buffer_end - g->buffer, size);
}

static inline unsigned int bytestream2_get_be32u(GetByteContext *g)
{
    unsigned int v = AV_RB32(g->buffer);
    g->buffer += 4;
    return v;
}
static inline unsigned int bytestream2_get_be32(GetByteContext *g)
{
    if (g->buffer_end - g->buffer < 4) {
        g->buffer = g->buffer_end;
        return 0;
    }
    return bytestream2_get_be32u(g);
}

static inline uint64_t bytestream2_get_be64u(GetByteContext *g)
{
    uint64_t v = AV_RB64(g->buffer);
    g->buffer += 8;
    return v;
}
static inline uint64_t bytestream2_get_be64(GetByteContext *g)
{
    if (g->buffer_end - g->buffer < 8) {
        g->buffer = g->buffer_end;
        return 0;
    }
    return bytestream2_get_be64u(g);
}

static inline unsigned int bytestream2_peek_le16u(GetByteContext *g)
{
    return AV_RL16(g->buffer);
}
static inline unsigned int bytestream2_peek_le16(GetByteContext *g)
{
    if (g->buffer_end - g->buffer < 2)
        return 0;
    return bytestream2_peek_le16u(g);
}

static inline uint64_t bytestream2_peek_le64u(GetByteContext *g)
{
    return AV_RL64(g->buffer);
}
static inline uint64_t bytestream2_peek_le64(GetByteContext *g)
{
    if (g->buffer_end - g->buffer < 8)
        return 0;
    return bytestream2_peek_le64u(g);
}

/* ---- libavcodec/jpegxl_parser.c: JXLParseContext, trimmed to the one field
 * skip_boxes() references (real name + real type: `int skip;`). ---- */
typedef struct JXLParseContext {
    int skip;
} JXLParseContext;

/* =====================================================================
 * skip_boxes() -- copied VERBATIM, byte-for-byte, from
 * data_cve/cve_a809f261/target/original_function.c
 * ===================================================================== */
static int skip_boxes(JXLParseContext *ctx, const uint8_t *buf, int buf_size)
{
    GetByteContext gb;

    if (ctx->skip > buf_size)
        return AVERROR_BUFFER_TOO_SMALL;

    buf += ctx->skip;
    buf_size -= ctx->skip;
    bytestream2_init(&gb, buf, buf_size);

    while (1) {
        uint64_t size;
        int head_size = 4;

        if (bytestream2_peek_le16(&gb) == FF_JPEGXL_CODESTREAM_SIGNATURE_LE)
            break;
        if (bytestream2_peek_le64(&gb) == FF_JPEGXL_CONTAINER_SIGNATURE_LE)
            break;

        if (bytestream2_get_bytes_left(&gb) < 8)
            return AVERROR_BUFFER_TOO_SMALL;

        size = bytestream2_get_be32(&gb);
        if (size == 1) {
            if (bytestream2_get_bytes_left(&gb) < 12)
                return AVERROR_BUFFER_TOO_SMALL;
            size = bytestream2_get_be64(&gb);
            head_size = 12;
        }
        if (!size)
            return AVERROR_INVALIDDATA;
        /* invalid ISOBMFF size */
        if (size <= head_size + 4)
            return AVERROR_INVALIDDATA;

        ctx->skip += size;
        bytestream2_skip(&gb, size - head_size);
        if (bytestream2_get_bytes_left(&gb) <= 0)
            return AVERROR_BUFFER_TOO_SMALL;
    }

    return 0;
}

/* =====================================================================
 * main() -- drives skip_boxes() exactly the way the real caller does:
 * two successive calls sharing one JXLParseContext. The input file supplies
 * both calls' buffers back to back:
 *   bytes [0, 16)    -> call #1 buffer (heap, 16 bytes)
 *   bytes [16, end)  -> call #2 buffer (heap, remaining bytes)
 * If the file is shorter than 16 bytes it is zero-padded for call #1 and
 * call #2 gets an empty (but still separately malloc'd) buffer.
 * ===================================================================== */
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
    long flen = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (flen < 0) flen = 0;

    unsigned char *filebuf = malloc((size_t)flen > 0 ? (size_t)flen : 1);
    if (!filebuf) { fclose(f); return 1; }
    size_t nread = flen > 0 ? fread(filebuf, 1, (size_t)flen, f) : 0;
    fclose(f);
    (void)nread;

    /* call #1 buffer: fixed 16 bytes, zero-padded, heap-allocated */
    const int CALL1_SIZE = 16;
    unsigned char *buf1 = malloc(CALL1_SIZE);
    if (!buf1) { free(filebuf); return 1; }
    memset(buf1, 0, CALL1_SIZE);
    {
        long n1 = flen < CALL1_SIZE ? flen : CALL1_SIZE;
        if (n1 > 0)
            memcpy(buf1, filebuf, (size_t)n1);
    }

    /* call #2 buffer: the remainder of the file, independently malloc'd
     * (so ASAN gives it its own redzone) */
    long remain = flen - CALL1_SIZE;
    size_t buf2_size = remain > 0 ? (size_t)remain : 0;
    unsigned char *buf2 = malloc(buf2_size > 0 ? buf2_size : 1);
    if (!buf2) { free(filebuf); free(buf1); return 1; }
    if (buf2_size > 0)
        memcpy(buf2, filebuf + CALL1_SIZE, buf2_size);

    free(filebuf);

    JXLParseContext *ctx = calloc(1, sizeof(JXLParseContext));
    if (!ctx) { free(buf1); free(buf2); return 1; }

    int r1 = skip_boxes(ctx, buf1, CALL1_SIZE);
    (void)r1;

    /* second call: buf_size passed matches the REAL size of the buf2
     * allocation, exactly like the real caller passes ctx->pc.index (the
     * actual accumulated-buffer length) -- if ctx->skip was corrupted by
     * call #1, this walks buf2's start pointer backward past its redzone. */
    int r2 = skip_boxes(ctx, buf2, (int)buf2_size);
    (void)r2;

    free(buf1);
    free(buf2);
    free(ctx);
    return 0;
}
