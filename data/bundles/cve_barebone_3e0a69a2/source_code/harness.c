/* cve_barebone isolation harness: ffmpeg read_quant_matrix_ext (CVE-2023-51793 family,
 * fix commit 5aba5b89d0, CWE-125). Self-contained: real FFmpeg type/callee names +
 * faithful UNCHECKED_BITSTREAM_READER bit reader copied from libavcodec/get_bits.h,
 * matching mpeg4videodec.c's own "#define UNCHECKED_BITSTREAM_READER 1" (that file's
 * line 23). Bug: none of the four 64-iteration get_bits(gb,8) loops check
 * get_bits_left() before reading (the fix adds that check) -- with the unchecked
 * reader, get_bits()'s UPDATE_CACHE macro does an unconditional 4-byte read at
 * buffer+index/8 with NO bound on index, so a GetBitContext initialized on a short
 * (but AV_INPUT_BUFFER_PADDING_SIZE-padded, exactly like real ffmpeg callers) heap
 * buffer overreads past the padding -> ASAN heap-buffer-overflow READ.
 * Links with only -lm. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

/* ---- attribute / misc shims ---- */
#define av_always_inline inline
#define av_const
#define av_unused
#define AV_INPUT_BUFFER_PADDING_SIZE 64

/* ---- error codes (return values only; not crash-relevant) ---- */
#define AVERROR_INVALIDDATA (-1094995529)

/* ---- min/max ---- */
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))

/* ---- assertions: disabled (release-build behavior), avoids spurious abort() ---- */
#define av_assert2(cond) do{}while(0)

/* ---- byte reads (verbatim semantics from libavutil/intreadwrite.h, big-endian) ---- */
#define AV_RB32(p) ( ((uint32_t)((const uint8_t*)(p))[0] << 24) | \
                     ((uint32_t)((const uint8_t*)(p))[1] << 16) | \
                     ((uint32_t)((const uint8_t*)(p))[2] <<  8) | \
                      (uint32_t)((const uint8_t*)(p))[3] )

/* ---- mathops (verbatim from libavcodec/mathops.h) ---- */
#define NEG_USR32(a,s) (((uint32_t)(a))>>(32-(s)))

/* ================= bit reader (verbatim from libavcodec/get_bits.h,
 * UNCHECKED_BITSTREAM_READER=1, big-endian -- the exact configuration
 * mpeg4videodec.c compiles this function under) ================= */
#define UNCHECKED_BITSTREAM_READER 1
#define MIN_CACHE_BITS 25

typedef struct GetBitContext {
    const uint8_t *buffer, *buffer_end;
    int index;
    int size_in_bits;
    int size_in_bits_plus8;
} GetBitContext;

#define OPEN_READER_NOSIZE(name, gb)            \
    unsigned int name ## _index = (gb)->index;  \
    unsigned int av_unused name ## _cache
#define OPEN_READER(name, gb) OPEN_READER_NOSIZE(name, gb)
#define CLOSE_READER(name, gb) (gb)->index = name ## _index

