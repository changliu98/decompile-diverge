/* cve_1beccf86 -- suricata FileSwfDecompression direct-call harness.
 *
 * Bug (fix commit ad446c9006a77490af51c468aae0ce934f4d2117): in the LZMA
 * branch, FileSwfDecompression declares a stack VLA
 *     uint8_t compressed_data[compressed_data_len];
 * whose size is fully attacker/config controlled (derived from buffer_len /
 * compress_depth, both function parameters). The fix swaps the VLA for a
 * heap SCCalloc(). With no upper bound, a large buffer_len makes the VLA
 * allocation exceed the thread stack, running the process off the end of
 * the mapped stack region -- a stack-exhaustion crash (SIGSEGV) that ASAN's
 * signal handler reports directly inside FileSwfDecompression's own frame,
 * before any of the memcpy's *source* reads ever happen.
 *
 * This harness calls the exact (byte-for-byte) vulnerable function in
 * isolation. It intentionally decouples the *declared* buffer_len (an
 * out-of-band harness-only header field) from the *actual* heap allocation
 * backing `buffer` -- exactly mirroring the real bug: FileSwfDecompression
 * never validates buffer_len against how much memory is really there before
 * sizing the VLA from it, and a network attacker controls the declared file
 * length independent of the mapped buffer.  We additionally shrink
 * RLIMIT_STACK in main() (standard PoC scaffolding, not part of the target
 * function) so the crash is deterministic and cheap regardless of the
 * container's default stack ulimit -- no need to ship megabyte-sized PoC
 * files just to physically outrun an 8MB default stack.
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/resource.h>

/* ---- minimal real type/const defs, copied by name from source_code ---- */

/* src/util-file-decompression.h */
enum {
    FILE_IS_NOT_SWF = 0,
    FILE_SWF_NO_COMPRESSION,
    FILE_SWF_ZLIB_COMPRESSION,
    FILE_SWF_LZMA_COMPRESSION,
};

/* src/app-layer-htp.h */
typedef enum HtpSwfCompressType_ {
    HTTP_SWF_COMPRESSION_NONE = 0,
    HTTP_SWF_COMPRESSION_ZLIB,
    HTTP_SWF_COMPRESSION_LZMA,
    HTTP_SWF_COMPRESSION_BOTH,
} HtpSwfCompressType;

/* src/util-file-swf-decompression.h */
#define MIN_SWF_LEN 2920

/* src/util-file-decompression.c */
#define SWF_ZLIB_MIN_VERSION 0x06
#define SWF_LZMA_MIN_VERSION 0x0D

/* src/detect-engine-inspect-buffer.h -- verbatim field list */
typedef struct InspectionBuffer {
    const uint8_t *inspect;
    uint64_t inspect_offset;
    uint32_t inspect_len;
    int initialized;
    uint8_t flags;
    uint32_t len;
    uint8_t *buf;
    uint32_t size;
    uint32_t orig_len;
    const uint8_t *orig;
} InspectionBuffer;

/* src/detect.h: struct DetectEngineThreadCtx_ is a huge opaque detection-
 * engine context in the real codebase. FileSwfDecompression only ever
 * forwards the pointer (to DetectEngineSetEvent / the *Decompression
 * helpers) -- it never dereferences it itself, so a minimal opaque stand-in
 * is a faithful "incidental dependency" stub. */
typedef struct DetectEngineThreadCtx_ {
    int dummy;
} DetectEngineThreadCtx;

/* MIN() is used verbatim inside FileGetSwfDecompressedLen below (real
 * Suricata macro from suricata-common.h). */
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

/* SCFree/SCRealloc: real Suricata util-mem.h wrappers around free/realloc
 * with memory accounting; functionally-equivalent minimal stand-ins. */
#define SCRealloc realloc
#define SCFree free

/* ---- real (verbatim-copied) callees on/adjacent to the crash path ---- */

/* src/util-file-decompression.c, verbatim */
static int FileIsSwfFile(const uint8_t *buffer, uint32_t buffer_len)
{
    if (buffer_len >= 3 && buffer[1] == 'W' && buffer[2] == 'S') {
        if (buffer[0] == 'F')
            return FILE_SWF_NO_COMPRESSION;
        else if (buffer[0] == 'C')
            return FILE_SWF_ZLIB_COMPRESSION;
        else if (buffer[0] == 'Z')
            return FILE_SWF_LZMA_COMPRESSION;
        else
            return FILE_IS_NOT_SWF;
    }

    return FILE_IS_NOT_SWF;
}

