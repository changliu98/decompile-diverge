/* cve_barebone direct-call harness for cve_87da1e81 (ffmpeg, CVE-2024-36613)
 * Target: dxa_read_header  (libavformat/dxa.c)
 * Bug class: 32-bit signed-integer overflow (CWE-190).
 *
 * See the module docstring of scripts/gen_dc_cve_87da1e81.py for the full mechanism: an
 * off-by-one overflow guard lets `c->bpc + ast->codecpar->block_align` land exactly one past
 * INT_MAX when c->bpc == INT_MAX - block_align + 1, both fully attacker-controlled via the WAV
 * sub-chunk this function parses. UBSAN's signed-integer-overflow check catches it in place.
 *
 * This harness reimplements AVIOContext's avio_r8/avio_rl16/avio_rl32/avio_rb16/avio_rb32 as a
 * faithful reduction of libavformat/aviobuf.c for the ONE mode this driver ever uses: the whole
 * input file is preloaded into a single heap buffer up front (there is no real packet I/O) --
 * exactly the `read_packet == NULL` case aviobuf.c's own fill_buffer() already special-cases
 * ("can't fill the buffer without read_packet, just set EOF if appropriate"). avio_rl16/
 * avio_rl32/avio_rb16/avio_rb32 are copied byte-for-byte from aviobuf.c (pure compositions of
 * avio_r8, no I/O of their own to reduce); avio_seek/avio_tell/avio_skip/avio_feof are reduced
 * to that same whole-buffer-resident case (real aviobuf.c's general form additionally handles
 * growing/refilling/reverse-seeking a streaming buffer, unreachable once the buffer holds the
 * entire file). ff_get_wav_header (libavformat/riffdec.c) is reduced to the one shape this
 * harness ever feeds it (big_endian=0, id != 0x0165): same field read order/endianness as the
 * real function (id, channels, sample_rate, bitrate, block_align, bits_per_coded_sample,
 * cbSize), consuming exactly `size` bytes net so pb's position after the call matches the real
 * function (dxa_read_header's later 'data'-chunk search depends on that position).
 * avformat_new_stream/avpriv_set_pts_info/av_reduce/av_rescale/av_log are incidental
 * scaffolding stubs -- none sit on the overflow line; av_reduce/av_rescale/avpriv_set_pts_info
 * only run AFTER the would-be overflow site (safe-path inputs only), so their exact numerics
 * don't matter, they just must not crash on their own.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 \
 *         -fsanitize=signed-integer-overflow -fno-sanitize-recover=signed-integer-overflow \
 *         harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

/* ---- real macros (libavutil/macros.h + libavutil/error.h, verbatim) ---- */
#define MKTAG(a,b,c,d)   ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#define FFERRTAG(a, b, c, d) (-(int)MKTAG(a, b, c, d))
#define AVERROR(e) (-(e))
#define AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A')
#define AV_TIME_BASE 1000000

#define AV_LOG_ERROR 16
#define AV_LOG_WARNING 24
#define AV_LOG_DEBUG 48
static void av_log(void *avcl, int level, const char *fmt, ...) { (void)avcl; (void)level; (void)fmt; }

/* ---- real enums (libavutil/avutil.h / libavcodec/codec_id.h; names verbatim, reduced to the
 * members this call graph actually assigns). ---- */
enum AVMediaType { AVMEDIA_TYPE_UNKNOWN = -1, AVMEDIA_TYPE_VIDEO = 0, AVMEDIA_TYPE_AUDIO = 1 };
enum AVCodecID { AV_CODEC_ID_NONE = 0, AV_CODEC_ID_DXA = 86016 };
typedef struct AVCodec AVCodec; /* opaque; dxa_read_header only ever passes NULL for this */

/* ---- AVCodecParameters: REDUCED to the fields dxa_read_header/ff_get_wav_header touch (real
 * names/types, codec_par.h). The real struct carries ~35 more fields (extradata, ch_layout,
 * bit_rate, profile/level, color/chroma metadata, ...) this call graph never reads or writes. */
typedef struct AVCodecParameters {
    enum AVMediaType codec_type;
    enum AVCodecID   codec_id;
    int              width;
    int              height;
    int              sample_rate;
    int              block_align;
} AVCodecParameters;

/* ---- AVStream: REDUCED to the one field used (real name, avformat.h). ---- */
typedef struct AVStream {
    AVCodecParameters *codecpar;
} AVStream;

