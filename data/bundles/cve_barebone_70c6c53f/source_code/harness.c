/* cve_barebone direct-call harness for cve_70c6c53f (ffmpeg, CVE-2024-35369)
 * Target: parse_speex_extradata  (libavcodec/speexdec.c)
 * Bug class: 32-bit signed-integer overflow (CWE-190).
 *
 * fix_commit 0895ef0d6d6406ee6cd158fc4d47d80f201b8e9c adds a missing UPPER bound on
 * attacker-controlled `frame_size` before it is doubled (`frame_size *= 1 + (mode>0)`).
 * With mode>0 and frame_size >= 2^30, that multiply overflows a 32-bit signed int --
 * UB, caught here by UBSAN's signed-integer-overflow check. See the module docstring
 * of scripts/gen_dc_cve_70c6c53f.py for the full mechanism.
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

/* ---- real macros (libavutil/macros.h + libavutil/error.h, verbatim) ---- */
#define MKTAG(a,b,c,d)   ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#define FFERRTAG(a, b, c, d) (-(int)MKTAG(a, b, c, d))
#define AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A') /* speexdec.c uses this verbatim */

/* ---- real #defines (libavcodec/speexdec.c:64,69, verbatim) ---- */
#define SPEEX_NB_MODES 3
#define NB_FRAME_SIZE 160

/* ---- AVCodecContext: REDUCED to the one field parse_speex_extradata reads off it (real
 * field name/type, avcodec.h:468 `void *priv_data;`). The real struct carries ~150 more
 * fields of unrelated codec/stream metadata this function never touches. ---- */
typedef struct AVCodecContext {
    void *priv_data;
} AVCodecContext;

/* ---- SpeexContext: REDUCED to the 10 int32_t fields parse_speex_extradata actually
 * writes (real names/types/declared order, speexdec.c:239-260). The real struct also
 * carries `class`/`gb`(GetBitContext)/pkt_size/stereo/st[SPEEX_NB_MODES]/fdsp -- decoder
 * state this function never reads or writes. ---- */
typedef struct SpeexContext {
    int32_t version_id;
    int32_t rate;
    int32_t mode;
    int32_t bitstream_version;
    int32_t nb_channels;
    int32_t bitrate;
    int32_t frame_size;
    int32_t vbr;
    int32_t frames_per_packet;
    int32_t extra_headers;
} SpeexContext;

/* ---- real av_strnstr (libavutil/avstring.c, verbatim) ---- */
char *av_strnstr(const char *haystack, const char *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    if (!needle_len)
        return (char*)haystack;
    while (hay_length >= needle_len) {
        hay_length--;
        if (!memcmp(haystack, needle, needle_len))
            return (char*)haystack;
        haystack++;
    }
    return NULL;
}

/* ---- real bytestream_get_le32 (libavcodec/bytestream.h's DEF(unsigned int, le32, 4,
 * AV_RL32, AV_WL32) macro expansion, verbatim behavior: read LE32 at *b, then advance *b
 * by 4). AV_RL32 itself (libavutil/intreadwrite.h) is byte-order-correct on any host
 * regardless of alignment/endianness -- reproduced here via the always-correct
 * byte-composition form (the same value AV_RL32 computes, whichever internal path the
 * real macro takes on a given arch). ---- */