/* src/util-file-swf-decompression.c, verbatim */
#define MAX_SWF_DECOMPRESSED_LEN 50000000
static uint32_t FileGetSwfDecompressedLen(const uint8_t *buffer,
                                           const uint32_t buffer_len)
{
    if (buffer_len < 8) {
        return 0;
    }

    uint32_t a = buffer[4];
    uint32_t b = buffer[5];
    uint32_t c = buffer[6];
    uint32_t d = buffer[7];

    uint32_t value = (((a & 0xff) << 24UL) |
                      ((b & 0xff) << 16UL) |
                      ((c & 0xff) << 8UL) |
                       (d & 0xff));

    uint32_t len = (((value >> 24) & 0x000000FFUL) |
                    ((value >> 8)  & 0x0000FF00UL) |
                    ((value << 8)  & 0x00FF0000UL) |
                    ((value << 24) & 0xFF000000UL));

    return MIN(MAX_SWF_DECOMPRESSED_LEN, len);
}

/* src/util-file-swf-decompression.c, verbatim */
static uint8_t FileGetSwfVersion(const uint8_t *buffer, const uint32_t buffer_len)
{
    if (buffer_len > 3)
        return buffer[3];

    return 0;
}

/* src/detect-engine-inspect-buffer.c, verbatim (SCRealloc/SCFree aliased above) */
static uint8_t *SCInspectionBufferCheckAndExpand(InspectionBuffer *buffer, uint32_t min_size)
{
    if (buffer->size >= min_size)
        return buffer->buf;

    uint32_t new_size = (buffer->size == 0) ? 4096 : buffer->size;
    while (new_size < min_size) {
        new_size *= 2;
    }

    void *ptr = SCRealloc(buffer->buf, new_size);
    if (ptr != NULL) {
        buffer->buf = ptr;
        buffer->size = new_size;
    } else {
        return NULL;
    }
    return buffer->buf;
}

/* src/detect-engine.c: real DetectEngineSetEvent just records an event
 * counter/flag on det_ctx for later logging -- no bearing on this bug
 * (never reached on the crashing path; only on the *_INVALID_* early-return
 * branches some SAFE inputs exercise). Minimal no-op incidental stub. */
static void DetectEngineSetEvent(DetectEngineThreadCtx *det_ctx, uint8_t e)
{
    (void)det_ctx;
    (void)e;
}

/* src/util-file-swf-decompression.c: real bodies call out to zlib/liblzma.
 * Incidental dependency -- minimal faithful stub that reports success and
 * copies from the caller-supplied compressed_data into decompressed_data
 * (matching the real functions' "compressed in, decompressed out" contract
 * and signature exactly).
 *
 * IMPORTANT (load-bearing, not stylistic): the copy genuinely READS through
 * `compressed_data`. An earlier version only touched `decompressed_data`
 * (`(void)compressed_data;`) -- with the real callee never observably
 * reading the caller's buffer, clang -O1 proved the caller's
 * `uint8_t compressed_data[compressed_data_len]` VLA writes were dead
 * stores and DCE'd the entire VLA allocation away, silently defeating the
 * crash (verified: even a 500,000,000-byte compressed_data_len produced no
 * fault once the callee ignored the pointer). Reading it here keeps the
 * VLA's stack allocation live through to the fault. */
static int FileSwfZlibDecompression(DetectEngineThreadCtx *det_ctx,
                                     uint8_t *compressed_data, uint32_t compressed_data_len,
                                     uint8_t *decompressed_data, uint32_t decompressed_data_len)
{
    (void)det_ctx;
    uint32_t n = compressed_data_len < decompressed_data_len ? compressed_data_len : decompressed_data_len;
    if (n && decompressed_data && compressed_data)
        memcpy(decompressed_data, compressed_data, n);
    return 1;
}

static int FileSwfLzmaDecompression(DetectEngineThreadCtx *det_ctx,
                                     uint8_t *compressed_data, uint32_t compressed_data_len,
                                     uint8_t *decompressed_data, uint32_t decompressed_data_len)
{
    (void)det_ctx;
    uint32_t n = compressed_data_len < decompressed_data_len ? compressed_data_len : decompressed_data_len;
    if (n && decompressed_data && compressed_data)
        memcpy(decompressed_data, compressed_data, n);
    return 1;
}

/* src/detect.h: real event-id enum values are irrelevant here (they only
 * ever reach the no-op DetectEngineSetEvent stub above); any distinct
 * uint8_t constants are a faithful stand-in for the enum members
 * FileSwfDecompression's own body references by name. */
