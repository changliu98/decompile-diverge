/* cve_barebone harness -- php-src CVE-2016-5766 / _gd2GetHeader integer overflow
 * -> heap-buffer-overflow WRITE (CWE-787), upstream bug #72339.
 *
 * Isolated reproduction: _gd2GetHeader() is called directly on a hand-built in-memory
 * "GD2 file" (a minimal gdIOCtx backed by a heap buffer). GD2 header fields ncx/ncy
 * ("chunks wide"/"chunks high") are each an attacker-controlled 16-bit word; the
 * pre-fix body computes `sidx = sizeof(t_chunk_info) * (ncx*ncy)` in plain `int`
 * arithmetic with no overflow guard, then gdCalloc(sidx, 1)s that (possibly wrapped,
 * too-small) byte count while the read loop right below is still bounded by the
 * UN-wrapped chunk count -- a classic undersized-alloc-then-OOB-fill.
 *
 * TRIGGER: ncx*ncy chosen so `8 * (ncx*ncy)` overflows 32-bit int down to a small
 *          positive `sidx` (see the module docstring for the exact arithmetic), while
 *          `nc` itself stays huge and positive -> the header-index read loop writes
 *          well past the tiny gdCalloc allocation -> ASAN heap-buffer-overflow WRITE
 *          inside _gd2GetHeader itself.
 * SAFE:    every other path -- bad magic/version/chunk-size/format, EOF-truncated
 *          headers, ncx==0 || ncy==0 (the sidx<=0 guard catches that legitimately),
 *          GD2_FMT_RAW (never enters the indexed-chunk branch at all), and small
 *          NON-overflowing ncx*ncy pairs with a fully-matching, correctly-sized index
 *          (the same code path as the trigger, just with values that don't overflow) --
 *          _gd2GetHeader returns cleanly (0 or 1), no crash.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- real GD2 constants (gd.h, verbatim) ---- */
#define GD2_CHUNKSIZE_MIN       64
#define GD2_CHUNKSIZE_MAX       4096
#define GD2_ID                  "gd2"
#define GD2_FMT_RAW             1
#define GD2_FMT_COMPRESSED      2

/* ---- real GD2 constants + macro (gd_gd2.c, verbatim) ---- */
#define GD2_FMT_TRUECOLOR_RAW 3
#define GD2_FMT_TRUECOLOR_COMPRESSED 4
#define gd2_compressed(fmt) (((fmt) == GD2_FMT_COMPRESSED) || ((fmt) == GD2_FMT_TRUECOLOR_COMPRESSED))
/* debug logging is compiled OUT in the real build (GD2_DBG(s) discards its whole
 * argument textually) -- every php_gd_error(...) call in the target function below is
 * wrapped in GD2_DBG(...), so php_gd_error is never actually referenced and needs no
 * stub. */
#define GD2_DBG(s)

/* ---- real struct (gd_gd2.c, verbatim field names/order) ---- */
typedef struct
{
	int offset;
	int size;
} t_chunk_info;

/* ---- real gdIOCtx interface (gd_io.h, verbatim field names/order) ---- */
typedef struct gdIOCtx {
	int	(*getC)(struct gdIOCtx*);
	int	(*getBuf)(struct gdIOCtx*, void*, int);

	void	(*putC)(struct gdIOCtx*, int);
	int	(*putBuf)(struct gdIOCtx*, const void*, int);

	int	(*seek)(struct gdIOCtx*, const int);
	long	(*tell)(struct gdIOCtx*);

	void	(*gd_free)(struct gdIOCtx*);

	void	*data;
} gdIOCtx;

typedef struct gdIOCtx	*gdIOCtxPtr;

/* ---- real gdGetC/gdGetWord/gdGetInt (gd_io.c, verbatim) -- callees on the crash
 * path (every field read in _gd2GetHeader goes through one of these). ---- */
#define GD_IO_EOF_CHK(r)	\
	if (r == EOF) {		\
		return 0;	\
	}			\

int gdGetC (gdIOCtx * ctx)
{
	return ((ctx->getC) (ctx));
}

int gdGetWord (int *result, gdIOCtx * ctx)
{
	int r;
	r = (ctx->getC) (ctx);
	GD_IO_EOF_CHK(r);
	*result = r << 8;
	r = (ctx->getC) (ctx);
	GD_IO_EOF_CHK(r);
	*result += r;
	return 1;
}


