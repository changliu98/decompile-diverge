/* cve_barebone direct-call harness for htslib bgzf_index_load_hfile (CVE-2026-31970, CWE-787).
 *
 * Isolation: the vulnerable function is pasted BYTE-FOR-BYTE from
 * data_cve/cve_e7fe959d/target/original_function.c, together with the REAL htslib
 * type definitions (BGZF, hFILE, bgzidx_t, bgzidx1_t) and the REAL crash-path
 * callees (hread_uint64, hread, ed_is_big/ed_swap_8/ed_swap_8p) copied verbatim
 * from source_code/. Incidental logging (hts_log_error) is a faithful stub.
 *
 * Bug: hread_uint64 reads a uint64_t x from the index; noffs=moffs=x+1 is stored
 * in an `int`. When the low 32 bits of x are 0xFFFFFFFF, x+1 narrows to moffs=0,
 * so `malloc(0*sizeof(bgzidx1_t)) == malloc(0)` returns a 0-byte region and the
 * write `fp->idx->offs[0].caddr = fp->idx->offs[0].uaddr = 0;` (bgzf.c:2478)
 * overflows it -> ASAN heap-buffer-overflow WRITE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/types.h>

/* ---- opaque forward decls for BGZF's other pointer members (never touched) ---- */
struct hFILE_backend;
struct bgzf_mtaux_t;
struct z_stream_s;
typedef struct bgzf_cache_t bgzf_cache_t;

/* ---- REAL htslib index types (source_code/bgzf.c:162-174) ---- */
typedef struct
{
    uint64_t uaddr;  // offset w.r.t. uncompressed data
    uint64_t caddr;  // offset w.r.t. compressed data
}
bgzidx1_t;

struct bgzidx_t
{
    int noffs, moffs;       // the size of the index, n:used, m:allocated
    bgzidx1_t *offs;        // offsets
    uint64_t ublock_addr;   // offset of the current block (uncompressed data)
};
typedef struct bgzidx_t bgzidx_t;

/* ---- REAL BGZF struct (source_code/htslib/bgzf.h:68-84) ---- */
struct BGZF {
    // Reserved bits should be written as 0; read as "don't care"
    unsigned errcode:16, reserved:1, is_write:1, no_eof_block:1, is_be:1;
    signed compress_level:9;
    unsigned last_block_eof:1, is_compressed:1, is_gzip:1;
    int cache_size;
    int block_length, block_clength, block_offset;
    int64_t block_address, uncompressed_address;
    void *uncompressed_block, *compressed_block;
    bgzf_cache_t *cache;
    struct hFILE *fp; // actual file handle
    struct bgzf_mtaux_t *mt; // only used for multi-threading
    bgzidx_t *idx;      // BGZF index
    int idx_build_otf;  // build index on the fly, set by bgzf_index_build_init()
    struct z_stream_s *gz_stream; // for gzip-compressed files
    int64_t seeked;     // virtual offset of last seek
};
typedef struct BGZF BGZF;

/* ---- REAL hFILE struct (source_code/htslib/hfile.h:55-63) ---- */
typedef struct hFILE {
    char *buffer, *begin, *end, *limit;
    const struct hFILE_backend *backend;
    off_t offset;
    unsigned at_eof:1, mobile:1, readonly:1, preserve:1;
    int has_errno;
} hFILE;

/* ---- REAL endian helpers (source_code/htslib/hts.h:1567-1600) ---- */
static inline int ed_is_big(void)
{
    long one= 1;
    return !(*((char *)(&one)));
}
static inline uint64_t ed_swap_8(uint64_t v)
{
    v = ((v & 0x00000000FFFFFFFFLLU) << 32) | (v >> 32);
    v = ((v & 0x0000FFFF0000FFFFLLU) << 16) | ((v & 0xFFFF0000FFFF0000LLU) >> 16);
    return ((v & 0x00FF00FF00FF00FFLLU) << 8) | ((v & 0xFF00FF00FF00FF00LLU) >> 8);
}
static inline void *ed_swap_8p(void *x)
{
    *(uint64_t*)x = ed_swap_8(*(uint64_t*)x);
    return x;
}

/* ---- REAL hread (source_code/htslib/hfile.h:234-245). With mobile=0 the
 * hread2 slow path is never taken; a faithful stub satisfies the reference. ---- */
