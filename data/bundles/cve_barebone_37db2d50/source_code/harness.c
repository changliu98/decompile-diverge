/* cve_barebone harness -- CVE-2021-3881 / libmobi mobi_decompress_huffman_internal
 * Target: mobi_decompress_huffman_internal (src/compression.c, the exact text frozen
 *   in target/original_function.c)
 * Bug class: unbounded array index -> heap-buffer-overflow READ (CWE-125).
 *
 * Fix (bec783e6212439a335ba6e8df7ab8ed610ca9a21) changes:
 *     while (code < huffcdic->mincode_table[code_length]) {
 *         code_length++;
 *     }
 *   to:
 *     while (code < huffcdic->mincode_table[code_length]) {
 *         if (++code_length >= HUFF_CODETABLE_SIZE) {   // new define, == 33
 *             debug_print("Wrong offset to mincode table: %hhu\n", code_length);
 *             return MOBI_DATA_CORRUPT;
 *         }
 *     }
 * i.e. the PRE-FIX loop has NO bound on code_length at all: as long as
 * `code < huffcdic->mincode_table[code_length]` keeps holding, code_length (a
 * uint8_t, so it can climb 0..255) keeps incrementing past the declared 33-entry
 * bound of mincode_table[]/maxcode_table[] and walks straight off the end of the
 * MOBIHuffCdic allocation -- a heap-buffer-overflow READ. huffcdic is parsed from
 * the book's HUFF/CDIC records in the real caller (mobi_parse_huff); here it is
 * built directly, shaped exactly the way a crafted HUFF record would leave it: a
 * `table1` entry that clears the termination bit (so the mincode/maxcode search
 * loop is entered at all) and a `mincode_table` that never stops looking "too
 * small" for the probe `code` -- exactly the missing-bound condition the fix
 * guards against.
 *
 * TRIGGER: mincode_table[] (and everything after it out to the end of this heap
 *   chunk) holds 0xFFFFFFFF -> `code < mincode_table[code_length]` stays true for
 *   any code_length the loop reaches (any real `code` is < 0xFFFFFFFF), so
 *   code_length climbs unbounded until the read address leaves the
 *   malloc(sizeof(MOBIHuffCdic)) allocation -> ASAN heap-buffer-overflow READ,
 *   well inside code_length's uint8_t range (crosses the ~1.3 KB allocation
 *   around code_length ~= 70, far short of the 0..255 wraparound).
 * SAFE: mincode_table[1] == 0 -> `code < 0` is false for the (unsigned) `code` on
 *   the very first check, so code_length never grows past its starting value (1);
 *   huffcdic's own `index_count == 0` then trips mobi_decompress_huffman_internal's
 *   OWN bounds check (`index >= huffcdic->index_count`) immediately afterwards,
 *   returning MOBI_DATA_CORRUPT cleanly -- a real, in-spec call that exercises the
 *   function (through the table1/mincode/maxcode lookup and the index bounds
 *   check) without ever growing code_length or touching symbol_offsets/symbols.
 * Neither recipe needs a second mobi_buffer_fill64() refill -- both recipes settle
 * (crash or clean-return) within the loop's first pass, so buf_in's exact content
 * beyond the mode-select byte doesn't change the outcome and is free to vary
 * per-input for corpus realism.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- mobi.h: real return-code enum, verbatim membership/values ---- */
typedef enum {
    MOBI_SUCCESS = 0,
    MOBI_ERROR = 1,
    MOBI_PARAM_ERR = 2,
    MOBI_DATA_CORRUPT = 3,
    MOBI_FILE_NOT_FOUND = 4,
    MOBI_FILE_ENCRYPTED = 5,
    MOBI_FILE_UNSUPPORTED = 6,
    MOBI_MALLOC_FAILED = 7,
    MOBI_INIT_FAILED = 8,
    MOBI_BUFFER_END = 9,
    MOBI_XML_ERR = 10,
    MOBI_DRM_PIDINV = 11,
    MOBI_DRM_KEYNOTFOUND = 12,
    MOBI_DRM_UNSUPPORTED = 13,
    MOBI_WRITE_FAILED = 14,
} MOBI_RET;

/* ---- debug.h: MOBI_DEBUG defaults to 0 -> debug_print's real default expansion is
 * a no-op (not an invented stub -- this is the stock non-debug build). ---- */
#define debug_print(fmt, ...)

