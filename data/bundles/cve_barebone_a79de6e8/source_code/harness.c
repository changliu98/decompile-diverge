/* Direct-call crash harness for libmobi CVE-2021-3751 (CWE-787).
 *
 * Target: mobi_buffer_move (src/buffer.c) — embedded VERBATIM.
 * Bug: the offset<0 branch only checks `buf->offset < aoffset` (that the
 * backward SOURCE read doesn't run before buf->data) but never checks that
 * the forward DESTINATION write `buf->data + buf->offset` .. `+ len` stays
 * inside `buf->maxlen` — unlike the offset>=0 branch, which does check that.
 * A single call with buf->offset near the end of a heap buffer and offset<0
 * therefore memmove()s past the end of the heap allocation: a WRITE
 * heap-buffer-overflow inside mobi_buffer_move, matching the real bug's
 * dedup token __asan_memmove--mobi_buffer_move--mobi_decompress_lz77 (the
 * real caller loops mobi_buffer_move(buf_out, -distance, 1) while decoding
 * a PalmDOC LZ77 back-reference, growing buf_out->offset past maxlen with
 * no destination bound check — exactly the missing check reproduced here).
 *
 * Minimal REAL type/macro defs are lifted verbatim from libmobi's
 * src/mobi.h (MOBI_RET enum values), src/buffer.h (MOBIBuffer), and
 * src/debug.h (debug_print, no-op in release builds) — just enough for
 * mobi_buffer_move to compile standalone, no other project code needed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- from src/mobi.h (MOBI_RET, subset actually used by buffer.c) ---- */
typedef enum {
    MOBI_SUCCESS = 0,   /**< Generic success return value */
    MOBI_BUFFER_END = 9 /**< Out of buffer error */
} MOBI_RET;

/* ---- from src/buffer.h ---- */
typedef struct {
    size_t offset;        /**< Current offset in respect to buffer start */
    size_t maxlen;         /**< Length of the buffer data */
    unsigned char *data;   /**< Pointer to buffer data */
    MOBI_RET error;        /**< MOBI_SUCCESS = 0 if operation on buffer is successful, non-zero value on failure */
} MOBIBuffer;

/* ---- from src/debug.h (release build: debug_print is a no-op) ---- */
#define debug_print(fmt, ...)

/* ==== target function, VERBATIM from dataset/cve_a79de6e8/target/original_function.c ==== */
void mobi_buffer_move(MOBIBuffer *buf, const int offset, const size_t len) {
    size_t aoffset = (size_t) abs(offset);
    unsigned char *source = buf->data + buf->offset;
    if (offset >= 0) {
        if (buf->offset + aoffset + len > buf->maxlen) {
            debug_print("%s", "End of buffer\n");
            buf->error = MOBI_BUFFER_END;
            return;
        }
        source += aoffset;
    } else {
        if (buf->offset < aoffset) {
            debug_print("%s", "End of buffer\n");
            buf->error = MOBI_BUFFER_END;
            return;
        }
        source -= aoffset;
    }
    memmove(buf->data + buf->offset, source, len);
    buf->offset += len;
}
/* ==== end target function ==== */

/* ---- harness ----
 * argv[1] is a raw file laid out as:
 *   bytes [0:4)  little/host-endian uint32 -> initial buf.offset
 *   bytes [4:8)  host-endian int32          -> `offset` arg to mobi_buffer_move
 *   bytes [8:12) host-endian uint32         -> `len` arg to mobi_buffer_move
 *   bytes [12:)  the vulnerable MOBIBuffer's backing store: copied into a
 *                HEAP buffer of EXACTLY that many bytes (no slack) so ASAN's
 *                redzone sits right where the real allocation ends, and
 *                buf.maxlen == that exact size. This mirrors mobi_buffer_out
 *                being sized to `*len_out` by the real caller
 *                (mobi_buffer_init_null(out, *len_out) in mobi_decompress_lz77).
 * The struct fields (offset/maxlen/data) and the move() call's own args are
 * ALL attacker-controlled, exactly as they are in the real bug: buf->offset
 * is driven by the compressed stream's own history of prior moves, and the
 * (offset,len) pair is decoded straight from the compressed byte stream
 * (distance/length of a PalmDOC LZ77 back-reference).
 */
#define HDR_SIZE 12

int main(int argc, char **argv) {
    if (argc < 2) return 1;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 1;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    long fsz = ftell(f);
    if (fsz < 0) { fclose(f); return 1; }
    fseek(f, 0, SEEK_SET);

    if (fsz < HDR_SIZE) {
        /* too short to encode header -> nothing to do, exit clean */
        fclose(f);
        return 0;
    }

    unsigned char *filebuf = (unsigned char *) malloc((size_t) fsz);
    if (!filebuf) { fclose(f); return 1; }
    size_t nread = fread(filebuf, 1, (size_t) fsz, f);
    fclose(f);
    if (nread != (size_t) fsz) { free(filebuf); return 1; }

    uint32_t u_init = 0, u_len = 0;
    int32_t s_offset = 0;
    memcpy(&u_init, filebuf + 0, 4);
    memcpy(&s_offset, filebuf + 4, 4);
    memcpy(&u_len, filebuf + 8, 4);

    size_t bufsize = (size_t) (fsz - HDR_SIZE);
    unsigned char *heapbuf;
    if (bufsize > 0) {
        heapbuf = (unsigned char *) malloc(bufsize);
        if (!heapbuf) { free(filebuf); return 1; }
        memcpy(heapbuf, filebuf + HDR_SIZE, bufsize);
    } else {
        /* keep buf.data a valid non-NULL heap pointer even for an empty backing store */
        heapbuf = (unsigned char *) malloc(1);
        if (!heapbuf) { free(filebuf); return 1; }
    }
    free(filebuf);

    MOBIBuffer buf;
    buf.data = heapbuf;
    buf.maxlen = bufsize;
    buf.offset = (size_t) u_init;
    buf.error = MOBI_SUCCESS;

    int move_offset = (int) s_offset;
    size_t move_len = (size_t) u_len;

    mobi_buffer_move(&buf, move_offset, move_len);

    free(heapbuf);
    return 0;
}
