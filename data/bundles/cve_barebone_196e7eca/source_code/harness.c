/* cve_196e7eca (CVE-2017-14222) direct-call harness for ffmpeg's read_tfra (libavformat/mov.c).
 *
 * read_tfra() reads an attacker-controlled `item_count` (uint32, no cap) from the input and
 * then loops `item_count` times pulling `time`/`offset`/skip bytes straight off the AVIOContext
 * `f` with no per-iteration bounds check. The fix (commit 9cb4eb7) adds an avio_feof(f) check
 * inside that very loop -- i.e. the missing check is the trigger condition we reproduce here.
 *
 * To isolate read_tfra we replace the real (multi-file, buffered-refill) AVIOContext with a
 * minimal direct-buffer reader over a single heap allocation sized EXACTLY to the attacker
 * input (malloc(file_len), no slack/padding). Real avio_r8() pads with 0 at true stream EOF
 * (a different I/O layer we are not reproducing); our minimal reader instead does the raw
 * pointer walk read_tfra's own loop assumes is safe, so once the loop consumes more bytes than
 * the input actually holds, the read runs off the end of the heap allocation -- a genuine
 * ASAN heap-buffer-overflow READ inside read_tfra's own body (CWE-125), not in scaffolding.
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

/* ---- libavutil/common.h + libavutil/error.h macros, real names/values ---- */
#define MKTAG(a,b,c,d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#define MKBETAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((unsigned)(a) << 24))
#define FFERRTAG(a,b,c,d) (-(int)MKTAG(a,b,c,d))
#define AVERROR(e) (-(e))
#define AVERROR_INVALIDDATA FFERRTAG('I','N','D','A')
#define AV_LOG_VERBOSE 40

typedef struct AVFormatContext AVFormatContext; /* opaque; only ever passed through as a log handle */

static void av_log(void *avcl, int level, const char *fmt, ...) {
    (void)avcl; (void)level; (void)fmt;
}

/* ---- libavutil/mem.c-equivalent allocators: same overflow-checked contract as the real
 * av_mallocz / av_mallocz_array / av_realloc_array / av_freep, minimal bodies. ---- */
static void *av_mallocz(size_t size) {
    void *p;
    if (!size) size = 1;
    p = malloc(size);
    if (p) memset(p, 0, size);
    return p;
}
static void *av_mallocz_array(size_t nmemb, size_t size) {
    if (size == 0 || nmemb > (SIZE_MAX / size)) return NULL;
    return av_mallocz(nmemb * size);
}
static void *av_realloc_array(void *ptr, size_t nmemb, size_t size) {
    if (size == 0 || nmemb > (SIZE_MAX / size)) return NULL;
    return realloc(ptr, nmemb * size);
}
static void av_freep(void *arg) {
    void **p = (void **)arg;
    free(*p);
    *p = NULL;
}

/* ---- real struct defs, copied verbatim from libavformat/isom.h ---- */
typedef struct MOVFragmentIndexItem {
    int64_t moof_offset;
    int64_t time;
    int headers_read;
} MOVFragmentIndexItem;

typedef struct MOVFragmentIndex {
    unsigned track_id;
    unsigned item_count;
    unsigned current_item;
    MOVFragmentIndexItem *items;
} MOVFragmentIndex;

/* Minimal MOVContext: carries only the real fields (real names/types) read_tfra touches
 * (mov->fc, mov->fragment_index_data, mov->fragment_index_count) -- the rest of the real
 * struct (AVStream/chapter/etc. bookkeeping) is untouched by read_tfra's body. */
typedef struct MOVContext {
    AVFormatContext *fc;
    MOVFragmentIndex **fragment_index_data;
    unsigned fragment_index_count;
} MOVContext;

/* ---- minimal direct-buffer AVIOContext (see file header comment) ---- */
typedef struct AVIOContext {
    uint8_t *buf;
    size_t size;
    size_t pos;
} AVIOContext;

static int64_t avio_tell(AVIOContext *s) { return (int64_t)s->pos; }

static int avio_r8(AVIOContext *s) {
    return s->buf[s->pos++];
}

