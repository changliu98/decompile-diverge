/*
 * cve_barebone direct-call harness for ffmpeg / sdp_parse_fmtp_config_h264
 * (libavformat/rtpdec_h264.c)
 *
 * Bug (fixed by c42a1388a6d1bfd8001bf6a4241d8ca27e49326d): in the
 * "sprop-parameter-sets" branch the vulnerable code does
 *     if (value[strlen(value) - 1] == ',')
 * without first checking value is non-empty. When value == "" (an empty,
 * heap-allocated string), strlen(value) == 0 and the code reads
 * value[(size_t)0 - 1] == value[-1], one byte BEFORE the heap allocation ->
 * heap-buffer-underflow READ (CWE-125). The fix adds `*value == 0 ||`
 * before the strlen indexing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- minimal real type defs (names/fields copied from the real ffmpeg
 * headers; only the members sdp_parse_fmtp_config_h264 itself touches). ---- */

typedef struct AVFormatContext AVFormatContext; /* opaque: only ever passed through */

/* libavcodec/avcodec.h: struct AVCodecParameters { ...; uint8_t *extradata;
 * int extradata_size; ...; } */
typedef struct AVCodecParameters {
    uint8_t *extradata;
    int      extradata_size;
} AVCodecParameters;

/* libavformat/avformat.h: typedef struct AVStream { ...; AVCodecParameters
 * *codecpar; ...; } AVStream; */
typedef struct AVStream {
    AVCodecParameters *codecpar;
} AVStream;

/* libavformat/rtpdec_h264.c: struct PayloadContext { ... } (verbatim). */
struct PayloadContext {
    uint8_t profile_idc;
    uint8_t profile_iop;
    uint8_t level_idc;
    int packetization_mode;
};
typedef struct PayloadContext PayloadContext;

/* libavutil/log.h */
#define AV_LOG_ERROR    16
#define AV_LOG_WARNING  24
#define AV_LOG_DEBUG    48

/* Real av_log() just formats+prints through the AVClass in avcl; for the
 * harness we only need it to not crash / not touch avcl, since s == NULL. */
static void av_log(void *avcl, int level, const char *fmt, ...)
{
    (void)avcl; (void)level; (void)fmt;
}

/* libavutil/mem.c: av_freep() frees *arg and NULLs it out (verbatim shape). */
static void av_freep(void *arg)
{
    void **p = (void **)arg;
    if (p && *p) {
        free(*p);
        *p = NULL;
    }
}

/* verbatim callee from libavformat/rtpdec_h264.c (on the "profile-level-id"
 * path, not the crash path, but real code so that path stays faithful). */
static void parse_profile_level_id(AVFormatContext *s,
                                   PayloadContext *h264_data,
                                   const char *value)
{
    char buffer[3];
    uint8_t profile_idc;
    uint8_t profile_iop;
    uint8_t level_idc;

    buffer[0]   = value[0];
    buffer[1]   = value[1];
    buffer[2]   = '\0';
    profile_idc = strtol(buffer, NULL, 16);
    buffer[0]   = value[2];
    buffer[1]   = value[3];
    profile_iop = strtol(buffer, NULL, 16);
    buffer[0]   = value[4];
    buffer[1]   = value[5];
    level_idc   = strtol(buffer, NULL, 16);

    av_log(s, AV_LOG_DEBUG,
           "RTP Profile IDC: %x Profile IOP: %x Level: %x\n",
           profile_idc, profile_iop, level_idc);
    h264_data->profile_idc = profile_idc;
    h264_data->profile_iop = profile_iop;
    h264_data->level_idc   = level_idc;
}

/* ff_h264_parse_sprop_parameter_sets() is called AFTER the vulnerable
 * value[strlen(value)-1] read, so it is off the crash path (incidental).
 * The real implementation needs av_base64_decode()/av_realloc() from
 * libavutil, which drag in far more of ffmpeg than this harness wants; this
 * minimal, safe stand-in preserves the (AVFormatContext*, uint8_t**, int*,
 * const char*) contract and the "allocate + report success" shape used by
 * the caller, without touching value[-1] or any OOB memory itself. */
static int ff_h264_parse_sprop_parameter_sets(AVFormatContext *s,
                                       uint8_t **data_ptr, int *size_ptr,
                                       const char *value)
{
    size_t len = strlen(value);
    uint8_t *buf = (uint8_t *)malloc(len + 16);
    (void)s;
    if (!buf)
        return -12; /* -ENOMEM */
    memset(buf, 0, len + 16);
    memcpy(buf, value, len);
    *data_ptr = buf;
    *size_ptr = (int)len;
    return 0;
}