/* ---- AVIOContext: REDUCED to the fields (real names, avio.h / aviobuf.c's internal
 * FFIOContext) this harness's whole-buffer-preloaded avio_* implementation needs: `buffer`/
 * `buf_ptr`/`buf_end` bound the (one and only, fully resident) input; `eof_reached` mirrors the
 * real flag. The real struct also carries write-side state, a read_packet/seek callback pair,
 * a checksum hook, packet-size hints, etc -- none reachable once read_packet == NULL and the
 * whole file is already sitting in `buffer`. ---- */
typedef struct AVIOContext {
    unsigned char *buffer;
    unsigned char *buf_ptr;
    unsigned char *buf_end;
    int eof_reached;
} AVIOContext;

/* ---- AVFormatContext: REDUCED to the fields dxa_read_header touches (real names,
 * avformat.h). ---- */
typedef struct AVFormatContext {
    void        *priv_data;
    AVIOContext *pb;
    int64_t      start_time;
    int64_t      duration;
} AVFormatContext;

/* ---- DXAContext: byte-for-byte VERBATIM (libavformat/dxa.c:31-38 -- this function's own
 * private-data struct, real field names/order/types, not reduced). ---- */
typedef struct DXAContext {
    int frames;
    int has_sound;
    int bpc;
    uint32_t bytes_left;
    int64_t wavpos, vidpos;
    int readvid;
} DXAContext;

/* ================= avio_* -- faithful reduction of libavformat/aviobuf.c for the
 * whole-buffer-preloaded (read_packet == NULL) mode ================= */

static int avio_r8(AVIOContext *s)
{
    /* real avio_r8 calls fill_buffer() when buf_ptr>=buf_end; fill_buffer's own comment for
     * this exact mode: "can't fill the buffer without read_packet, just set EOF if
     * appropriate" -- sets eof_reached and returns without moving buf_ptr, so avio_r8 falls
     * through to its own `return 0;`. */
    if (s->buf_ptr >= s->buf_end) { s->eof_reached = 1; return 0; }
    return *s->buf_ptr++;
}

/* avio_rl16/avio_rl32/avio_rb16/avio_rb32 bodies copied byte-for-byte from
 * libavformat/aviobuf.c -- they only ever call avio_r8, no I/O of their own to reduce. */
static unsigned int avio_rl16(AVIOContext *s)
{
    unsigned int val;
    val = avio_r8(s);
    val |= avio_r8(s) << 8;
    return val;
}
static unsigned int avio_rl32(AVIOContext *s)
{
    unsigned int val;
    val = avio_rl16(s);
    val |= avio_rl16(s) << 16;
    return val;
}
static unsigned int avio_rb16(AVIOContext *s)
{
    unsigned int val;
    val = avio_r8(s) << 8;
    val |= avio_r8(s);
    return val;
}
static unsigned int avio_rb32(AVIOContext *s)
{
    unsigned int val;
    val = avio_rb16(s) << 16;
    val |= avio_rb16(s);
    return val;
}

/* avio_seek: reduced to the real function's "in-buffer" fast path (aviobuf.c's first branch,
 * `offset1 >= 0 && offset1 <= buffer_size` -> `s->buf_ptr = s->buffer + offset1`), the ONLY
 * path reachable once the whole file is resident (real `pos` == `buffer_size` always here, so
 * real `pos_for_offset1 = s->pos - buffer_size` == 0 and `offset1 == offset` identically).
 * Only SEEK_SET/SEEK_CUR are used anywhere on dxa_read_header's call path. An out-of-buffer
 * request degrades to EOF (matches "avio_feof() reports true past the loaded data") instead of
 * forming an out-of-bounds pointer. */
static int64_t avio_seek(AVIOContext *s, int64_t offset, int whence)
{
    int64_t buffer_size = s->buf_end - s->buffer;
    if (whence == SEEK_CUR) {
        int64_t cur = s->buf_ptr - s->buffer;
        if (offset == 0) return cur;
        offset += cur;
    }
    if (offset < 0) return AVERROR(EINVAL);
    if (offset <= buffer_size) {
        s->buf_ptr = s->buffer + offset;
        s->eof_reached = 0;
    } else {
        s->buf_ptr = s->buf_end;
        s->eof_reached = 1;
    }
    return offset;
}
/* real avio_tell/avio_skip are literally `return avio_seek(s, 0, SEEK_CUR);` /
 * `return avio_seek(s, offset, SEEK_CUR);` (avio.h/aviobuf.c) -- copied verbatim. */
