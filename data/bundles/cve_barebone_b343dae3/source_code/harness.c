/* cve_barebone direct-call harness for cve_b343dae3 (ffmpeg)
 * Target: build_open_gop_key_points  (libavformat/mov.c, the exact text frozen in
 *   target/original_function.c)
 * Bug class: 32-bit unsigned-sum overflow -> undersized av_calloc() -> heap-buffer-
 *   overflow WRITE (CWE-787).
 *
 * fix_commit c953baa084607dd1d84c3bfcce3cf6a87c3e6e05 adds
 *   if (sc->ctts_data[i].count > INT_MAX - sc->sample_offsets_count) return AVERROR(ENOMEM);
 * inside the FIRST accumulation loop below (and the analogous guard on the second,
 * open_key_samples, block). Without it:
 *
 *   sc->sample_offsets_count = 0;                                  // int (signed)
 *   for (uint32_t i = 0; i < sc->ctts_count; i++)
 *       sc->sample_offsets_count += sc->ctts_data[i].count;        // ctts_data[i].count: unsigned int
 *   ...
 *   sc->sample_offsets = av_calloc(sc->sample_offsets_count, sizeof(*sc->sample_offsets));
 *   ...
 *   for (uint32_t i = 0; i < sc->ctts_count; i++)
 *       for (int j = 0; j < sc->ctts_data[i].count; j++)
 *            sc->sample_offsets[k++] = sc->ctts_data[i].duration;  // <-- OOB write here
 *
 * With two ctts entries whose individual `.count` (unsigned int) values are each
 * bounded (<=UINT32_MAX) but whose SUM wraps mod 2^32 to a small value that is still a
 * legal POSITIVE `int` (e.g. 0xFFFFFFF0 + 20 == 0x100000004 -> truncates to 4), the
 * accumulation loop leaves sc->sample_offsets_count == 4: av_calloc(4, 4) happily
 * allocates a 16-byte (4 x int32_t) buffer. But the SECOND loop re-reads the
 * individual (un-wrapped) sc->ctts_data[0].count == 0xFFFFFFF0 as its own `j` bound
 * (promoted to unsigned int, so ~4.29 BILLION iterations) and writes every one of them
 * into that 4-element buffer: ASAN traps the write the instant k reaches 4 (5th write),
 * long before the loop would ever finish on its own. A negative wrapped sum (e.g. a
 * single huge .count with the top bit set) instead makes av_calloc's own overflow-
 * checked size_mult() reject the request outright (nmemb sign-extends to a huge
 * size_t) -> clean AVERROR(ENOMEM), no crash -- this is why the harness targets the
 * "wraps to a small POSITIVE int" case specifically, not just "any large count".
 *
 * The crash fires inside the FIRST block, before get_sgpd_sync_index() is ever called
 * -- it is included verbatim anyway (real body, real HEVC_NAL_CRA_NUT value 21 from
 * libavcodec/hevc.h) purely so the translation unit compiles/links, and so the "safe,
 * full traversal" corpus inputs below can genuinely walk the rest of the function
 * (open_key_samples block + min_sample_duration scan) with legitimately small counts
 * and no overflow anywhere.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

/* ---- libavutil/macros.h, libavutil/error.h (verbatim) ---- */
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define AVERROR(e) (-(e))

/* ---- libavcodec/hevc.h (verbatim value) ---- */
#define HEVC_NAL_CRA_NUT 21

/* ---- minimal AVCodecID / AVCodecParameters / AVStream (real field names/types used
 * by build_open_gop_key_points; libavcodec/codec_par.h + libavformat/avformat.h). The
 * real AV_CODEC_ID_HEVC ordinal is elided -- build_open_gop_key_points only ever
 * compares st->codecpar->codec_id for equality against it, so any value distinct from
 * AV_CODEC_ID_NONE is behaviourally identical inside this self-contained harness. ---- */
typedef enum AVCodecID {
    AV_CODEC_ID_NONE = 0,
    AV_CODEC_ID_HEVC,
} AVCodecID;

typedef struct AVCodecParameters {
    enum AVCodecID codec_id;
} AVCodecParameters;

typedef struct AVStream {
    void *priv_data;
    AVCodecParameters *codecpar;
} AVStream;

/* ---- libavformat/isom.h (verbatim field shapes) ---- */
typedef struct MOVStts {
    unsigned int count;
    unsigned int duration;
} MOVStts;

typedef struct MOVCtts {
    unsigned int count;
    int duration;
} MOVCtts;

typedef struct MOVSbgp {
    unsigned int count;
    unsigned int index;
} MOVSbgp;

/* Minimal MOVStreamContext: real names/types, subset of libavformat/isom.h limited to
 * the fields build_open_gop_key_points (and its callee get_sgpd_sync_index) touch. */