/* ---- target function: byte-for-byte from
 * data_cve/cve_f41f1084/target/original_function.c. The noinline attribute
 * is harness scaffolding (kept OUTSIDE the copied bytes) so -O1 cannot fold
 * the single call site in main() into it and hide the frame from ASAN. ---- */
__attribute__((noinline))
static int sdp_parse_fmtp_config_h264(AVFormatContext *s,
                                      AVStream *stream,
                                      PayloadContext *h264_data,
                                      const char *attr, const char *value)
{
    AVCodecParameters *par = stream->codecpar;

    if (!strcmp(attr, "packetization-mode")) {
        av_log(s, AV_LOG_DEBUG, "RTP Packetization Mode: %d\n", atoi(value));
        h264_data->packetization_mode = atoi(value);
        /*
         * Packetization Mode:
         * 0 or not present: Single NAL mode (Only nals from 1-23 are allowed)
         * 1: Non-interleaved Mode: 1-23, 24 (STAP-A), 28 (FU-A) are allowed.
         * 2: Interleaved Mode: 25 (STAP-B), 26 (MTAP16), 27 (MTAP24), 28 (FU-A),
         *                      and 29 (FU-B) are allowed.
         */
        if (h264_data->packetization_mode > 1)
            av_log(s, AV_LOG_ERROR,
                   "Interleaved RTP mode is not supported yet.\n");
    } else if (!strcmp(attr, "profile-level-id")) {
        if (strlen(value) == 6)
            parse_profile_level_id(s, h264_data, value);
    } else if (!strcmp(attr, "sprop-parameter-sets")) {
        int ret;
        if (value[strlen(value) - 1] == ',') {
            av_log(s, AV_LOG_WARNING, "Missing PPS in sprop-parameter-sets, ignoring\n");
            return 0;
        }
        par->extradata_size = 0;
        av_freep(&par->extradata);
        ret = ff_h264_parse_sprop_parameter_sets(s, &par->extradata,
                                                 &par->extradata_size, value);
        av_log(s, AV_LOG_DEBUG, "Extradata set to %p (size: %d)\n",
               par->extradata, par->extradata_size);
        return ret;
    }
    return 0;
}

/* ---- driver: read argv[1] into a heap buffer, use its bytes to build the
 * (attr, value) arguments and call the target directly. ---- */

int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    FILE *f = fopen(argv[1], "rb");
    if (!f)
        return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long fsz = ftell(f);
    if (fsz < 0) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }
    if (fsz < 1) { fclose(f); return 0; }

    uint8_t *filebuf = (uint8_t *)malloc((size_t)fsz);
    if (!filebuf) { fclose(f); return 0; }
    size_t rd = fread(filebuf, 1, (size_t)fsz, f);
    fclose(f);
    if (rd < 1) { free(filebuf); return 0; }

    uint8_t mode = filebuf[0];
    size_t vlen = rd - 1;

    /* value is its OWN heap allocation, sized exactly vlen+1 (payload bytes
     * + NUL) so ASAN places a redzone immediately before it -- an empty
     * value ("") still gets a real 1-byte heap allocation, and value[-1]
     * lands squarely in that redzone. */
    char *value = (char *)malloc(vlen + 1);
    if (!value) { free(filebuf); return 0; }
    if (vlen > 0)
        memcpy(value, filebuf + 1, vlen);
    value[vlen] = '\0';
    free(filebuf);

    const char *attr;
    switch (mode % 4) {
        case 0: attr = "packetization-mode"; break;
        case 1: attr = "profile-level-id"; break;
        case 2: attr = "sprop-parameter-sets"; break;
        default: attr = "unknown-attr"; break;
    }

    AVCodecParameters par;
    memset(&par, 0, sizeof(par));
    AVStream stream;
    stream.codecpar = &par;
    PayloadContext h264_data;
    memset(&h264_data, 0, sizeof(h264_data));
    AVFormatContext *s = NULL;

    int ret = sdp_parse_fmtp_config_h264(s, &stream, &h264_data, attr, value);
    (void)ret;

    free(value);
    if (par.extradata)
        free(par.extradata);
    return 0;
}