static int64_t avio_tell(AVIOContext *s) { return avio_seek(s, 0, SEEK_CUR); }
static int64_t avio_skip(AVIOContext *s, int64_t offset) { return avio_seek(s, offset, SEEK_CUR); }

static int avio_feof(AVIOContext *s)
{
    if (s->buf_ptr >= s->buf_end) s->eof_reached = 1;
    return s->eof_reached;
}

/* ================= incidental callee stubs (none sit on the overflow line) ================= */

/* ff_get_wav_header (libavformat/riffdec.c), reduced to the one shape this harness ever
 * constructs (big_endian == 0, id != 0x0165 -- the WAVEFORMATEXTENSIBLE/extradata/ADPCM-table
 * branches are unreachable input this harness never crafts). Reads the SAME fields in the SAME
 * order/endianness as the real function -- id, channels, sample_rate, bitrate, block_align,
 * bits_per_coded_sample, then (size>=18) cbSize -- and consumes exactly `size` bytes net, so
 * pb's position after the call matches the real function. `par->block_align` is the field the
 * overflow actually pivots on. */
static int ff_get_wav_header(void *logctx, AVIOContext *pb, AVCodecParameters *par,
                              int size, int big_endian)
{
    (void)logctx; (void)big_endian;
    if (size < 14)
        return AVERROR_INVALIDDATA;
    par->codec_type = AVMEDIA_TYPE_AUDIO;
    (void)avio_rl16(pb);              /* id (unused by dxa_read_header) */
    (void)avio_rl16(pb);              /* channels (unused) */
    par->sample_rate = avio_rl32(pb);
    (void)avio_rl32(pb);              /* byte rate (unused) */
    par->block_align = avio_rl16(pb);
    int consumed = 14;
    if (size != 14) {
        (void)avio_rl16(pb);          /* bits_per_coded_sample (unused) */
        consumed = 16;
        if (size >= 18) {
            int cb = avio_rl16(pb);   /* cbSize */
            int rem = size - 18;
            consumed = 18;
            if (cb > rem) cb = rem;
            if (cb > 0) { avio_skip(pb, cb); consumed += cb; rem -= cb; }
            if (rem > 0) { avio_skip(pb, rem); consumed += rem; }
        }
    }
    if (size > consumed) avio_skip(pb, size - consumed);
    return 0;
}

/* avformat_new_stream (libavformat/avformat.c): reduced to what dxa_read_header needs from it
 * -- a live AVStream with an allocated codecpar; the real function also threads it onto
 * s->streams[]/s->nb_streams, sets ->index/->id, etc, none of which dxa_read_header reads back
 * through `s`. */
static AVStream *avformat_new_stream(AVFormatContext *s, const AVCodec *c)
{
    (void)s; (void)c;
    AVStream *st = (AVStream *)calloc(1, sizeof(AVStream));
    if (!st) return NULL;
    st->codecpar = (AVCodecParameters *)calloc(1, sizeof(AVCodecParameters));
    if (!st->codecpar) { free(st); return NULL; }
    return st;
}

/* avpriv_set_pts_info: only touches time-base/pts-wrap fields dxa_read_header never reads
 * back -- no-op stub. */
static void avpriv_set_pts_info(AVStream *s, int pts_wrap_bits, unsigned int num, unsigned int den)
{
    (void)s; (void)pts_wrap_bits; (void)num; (void)den;
}

/* av_reduce (libavutil/mathematics.c): standard Euclidean fraction reduction; only reached
 * AFTER the would-be overflow site (safe-path inputs only), so exact numerics don't matter --
 * it just must terminate cleanly for the small values this harness ever passes it. */
static int av_reduce(int *dst_num, int *dst_den, int64_t num, int64_t den, int64_t max)
{
    if (den < 0) { num = -num; den = -den; }
    if (num < 0) num = -num;
    if (den == 0) { *dst_num = 0; *dst_den = 1; return 1; }
    int64_t a = num, b = den;
    while (b) { int64_t t = a % b; a = b; b = t; }
    int64_t g = a ? a : 1;
    int64_t n = num / g, d = den / g;
    if (n > max) n = max;
    if (d > max) d = max;
    if (d == 0) d = 1;
    *dst_num = (int)n;
    *dst_den = (int)d;
    return 1;
}