int gdGetInt (int *result, gdIOCtx * ctx)
{
	int r;
	r = (ctx->getC) (ctx);
	GD_IO_EOF_CHK(r);
	*result = r << 24;

	r = (ctx->getC) (ctx);
	GD_IO_EOF_CHK(r);
	*result += r << 16;

	r = (ctx->getC) (ctx);
	if (r == EOF) {
		return 0;
	}
	*result += r << 8;

	r = (ctx->getC) (ctx);
	GD_IO_EOF_CHK(r);
	*result += r;

	return 1;
}

/* ---- gdCalloc/gdFree: real macro NAMES (gdhelpers.h); their real bodies map to
 * PHP's ecalloc/efree (zend memory manager). That is a memory-management-BACKEND
 * swap only -- ecalloc(sidx,1)/calloc(sidx,1) both simply allocate `sidx` bytes
 * zero-filled; the overflow that produced the too-small `sidx` already happened one
 * line earlier in plain `int` arithmetic inside the target function, untouched here. */
#define gdCalloc(nmemb, size)	calloc((nmemb), (size))
#define gdFree(ptr)		free(ptr)

/* ---- minimal in-memory gdIOCtx backend (gd's own I/O layer is pluggable this way --
 * see gd_io_dp.c/gd_io_file.c/gd_io_ss.c for the real analogues; this is the
 * read-only, heap-buffer-backed minimal faithful stand-in, same first-member-aliasing
 * technique gd_io_dp.c's `dpIOCtx { gdIOCtx ctx; ... }` uses). Not part of the
 * vulnerable logic -- _gd2GetHeader only ever calls back through ctx->getC. ---- */
typedef struct {
	gdIOCtx ctx;
	const unsigned char *data;
	long len;
	long pos;
} memIOCtx;

static int mem_getC(gdIOCtx *ctx)
{
	memIOCtx *m = (memIOCtx *)ctx;
	if (m->pos >= m->len) return EOF;
	return m->data[m->pos++];
}

static int mem_getBuf(gdIOCtx *ctx, void *buf, int want)
{
	memIOCtx *m = (memIOCtx *)ctx;
	long avail = m->len - m->pos;
	long n = (want < avail) ? want : avail;
	if (n < 0) n = 0;
	if (n > 0) memcpy(buf, m->data + m->pos, (size_t)n);
	m->pos += n;
	return (int)n;
}

static void mem_putC(gdIOCtx *ctx, int c) { (void)ctx; (void)c; }
static int mem_putBuf(gdIOCtx *ctx, const void *buf, int len) { (void)ctx; (void)buf; return len; }

static int mem_seek(gdIOCtx *ctx, const int pos)
{
	memIOCtx *m = (memIOCtx *)ctx;
	if (pos < 0 || pos > m->len) return 0;
	m->pos = pos;
	return 1;
}

static long mem_tell(gdIOCtx *ctx) { return ((memIOCtx *)ctx)->pos; }
static void mem_free(gdIOCtx *ctx) { (void)ctx; }

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the crash keeps its own stack frame (dc_batch requires the target
 * function name in the ASAN backtrace). */
