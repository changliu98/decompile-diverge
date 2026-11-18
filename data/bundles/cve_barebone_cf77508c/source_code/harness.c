/* cve_cf77508c (CVE-2024-22860) direct-call harness for ffmpeg's jpegxl_anim_read_packet
 * (libavformat/jpegxl_anim_dec.c).
 *
 * jpegxl_anim_read_packet() does:
 *
 *     size = avio_size(pb);                          // int64_t, from the I/O layer
 *     if (size < 0) return size;
 *     if (size == 0) size = 4096;
 *     if (ctx->initial && size < ctx->initial->size)
 *         size = ctx->initial->size;
 *     ret = av_new_packet(pkt, size);                 // <-- size implicitly truncated int64_t->int here
 *     ...
 *     if (ctx->initial) {
 *         offset = ctx->initial->size;
 *         memcpy(pkt->data, ctx->initial->data, offset);   // <-- WRITE into the (possibly truncated) buffer
 *         av_buffer_unref(&ctx->initial);
 *     }
 *
 * avio_size() reports the size of the underlying resource (e.g. an HTTP Content-Length, or
 * any custom AVIOContext whose `seek(..., AVSEEK_SIZE)` callback answers it) -- a value that is
 * NOT guaranteed to fit in 32 bits and is NOT tied to how many bytes are actually readable.
 * av_new_packet() takes a plain `int size`, so when the 64-bit `size` exceeds INT_MAX the call
 * silently truncates it to its low 32 bits before allocating -- e.g. a reported size of
 * 0x100000000 (4294967296, > INT_MAX) truncates to 0, so av_new_packet() allocates a packet
 * with (about) zero usable bytes. But the *comparison* two lines above,
 * `size < ctx->initial->size`, is done on the untruncated 64-bit value, so it correctly judges
 * the (huge) reported size to already cover `ctx->initial->size` and skips the bump-up that
 * would otherwise have grown the allocation to fit. The result: `ctx->initial->size` bytes get
 * memcpy'd into a packet buffer sized from the truncated (near-zero) value -- a heap buffer
 * overflow WRITE (CWE-787) entirely inside jpegxl_anim_read_packet's own body. The fix
 * (commit d2e897469) rejects `size > INT_MAX` outright before any of this can happen.
 *
 * To isolate jpegxl_anim_read_packet we replace the real (buffered, protocol-backed)
 * AVIOContext with a minimal stand-in whose avio_size() returns an attacker/harness-controlled
 * int64_t independent of the small backing buffer avio_read() actually serves from -- exactly
 * mirroring the real seek(AVSEEK_SIZE) decoupling above -- and reimplement av_new_packet() with
 * the SAME `int size` parameter (so the int64_t->int truncation the bug depends on happens the
 * same way, driven purely by C's own argument-passing rules) and the same
 * `size < 0 || size >= INT_MAX - AV_INPUT_BUFFER_PADDING_SIZE` reject-guard packet_alloc() uses.
 *
 * argv[1] layout (all little-endian, heap-loaded):
 *   bytes  0..7  int64_t reported_size  -- what our avio_size() stub returns
 *   bytes  8..11 uint32_t initial_len_raw -- 0 => ctx->initial stays NULL; else (mod 8192) is
 *                the byte length of a heap-allocated ctx->initial AVBufferRef installed before
 *                the call (its *content* is irrelevant to the bug -- only its *size* matters,
 *                and it is always allocated to exactly that many bytes, so the memcpy's READ
 *                side is always in-bounds; only the WRITE side, sized off `reported_size`, can
 *                overflow)
 *   bytes 12..   "source" bytes avio_read() may hand back in the non-overflowing paths
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

/* ---- libavutil/error.h, real macro ---- */
#define AVERROR(e) (-(e))

/* ---- libavcodec/defs.h, real name+value ---- */
#define AV_INPUT_BUFFER_PADDING_SIZE 64

/* ---- libavutil/buffer.h AVBufferRef, real field names/types (the internal ref-counted
 * `AVBuffer *buffer` bookkeeping is not touched by jpegxl_anim_read_packet and is omitted;
 * our stand-in AVBufferRefs are single-owner). ---- */
typedef struct AVBufferRef {
    uint8_t *data;
    size_t   size;
} AVBufferRef;

static void av_buffer_unref(AVBufferRef **buf) {
    if (!buf || !*buf)
        return;
    free((*buf)->data);
    free(*buf);
    *buf = NULL;
}

/* ---- minimal AVIOContext stand-in: a small backing buffer for avio_read() plus an
 * independently-controlled `reported_size` standing in for the real seek(AVSEEK_SIZE) result
 * avio_size() forwards verbatim (see file header). ---- */
typedef struct AVIOContext {
    const uint8_t *src;
    size_t src_size;
    size_t pos;
    int64_t reported_size;
} AVIOContext;

static int64_t avio_size(AVIOContext *s) {
    return s->reported_size;
}

static int avio_read(AVIOContext *s, unsigned char *buf, int size) {
    if (size <= 0)
        return 0;
    size_t avail = (s->pos < s->src_size) ? (s->src_size - s->pos) : 0;
    size_t n = ((size_t)size < avail) ? (size_t)size : avail;
    if (n > 0) {
        memcpy(buf, s->src + s->pos, n);
        s->pos += n;
    }
    return (int)n;
}

