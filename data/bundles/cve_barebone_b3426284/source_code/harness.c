/* cve_barebone direct-call harness for ffmpeg parse_video_info
 * (libavformat/asfdec_o.c) — CVE fix commit 2b46ebdbff1d8dec7a3d8ea280a612b91a582869.
 *
 * Bug: size_bmp (uint32_t) = FFMAX(size_asf, size_bmp_from_bmp_header) is attacker
 * controlled via the BMP-header "biSize" field. When size_bmp is within ~64 of
 * UINT32_MAX, `st->codecpar->extradata_size = size_bmp - BMP_HEADER_SIZE` wraps to a
 * SMALL NEGATIVE int (implementation-defined narrowing of the unsigned subtraction
 * result into a 32-bit signed field). `av_malloc(extradata_size + AV_INPUT_BUFFER_
 * PADDING_SIZE)` then receives a small POSITIVE size and succeeds, but the very next
 * line, `memset(extradata + extradata_size, 0, AV_INPUT_BUFFER_PADDING_SIZE)`, uses
 * the same negative extradata_size as a pointer offset -> writes 64 zero bytes
 * starting well BEFORE the small heap allocation: a heap-buffer-overflow WRITE
 * (CWE-787), which is exactly the fault class the upstream size_bmp upper-bound
 * check now guards against.
 *
 * This harness re-implements only the plumbing parse_video_info needs (a minimal
 * memory-backed AVIOContext + the handful of struct fields/macros it touches) so it
 * links standalone with -lm. parse_video_info itself, and its real callee
 * ff_get_bmp_header, are reproduced with their real field/type names; the crash lives
 * entirely inside parse_video_info's own body, unmodified.
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

/* ---- minimal memory-backed AVIOContext + accessors (real read-order/LE semantics,
 * real EOF-returns-0 behaviour of avio_rl16/avio_rl32; no I/O, just a cursor over the
 * harness's input buffer) ---- */
typedef struct AVIOContext {
    const uint8_t *buf;
    size_t size;
    size_t pos;
} AVIOContext;

static uint32_t avio_rl32(AVIOContext *pb)
{
    uint32_t v = 0;
    for (int i = 0; i < 4; i++) {
        uint8_t b = (pb->pos < pb->size) ? pb->buf[pb->pos] : 0;
        if (pb->pos < pb->size) pb->pos++;
        v |= ((uint32_t)b) << (8 * i);
    }
    return v;
}

static uint16_t avio_rl16(AVIOContext *pb)
{
    uint16_t v = 0;
    for (int i = 0; i < 2; i++) {
        uint8_t b = (pb->pos < pb->size) ? pb->buf[pb->pos] : 0;
        if (pb->pos < pb->size) pb->pos++;
        v |= ((uint16_t)b) << (8 * i);
    }
    return v;
}

static void avio_skip(AVIOContext *pb, int64_t offset)
{
    if (offset > 0) {
        size_t n = (size_t)offset;
        pb->pos = (pb->pos + n <= pb->size) ? pb->pos + n : pb->size;
    }
}

static int avio_read(AVIOContext *pb, unsigned char *buf, int size)
{
    if (size <= 0)
        return 0;
    size_t remain = (pb->pos < pb->size) ? (pb->size - pb->pos) : 0;
    size_t n = ((size_t)size < remain) ? (size_t)size : remain;
    if (n > 0) {
        memcpy(buf, pb->buf + pb->pos, n);
        pb->pos += n;
    }
    return (int)n;
}

/* ---- minimal AVCodecID / AVCodecTag (real names/shape, libavformat/internal.h) ---- */
typedef enum AVCodecID { AV_CODEC_ID_NONE = 0 } AVCodecID;

typedef struct AVCodecTag {
    enum AVCodecID id;
    unsigned int tag;
} AVCodecTag;

/* Real ff_codec_bmp_tags is a big FOURCC->codec table; an empty (sentinel-only)
 * table is a faithful stand-in for this harness's purposes since parse_video_info's
 * own crash does not depend on which codec_id the tag resolves to -- only that the
 * lookup returns AV_CODEC_ID_NONE for an unrecognised tag, exactly like the real
 * table does for any FOURCC not in it. */
static const AVCodecTag ff_codec_bmp_tags[] = {
    { AV_CODEC_ID_NONE, 0 }
};

/* ---- minimal AVCodecParameters / AVStream (real field names/types, subset used) ---- */
typedef struct AVCodecParameters {
    enum AVCodecID   codec_id;
    uint32_t         codec_tag;
    uint8_t         *extradata;
    int              extradata_size;
    int              bits_per_coded_sample;
    int              width;
    int              height;
} AVCodecParameters;

