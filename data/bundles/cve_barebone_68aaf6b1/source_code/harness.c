/* cve_68aaf6b1 -- ffmpeg libavcodec/cbs_av1.c: cbs_av1_read_uvlc
 * Direct-call ASAN harness.
 *
 * Bug (fixed in b97a4b658814b2de8b9f2a3bce491c002d34de31):
 *   cbs_av1_read_uvlc() reads a "unary" prefix of zero bits terminated by a
 *   '1' bit, writing one character per bit consumed into a fixed-size local
 *   array `char bits[65]`, with NO bound on the number of zero bits versus
 *   the array size.  A bitstream containing 65+ leading zero bits before a
 *   terminating '1' bit overflows `bits[65]` on the stack -- unconditionally
 *   (the write is NOT gated by ctx->trace_enable). This is a stack
 *   buffer overflow WRITE (CWE-787).
 *
 * This harness reproduces the bug by calling cbs_av1_read_uvlc() directly on
 * a heap-allocated buffer built from argv[1], with a real (but minimal)
 * GetBitContext / CodedBitstreamContext pair. The bit-reader helpers
 * (get_bits_count/get_bits_left/get_bits1/get_bits_long) are re-implemented
 * here as a faithful, minimal MSB-first ("big-endian") bit reader matching
 * the real libavcodec/get_bits.h semantics for the non-cached,
 * non-BITSTREAM_READER_LE configuration that libavcodec/cbs_av1.c actually
 * uses (BITSTREAM_READER_LE / CACHED_BITSTREAM_READER are not defined by the
 * cbs code) -- they are generic library-level bit-reading utilities, not
 * part of the vulnerability itself.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

/* ---- real macros/constants from libavcodec/cbs_internal.h, libavutil/error.h, libavutil/log.h ---- */
#define MAX_UINT_BITS(length) ((UINT64_C(1) << (length)) - 1)
#define FFERRTAG(a, b, c, d) (-(int)((unsigned)(a) | ((unsigned)(b) << 8) | \
                              ((unsigned)(c) << 16) | ((unsigned)(d) << 24)))
#define AVERROR_INVALIDDATA FFERRTAG('I','N','D','A')
#define AV_LOG_ERROR 16

/* ---- real struct: libavcodec/get_bits.h : GetBitContext (fields used here) ---- */
typedef struct GetBitContext {
    const uint8_t *buffer, *buffer_end;
    int index;
    int size_in_bits;
    int size_in_bits_plus8;
} GetBitContext;

/* ---- real struct: libavcodec/cbs.h : CodedBitstreamContext (fields cbs_av1_read_uvlc touches) ---- */
typedef struct CodedBitstreamContext {
    void *log_ctx;
    int trace_enable;
} CodedBitstreamContext;

/* av_log(): normal callees are used verbatim on the crash path; av_log() is
 * a variadic logging sink only reached on the (non-crashing) invalid-data /
 * range-error return paths -- a no-op stub is faithful here (we never
 * inspect its output). */
static void av_log(void *avcl, int level, const char *fmt, ...) { (void)avcl; (void)level; (void)fmt; }

/* ff_cbs_trace_syntax_element(): only called when ctx->trace_enable is set;
 * the driver below sets trace_enable = 1, so this genuinely executes on
 * every call, matching the real (trace-enabled) code path. A minimal stub
 * with the real signature (libavcodec/cbs.c) satisfies the link -- but it
 * must actually read `bits` (it logs it here), not be a total no-op:
 * ctx->trace_enable is a compile-time-visible constant once the (single-
 * call-site, static) target function is inlined into main() at -O1, so a
 * no-op stub would let the optimizer prove the caller's writes into its
 * local `bits[65]` buffer are dead stores and delete them -- silently
 * optimizing away the very overflow this harness exists to reproduce.
 * Genuinely dereferencing `bits` here (and unconditionally exercising the
 * branch via trace_enable=1) keeps the writes live regardless. */
static void ff_cbs_trace_syntax_element(CodedBitstreamContext *ctx, int position,
                                         const char *str, const int *subscripts,
                                         const char *bits, int64_t value) {
    (void)ctx; (void)subscripts;
    fprintf(stderr, "trace: %s @ %d = %s (%lld)\n", str ? str : "?", position,
            bits, (long long)value);
}