typedef struct MOVStreamContext {
    unsigned int stts_count;
    MOVStts *stts_data;
    unsigned int ctts_count;
    MOVCtts *ctts_data;
    unsigned int sync_group_count;
    MOVSbgp *sync_group;
    uint8_t *sgpd_sync;
    uint32_t sgpd_sync_count;
    int32_t *sample_offsets;
    int sample_offsets_count;
    int *open_key_samples;
    int open_key_samples_count;
    uint32_t min_sample_duration;
} MOVStreamContext;

/* ---- libavutil/mem.c (faithful minimal ports: same overflow-checked size_mult(),
 * same malloc(0)-retry special case in av_malloc(); no alignment/poisoning paths,
 * which don't affect this bug) ---- */
static int vb_size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;
    if (__builtin_mul_overflow(a, b, &t))
        return AVERROR(EINVAL);
    *r = t;
    return 0;
}

static void *av_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr && !size) {
        size = 1;
        ptr = malloc(1);
    }
    return ptr;
}

static void *av_mallocz(size_t size)
{
    void *ptr = av_malloc(size);
    if (ptr)
        memset(ptr, 0, size);
    return ptr;
}

static void *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    if (vb_size_mult(nmemb, size, &result) < 0)
        return NULL;
    return av_mallocz(result);
}

static void av_free(void *ptr) { free(ptr); }

static void av_freep(void *arg)
{
    void *val;
    memcpy(&val, arg, sizeof(val));
    memcpy(arg, &(void *){ NULL }, sizeof(val));
    av_free(val);
}

/* ==== VERBATIM from data_cve/cve_b343dae3/target/original_function.c ====
 * (get_sgpd_sync_index is build_open_gop_key_points's own real, unmodified callee --
 * copied from libavformat/mov.c immediately above it; not itself on the crash path) */
static uint32_t get_sgpd_sync_index(const MOVStreamContext *sc, int nal_unit_type)
{
    for (uint32_t i = 0; i < sc->sgpd_sync_count; i++)
        if (sc->sgpd_sync[i] == HEVC_NAL_CRA_NUT)
            return i + 1;
    return 0;
}

static int build_open_gop_key_points(AVStream *st)
{
    int k;
    int sample_id = 0;
    uint32_t cra_index;
    MOVStreamContext *sc = st->priv_data;

    if (st->codecpar->codec_id != AV_CODEC_ID_HEVC || !sc->sync_group_count)
        return 0;

    /* Build an unrolled index of the samples */
    sc->sample_offsets_count = 0;
    for (uint32_t i = 0; i < sc->ctts_count; i++)
        sc->sample_offsets_count += sc->ctts_data[i].count;
    av_freep(&sc->sample_offsets);
    sc->sample_offsets = av_calloc(sc->sample_offsets_count, sizeof(*sc->sample_offsets));
    if (!sc->sample_offsets)
        return AVERROR(ENOMEM);
    k = 0;
    for (uint32_t i = 0; i < sc->ctts_count; i++)
        for (int j = 0; j < sc->ctts_data[i].count; j++)
             sc->sample_offsets[k++] = sc->ctts_data[i].duration;

    /* The following HEVC NAL type reveal the use of open GOP sync points
     * (TODO: BLA types may also be concerned) */
    cra_index = get_sgpd_sync_index(sc, HEVC_NAL_CRA_NUT); /* Clean Random Access */
    if (!cra_index)
        return 0;

    /* Build a list of open-GOP key samples */
    sc->open_key_samples_count = 0;
    for (uint32_t i = 0; i < sc->sync_group_count; i++)
        if (sc->sync_group[i].index == cra_index)
            sc->open_key_samples_count += sc->sync_group[i].count;
    av_freep(&sc->open_key_samples);
    sc->open_key_samples = av_calloc(sc->open_key_samples_count, sizeof(*sc->open_key_samples));
    if (!sc->open_key_samples)
        return AVERROR(ENOMEM);
    k = 0;
    for (uint32_t i = 0; i < sc->sync_group_count; i++) {
        const MOVSbgp *sg = &sc->sync_group[i];
        if (sg->index == cra_index)
            for (uint32_t j = 0; j < sg->count; j++)
                sc->open_key_samples[k++] = sample_id;
        sample_id += sg->count;
    }

    /* Identify the minimal time step between samples */
    sc->min_sample_duration = UINT_MAX;
    for (uint32_t i = 0; i < sc->stts_count; i++)
        sc->min_sample_duration = FFMIN(sc->min_sample_duration, sc->stts_data[i].duration);

    return 0;
}
/* ==== end verbatim ==== */