/* ---- libavcodec/packet.h AVPacket, real field names/types, trimmed to the two fields
 * jpegxl_anim_read_packet touches. ---- */
typedef struct AVPacket {
    uint8_t *data;
    int size;
} AVPacket;

/* ---- libavcodec/avpacket.c av_new_packet()/packet_alloc(), reproduced with the SAME `int
 * size` parameter (so the caller's int64_t->int truncation happens via ordinary C argument
 * passing, exactly as in the real build) and the same reject-guard; the real
 * av_buffer_realloc(buf, size + AV_INPUT_BUFFER_PADDING_SIZE) is a plain heap allocation of
 * exactly that many bytes here. ---- */
static int av_new_packet(AVPacket *pkt, int size) {
    if (size < 0 || size >= INT_MAX - AV_INPUT_BUFFER_PADDING_SIZE)
        return AVERROR(EINVAL);
    uint8_t *data = (uint8_t *)malloc((size_t)size + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!data)
        return AVERROR(ENOMEM);
    memset(data + size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    pkt->data = data;
    pkt->size = size;
    return 0;
}

/* ---- libavformat/jpegxl_anim_dec.c JXLAnimDemuxContext, copied verbatim. ---- */
typedef struct JXLAnimDemuxContext {
    AVBufferRef *initial;
} JXLAnimDemuxContext;

/* ---- minimal AVFormatContext: only the two fields jpegxl_anim_read_packet accesses
 * (s->priv_data, s->pb). ---- */
typedef struct AVFormatContext {
    void *priv_data;
    AVIOContext *pb;
} AVFormatContext;

/* ==== FUNCTION: jpegxl_anim_read_packet -- pasted byte-for-byte from
 * data_cve/cve_cf77508c/target/original_function.c ==== */
static int jpegxl_anim_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    JXLAnimDemuxContext *ctx = s->priv_data;
    AVIOContext *pb = s->pb;
    int ret;
    int64_t size;
    size_t offset = 0;

    size = avio_size(pb);
    if (size < 0)
        return size;
    if (size == 0)
        size = 4096;

    if (ctx->initial && size < ctx->initial->size)
        size = ctx->initial->size;

    ret = av_new_packet(pkt, size);
    if (ret < 0)
        return ret;

    if (ctx->initial) {
        offset = ctx->initial->size;
        memcpy(pkt->data, ctx->initial->data, offset);
        av_buffer_unref(&ctx->initial);
    }

    ret = avio_read(pb, pkt->data + offset, size - offset);
    if (ret < 0)
        return ret;
    if (ret < size - offset)
        pkt->size = ret + offset;

    return 0;
}
/* ==== END FUNCTION ==== */

static uint64_t rd_le64(const uint8_t *p) {
    uint64_t v = 0;
    for (int i = 7; i >= 0; i--)
        v = (v << 8) | p[i];
    return v;
}

static uint32_t rd_le32(const uint8_t *p) {
    uint32_t v = 0;
    for (int i = 3; i >= 0; i--)
        v = (v << 8) | p[i];
    return v;
}

int main(int argc, char **argv) {
    if (argc < 2) return 0;
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) return 0;
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 0; }
    long fsz = ftell(fp);
    if (fsz < 0) { fclose(fp); return 0; }
    fseek(fp, 0, SEEK_SET);

    /* heap-allocate the whole input file, ASAN-guarded. */
    uint8_t *filebuf = (uint8_t *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
    if (!filebuf) { fclose(fp); return 0; }
    size_t rd = fread(filebuf, 1, (size_t)fsz, fp);
    fclose(fp);

    if (rd < 12) { free(filebuf); return 0; }

    int64_t reported_size = (int64_t)rd_le64(filebuf);
    uint32_t initial_len_raw = rd_le32(filebuf + 8);

    const uint8_t *src_bytes = filebuf + 12;
    size_t src_len = rd - 12;

    JXLAnimDemuxContext ctx;
    ctx.initial = NULL;

    uint32_t init_len = initial_len_raw % 8192u; /* 0 => no initial buffer */
    if (init_len > 0) {
        AVBufferRef *ref = (AVBufferRef *)malloc(sizeof(AVBufferRef));
        if (!ref) { free(filebuf); return 0; }
        ref->data = (uint8_t *)malloc(init_len);
        if (!ref->data) { free(ref); free(filebuf); return 0; }
        /* content is irrelevant to the bug -- fill from whatever source bytes we have,
         * cycling/zero-padding as needed; this buffer is ALWAYS sized exactly init_len, so
         * the memcpy's READ side is always in-bounds. */
        for (uint32_t i = 0; i < init_len; i++)
            ref->data[i] = src_len ? src_bytes[i % src_len] : 0;
        ref->size = init_len;
        ctx.initial = ref;
    }

    AVIOContext io;
    io.src = src_bytes;
    io.src_size = src_len;
    io.pos = 0;
    io.reported_size = reported_size;

    AVFormatContext s;
    s.priv_data = &ctx;
    s.pb = &io;

    AVPacket pkt;
    pkt.data = NULL;
    pkt.size = 0;

    int ret = jpegxl_anim_read_packet(&s, &pkt);
    (void)ret;

    /* only reached on non-crashing runs */
    if (ctx.initial)
        av_buffer_unref(&ctx.initial);
    free(pkt.data);
    free(filebuf);
    return 0;
}