/* ---- faithful minimal MSB-first bit reader (libavcodec/get_bits.h semantics,
 * non-cached / non-LE configuration, as used by cbs_av1.c) ---- */
static inline int get_bits_count(const GetBitContext *s) { return s->index; }

static inline int get_bits_left(GetBitContext *gb) { return gb->size_in_bits - get_bits_count(gb); }

static inline unsigned int get_bits1(GetBitContext *s) {
    unsigned int index = (unsigned int)s->index;
    uint8_t result = s->buffer[index >> 3];
    result <<= (index & 7);
    result >>= 8 - 1;
    if (s->index < s->size_in_bits_plus8)
        index++;
    s->index = (int)index;
    return result;
}

static inline unsigned int get_bits_long(GetBitContext *s, int n) {
    unsigned int ret = 0;
    int k;
    if (n <= 0) return 0;
    for (k = 0; k < n; k++)
        ret = (ret << 1) | get_bits1(s);
    return ret;
}

/* =====================================================================
 * cbs_av1_read_uvlc -- pasted BYTE-FOR-BYTE from
 * data_cve/cve_68aaf6b1/target/original_function.c
 * ===================================================================== */
static int cbs_av1_read_uvlc(CodedBitstreamContext *ctx, GetBitContext *gbc,
                             const char *name, uint32_t *write_to,
                             uint32_t range_min, uint32_t range_max)
{
    uint32_t value;
    int position, zeroes, i, j;
    char bits[65];

    if (ctx->trace_enable)
        position = get_bits_count(gbc);

    zeroes = i = 0;
    while (1) {
        if (get_bits_left(gbc) < zeroes + 1) {
            av_log(ctx->log_ctx, AV_LOG_ERROR, "Invalid uvlc code at "
                   "%s: bitstream ended.\n", name);
            return AVERROR_INVALIDDATA;
        }

        if (get_bits1(gbc)) {
            bits[i++] = '1';
            break;
        } else {
            bits[i++] = '0';
            ++zeroes;
        }
    }

    if (zeroes >= 32) {
        value = MAX_UINT_BITS(32);
    } else {
        value = get_bits_long(gbc, zeroes);

        for (j = 0; j < zeroes; j++)
            bits[i++] = (value >> (zeroes - j - 1) & 1) ? '1' : '0';

        value += (1 << zeroes) - 1;
    }

    if (ctx->trace_enable) {
        bits[i] = 0;
        ff_cbs_trace_syntax_element(ctx, position, name, NULL,
                                    bits, value);
    }

    if (value < range_min || value > range_max) {
        av_log(ctx->log_ctx, AV_LOG_ERROR, "%s out of range: "
               "%"PRIu32", but must be in [%"PRIu32",%"PRIu32"].\n",
               name, value, range_min, range_max);
        return AVERROR_INVALIDDATA;
    }

    *write_to = value;
    return 0;
}

/* ===================== driver ===================== */
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) { fprintf(stderr, "cannot open %s\n", argv[1]); return 1; }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz < 0) sz = 0;

    /* Heap-allocate the bitstream buffer (ASAN-guarded). */
    uint8_t *buf = (uint8_t *)malloc((size_t)sz > 0 ? (size_t)sz : 1);
    if (!buf) { fclose(f); return 1; }
    size_t got = sz > 0 ? fread(buf, 1, (size_t)sz, f) : 0;
    fclose(f);

    GetBitContext gbc;
    memset(&gbc, 0, sizeof(gbc));
    gbc.buffer = buf;
    gbc.buffer_end = buf + got;
    gbc.index = 0;
    gbc.size_in_bits = (int)(got * 8);
    gbc.size_in_bits_plus8 = (int)(got * 8) + 8;

    CodedBitstreamContext ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.log_ctx = NULL;
    /* trace_enable = 1: genuinely exercise the ctx->trace_enable branch (see
     * the ff_cbs_trace_syntax_element comment above -- this also keeps the
     * `bits[]` writes from being optimized away as dead stores). */
    ctx.trace_enable = 1;

    uint32_t write_to = 0;
    int ret = cbs_av1_read_uvlc(&ctx, &gbc, "test_uvlc", &write_to, 0, UINT32_MAX);

    fprintf(stderr, "ret=%d value=%u\n", ret, write_to);

    free(buf);
    return 0;
}