__attribute__((noinline))
static int _gd2GetHeader(gdIOCtxPtr in, int *sx, int *sy, int *cs, int *vers, int *fmt, int *ncx, int *ncy, t_chunk_info ** chunkIdx)
{
	int i;
	int ch;
	char id[5];
	t_chunk_info *cidx;
	int sidx;
	int nc;

	GD2_DBG(php_gd_error("Reading gd2 header info"));

	for (i = 0; i < 4; i++) {
		ch = gdGetC(in);
		if (ch == EOF) {
			goto fail1;
		}
		id[i] = ch;
	}
	id[4] = 0;

	GD2_DBG(php_gd_error("Got file code: %s", id));

	/* Equiv. of 'magick'.  */
	if (strcmp(id, GD2_ID) != 0) {
		GD2_DBG(php_gd_error("Not a valid gd2 file"));
		goto fail1;
	}

	/* Version */
	if (gdGetWord(vers, in) != 1) {
		goto fail1;
	}
	GD2_DBG(php_gd_error("Version: %d", *vers));

	if ((*vers != 1) && (*vers != 2)) {
		GD2_DBG(php_gd_error("Bad version: %d", *vers));
		goto fail1;
	}

	/* Image Size */
	if (!gdGetWord(sx, in)) {
		GD2_DBG(php_gd_error("Could not get x-size"));
		goto fail1;
	}
	if (!gdGetWord(sy, in)) {
		GD2_DBG(php_gd_error("Could not get y-size"));
		goto fail1;
	}
	GD2_DBG(php_gd_error("Image is %dx%d", *sx, *sy));

	/* Chunk Size (pixels, not bytes!) */
	if (gdGetWord(cs, in) != 1) {
		goto fail1;
	}
	GD2_DBG(php_gd_error("ChunkSize: %d", *cs));

	if ((*cs < GD2_CHUNKSIZE_MIN) || (*cs > GD2_CHUNKSIZE_MAX)) {
		GD2_DBG(php_gd_error("Bad chunk size: %d", *cs));
		goto fail1;
	}

	/* Data Format */
	if (gdGetWord(fmt, in) != 1) {
		goto fail1;
	}
	GD2_DBG(php_gd_error("Format: %d", *fmt));

	if ((*fmt != GD2_FMT_RAW) && (*fmt != GD2_FMT_COMPRESSED) && (*fmt != GD2_FMT_TRUECOLOR_RAW) && (*fmt != GD2_FMT_TRUECOLOR_COMPRESSED)) {
		GD2_DBG(php_gd_error("Bad data format: %d", *fmt));
		goto fail1;
	}

	/* # of chunks wide */
	if (gdGetWord(ncx, in) != 1) {
		goto fail1;
	}
	GD2_DBG(php_gd_error("%d Chunks Wide", *ncx));

	/* # of chunks high */
	if (gdGetWord(ncy, in) != 1) {
		goto fail1;
	}
	GD2_DBG(php_gd_error("%d Chunks vertically", *ncy));

	if (gd2_compressed(*fmt)) {
		nc = (*ncx) * (*ncy);
		GD2_DBG(php_gd_error("Reading %d chunk index entries", nc));
		sidx = sizeof(t_chunk_info) * nc;
		if (sidx <= 0) {
			goto fail1;
		}
		cidx = gdCalloc(sidx, 1);
		for (i = 0; i < nc; i++) {
			if (gdGetInt(&cidx[i].offset, in) != 1) {
				gdFree(cidx);
				goto fail1;
			}
			if (gdGetInt(&cidx[i].size, in) != 1) {
				gdFree(cidx);
				goto fail1;
			}
			if (cidx[i].offset < 0 || cidx[i].size < 0) {
				gdFree(cidx);
				goto fail1;
			}
		}
		*chunkIdx = cidx;
	}

	GD2_DBG(php_gd_error("gd2 header complete"));

	return 1;

fail1:
	return 0;
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
	unsigned char *data = (unsigned char *)malloc(n ? n : 1);   /* HEAP input, ASAN-guarded */
	if (!data) { fclose(fp); return 2; }
	size_t got = fread(data, 1, n, fp);
	fclose(fp);

	memIOCtx mio;
	memset(&mio, 0, sizeof(mio));
	mio.ctx.getC    = mem_getC;
	mio.ctx.getBuf  = mem_getBuf;
	mio.ctx.putC    = mem_putC;
	mio.ctx.putBuf  = mem_putBuf;
	mio.ctx.seek    = mem_seek;
	mio.ctx.tell    = mem_tell;
	mio.ctx.gd_free = mem_free;
	mio.ctx.data    = NULL;
	mio.data = data;
	mio.len  = (long)got;
	mio.pos  = 0;

	int sx = 0, sy = 0, cs = 0, vers = 0, fmt = 0, ncx = 0, ncy = 0;
	t_chunk_info *chunkIdx = NULL;

	/* volatile function pointer: forbid the compiler from inlining/proving-away the call. */
	int (* volatile fn)(gdIOCtxPtr, int *, int *, int *, int *, int *, int *, int *, t_chunk_info **) = _gd2GetHeader;
	int rc = fn((gdIOCtxPtr)&mio, &sx, &sy, &cs, &vers, &fmt, &ncx, &ncy, &chunkIdx);

	if (rc && chunkIdx) gdFree(chunkIdx);
	free(data);
	return 0;
}
