/* cve_barebone harness -- libgd CVE-2016-10168 / _gd2GetHeader signed-integer-overflow
 * (CWE-190), upstream issue #354, fix 69d2fd2c597ffc0c217de1238b9bf4d4bceba8e6.
 *
 * Isolated reproduction: _gd2GetHeader() is called directly on a hand-built in-memory
 * "GD2 file" (a minimal gdIOCtx backed by a heap buffer). GD2 header fields ncx/ncy
 * ("chunks wide"/"chunks high") are each an attacker-controlled 16-bit word; the pre-fix
 * body computes `nc = (*ncx) * (*ncy)` in plain `int` arithmetic with NO guard against
 * the mathematical product exceeding INT_MAX -- signed integer overflow, UB (CWE-190),
 * caught here by -fsanitize=signed-integer-overflow (layered onto the required ASAN
 * build via harness.flags).
 *
 * TRIGGER: ncx*ncy > INT_MAX (2147483647), fmt=GD2_FMT_COMPRESSED or
 *          GD2_FMT_TRUECOLOR_COMPRESSED (so the `nc = (*ncx) * (*ncy)` line actually
 *          executes -- it lives inside `if (gd2_compressed (*fmt))`) -> UBSan
 *          signed-integer-overflow abort inside _gd2GetHeader itself, before any
 *          further I/O.
 * SAFE:    truncated/EOF headers at every field boundary, bad magic/version/chunk-size/
 *          format, GD2_FMT_RAW/_TRUECOLOR_RAW (never reaches the multiply -- format
 *          check short-circuits the `if (gd2_compressed(*fmt))` block), ncx==0 ||
 *          ncy==0 (nc==0, legitimately caught by the pre-existing `overflow2`/`sidx<=0`
 *          guards one line below), small non-overflowing ncx*ncy pairs run to a clean
 *          success (fully-provided chunk index) or a clean EOF/negative-field failure,
 *          and one boundary pair whose product stays < INT_MAX (so the multiply itself
 *          is well-defined) but is still large enough for the *existing* `sizeof(
 *          t_chunk_info)*nc` overflow check to reject it -- proving the crash is
 *          specifically the *ncx*ncy* multiplication, not "big chunk counts" in general.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* ---- real GD2 constants (gd.h, verbatim) ---- */
#define GD2_CHUNKSIZE_MIN	64
#define GD2_CHUNKSIZE_MAX       4096
#define GD2_ID                  "gd2"
#define GD2_FMT_RAW             1
#define GD2_FMT_COMPRESSED      2

/* ---- real GD2 constants + macro (gd_gd2.c, verbatim) ---- */
#define GD2_FMT_TRUECOLOR_RAW 3
#define GD2_FMT_TRUECOLOR_COMPRESSED 4

#define gd2_compressed(fmt) (((fmt) == GD2_FMT_COMPRESSED) || \
	((fmt) == GD2_FMT_TRUECOLOR_COMPRESSED))

/* debug logging is compiled OUT in the real (non-debug) build -- GD2_DBG(s) discards
 * its whole argument textually, so every `printf(...)` call in the target function
 * below vanishes and needs no stub. */
#define GD2_DBG(s)

/* ---- real struct (gd_gd2.c, verbatim field names/order) ---- */
typedef struct {
	int offset;
	int size;
}
t_chunk_info;

/* ---- real gdIOCtx interface (gd_io.h, verbatim field names/order) ---- */
typedef struct gdIOCtx {
    int (*getC)(struct gdIOCtx *);
    int (*getBuf)(struct gdIOCtx *, void *, int);
    void (*putC)(struct gdIOCtx *, int);
    int (*putBuf)(struct gdIOCtx *, const void *, int);
    /* seek must return 1 on SUCCESS, 0 on FAILURE. Unlike fseek! */
    int (*seek)(struct gdIOCtx *, const int);
    long (*tell)(struct gdIOCtx *);
    void (*gd_free)(struct gdIOCtx *);
    void *data;
} gdIOCtx;

typedef struct gdIOCtx *gdIOCtxPtr;


/* ---- gd_error_ex: varargs *logging* callee of overflow2 (gd_errors.h), entirely off
 * the crash path -- it never affects control flow or any value. Minimal faithful
 * no-op stub. GD_WARNING is the real gd_errors.h value (LOG_WARNING, syslog.h). ---- */
#define GD_WARNING 4
static void gd_error_ex(int priority, const char *format, ...)
{
	(void)priority; (void)format;
}

/* ---- real overflow2 (gd_security.c, verbatim) -- called directly from the target's
 * own body one line after the vulnerable multiplication; a real callee, not a stub. ---- */
int overflow2(int a, int b)
{
	if(a <= 0 || b <= 0) {
		gd_error_ex(GD_WARNING, "one parameter to a memory allocation multiplication is negative or zero, failing operation gracefully\n");
		return 1;
	}
	if(a > INT_MAX / b) {
		gd_error_ex(GD_WARNING, "product of memory allocation multiplication would exceed INT_MAX, failing operation gracefully\n");
		return 1;
	}
	return 0;
}


/* ---- real gdGetC/gdGetWord/gdGetInt (gd_io.c, verbatim) -- every field read in
 * _gd2GetHeader goes through one of these. ---- */
int gdGetC(gdIOCtx *ctx)
{
	return ((ctx->getC)(ctx));
}