/* av_rescale (libavutil/mathematics.c): a*b/c with overflow-safe evaluation (real
 * implementation uses a 64x64->128-bit muldiv on overflow; __int128 here is exact for every
 * value this harness's safe path ever passes -- frames <= 65535, num/den from av_reduce
 * above). Only reached after the overflow site. */
static int64_t av_rescale(int64_t a, int64_t b, int64_t c)
{
    if (c == 0) return 0;
    return (int64_t)(((__int128)a * (__int128)b) / (__int128)c);
}

/* ================= TARGET (VERBATIM, byte-for-byte target/original_function.c) =================
 * noinline (+ called through a volatile function pointer below) purely so it keeps its own
 * stack frame in the UBSAN/ASAN backtrace -- does not touch the function's own bytes. */
__attribute__((noinline))
static int dxa_read_header(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    DXAContext *c = s->priv_data;
    AVStream *st, *ast;
    uint32_t tag;
    int32_t fps;
    int w, h;
    int num, den;
    int flags;
    int ret;

    tag = avio_rl32(pb);
    if (tag != MKTAG('D', 'E', 'X', 'A'))
        return AVERROR_INVALIDDATA;
    flags = avio_r8(pb);
    c->frames = avio_rb16(pb);
    if(!c->frames){
        av_log(s, AV_LOG_ERROR, "File contains no frames ???\n");
        return AVERROR_INVALIDDATA;
    }

    fps = avio_rb32(pb);
    if(fps > 0){
        den = 1000;
        num = fps;
    }else if (fps < 0 && fps > INT_MIN){
        den = 100000;
        num = -fps;
    }else{
        den = 10;
        num = 1;
    }
    w = avio_rb16(pb);
    h = avio_rb16(pb);
    c->has_sound = 0;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    // Parse WAV data header
    if(avio_rl32(pb) == MKTAG('W', 'A', 'V', 'E')){
        uint32_t size, fsize;
        c->has_sound = 1;
        size = avio_rb32(pb);
        c->vidpos = avio_tell(pb) + size;
        avio_skip(pb, 16);
        fsize = avio_rl32(pb);

        ast = avformat_new_stream(s, NULL);
        if (!ast)
            return AVERROR(ENOMEM);
        ret = ff_get_wav_header(s, pb, ast->codecpar, fsize, 0);
        if (ret < 0)
            return ret;
        if (ast->codecpar->sample_rate > 0)
            avpriv_set_pts_info(ast, 64, 1, ast->codecpar->sample_rate);
        // find 'data' chunk
        while(avio_tell(pb) < c->vidpos && !avio_feof(pb)){
            tag = avio_rl32(pb);
            fsize = avio_rl32(pb);
            if(tag == MKTAG('d', 'a', 't', 'a')) break;
            avio_skip(pb, fsize);
        }
        c->bpc = (fsize + (int64_t)c->frames - 1) / c->frames;
        if(ast->codecpar->block_align) {
            if (c->bpc > INT_MAX - ast->codecpar->block_align + 1)
                return AVERROR_INVALIDDATA;
            c->bpc = ((c->bpc + ast->codecpar->block_align - 1) / ast->codecpar->block_align) * ast->codecpar->block_align;
        }
        c->bytes_left = fsize;
        c->wavpos = avio_tell(pb);
        avio_seek(pb, c->vidpos, SEEK_SET);
    }

    /* now we are ready: build format streams */
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id   = AV_CODEC_ID_DXA;
    st->codecpar->width      = w;
    st->codecpar->height     = h;
    av_reduce(&den, &num, den, num, (1UL<<31)-1);
    avpriv_set_pts_info(st, 33, num, den);
    /* flags & 0x80 means that image is interlaced,
     * flags & 0x40 means that image has double height
     * either way set true height
     */
    if(flags & 0xC0){
        st->codecpar->height >>= 1;
    }
    c->readvid = !c->has_sound;
    c->vidpos  = avio_tell(pb);
    s->start_time = 0;
    s->duration = av_rescale(c->frames, AV_TIME_BASE * (int64_t)num, den);
    av_log(s, AV_LOG_DEBUG, "%d frame(s)\n",c->frames);

    return 0;
}
/* ==== end verbatim target function ==== */

