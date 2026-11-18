/*
 * cve_barebone direct-call harness for CVE-2017-16803
 * libav / libavcodec/smacker.c : smacker_decode_tree
 * CWE-674 (uncontrolled recursion -> stack overflow)
 *
 * smacker_decode_tree reads one bit per invocation; a "Node" bit (1) recurses,
 * incrementing `length`, with NO depth guard.  A bitstream of consecutive 1-bits
 * drives an unbounded left descent -> stack overflow (ASAN: stack-overflow, all
 * frames == smacker_decode_tree, dedup smacker_decode_tree x3).
 *
 * Everything below the target function is the minimal REAL vocabulary copied from
 * data_cve/cve_0bf211f9/source_code (libavcodec/bitstream.h, libavcodec/smacker.c).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>

/* --- avutil/avcodec minimal vocabulary (real names/values) --- */
#define AV_INPUT_BUFFER_PADDING_SIZE 8
#define AVERROR(e) (-(e))
#define AVERROR_INVALIDDATA (-1094995529) /* real value: MKTAG-based; only sign matters */
#define AV_LOG_ERROR 16

/* av_log: incidental logging on the tree-size-exceeded path -> faithful no-op-ish stub */
static void av_log(void *avcl, int level, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}

/* little-endian buffer reads (libavutil/intreadwrite.h AV_RL64/AV_RL32) */
static inline uint64_t AV_RL64(const uint8_t *p)
{
    uint64_t v = 0;
    for (int i = 0; i < 8; i++)
        v |= (uint64_t)p[i] << (8 * i);
    return v;
}
static inline uint32_t AV_RL32(const uint8_t *p)
{
    uint32_t v = 0;
    for (int i = 0; i < 4; i++)
        v |= (uint32_t)p[i] << (8 * i);
    return v;
}

/* smacker.c selects the little-endian bitstream reader */
#define BITSTREAM_READER_LE

/* --- libavcodec/bitstream.h (verbatim, LE path) --- */
typedef struct BitstreamContext {
    uint64_t bits;      // stores bits read from the buffer
    const uint8_t *buffer, *buffer_end;
    const uint8_t *ptr; // position inside a buffer
    unsigned bits_left; // number of bits left in bits field
    unsigned size_in_bits;
} BitstreamContext;

static inline void refill_64(BitstreamContext *bc)
{
    if (bc->ptr >= bc->buffer_end)
        return;

#ifdef BITSTREAM_READER_LE
    bc->bits       = AV_RL64(bc->ptr);
#else
    bc->bits       = AV_RB64(bc->ptr);
#endif
    bc->ptr       += 8;
    bc->bits_left  = 64;
}

static inline void refill_32(BitstreamContext *bc)
{
    if (bc->ptr >= bc->buffer_end)
        return;

#ifdef BITSTREAM_READER_LE
    bc->bits       = (uint64_t)AV_RL32(bc->ptr) << bc->bits_left | bc->bits;
#else
    bc->bits       = bc->bits | (uint64_t)AV_RB32(bc->ptr) << (32 - bc->bits_left);
#endif
    bc->ptr       += 4;
    bc->bits_left += 32;
}

static inline int bitstream_init(BitstreamContext *bc, const uint8_t *buffer,
                                 unsigned bit_size)
{
    unsigned buffer_size;

    if (bit_size > INT_MAX - 7 || !buffer) {
        buffer        =
        bc->buffer    =
        bc->ptr       = NULL;
        bc->bits_left = 0;
        return AVERROR_INVALIDDATA;
    }

    buffer_size = (bit_size + 7) >> 3;

    bc->buffer       = buffer;
    bc->buffer_end   = buffer + buffer_size;
    bc->ptr          = bc->buffer;
    bc->size_in_bits = bit_size;
    bc->bits_left    = 0;
    bc->bits         = 0;

    refill_64(bc);

    return 0;
}

static inline int bitstream_init8(BitstreamContext *bc, const uint8_t *buffer,
                                  unsigned byte_size)
{
    if (byte_size > INT_MAX / 8)
        return AVERROR_INVALIDDATA;
    return bitstream_init(bc, buffer, byte_size * 8);
}