typedef struct AVStream {
    AVCodecParameters *codecpar;
} AVStream;

static int ff_get_bmp_header(AVIOContext *pb, AVStream *st, uint32_t *size)
{
    int tag1;
    uint32_t size_ = avio_rl32(pb);
    if (size)
        *size = size_;
    st->codecpar->width  = avio_rl32(pb);
    st->codecpar->height = (int32_t)avio_rl32(pb);
    avio_rl16(pb); /* planes */
    st->codecpar->bits_per_coded_sample = avio_rl16(pb); /* depth */
    tag1                                = avio_rl32(pb);
    avio_rl32(pb); /* ImageSize */
    avio_rl32(pb); /* XPelsPerMeter */
    avio_rl32(pb); /* YPelsPerMeter */
    avio_rl32(pb); /* ClrUsed */
    avio_rl32(pb); /* ClrImportant */
    return tag1;
}

static enum AVCodecID ff_codec_get_id(const AVCodecTag *tags, unsigned int tag)
{
    while (tags->id != AV_CODEC_ID_NONE) {
        if (tags->tag == tag)
            return tags->id;
        tags++;
    }
    return AV_CODEC_ID_NONE;
}

/* real macros/constants (libavutil/common.h, libavcodec/avcodec.h,
 * libavformat/asfdec_o.c, libavutil/error.h) */
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define AV_INPUT_BUFFER_PADDING_SIZE 64
#define BMP_HEADER_SIZE 40
#define AVERROR(e) (-(e))

/* faithful minimal av_malloc (libavutil/mem.c): same oversize guard
 * (`size > max_alloc_size - 32`, max_alloc_size defaults to INT_MAX), plain malloc
 * otherwise. */
static void *av_malloc(size_t size)
{
    static const size_t max_alloc_size = INT_MAX;
    if (size > max_alloc_size - 32)
        return NULL;
    return malloc(size);
}

/* ==== verbatim splice of data_cve/cve_b3426284/target/original_function.c ==== */
static int parse_video_info(AVIOContext *pb, AVStream *st)
{
    uint16_t size_asf; // ASF-specific Format Data size
    uint32_t size_bmp; // BMP_HEADER-specific Format Data size
    unsigned int tag;

    st->codecpar->width  = avio_rl32(pb);
    st->codecpar->height = avio_rl32(pb);
    avio_skip(pb, 1); // skip reserved flags
    size_asf = avio_rl16(pb);
    tag = ff_get_bmp_header(pb, st, &size_bmp);
    st->codecpar->codec_tag = tag;
    st->codecpar->codec_id  = ff_codec_get_id(ff_codec_bmp_tags, tag);
    size_bmp = FFMAX(size_asf, size_bmp);

    if (size_bmp > BMP_HEADER_SIZE) {
        int ret;
        st->codecpar->extradata_size  = size_bmp - BMP_HEADER_SIZE;
        if (!(st->codecpar->extradata = av_malloc(st->codecpar->extradata_size +
                                               AV_INPUT_BUFFER_PADDING_SIZE))) {
            st->codecpar->extradata_size = 0;
            return AVERROR(ENOMEM);
        }
        memset(st->codecpar->extradata + st->codecpar->extradata_size , 0,
               AV_INPUT_BUFFER_PADDING_SIZE);
        if ((ret = avio_read(pb, st->codecpar->extradata,
                             st->codecpar->extradata_size)) < 0)
            return ret;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;
    FILE *f = fopen(argv[1], "rb");
    if (!f)
        return 1;
    fseek(f, 0, SEEK_END);
    long fsz = ftell(f);
    if (fsz < 0) {
        fclose(f);
        return 1;
    }
    fseek(f, 0, SEEK_SET);

    /* heap-allocate the ASAN-guarded input buffer */
    uint8_t *filebuf = (uint8_t *)malloc(fsz > 0 ? (size_t)fsz : 1);
    if (!filebuf) {
        fclose(f);
        return 1;
    }
    size_t rd = fsz > 0 ? fread(filebuf, 1, (size_t)fsz, f) : 0;
    fclose(f);

    AVIOContext pb;
    pb.buf  = filebuf;
    pb.size = rd;
    pb.pos  = 0;

    AVCodecParameters codecpar;
    memset(&codecpar, 0, sizeof(codecpar));

    AVStream st;
    st.codecpar = &codecpar;

    int ret = parse_video_info(&pb, &st);
    (void)ret;

    free(codecpar.extradata);
    free(filebuf);
    return 0;
}
