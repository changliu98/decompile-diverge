/*
 * Decompile-Diverge direct-call harness -- cve_ce7ebddd (vim, patch 8.2.4233)
 *
 * TARGET FUNCTION (embedded VERBATIM below, unmodified): delete_buff_tail
 *   src/getchar.c, pre-fix (vulnerable) revision.
 *
 * Bug: delete_buff_tail(buf, slen) unconditionally does
 *      int len = (int)STRLEN(buf->bh_curr->b_str);
 *   with no check that buf->bh_curr is non-NULL first.  buf->bh_curr is a
 *   buffblock_T* that stays NULL for any buffheader_T that has never had
 *   anything appended to it: add_buff() only assigns bh_curr "on first
 *   add" (`if (buf->bh_first.b_next == NULL) { ... buf->bh_curr =
 *   &(buf->bh_first); }`).  The stuff/redo/record buffers this function is
 *   used on are plain zero-initialized globals (e.g. `recordbuff`), so a
 *   never-appended-to buffheader_T is bh_curr == NULL by construction.
 *
 *   The real call site is ungetchars() (also in src/getchar.c):
 *       void ungetchars(int len) {
 *           if (reg_recording != 0) {
 *               delete_buff_tail(&recordbuff, len);
 *               ...
 *           }
 *       }
 *   which calls delete_buff_tail() unconditionally whenever a recording is
 *   active, with no check that anything was actually recorded yet -- so a
 *   recording session that reaches ungetchars() before any character was
 *   ever added to recordbuff hits delete_buff_tail() with
 *   recordbuff.bh_curr == NULL, and `buf->bh_curr->b_str` dereferences a
 *   near-NULL pointer (NULL + offsetof(buffblock_T, b_str)) -> SIGSEGV.
 *
 *   Fixed upstream (commit a4bc2dd7cccf5a4a9f78b58b6f35a45d17164323) by
 *   adding, before the STRLEN call:
 *       if (buf->bh_curr == NULL || buf->bh_curr->b_str == NULL)
 *           return;  // nothing to delete
 *
 *   ASAN/SEGV classifies this as CWE-476 (NULL pointer dereference).
 *
 * Harness I/O contract (all attacker bytes live in a single HEAP buffer,
 * required so ASAN can catch the near-NULL access):
 *   argv[1] byte[0]    mode selector: EVEN => TRIGGER (buf.bh_curr is left
 *                      NULL, mirroring a never-appended-to buffheader_T --
 *                      the exact state ungetchars() hands to
 *                      delete_buff_tail() in the real bug); ODD => SAFE
 *                      (buf.bh_curr is pointed at a freshly heap-allocated,
 *                      NUL-terminated buffblock_T, mirroring the state
 *                      add_buff() leaves behind after a normal append).
 *   argv[1] byte[1]    (SAFE path only) slen selector, reduced modulo
 *                      (content length + 1) so "len >= slen" always holds
 *                      against real content -- the write this exercises
 *                      stays provably in-bounds.
 *   argv[1] byte[2..]  (SAFE path only) the buffblock's b_str payload,
 *                      copied verbatim; the harness appends the real
 *                      NUL terminator delete_buff_tail's STRLEN relies on.
 *
 *   main() reads argv[1] into a malloc'd heap buffer and calls
 *   delete_buff_tail() ONCE with a stack buffheader_T built per the above
 *   -- exactly the shape ungetchars()'s &recordbuff argument has in the
 *   real crash (a buffheader_T whose bh_curr is either NULL or a single
 *   heap-allocated buffblock_T).
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * Real type/macro definitions, copied verbatim from vim's
 * src/vim.h / src/structs.h / src/ascii.h (trimmed to exactly what
 * delete_buff_tail touches).
 * ============================================================ */

typedef unsigned char char_u;                  /* src/vim.h:341 */

#define NUL		'\000'                  /* src/ascii.h:24 */

#define STRLEN(s)	    strlen((char *)(s)) /* src/vim.h:1621 */

typedef struct buffblock buffblock_T;          /* src/structs.h:550 */
typedef struct buffheader buffheader_T;        /* src/structs.h:551 */

/*
 * structure used to store one block of the stuff/redo/recording buffers
 * (src/structs.h, verbatim)
 */