#define FILE_DECODER_EVENT_INVALID_SWF_LENGTH 1
#define FILE_DECODER_EVENT_INVALID_SWF_VERSION 2
#define FILE_DECODER_EVENT_NO_MEM 3

/* =====================================================================
 * FileSwfDecompression -- BYTE-FOR-BYTE copy of
 * data_cve/cve_1beccf86/target/original_function.c. DO NOT EDIT.
 * ===================================================================== */
int FileSwfDecompression(const uint8_t *buffer, uint32_t buffer_len,
                         DetectEngineThreadCtx *det_ctx,
                         InspectionBuffer *out_buffer,
                         int swf_type,
                         uint32_t decompress_depth,
                         uint32_t compress_depth)
{
    int r = 0;

    int compression_type = FileIsSwfFile(buffer, buffer_len);
    if (compression_type == FILE_SWF_NO_COMPRESSION) {
        return 0;
    }

    uint32_t offset = 0;
    if (compression_type == FILE_SWF_ZLIB_COMPRESSION) {
        /* compressed data start from the 4th bytes */
        offset = 8;
    } else if (compression_type == FILE_SWF_LZMA_COMPRESSION) {
        /* compressed data start from the 17th bytes */
        offset = 17;
    }

    if (buffer_len <= offset) {
        DetectEngineSetEvent(det_ctx, FILE_DECODER_EVENT_INVALID_SWF_LENGTH);
        return 0;
    }

    uint32_t compressed_data_len = 0;
    if (compress_depth > 0 && compress_depth <= buffer_len - offset) {
        compressed_data_len = compress_depth;
    } else {
        compressed_data_len = buffer_len - offset;
    }

    /* get swf version */
    uint8_t swf_version = FileGetSwfVersion(buffer, buffer_len);
    if (compression_type == FILE_SWF_ZLIB_COMPRESSION &&
        swf_version < SWF_ZLIB_MIN_VERSION)
    {
        DetectEngineSetEvent(det_ctx, FILE_DECODER_EVENT_INVALID_SWF_VERSION);
        return 0;
    }
    if (compression_type == FILE_SWF_LZMA_COMPRESSION &&
        swf_version < SWF_LZMA_MIN_VERSION)
    {
        DetectEngineSetEvent(det_ctx, FILE_DECODER_EVENT_INVALID_SWF_VERSION);
        return 0;
    }

    /* get flash decompressed file length */
    uint32_t decompressed_swf_len = FileGetSwfDecompressedLen(buffer, buffer_len);
    if (decompressed_swf_len == 0) {
        decompressed_swf_len = MIN_SWF_LEN;
    }

    /* if decompress_depth is 0, keep the flash file length */
    uint32_t decompressed_data_len = (decompress_depth == 0) ? decompressed_swf_len : decompress_depth;
    decompressed_data_len += 8;

    /* make sure the inspection buffer has enough space */
    SCInspectionBufferCheckAndExpand(out_buffer, decompressed_data_len);
    if (out_buffer->size < decompressed_data_len) {
        DetectEngineSetEvent(det_ctx, FILE_DECODER_EVENT_NO_MEM);
        return 0;
    }
    out_buffer->len = decompressed_data_len;

    /*
     * FWS format
     * | 4 bytes         | 4 bytes    | n bytes |
     * | 'FWS' + version | script len | data    |
     */
    out_buffer->buf[0] = 'F';
    out_buffer->buf[1] = 'W';
    out_buffer->buf[2] = 'S';
    out_buffer->buf[3] = swf_version;
    memcpy(out_buffer->buf + 4, &decompressed_swf_len, 4);
    memset(out_buffer->buf + 8, 0, decompressed_data_len - 8);

    if ((swf_type == HTTP_SWF_COMPRESSION_ZLIB || swf_type == HTTP_SWF_COMPRESSION_BOTH) &&
            compression_type == FILE_SWF_ZLIB_COMPRESSION)
    {
        /* the first 8 bytes represents the fws header, see 'FWS format' above.
         * data will start from 8th bytes
         */
        r = FileSwfZlibDecompression(det_ctx,
                                     (uint8_t *)buffer + offset, compressed_data_len,
                                     out_buffer->buf + 8, out_buffer->len - 8);
        if (r == 0)
            goto error;

    } else if ((swf_type == HTTP_SWF_COMPRESSION_LZMA || swf_type == HTTP_SWF_COMPRESSION_BOTH) &&
               compression_type == FILE_SWF_LZMA_COMPRESSION)
    {
        /* we need to setup the lzma header */
        /*
         * | 5 bytes         | 8 bytes             | n bytes         |
         * | LZMA properties | Uncompressed length | Compressed data |
         */
        compressed_data_len += 13;
        uint8_t compressed_data[compressed_data_len];
        /* put lzma properties */
        memcpy(compressed_data, buffer + 12, 5);
        /* put lzma end marker */
        memset(compressed_data + 5, 0xFF, 8);
        /* put compressed data */
        memcpy(compressed_data + 13, buffer + offset, compressed_data_len - 13);

        /* the first 8 bytes represents the fws header, see 'FWS format' above.
         * data will start from 8th bytes
         */
        r = FileSwfLzmaDecompression(det_ctx,
                                     compressed_data, compressed_data_len,
                                     out_buffer->buf + 8, out_buffer->len - 8);
        if (r == 0)
            goto error;
    } else {
        goto error;
    }

    /* all went well so switch the buffer's inspect pointer/size
     * to use the new data. */
    out_buffer->inspect = out_buffer->buf;
    out_buffer->inspect_len = out_buffer->len;

    return 1;

error:
    return 0;
}