int gdGetWord(int *result, gdIOCtx *ctx)
{
	int r;

	r = (ctx->getC)(ctx);
	if(r == EOF) {
		return 0;
	}

	*result = r << 8;

	r = (ctx->getC)(ctx);
	if(r == EOF) {
		return 0;
	}

	*result += r;

	return 1;
}

int gdGetInt(int *result, gdIOCtx *ctx)
{
	int r;

	r = (ctx->getC)(ctx);
	if(r == EOF) {
		return 0;
	}

	*result = r << 24;

	r = (ctx->getC)(ctx);
	if(r == EOF) {
		return 0;
	}

	*result += r << 16;

	r = (ctx->getC)(ctx);
	if(r == EOF) {
		return 0;
	}

	*result += r << 8;

	r = (ctx->getC)(ctx);
	if(r == EOF) {
		return 0;
	}

	*result += r;

	return 1;
}


/* ---- real gdCalloc/gdFree (gdhelpers.c, verbatim bodies -- thin calloc/free
 * wrappers; gdFree's BGD_DECLARE export/calling-convention macro dropped, ABI noise
 * only, body untouched). ---- */
void * gdCalloc (size_t nmemb, size_t size)
{
	return calloc (nmemb, size);
}

void gdFree (void *ptr)
{
	free (ptr);
}


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
 * function name in the ASAN/UBSan backtrace). */
__attribute__((noinline))
static int
_gd2GetHeader (gdIOCtxPtr in, int *sx, int *sy,
               int *cs, int *vers, int *fmt, int *ncx, int *ncy,
               t_chunk_info ** chunkIdx)
{
	int i;
	int ch;
	char id[5];
	t_chunk_info *cidx;
	int sidx;
	int nc;

	GD2_DBG (printf ("Reading gd2 header info\n"));

	for (i = 0; i < 4; i++) {
		ch = gdGetC (in);
		if (ch == EOF) {
			goto fail1;
		};
		id[i] = ch;
	};
	id[4] = 0;

	GD2_DBG (printf ("Got file code: %s\n", id));

	/* Equiv. of 'magick'.  */
	if (strcmp (id, GD2_ID) != 0) {
		GD2_DBG (printf ("Not a valid gd2 file\n"));
		goto fail1;
	};

	/* Version */
	if (gdGetWord (vers, in) != 1) {
		goto fail1;
	};
	GD2_DBG (printf ("Version: %d\n", *vers));

	if ((*vers != 1) && (*vers != 2)) {
		GD2_DBG (printf ("Bad version: %d\n", *vers));
		goto fail1;
	};

	/* Image Size */
	if (!gdGetWord (sx, in)) {
		GD2_DBG (printf ("Could not get x-size\n"));
		goto fail1;
	}
	if (!gdGetWord (sy, in)) {
		GD2_DBG (printf ("Could not get y-size\n"));
		goto fail1;
	}
	GD2_DBG (printf ("Image is %dx%d\n", *sx, *sy));

	/* Chunk Size (pixels, not bytes!) */
	if (gdGetWord (cs, in) != 1) {
		goto fail1;
	};
	GD2_DBG (printf ("ChunkSize: %d\n", *cs));

	if ((*cs < GD2_CHUNKSIZE_MIN) || (*cs > GD2_CHUNKSIZE_MAX)) {
		GD2_DBG (printf ("Bad chunk size: %d\n", *cs));
		goto fail1;
	};

	/* Data Format */
	if (gdGetWord (fmt, in) != 1) {
		goto fail1;
	};
	GD2_DBG (printf ("Format: %d\n", *fmt));

	if ((*fmt != GD2_FMT_RAW) && (*fmt != GD2_FMT_COMPRESSED) &&
	        (*fmt != GD2_FMT_TRUECOLOR_RAW) &&
	        (*fmt != GD2_FMT_TRUECOLOR_COMPRESSED)) {
		GD2_DBG (printf ("Bad data format: %d\n", *fmt));
		goto fail1;
	};


	/* # of chunks wide */
	if (gdGetWord (ncx, in) != 1) {
		goto fail1;
	};
	GD2_DBG (printf ("%d Chunks Wide\n", *ncx));

	/* # of chunks high */
	if (gdGetWord (ncy, in) != 1) {
		goto fail1;
	};
	GD2_DBG (printf ("%d Chunks vertically\n", *ncy));

	if (gd2_compressed (*fmt)) {
		nc = (*ncx) * (*ncy);

		GD2_DBG (printf ("Reading %d chunk index entries\n", nc));
		if (overflow2(sizeof(t_chunk_info), nc)) {
			goto fail1;
		}
		sidx = sizeof (t_chunk_info) * nc;
		if (sidx <= 0) {
			goto fail1;
		}

		cidx = gdCalloc (sidx, 1);
		if (cidx == NULL) {
			goto fail1;
		}
		for (i = 0; i < nc; i++) {
			if (gdGetInt (&cidx[i].offset, in) != 1) {
				goto fail2;
			};
			if (gdGetInt (&cidx[i].size, in) != 1) {
				goto fail2;
			};
			if (cidx[i].offset < 0 || cidx[i].size < 0)
				goto fail2;
		};
		*chunkIdx = cidx;
	};

	GD2_DBG (printf ("gd2 header complete\n"));

	return 1;
fail2:
	gdFree(cidx);
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
