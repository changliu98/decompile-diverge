/*
 * Direct-call ASAN harness for CVE-2020 libmobi mobi_decompress_huffman_internal
 * out-of-bounds read (bfabiszewski/libmobi, fixed by
 * bec783e6212439a335ba6e8df7ab8ed610ca9a21).
 *
 * Bug: in the huffman decompression inner loop, when the code isn't found in
 * table1's terminal entries, the code walks huffcdic->mincode_table[code_length]
 * upward with `code_length++` and NO bound against HUFF_CODETABLE_SIZE (33).
 * If mincode_table never yields a value > code, code_length (a uint8_t) keeps
 * growing past the 33-entry mincode_table / maxcode_table arrays and reads
 * past the end of the MOBIHuffCdic allocation -> heap-buffer-overflow READ
 * (CWE-125). The fix commit adds:
 *     if (++code_length >= HUFF_CODETABLE_SIZE) { ...; return MOBI_DATA_CORRUPT; }
 *
 * This harness calls mobi_decompress_huffman_internal directly on a
 * heap-allocated, attacker-controlled MOBIHuffCdic. All type defs and the
 * one real crash-path callee (mobi_buffer_fill64) are copied verbatim from
 * source_code/src/{compression.h,compression.c,buffer.h,mobi.h}.
 * mobi_buffer_addraw is not on the crash path (never reached: the crash
 * happens inside the mincode_table lookup, before is_decompressed is ever
 * read) -- included as a minimal faithful stub matching buffer.c's real
 * signature/behavior only so the translation unit links standalone.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- minimal subset of src/mobi.h ---- */
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

/* src/compression.h: #define MOBI_INLINE (empty unless config.h overrides it) */
#define MOBI_INLINE
/* src/debug.h: debug_print is a no-op unless MOBI_DEBUG is set */
#define debug_print(fmt, ...)

/* ---- minimal subset of src/buffer.h ---- */
typedef struct {
    size_t offset;          /**< Current offset in respect to buffer start */
    size_t maxlen;           /**< Length of the buffer data */
    unsigned char *data;     /**< Pointer to buffer data */
    MOBI_RET error;          /**< MOBI_SUCCESS = 0 if operation on buffer is successful, non-zero value on failure */
} MOBIBuffer;

/* ---- minimal subset of src/compression.h (pre-fix layout: NO HUFF_CODETABLE_SIZE bound) ---- */
#define MOBI_HUFFMAN_MAXDEPTH 20

typedef struct {
    size_t index_count;       /**< Total number of indices in all CDIC records, stored in each CDIC record header */
    size_t index_read;        /**< Number of indices parsed, used by parser */
    size_t code_length;       /**< Code length value stored in CDIC record header */
    uint32_t table1[256];     /**< Table of big-endian indices from HUFF record data1 */
    uint32_t mincode_table[33]; /**< Table of big-endian mincodes from HUFF record data2 */
    uint32_t maxcode_table[33]; /**< Table of big-endian maxcodes from HUFF record data2 */
    uint16_t *symbol_offsets; /**< Index of symbol offsets parsed from CDIC records (index_count entries) */
    unsigned char **symbols;  /**< Array of pointers to start of symbols data in each CDIC record (index = number of CDIC record) */
} MOBIHuffCdic;

/* ---- real callee, verbatim from source_code/src/compression.c: it IS on
 * the crash path (called at function entry to fill `buffer`). ---- */
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

/* Incidental callee (NOT on the crash path: mobi_decompress_huffman_internal
 * crashes inside the mincode_table lookup, long before `is_decompressed` is
 * read, so this is never invoked at runtime). Minimal faithful stub matching
 * source_code/src/buffer.c's real signature/behavior, needed only so the
 * translation unit links standalone. */
static void mobi_buffer_addraw(MOBIBuffer *buf, const unsigned char *data, const size_t len) {
    if (buf->offset + len > buf->maxlen) {
        buf->error = MOBI_BUFFER_END;
        return;
    }
    memcpy(buf->data + buf->offset, data, len);
    buf->offset += len;
}