int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) sz = 0;
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* HEAP-allocate the raw input (ASAN-guarded); its bytes only ever SELECT the
     * shape of the MOVStreamContext constructed below. */
    unsigned char *seed = (unsigned char *)malloc((size_t)sz + 1);
    if (!seed) { fclose(f); return 0; }
    size_t n = sz > 0 ? fread(seed, 1, (size_t)sz, f) : 0;
    fclose(f);
    seed[n] = 0;

    unsigned char b0 = n > 0 ? seed[0] : 0;
    unsigned char b1 = n > 1 ? seed[1] : 0;
    unsigned char b2 = n > 2 ? seed[2] : 0;
    unsigned char b3 = n > 3 ? seed[3] : 0;
    unsigned char b4 = n > 4 ? seed[4] : 0;

    MOVStreamContext sc;
    memset(&sc, 0, sizeof(sc));
    AVCodecParameters codecpar;
    memset(&codecpar, 0, sizeof(codecpar));
    AVStream st;
    memset(&st, 0, sizeof(st));
    st.codecpar  = &codecpar;
    st.priv_data = &sc;

    codecpar.codec_id = (b0 & 1) ? AV_CODEC_ID_HEVC : AV_CODEC_ID_NONE;

    if ((b0 & 3) == 3) {
        /* TRIGGER shape: HEVC codec + sync_group_count>0 (clears the top guard) + two
         * ctts entries whose unsigned-32 SUM wraps to a small positive int (4..23)
         * while ctts_data[0].count itself stays huge -> heap-buffer-overflow WRITE
         * inside build_open_gop_key_points's own first accumulate/alloc/fill block. */
        sc.ctts_count = 2;
        sc.ctts_data = (MOVCtts *)malloc(sc.ctts_count * sizeof(MOVCtts));
        sc.ctts_data[0].count    = 0xFFFFFFF0u;              /* == -16 mod 2^32 */
        sc.ctts_data[0].duration = (int)(10 + b1);
        sc.ctts_data[1].count    = 20u + (unsigned)(b2 % 20); /* wraps sum to 4..23 */
        sc.ctts_data[1].duration = (int)(1 + b3);

        sc.sync_group_count = 1;
        sc.sync_group = (MOVSbgp *)malloc(sizeof(MOVSbgp));
        sc.sync_group[0].count = 1;
        sc.sync_group[0].index = 1;
    } else {
        /* SAFE shapes: either non-HEVC / no sync groups (early return at the top
         * guard) or HEVC with small, non-overflowing ctts/sync_group/sgpd_sync/stts
         * arrays -- build_open_gop_key_points runs its real logic (partially or all
         * the way through, depending on b0's bits) and returns 0 with no OOB access. */
        unsigned n_ctts = 1 + (b1 % 3);
        sc.ctts_count = n_ctts;
        sc.ctts_data = (MOVCtts *)malloc(n_ctts * sizeof(MOVCtts));
        for (unsigned i = 0; i < n_ctts; i++) {
            sc.ctts_data[i].count    = b2 % 9;              /* 0..8, tiny -- no overflow */
            sc.ctts_data[i].duration = (int)((b3 + i) % 100);
        }

        sc.sync_group_count = (b0 & 4) ? (1u + (b4 % 3)) : 0u;
        if (sc.sync_group_count) {
            sc.sync_group = (MOVSbgp *)malloc(sc.sync_group_count * sizeof(MOVSbgp));
            for (unsigned i = 0; i < sc.sync_group_count; i++) {
                sc.sync_group[i].count = b2 % 5;
                sc.sync_group[i].index = 1;
            }
        }

        if (b0 & 8) {
            /* makes get_sgpd_sync_index() return a nonzero cra_index, so a
             * sync_group_count>0 safe input also walks the open_key_samples block. */
            sc.sgpd_sync_count = 1;
            sc.sgpd_sync = (uint8_t *)malloc(1);
            sc.sgpd_sync[0] = HEVC_NAL_CRA_NUT;
        }

        sc.stts_count = 1u + (b4 % 3);
        sc.stts_data = (MOVStts *)malloc(sc.stts_count * sizeof(MOVStts));
        for (unsigned i = 0; i < sc.stts_count; i++) {
            sc.stts_data[i].count    = 1;
            sc.stts_data[i].duration = 100 + i;
        }
    }

    int ret = build_open_gop_key_points(&st);
    (void)ret;

    free(sc.ctts_data);
    free(sc.sync_group);
    free(sc.sample_offsets);      /* unreached on the TRIGGER path: ASAN aborts first */
    free(sc.open_key_samples);
    free(sc.sgpd_sync);
    free(sc.stts_data);
    free(seed);
    return 0;
}