static inline uint32_t AV_RL32(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static inline unsigned int bytestream_get_le32(const uint8_t **b)
{
    (*b) += 4;
    return AV_RL32(*b - 4);
}

/* ================= TARGET (VERBATIM, byte-for-byte target/original_function.c) =================
 * noinline (+ called through a volatile function pointer below) purely so it keeps its own
 * stack frame in the UBSAN/ASAN backtrace -- does not touch the function's own bytes. */
__attribute__((noinline))
static int parse_speex_extradata(AVCodecContext *avctx,
    const uint8_t *extradata, int extradata_size)
{
    SpeexContext *s = avctx->priv_data;
    const uint8_t *buf = av_strnstr(extradata, "Speex   ", extradata_size);

    if (!buf)
        return AVERROR_INVALIDDATA;

    buf += 28;

    s->version_id = bytestream_get_le32(&buf);
    buf += 4;
    s->rate = bytestream_get_le32(&buf);
    if (s->rate <= 0)
        return AVERROR_INVALIDDATA;
    s->mode = bytestream_get_le32(&buf);
    if (s->mode < 0 || s->mode >= SPEEX_NB_MODES)
        return AVERROR_INVALIDDATA;
    s->bitstream_version = bytestream_get_le32(&buf);
    if (s->bitstream_version != 4)
        return AVERROR_INVALIDDATA;
    s->nb_channels = bytestream_get_le32(&buf);
    if (s->nb_channels <= 0 || s->nb_channels > 2)
        return AVERROR_INVALIDDATA;
    s->bitrate = bytestream_get_le32(&buf);
    s->frame_size = bytestream_get_le32(&buf);
    if (s->frame_size < NB_FRAME_SIZE << (s->mode > 0))
        return AVERROR_INVALIDDATA;
    s->frame_size *= 1 + (s->mode > 0);
    s->vbr = bytestream_get_le32(&buf);
    s->frames_per_packet = bytestream_get_le32(&buf);
    if (s->frames_per_packet <= 0 ||
        s->frames_per_packet > 64 ||
        s->frames_per_packet >= INT32_MAX / s->nb_channels / s->frame_size)
        return AVERROR_INVALIDDATA;
    s->extra_headers = bytestream_get_le32(&buf);

    return 0;
}
/* ==== end verbatim target function ==== */

/* ---- driver -------------------------------------------------------------------------------
 * Input format (attacker-controlled file, read into a HEAP buffer): a fixed 72-byte record,
 * modelled directly on the real Speex extradata header layout this function parses:
 *   [0:8)   "Speex   "                    (av_strnstr's match anchor, offset 0)
 *   [8:28)  20 bytes filler               (skipped by the real `buf += 28`)
 *   [28:32) version_id      (LE u32, unchecked)
 *   [32:36) 4 bytes filler                (skipped by the real extra `buf += 4`)
 *   [36:40) rate            (LE u32, must be > 0)
 *   [40:44) mode            (LE u32, must be in [0, SPEEX_NB_MODES); >0 to hit the doubling
 *                            branch that the fix commit bounds-checks)
 *   [44:48) bitstream_version (LE u32, must == 4)
 *   [48:52) nb_channels     (LE u32, must be in [1, 2])
 *   [52:56) bitrate         (LE u32, unchecked)
 *   [56:60) frame_size      (LE u32, must be >= NB_FRAME_SIZE<<(mode>0)=320) -- THE trigger
 *   [60:64) vbr             (LE u32, unchecked)
 *   [64:68) frames_per_packet (LE u32, must be in [1,64] and pass the divide-check)
 *   [68:72) extra_headers   (LE u32, unchecked)
 *
 * TRIGGER: mode=1, frame_size in [2^30, INT32_MAX] -> `frame_size *= 2` overflows a 32-bit
 * signed int (UBSAN signed-integer-overflow, execution aborts inside parse_speex_extradata
 * before any further field is read).
 * SAFE: mode=1, frame_size small (320..24320, comfortably < 2^30) -> doubling never
 * overflows; every later check passes (frames_per_packet=1) and the function returns 0
 * cleanly. File is always exactly 72 bytes so every real read in the function (including
 * the final extra_headers field, safe-path only) stays in-bounds of the heap allocation.
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
    uint8_t *extradata = (uint8_t *)malloc(n ? n : 1);  /* HEAP input, ASAN-guarded */
    if (!extradata) { fclose(fp); return 64; }
    size_t got = n ? fread(extradata, 1, n, fp) : 0;
    fclose(fp);
    if (got != n) { free(extradata); return 64; }

    SpeexContext s;
    memset(&s, 0, sizeof(s));
    AVCodecContext avctx;
    avctx.priv_data = &s;

    /* volatile function pointer: forbids inlining parse_speex_extradata into main() so it
     * keeps its own frame in the backtrace. Same arguments/semantics as a direct call. */
    int (*volatile vb_call)(AVCodecContext *, const uint8_t *, int) = parse_speex_extradata;
    int ret = vb_call(&avctx, extradata, (int)n);
    (void)ret;

    /* Only reached on a SAFE run (a triggering run aborts inside the multiply above). */
    free(extradata);
    return 0;
}