/* ---- compression.h: real defines (pre-fix state: no HUFF_CODETABLE_SIZE yet) ---- */
#define MOBI_INLINE
#define MOBI_HUFFMAN_MAXDEPTH 20

/* ---- buffer.h: real struct, verbatim ---- */
typedef struct {
    size_t offset;
    size_t maxlen;
    unsigned char *data;
    MOBI_RET error;
} MOBIBuffer;

/* ---- compression.h: real struct, verbatim (pre-fix 33-entry tables -- the fix
 * itself doesn't touch these sizes, only adds a runtime bound to the loop) ---- */
typedef struct {
    size_t index_count;
    size_t index_read;
    size_t code_length;
    uint32_t table1[256];
    uint32_t mincode_table[33];
    uint32_t maxcode_table[33];
    uint16_t *symbol_offsets;
    unsigned char **symbols;
} MOBIHuffCdic;

/* ---- buffer.c: mobi_buffer_fill64, VERBATIM -- called at the top of the target's
 * own loop, on the crash path. ---- */
static MOBI_INLINE uint64_t mobi_buffer_fill64(MOBIBuffer *buf) {
    uint64_t val = 0;
    uint8_t i = 8;
    size_t bytesleft = buf->maxlen - buf->offset;
    unsigned char *ptr = buf->data + buf->offset;
    while (i-- && bytesleft--) {
        val |= (uint64_t) *ptr++ << (i * 8);
    }
    /* increase counter by 4 bytes only, 4 bytes overlap on each call */
    buf->offset += 4;
    return val;
}

/* ---- buffer.c: mobi_buffer_addraw, VERBATIM -- called from the target's own body
 * (the is_decompressed branch); not reached by either TRIGGER or SAFE input here,
 * but the target's verbatim body calls it directly, so it must be defined to link. */