/* ---- driver -------------------------------------------------------------------------------
 * Input format (attacker-controlled file, read into a HEAP buffer): a fixed 69-byte record,
 * modelled directly on the real DXA header dxa_read_header parses:
 *   [0:4)   "DEXA"                          tag (must match, else immediate return)
 *   [4:5)   flags                            (u8; kept 0 here -- 0xC0 bits are cosmetic height
 *                                             halving, irrelevant to the overflow)
 *   [5:7)   frames                           (BE u16, >=1 -- guarded nonzero)
 *   [7:11)  fps                              (BE i32; kept small positive)
 *   [11:13) w                                (BE u16)
 *   [13:15) h                                (BE u16)
 *   [15:19) "WAVE"                           tag (must match to enter the sound branch)
 *   [19:23) size                             (BE u32 -> c->vidpos = tell()+size, kept large
 *                                             enough that the 'data' chunk below is found
 *                                             while tell() < vidpos)
 *   [23:39) 16 bytes filler                  (avio_skip(pb,16) in the real function; contents
 *                                             never read)
 *   [39:43) fsize                            (LE u32 -> ff_get_wav_header's `size` param;
 *                                             fixed 18 = a plain WAVEFORMATEX with cbSize=0)
 *   [43:45) wav id                           (LE u16, != 0x0165)
 *   [45:47) wav channels                     (LE u16, unused)
 *   [47:51) wav sample_rate                  (LE u32)
 *   [51:55) wav byte rate                    (LE u32, unused)
 *   [55:57) wav block_align                  (LE u16) -- THE second lever of the trigger
 *   [57:59) wav bits_per_coded_sample         (LE u16, unused)
 *   [59:61) wav cbSize                       (LE u16, kept 0 -- no WAVEFORMATEXTENSIBLE/extradata)
 *   [61:65) "data"                            tag (must match on the FIRST loop iteration)
 *   [65:69) data-chunk fsize                  (LE u32) -- THE first lever of the trigger; this
 *                                             is the `fsize` that feeds `c->bpc = (fsize +
 *                                             frames - 1) / frames`
 *
 * TRIGGER (0..24): frames=1 (so c->bpc == data-chunk fsize exactly), block_align = B (varies
 * per input), data-chunk fsize = T = INT_MAX - B + 1 (the exact boundary the off-by-one guard
 * fails to reject). `c->bpc + block_align` then evaluates to T + B = INT_MAX + 1 -- UBSAN
 * signed-integer-overflow, aborting inside dxa_read_header's own body.
 * SAFE (25..49): frames in [2,26], block_align either 0 (skips the whole guarded branch) or a
 * small nonzero value, data-chunk fsize small (~500-800) -- c->bpc stays a two/three-digit
 * number, nowhere near the overflow boundary; the function completes and returns 0 cleanly.
 */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 64; }
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
    long fsz = ftell(fp);
    if (fsz < 0) { fclose(fp); return 64; }
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }

    size_t n = (size_t)fsz;
    uint8_t *buf = (uint8_t *)malloc(n ? n : 1);   /* HEAP input, ASAN-guarded */
    if (!buf) { fclose(fp); return 64; }
    size_t got = n ? fread(buf, 1, n, fp) : 0;
    fclose(fp);
    if (got != n) { free(buf); return 64; }

    AVIOContext pbctx;
    memset(&pbctx, 0, sizeof(pbctx));
    pbctx.buffer  = buf;
    pbctx.buf_ptr = buf;
    pbctx.buf_end = buf + n;      /* exact length -- avio_r8 never reads past this */

    DXAContext dxactx;
    memset(&dxactx, 0, sizeof(dxactx));

    AVFormatContext fmt;
    memset(&fmt, 0, sizeof(fmt));
    fmt.priv_data = &dxactx;
    fmt.pb        = &pbctx;

    /* volatile function pointer: forbids inlining dxa_read_header into main() so it keeps its
     * own frame in the backtrace. Same argument/semantics as a direct call. */
    int (*volatile vb_call)(AVFormatContext *) = dxa_read_header;
    int ret = vb_call(&fmt);
    (void)ret;

    /* Only reached on a SAFE run (a triggering run aborts inside the overflow line above). */
    free(buf);
    return 0;
}