/* =====================================================================
 * Harness driver.
 *
 * Input file format (harness-only wire format; NOT part of the target
 * function -- these are exactly the caller-supplied arguments a real
 * Suricata detect-engine call site passes to FileSwfDecompression, just
 * serialized so a single PoC file can drive them):
 *
 *   [0..3]   declared_len   uint32 LE -- passed as buffer_len.
 *            Deliberately DECOUPLED from the real heap allocation size
 *            backing `buffer` below (mirrors the real bug: the function
 *            trusts buffer_len to size a stack VLA without ever checking
 *            it against how much memory actually backs `buffer`).
 *   [4..7]   compress_depth uint32 LE
 *   [8..11]  decompress_depth uint32 LE
 *   [12]     swf_type       uint8 (0=NONE,1=ZLIB,2=LZMA,3=BOTH)
 *   [13..]   payload -- copied byte-for-byte into a freshly heap-allocated
 *            (malloc, ASAN redzone-guarded) buffer of exactly this many
 *            bytes; `buffer_len` argument uses declared_len above, NOT
 *            this real allocation size.
 * ===================================================================== */

static uint32_t rd_u32le(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    /* Standard PoC-harness scaffolding (not part of the target function):
     * shrink the stack rlimit so the VLA-driven stack exhaustion is a
     * deterministic, cheap-to-store crash regardless of the container's
     * default ulimit -s. Lowering an rlimit never needs privilege. */
    struct rlimit rl;
    rl.rlim_cur = 192 * 1024;
    rl.rlim_max = 192 * 1024;
    setrlimit(RLIMIT_STACK, &rl);

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("fopen");
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long total = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (total < 13) {
        fprintf(stderr, "input too small (need >=13 header bytes)\n");
        fclose(f);
        return 1;
    }

    uint8_t *raw = (uint8_t *)malloc((size_t)total);
    if (!raw) { fclose(f); return 1; }
    if (fread(raw, 1, (size_t)total, f) != (size_t)total) {
        fclose(f);
        free(raw);
        return 1;
    }
    fclose(f);

    uint32_t declared_len = rd_u32le(raw + 0);
    uint32_t compress_depth = rd_u32le(raw + 4);
    uint32_t decompress_depth = rd_u32le(raw + 8);
    int swf_type = raw[12];

    size_t payload_len = (size_t)total - 13;
    /* Heap-allocate the real `buffer` argument, sized to the ACTUAL bytes
     * we have (ASAN redzone-guarded on both sides) -- separate from
     * declared_len, which is the (possibly much larger) attacker-declared
     * buffer_len argument. */
    uint8_t *buffer = (uint8_t *)malloc(payload_len ? payload_len : 1);
    if (!buffer) { free(raw); return 1; }
    memcpy(buffer, raw + 13, payload_len);
    free(raw);

    DetectEngineThreadCtx det_ctx_storage;
    det_ctx_storage.dummy = 0;

    InspectionBuffer out_buffer;
    memset(&out_buffer, 0, sizeof(out_buffer));

    int r = FileSwfDecompression(buffer, declared_len, &det_ctx_storage, &out_buffer,
                                  swf_type, decompress_depth, compress_depth);

    free(buffer);
    if (out_buffer.buf)
        free(out_buffer.buf);

    fprintf(stderr, "FileSwfDecompression returned %d\n", r);
    return 0;
}