static inline uint64_t get_val(BitstreamContext *bc, unsigned n)
{
#ifdef BITSTREAM_READER_LE
    uint64_t ret = bc->bits & ((UINT64_C(1) << n) - 1);
    bc->bits >>= n;
#else
    uint64_t ret = bc->bits >> (64 - n);
    bc->bits <<= n;
#endif
    bc->bits_left -= n;

    return ret;
}

static inline unsigned bitstream_read_bit(BitstreamContext *bc)
{
    if (!bc->bits_left)
        refill_64(bc);

    return get_val(bc, 1);
}

static inline uint32_t bitstream_read(BitstreamContext *bc, unsigned n)
{
    if (!n)
        return 0;

    if (n > bc->bits_left) {
        refill_32(bc);
        if (bc->bits_left < 32)
            bc->bits_left = n;
    }

    return get_val(bc, n);
}

/* --- libavcodec/smacker.c : HuffContext (verbatim) --- */
typedef struct HuffContext {
    int length;
    int maxlength;
    int current;
    uint32_t *bits;
    int *lengths;
    int *values;
} HuffContext;

/* ==== TARGET FUNCTION (byte-for-byte from target/original_function.c) ==== */
static int smacker_decode_tree(BitstreamContext *bc, HuffContext *hc,
                               uint32_t prefix, int length)
{
    if (!bitstream_read_bit(bc)) { // Leaf
        if(hc->current >= 256){
            av_log(NULL, AV_LOG_ERROR, "Tree size exceeded!\n");
            return AVERROR_INVALIDDATA;
        }
        if(length){
            hc->bits[hc->current] = prefix;
            hc->lengths[hc->current] = length;
        } else {
            hc->bits[hc->current] = 0;
            hc->lengths[hc->current] = 0;
        }
        hc->values[hc->current] = bitstream_read(bc, 8);
        hc->current++;
        if(hc->maxlength < length)
            hc->maxlength = length;
        return 0;
    } else { //Node
        int r;
        length++;
        r = smacker_decode_tree(bc, hc, prefix, length);
        if(r)
            return r;
        return smacker_decode_tree(bc, hc, prefix | (1 << (length - 1)), length);
    }
}
/* ==== END TARGET FUNCTION ==== */

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input>\n", argv[0]);
        return 2;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("fopen");
        return 2;
    }
    fseek(f, 0, SEEK_END);
    long fsz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (fsz < 0)
        fsz = 0;

    /* HEAP buffer (ASAN-guarded), padded like the real decoder so refill_* never
     * over-reads the payload; the payload region itself stays exactly fsz bytes. */
    size_t pad = AV_INPUT_BUFFER_PADDING_SIZE;
    uint8_t *buf = (uint8_t *)malloc((size_t)fsz + pad);
    if (!buf) {
        fclose(f);
        return 2;
    }
    size_t got = fsz ? fread(buf, 1, (size_t)fsz, f) : 0;
    fclose(f);
    memset(buf + got, 0, ((size_t)fsz + pad) - got);

    /* HuffContext exactly as the real caller sets it up (256-entry tables). */
    HuffContext hc;
    memset(&hc, 0, sizeof(hc));
    hc.bits    = (uint32_t *)calloc(256, sizeof(uint32_t));
    hc.lengths = (int *)calloc(256, sizeof(int));
    hc.values  = (int *)calloc(256, sizeof(int));
    if (!hc.bits || !hc.lengths || !hc.values) {
        free(buf);
        return 2;
    }

    BitstreamContext bc;
    bitstream_init8(&bc, buf, (unsigned)got);

    /* root invocation, verbatim call shape: prefix=0, length=0 */
    int r = smacker_decode_tree(&bc, &hc, 0, 0);
    fprintf(stderr, "smacker_decode_tree -> %d (current=%d)\n", r, hc.current);

    free(hc.bits);
    free(hc.lengths);
    free(hc.values);
    free(buf);
    return 0;
}