static unsigned int avio_rb24(AVIOContext *s) {
    unsigned int val = avio_r8(s) << 16;
    val |= avio_r8(s) << 8;
    val |= avio_r8(s);
    return val;
}

static unsigned int avio_rb32(AVIOContext *s) {
    unsigned int val = avio_rb24(s) << 8;
    val |= avio_r8(s);
    return val;
}

static int64_t avio_rb64(AVIOContext *s) {
    uint64_t hi = avio_rb32(s);
    uint64_t lo = avio_rb32(s);
    return (int64_t)((hi << 32) | lo);
}

static int64_t avio_seek(AVIOContext *s, int64_t offset, int whence) {
    (void)whence;
    s->pos = (size_t)offset;
    return (int64_t)s->pos;
}

/* ==== FUNCTION: read_tfra -- pasted byte-for-byte from
 * data_cve/cve_196e7eca/target/original_function.c ==== */
static int read_tfra(MOVContext *mov, AVIOContext *f)
{
    MOVFragmentIndex* index = NULL;
    int version, fieldlength, i, j;
    int64_t pos = avio_tell(f);
    uint32_t size = avio_rb32(f);
    void *tmp;

    if (avio_rb32(f) != MKBETAG('t', 'f', 'r', 'a')) {
        return 1;
    }
    av_log(mov->fc, AV_LOG_VERBOSE, "found tfra\n");
    index = av_mallocz(sizeof(MOVFragmentIndex));
    if (!index) {
        return AVERROR(ENOMEM);
    }

    tmp = av_realloc_array(mov->fragment_index_data,
                           mov->fragment_index_count + 1,
                           sizeof(MOVFragmentIndex*));
    if (!tmp) {
        av_freep(&index);
        return AVERROR(ENOMEM);
    }
    mov->fragment_index_data = tmp;
    mov->fragment_index_data[mov->fragment_index_count++] = index;

    version = avio_r8(f);
    avio_rb24(f);
    index->track_id = avio_rb32(f);
    fieldlength = avio_rb32(f);
    index->item_count = avio_rb32(f);
    index->items = av_mallocz_array(
            index->item_count, sizeof(MOVFragmentIndexItem));
    if (!index->items) {
        index->item_count = 0;
        return AVERROR(ENOMEM);
    }
    for (i = 0; i < index->item_count; i++) {
        int64_t time, offset;
        if (version == 1) {
            time   = avio_rb64(f);
            offset = avio_rb64(f);
        } else {
            time   = avio_rb32(f);
            offset = avio_rb32(f);
        }
        index->items[i].time = time;
        index->items[i].moof_offset = offset;
        for (j = 0; j < ((fieldlength >> 4) & 3) + 1; j++)
            avio_r8(f);
        for (j = 0; j < ((fieldlength >> 2) & 3) + 1; j++)
            avio_r8(f);
        for (j = 0; j < ((fieldlength >> 0) & 3) + 1; j++)
            avio_r8(f);
    }

    avio_seek(f, pos + size, SEEK_SET);
    return 0;
}
/* ==== END FUNCTION ==== */

int main(int argc, char **argv) {
    if (argc < 2) return 0;
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) return 0;
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 0; }
    long fsz = ftell(fp);
    if (fsz < 0) { fclose(fp); return 0; }
    fseek(fp, 0, SEEK_SET);

    /* heap-allocate the input EXACTLY the size of the file -- no slack padding, so a raw
     * pointer read past it is a real ASAN heap-buffer-overflow. */
    uint8_t *buf = (uint8_t *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
    if (!buf) { fclose(fp); return 0; }
    size_t rd = fread(buf, 1, (size_t)fsz, fp);
    fclose(fp);

    AVIOContext io;
    io.buf = buf;
    io.size = rd;
    io.pos = 0;

    MOVContext mov;
    memset(&mov, 0, sizeof(mov));

    read_tfra(&mov, &io);

    for (unsigned i = 0; i < mov.fragment_index_count; i++) {
        if (mov.fragment_index_data[i]) {
            free(mov.fragment_index_data[i]->items);
            free(mov.fragment_index_data[i]);
        }
    }
    free(mov.fragment_index_data);
    free(buf);
    return 0;
}