#define UPDATE_CACHE_BE(name, gb) name ## _cache = \
      AV_RB32((gb)->buffer + (name ## _index >> 3)) << (name ## _index & 7)
#define UPDATE_CACHE(name, gb) UPDATE_CACHE_BE(name, gb)

#define SKIP_CACHE(name, gb, num) name ## _cache <<= (num)
#define SKIP_COUNTER(name, gb, num) name ## _index += (num)
#define SKIP_BITS(name, gb, num)                \
    do { SKIP_CACHE(name, gb, num); SKIP_COUNTER(name, gb, num); } while (0)
#define LAST_SKIP_BITS(name, gb, num) SKIP_COUNTER(name, gb, num)

#define SHOW_UBITS_BE(name, gb, num) NEG_USR32(name ## _cache, num)
#define SHOW_UBITS(name, gb, num) SHOW_UBITS_BE(name, gb, num)
#define GET_CACHE(name, gb) ((uint32_t) name ## _cache)

static inline int get_bits_count(const GetBitContext *s)
{
    return s->index;
}

static inline unsigned int get_bits(GetBitContext *s, int n)
{
    register int tmp;
    OPEN_READER(re, s);
    av_assert2(n>0 && n<=25);
    UPDATE_CACHE(re, s);
    tmp = SHOW_UBITS(re, s, n);
    LAST_SKIP_BITS(re, s, n);
    CLOSE_READER(re, s);
    return tmp;
}

static inline unsigned int show_bits(GetBitContext *s, int n)
{
    register int tmp;
    OPEN_READER_NOSIZE(re, s);
    av_assert2(n>0 && n<=25);
    UPDATE_CACHE(re, s);
    tmp = SHOW_UBITS(re, s, n);
    return tmp;
}

static inline void skip_bits(GetBitContext *s, int n)
{
    OPEN_READER(re, s);
    LAST_SKIP_BITS(re, s, n);
    CLOSE_READER(re, s);
}

static inline unsigned int get_bits1(GetBitContext *s)
{
    unsigned int index = s->index;
    uint8_t result     = s->buffer[index >> 3];
    result <<= index & 7;
    result >>= 8 - 1;
    index++;
    s->index = index;

    return result;
}

static inline unsigned int show_bits_long(GetBitContext *s, int n)
{
    /* n is always 24 (<= MIN_CACHE_BITS) at this file's only call site. */
    return show_bits(s, n);
}

static inline const uint8_t *align_get_bits(GetBitContext *s)
{
    int n = -get_bits_count(s) & 7;
    if (n)
        skip_bits(s, n);
    return s->buffer + (s->index >> 3);
}

static inline int get_bits_left(GetBitContext *gb)
{
    return gb->size_in_bits - get_bits_count(gb);
}

/**
 * Initialize GetBitContext (verbatim from libavcodec/get_bits.h).
 */
static inline int init_get_bits(GetBitContext *s, const uint8_t *buffer,
                                int bit_size)
{
    int buffer_size;
    int ret = 0;

    if (bit_size >= INT_MAX - FFMAX(7, AV_INPUT_BUFFER_PADDING_SIZE*8) || bit_size < 0 || !buffer) {
        bit_size    = 0;
        buffer      = NULL;
        ret         = AVERROR_INVALIDDATA;
    }

    buffer_size = (bit_size + 7) >> 3;

    s->buffer             = buffer;
    s->size_in_bits       = bit_size;
    s->size_in_bits_plus8 = bit_size + 8;
    s->buffer_end         = buffer + buffer_size;
    s->index              = 0;

    return ret;
}

static inline int init_get_bits8(GetBitContext *s, const uint8_t *buffer,
                                 int byte_size)
{
    if (byte_size > INT_MAX / 8 || byte_size < 0)
        byte_size = -1;
    return init_get_bits(s, buffer, byte_size * 8);
}

/* ================= real callee: ff_zigzag_direct (verbatim from
 * libavcodec/mathtables.c) ================= */
const uint8_t ff_zigzag_direct[64] = {
    0,   1,  8, 16,  9,  2,  3, 10,
    17, 24, 32, 25, 18, 11,  4,  5,
    12, 19, 26, 33, 40, 48, 41, 34,
    27, 20, 13,  6,  7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36,
    29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46,
    53, 60, 61, 54, 47, 55, 62, 63
};

/* ================= real types read_quant_matrix_ext needs (reduced to the
 * fields it actually touches; real struct + field names, from
 * libavcodec/idctdsp.h:IDCTDSPContext and libavcodec/mpegvideo.h:MpegEncContext) */
typedef struct IDCTDSPContext {
    uint8_t idct_permutation[64];
} IDCTDSPContext;

typedef struct MpegEncContext {
    IDCTDSPContext idsp;
    uint16_t intra_matrix[64];
    uint16_t chroma_intra_matrix[64];
} MpegEncContext;

/* ================= real callee: next_start_code_studio (verbatim from
 * libavcodec/mpeg4videodec.c) ================= */
static void next_start_code_studio(GetBitContext *gb)
{
    align_get_bits(gb);

    while (get_bits_left(gb) >= 24 && show_bits_long(gb, 24) != 0x1) {
        get_bits(gb, 8);
    }
}

/* ================= TARGET FUNCTION -- verbatim copy of
 * data_cve/cve_3e0a69a2/target/original_function.c, byte-for-byte ================= */
static void read_quant_matrix_ext(MpegEncContext *s, GetBitContext *gb) __attribute__((noinline));

static void read_quant_matrix_ext(MpegEncContext *s, GetBitContext *gb)
{
    int i, j, v;

    if (get_bits1(gb)) {
        /* intra_quantiser_matrix */
        for (i = 0; i < 64; i++) {
            v = get_bits(gb, 8);
            j = s->idsp.idct_permutation[ff_zigzag_direct[i]];
            s->intra_matrix[j]        = v;
            s->chroma_intra_matrix[j] = v;
        }
    }

    if (get_bits1(gb)) {
        /* non_intra_quantiser_matrix */
        for (i = 0; i < 64; i++) {
            get_bits(gb, 8);
        }
    }

    if (get_bits1(gb)) {
        /* chroma_intra_quantiser_matrix */
        for (i = 0; i < 64; i++) {
            v = get_bits(gb, 8);
            j = s->idsp.idct_permutation[ff_zigzag_direct[i]];
            s->chroma_intra_matrix[j] = v;
        }
    }

    if (get_bits1(gb)) {
        /* chroma_non_intra_quantiser_matrix */
        for (i = 0; i < 64; i++) {
            get_bits(gb, 8);
        }
    }

    next_start_code_studio(gb);
}

/* ================= driver ================= */
int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("fopen");
        return 1;
    }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    long len = ftell(f);
    if (len < 0) { fclose(f); return 1; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

    /* Real ffmpeg callers hand init_get_bits8() a buffer that is
     * AV_INPUT_BUFFER_PADDING_SIZE bytes larger than the actual bitstream
     * data (see get_bits.h's own documented contract) -- so we honour that
     * contract here too. The CVE is that read_quant_matrix_ext still
     * overreads past even a correctly padded buffer. */
    size_t total = (size_t)len + AV_INPUT_BUFFER_PADDING_SIZE;
    uint8_t *buf = (uint8_t *)malloc(total ? total : 1);
    if (!buf) { fclose(f); return 1; }
    memset(buf, 0, total);
    if (len > 0) {
        size_t rd = fread(buf, 1, (size_t)len, f);
        (void)rd;
    }
    fclose(f);

    GetBitContext gb;
    init_get_bits8(&gb, buf, (int)len);

    MpegEncContext s;
    memset(&s, 0, sizeof(s));
    for (int i = 0; i < 64; i++)
        s.idsp.idct_permutation[i] = (uint8_t)i;

    read_quant_matrix_ext(&s, &gb);

    free(buf);
    return 0;
}