struct buffblock
{
    buffblock_T	*b_next;	// pointer to next buffblock
    char_u	b_str[1];	// contents (actually longer)
};

/*
 * header used for the stuff buffer and the redo buffer
 * (src/structs.h, verbatim)
 */
struct buffheader
{
    buffblock_T	bh_first;	// first (dummy) block of list
    buffblock_T	*bh_curr;	// buffblock for appending
    int		bh_index;	// index for reading
    int		bh_space;	// space in bh_curr for appending
};

/* ============================================================
 * TARGET FUNCTION, embedded VERBATIM (byte-for-byte from
 * target/original_function.c): src/getchar.c delete_buff_tail()
 * ============================================================ */

static void
delete_buff_tail(buffheader_T *buf, int slen)
{
    int len = (int)STRLEN(buf->bh_curr->b_str);

    if (len >= slen)
    {
	buf->bh_curr->b_str[len - slen] = NUL;
	buf->bh_space += slen;
    }
}

/* ============================================================
 * main() -- reads argv[1] into a HEAP buffer and calls
 * delete_buff_tail() once with a buffheader_T shaped exactly like
 * ungetchars()'s &recordbuff: either freshly zero-initialized (never
 * appended to -> bh_curr == NULL, the real bug) or pointing at one
 * heap-allocated buffblock_T (mirrors what add_buff() leaves behind
 * after a normal append).
 * ============================================================ */

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
    fseek(f, 0, SEEK_END);
    long fsz = ftell(f);
    if (fsz < 0)
        fsz = 0;
    fseek(f, 0, SEEK_SET);

    /* Attacker-controlled data MUST live on the heap so ASAN can catch a
     * wild/near-NULL access into/around it. */
    size_t alloc_len = (size_t) fsz > 0 ? (size_t) fsz : 1;
    uint8_t *raw = (uint8_t *) malloc(alloc_len);
    if (!raw) {
        fclose(f);
        return 1;
    }
    size_t raw_len = fsz > 0 ? fread(raw, 1, (size_t) fsz, f) : 0;
    fclose(f);

    buffheader_T buf;
    memset(&buf, 0, sizeof(buf));   /* bh_curr = NULL: the "never appended to" state */
    int slen = 0;
    int mode_trigger = 1;           /* default: empty input -> TRIGGER */
    buffblock_T *blk = NULL;

    if (raw_len >= 1 && (raw[0] & 1) != 0)
        mode_trigger = 0;           /* odd first byte -> SAFE path */

    if (!mode_trigger) {
        /* SAFE path: mirror add_buff()'s post-condition -- bh_curr points
         * at a real, heap-allocated, NUL-terminated buffblock_T, so
         * delete_buff_tail()'s STRLEN/index/write all operate on a valid
         * live allocation. */
        size_t content_len = (raw_len > 2) ? (raw_len - 2) : 0;
        blk = (buffblock_T *) malloc(sizeof(buffblock_T) + content_len + 1);
        if (!blk) {
            free(raw);
            return 1;
        }
        blk->b_next = NULL;
        if (content_len > 0)
            memcpy(blk->b_str, raw + 2, content_len);
        blk->b_str[content_len] = NUL;   /* real STRLEN-terminated content */

        buf.bh_curr = &blk[0];
        buf.bh_space = 0;

        uint8_t sel = (raw_len >= 2) ? raw[1] : 0;
        /* len (delete_buff_tail's own STRLEN result) is <= content_len,
         * so bounding slen by content_len+1 guarantees "len >= slen"
         * only ever indexes b_str within [0, content_len] -- in-bounds
         * of the (sizeof(buffblock_T)+content_len+1)-byte allocation. */
        slen = (int) (sel % (content_len + 1));
    }
    /* else: mode_trigger -- buf stays zeroed, buf.bh_curr == NULL, exactly
     * the state ungetchars() hands to delete_buff_tail() for an empty
     * recording buffer.  slen is irrelevant here: the crash is on the
     * very first dereference of buf->bh_curr, before slen is ever used. */

    delete_buff_tail(&buf, slen);

    fprintf(stderr, "delete_buff_tail returned normally (slen=%d, trigger=%d, raw_len=%zu)\n",
            slen, mode_trigger, raw_len);

    if (blk)
        free(blk);
    free(raw);
    return 0;
}