void mobi_buffer_addraw(MOBIBuffer *buf, const unsigned char* data, const size_t len) {
    if (buf->offset + len > buf->maxlen) {
        debug_print("%s", "Buffer full\n");
        buf->error = MOBI_BUFFER_END;
        return;
    }
    memcpy(buf->data + buf->offset, data, len);
    buf->offset += len;
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the crash keeps mobi_decompress_huffman_internal as its own stack
 * frame (dc_batch requires the target function name in the ASAN backtrace). */
__attribute__((noinline))
static MOBI_RET mobi_decompress_huffman_internal(MOBIBuffer *buf_out, MOBIBuffer *buf_in, const MOBIHuffCdic *huffcdic, size_t depth) {
    if (depth > MOBI_HUFFMAN_MAXDEPTH) {
        debug_print("Too many levels of recursion: %zu\n", depth);
        return MOBI_DATA_CORRUPT;
    }
    MOBI_RET ret = MOBI_SUCCESS;
    int8_t bitcount = 32;
    /* this cast should be safe: max record size is 4096 */
    int bitsleft = (int) (buf_in->maxlen * 8);
    uint8_t code_length = 0;
    uint64_t buffer = mobi_buffer_fill64(buf_in);
    while (ret == MOBI_SUCCESS) {
        if (bitcount <= 0) {
            bitcount += 32;
            buffer = mobi_buffer_fill64(buf_in);
        }
        uint32_t code = (buffer >> bitcount) & 0xffffffffU;
        /* lookup code in table1 */
        uint32_t t1 = huffcdic->table1[code >> 24];
        /* get maxcode and codelen from t1 */
        code_length = t1 & 0x1f;
        uint32_t maxcode = (((t1 >> 8) + 1) << (32 - code_length)) - 1;
        /* check termination bit */
        if (!(t1 & 0x80)) {
            /* get offset from mincode, maxcode tables */
            while (code < huffcdic->mincode_table[code_length]) {
                code_length++;
            }
            maxcode = huffcdic->maxcode_table[code_length];
        }
        bitcount -= code_length;
        bitsleft -= code_length;
        if (bitsleft < 0) {
            break;
        }
        /* get index for symbol offset */
        uint32_t index = (uint32_t) (maxcode - code) >> (32 - code_length);
        /* check which part of cdic to use */
        uint16_t cdic_index = (uint16_t) ((uint32_t)index >> huffcdic->code_length);
        if (index >= huffcdic->index_count) {
            debug_print("Wrong symbol offsets index: %u\n", index);
            return MOBI_DATA_CORRUPT;
        }
        /* get offset */
        uint32_t offset = huffcdic->symbol_offsets[index];
        uint32_t symbol_length = (uint32_t) huffcdic->symbols[cdic_index][offset] << 8 | (uint32_t) huffcdic->symbols[cdic_index][offset + 1];
        /* 1st bit is is_decompressed flag */
        int is_decompressed = symbol_length >> 15;
        /* get rid of flag */
        symbol_length &= 0x7fff;
        if (is_decompressed) {
            /* symbol is at (offset + 2), 2 bytes used earlier for symbol length */
            mobi_buffer_addraw(buf_out, (huffcdic->symbols[cdic_index] + offset + 2), symbol_length);
            ret = buf_out->error;
        } else {
            /* symbol is compressed */
            /* TODO cache uncompressed symbols? */
            MOBIBuffer buf_sym;
            buf_sym.data = huffcdic->symbols[cdic_index] + offset + 2;
            buf_sym.offset = 0;
            buf_sym.maxlen = symbol_length;
            buf_sym.error = MOBI_SUCCESS;
            ret = mobi_decompress_huffman_internal(buf_out, &buf_sym, huffcdic, depth + 1);
        }
    }
    return ret;
}

/* ================= driver ================= */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 2; }
    fseek(fp, 0, SEEK_END);
    long ln = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (ln < 0) ln = 0;
    size_t n = (size_t)ln;
    unsigned char *data = (unsigned char *)malloc(n ? n : 1);   /* HEAP input */
    size_t got = fread(data, 1, n, fp);
    fclose(fp);
    if (got < 1) { free(data); return 0; }                       /* empty -> clean */

    int trigger = data[0] & 1;                  /* 1 => TRIGGER, 0 => SAFE */

    /* buf_in: compressed source data. Heap, ASAN-guarded. Only ever feeds the loop's
     * FIRST `code` (both recipes are robust to whatever that comes out to be), so its
     * content is free to vary across the corpus for realism. */
    size_t bn = 16;
    unsigned char *bin_data = (unsigned char *)malloc(bn);
    for (size_t i = 0; i < bn; i++)
        bin_data[i] = (got > 1 + i) ? data[1 + i] : 0x00;
    MOBIBuffer *buf_in = (MOBIBuffer *)malloc(sizeof(MOBIBuffer));
    buf_in->data = bin_data;
    buf_in->offset = 0;
    buf_in->maxlen = bn;
    buf_in->error = MOBI_SUCCESS;

    /* buf_out: decompressed destination. Heap, ASAN-guarded. */
    size_t on = 256;
    unsigned char *out_data = (unsigned char *)malloc(on);
    MOBIBuffer *buf_out = (MOBIBuffer *)malloc(sizeof(MOBIBuffer));
    buf_out->data = out_data;
    buf_out->offset = 0;
    buf_out->maxlen = on;
    buf_out->error = MOBI_SUCCESS;

    /* huffcdic: parsed HUFF/CDIC tables, sized to EXACTLY sizeof(MOBIHuffCdic) so a
     * runaway mincode_table[] walk hits the ASAN redzone right after this chunk. */
    MOBIHuffCdic *huffcdic = (MOBIHuffCdic *)malloc(sizeof(MOBIHuffCdic));
    memset(huffcdic, 0xFF, sizeof(MOBIHuffCdic));  /* table1/mincode/maxcode default "huge" */
    for (int i = 0; i < 256; i++)
        huffcdic->table1[i] = 0x00000001u;  /* termination bit(0x80) clear; code_length starts at 1 */
    huffcdic->code_length = 0;              /* keeps the cdic_index shift amount in-range */

    if (trigger) {
        /* mincode_table[]/maxcode_table[] (and everything past them, out to the end
         * of this allocation) stay 0xFFFFFFFF from the memset above -- see header. */
    } else {
        for (int i = 0; i < 33; i++) {
            huffcdic->mincode_table[i] = 0;
            huffcdic->maxcode_table[i] = 0;
        }
        huffcdic->index_count = 0;      /* trips the function's OWN bounds check cleanly */
        huffcdic->symbol_offsets = NULL;
        huffcdic->symbols = NULL;
    }

    /* volatile function pointer: forbid inlining the call into main. */
    MOBI_RET (*volatile fn)(MOBIBuffer *, MOBIBuffer *, const MOBIHuffCdic *, size_t) =
        mobi_decompress_huffman_internal;
    MOBI_RET ret = fn(buf_out, buf_in, huffcdic, 0);
    (void)ret;

    free(bin_data);
    free(buf_in);
    free(out_data);
    free(buf_out);
    free(huffcdic);
    free(data);
    return 0;
}