/* ==== BEGIN verbatim copy of data_cve/cve_42f7559b/target/original_function.c ==== */
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
/* ==== END verbatim copy ==== */

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        fprintf(stderr, "cannot open %s\n", argv[1]);
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long szl = ftell(f);
    if (szl < 0) szl = 0;
    fseek(f, 0, SEEK_SET);
    size_t sz = (size_t) szl;

    /* heap-allocate the raw input (ASAN-guarded) */
    unsigned char *raw = (unsigned char *) malloc(sz > 0 ? sz : 1);
    size_t n = 0;
    if (raw && sz > 0) {
        n = fread(raw, 1, sz, f);
    }
    fclose(f);
    if (!raw) return 1;

    /*
     * File layout:
     *   byte[0]   = trigger flag: 0 => safe run, nonzero => trigger the OOB read
     *   byte[1..] = payload bytes fed to buf_in (real, attacker-controlled
     *               compressed-record bytes that mobi_buffer_fill64 reads)
     */
    unsigned char trigger = (n > 0) ? raw[0] : 0;
    size_t payload_len = (n > 1) ? (n - 1) : 0;
    unsigned char *payload = (unsigned char *) malloc(payload_len > 0 ? payload_len : 1);
    if (payload_len > 0) {
        memcpy(payload, raw + 1, payload_len);
    }

    /* heap-allocate the MOBIHuffCdic exactly (ASAN redzone right after it) */
    MOBIHuffCdic *huffcdic = (MOBIHuffCdic *) malloc(sizeof(MOBIHuffCdic));
    if (!huffcdic) {
        free(payload);
        free(raw);
        return 1;
    }

    if (trigger) {
        /*
         * Fill the WHOLE struct with the 0xFFFFFFFF word pattern. This makes
         * every uint32_t-aligned word from mincode_table[0] through the end
         * of the allocation (mincode_table, maxcode_table, and the trailing
         * symbol_offsets/symbols pointer bytes, none of which are ever
         * dereferenced before the crash) read back as 0xFFFFFFFF, so the
         * vulnerable `while (code < huffcdic->mincode_table[code_length])`
         * loop keeps incrementing code_length (a uint8_t, so up to 255)
         * clean past index 33 -- and clean past the entire allocation --
         * without ever hitting a "small" value that would stop the loop
         * in-bounds by chance.
         */
        memset(huffcdic, 0xFF, sizeof(MOBIHuffCdic));
    } else {
        /*
         * All-zero: huffcdic->mincode_table[k] == 0 for every k, so the
         * unsigned comparison `code < 0` is never true and the vulnerable
         * while loop body never executes (code_length stays at its initial
         * value). index_count == 0 additionally guarantees the legitimate
         * "Wrong symbol offsets index" bounds check just below fires on the
         * very next line touching huffcdic (`index >= huffcdic->index_count`
         * is always true for an unsigned index when index_count is 0), so
         * the call returns MOBI_DATA_CORRUPT before ever touching
         * symbol_offsets/symbols/buf_out.
         */
        memset(huffcdic, 0x00, sizeof(MOBIHuffCdic));
    }
    /* table1[code>>24] must be non-terminal (bit 0x80 clear) with a small,
     * valid code_length (bits 0x1f) so the unbounded loop above is entered
     * -- in BOTH cases, since which index of table1 gets hit depends on the
     * (attacker-controlled) payload's first byte. */
    for (int i = 0; i < 256; i++) {
        huffcdic->table1[i] = 1u; /* code_length = 1, termination bit clear */
    }

    MOBIBuffer buf_in;
    buf_in.data = payload;
    buf_in.offset = 0;
    buf_in.maxlen = payload_len;
    buf_in.error = MOBI_SUCCESS;

    unsigned char *outbuf = (unsigned char *) malloc(4096);
    MOBIBuffer buf_out;
    buf_out.data = outbuf;
    buf_out.offset = 0;
    buf_out.maxlen = outbuf ? 4096 : 0;
    buf_out.error = MOBI_SUCCESS;

    MOBI_RET ret = mobi_decompress_huffman_internal(&buf_out, &buf_in, huffcdic, 0);
    (void) ret;

    free(outbuf);
    free(huffcdic);
    free(payload);
    free(raw);
    return 0;
}