static ssize_t hread2(hFILE *fp, void *buffer, size_t nbytes, size_t nread)
{
    (void)fp; (void)buffer; (void)nbytes;   // unreachable when mobile==0
    return (ssize_t) nread;
}
static inline ssize_t hread(hFILE *fp, void *buffer, size_t nbytes)
{
    size_t n = fp->end - fp->begin;
    if (n > nbytes) n = nbytes;
    memcpy(buffer, fp->begin, n);
    fp->begin += n;
    return (n == nbytes || !fp->mobile)? (ssize_t) n : hread2(fp, buffer, nbytes, n);
}

/* ---- incidental logging: faithful stub for hts_log_error ---- */
static void hts_log_error(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
}

/* ---- REAL hread_uint64 (source_code/bgzf.c:2461-2466), verbatim ---- */
static inline int hread_uint64(uint64_t *xptr, hFILE *f)
{
    if (hread(f, xptr, sizeof(*xptr)) != sizeof(*xptr)) return -1;
    if (ed_is_big()) ed_swap_8p(xptr);
    return 0;
}

/* ===================================================================== */
/* TARGET FUNCTION — pasted BYTE-FOR-BYTE from                            */
/* data_cve/cve_e7fe959d/target/original_function.c (do NOT edit)         */
/* ===================================================================== */
int bgzf_index_load_hfile(BGZF *fp, struct hFILE *idx, const char *name)
{
    fp->idx = (bgzidx_t*) calloc(1,sizeof(bgzidx_t));
    if (fp->idx == NULL) goto fail;
    uint64_t x;
    if (hread_uint64(&x, idx) < 0) goto fail;

    fp->idx->noffs = fp->idx->moffs = x + 1;
    fp->idx->offs  = (bgzidx1_t*) malloc(fp->idx->moffs*sizeof(bgzidx1_t));
    if (fp->idx->offs == NULL) goto fail;
    fp->idx->offs[0].caddr = fp->idx->offs[0].uaddr = 0;

    int i;
    for (i=1; i<fp->idx->noffs; i++)
    {
        if (hread_uint64(&fp->idx->offs[i].caddr, idx) < 0) goto fail;
        if (hread_uint64(&fp->idx->offs[i].uaddr, idx) < 0) goto fail;
    }

    return 0;

 fail:
    hts_log_error("Error reading %s : %s", name ? name : "index", strerror(errno));
    if (fp->idx) {
        free(fp->idx->offs);
        free(fp->idx);
        fp->idx = NULL;
    }
    return -1;
}
/* ===================================================================== */

/* Read a whole file into a freshly malloc'd heap buffer (ASAN-guarded). */
static unsigned char *slurp(const char *path, size_t *len_out)
{
    FILE *f = fopen(path, "rb");
    if (!f) { perror("fopen"); exit(2); }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); exit(2); }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); exit(2); }
    rewind(f);
    /* malloc(0) is legal; ensure a non-NULL heap region even for empty files */
    unsigned char *buf = (unsigned char *) malloc(sz ? (size_t) sz : 1);
    if (!buf) { fclose(f); exit(2); }
    size_t got = sz ? fread(buf, 1, (size_t) sz, f) : 0;
    fclose(f);
    *len_out = got;
    return buf;
}

int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

    size_t len = 0;
    unsigned char *data = slurp(argv[1], &len);   // HEAP buffer -> ASAN-guarded

    /* Back a real hFILE with the heap input; mobile=0 so hread never needs hread2. */
    hFILE idx;
    memset(&idx, 0, sizeof(idx));
    idx.buffer   = (char *) data;
    idx.begin    = (char *) data;
    idx.end      = (char *) data + len;
    idx.limit    = (char *) data + len;
    idx.offset   = 0;
    idx.at_eof   = 0;
    idx.mobile   = 0;      // non-mobile in-memory buffer: hread reads directly
    idx.readonly = 1;

    BGZF *fp = (BGZF *) calloc(1, sizeof(BGZF));
    if (!fp) { free(data); return 2; }

    int rc = bgzf_index_load_hfile(fp, &idx, "index");
    (void) rc;

    free(fp);
    free(data);
    return 0;
}
