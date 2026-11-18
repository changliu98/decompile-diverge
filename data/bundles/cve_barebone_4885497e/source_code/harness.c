/* cve_barebone harness -- jasper CVE-2016-9388 / ras_putdatastd stack-buffer-overflow
 * (CWE-787; fixed by jasper-software/jasper@411a4068f8c464e883358bf403a3e25158863823).
 *
 * Isolated reproduction: ras_putdatastd() is called DIRECTLY with an attacker-controlled
 * `numcmpts` -- exactly the parameter whose caller-side restriction (ras_encode() only
 * ever passes 1 or 3, GRAY vs RGB) the function's OWN body never re-checks. It declares a
 * FIXED 3-slot local array:
 *
 *     jas_matrix_t *data[3];
 *     ...
 *     for (i = 0; i < numcmpts; ++i) {
 *         data[i] = jas_matrix_create(...);   <-- data[3], data[4], ... : OOB stack WRITE
 *         assert(data[i]);
 *     }
 *
 * With numcmpts > 3 the i==3 iteration writes a pointer one slot past the end of `data`
 * on the stack -- caught by ASAN as "stack-buffer-overflow ... WRITE of size 8" inside
 * ras_putdatastd itself. The fix commit adds `assert(numcmpts <= 3);` before this loop.
 *
 * TRIGGER: numcmpts in [4,8]  (overruns data[3]).
 * SAFE:    numcmpts in [1,3]  (the real ras_encode contract; runs to completion, exit 0).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

/* ---- jas_seq.h: matrix class (verbatim names/layout) ---- */
typedef int_fast32_t jas_seqent_t;

typedef struct {
	int flags_;
	int_fast32_t xstart_;
	int_fast32_t ystart_;
	int_fast32_t xend_;
	int_fast32_t yend_;
	int_fast32_t numrows_;
	int_fast32_t numcols_;
	jas_seqent_t **rows_;
	int_fast32_t maxrows_;
	jas_seqent_t *data_;
	int_fast32_t datasize_;
} jas_matrix_t;

/* Get an element in a matrix known to be a row or column vector (verbatim, jas_seq.h). */
#define jas_matrix_getv(matrix, i) \
	(((matrix)->numrows_ == 1) ? ((matrix)->rows_[0][i]) : \
	  ((matrix)->rows_[i][0]))

jas_matrix_t *jas_matrix_create(int numrows, int numcols);
void jas_matrix_destroy(jas_matrix_t *matrix);

/* ---- jas_image.h: image class (verbatim names/layout) ---- */
typedef int_fast32_t jas_image_coord_t;
typedef int jas_clrspc_t;                              /* jas_cm.h, verbatim */
typedef struct jas_cmprof jas_cmprof_t;                 /* opaque -- never dereferenced here */
typedef struct jas_image_cmpt jas_image_cmpt_t;          /* opaque -- never dereferenced here */

typedef struct {
	jas_image_coord_t tlx_;
	jas_image_coord_t tly_;
	jas_image_coord_t brx_;
	jas_image_coord_t bry_;
	int numcmpts_;
	int maxcmpts_;
	jas_image_cmpt_t **cmpts_;
	jas_clrspc_t clrspc_;
	jas_cmprof_t *cmprof_;
	bool inmem_;
} jas_image_t;

#define jas_image_width(image) \
	((image)->brx_ - (image)->tlx_)
#define	jas_image_height(image) \
	((image)->bry_ - (image)->tly_)

int jas_image_readcmpt(jas_image_t *image, int cmptno, jas_image_coord_t x,
  jas_image_coord_t y, jas_image_coord_t width, jas_image_coord_t height,
  jas_matrix_t *data);

/* ---- jas_stream.h: opaque stream handle + jas_stream_putc (verbatim name/contract) ---- */
typedef struct { int _unused; } jas_stream_t;
int jas_stream_putc(jas_stream_t *out, int c);

/* ---- ras_cod.h: Sun Rasterfile header + macros (verbatim) ---- */
typedef struct {
	int_fast32_t magic;
	int_fast32_t width;
	int_fast32_t height;
	int_fast32_t depth;
	int_fast32_t length;
	int_fast32_t type;
	int_fast32_t maptype;
	int_fast32_t maplength;
} ras_hdr_t;

#define	RAS_MAGIC	0x59a66a95
#define	RAS_TYPE_STD	1
#define	RAS_MT_NONE	0

#define RAS_BLUE(x)	(((x) & 0xff) << 16)
#define RAS_GREEN(x)	(((x) & 0xff) << 8)
#define	RAS_RED(x)	((x) & 0xff)

#define RAS_ROWSIZE(hdr) \
	((((hdr)->width * (hdr)->depth + 15) / 16) * 2)
#define RAS_ISRGB(hdr) \
	((hdr)->depth == 24 || (hdr)->depth == 32)

#define	RAS_ONES(n) \
	(((n) == 32) ? 0xffffffffUL : ((1UL << (n)) - 1))

/* ================= minimal faithful stubs (real names/contracts; jasper's own
 * allocator + component-bitstream I/O swapped for plain malloc / a synthetic sample
 * source -- incidental to the data[3] overrun below, which happens before any of this
 * matters) ================= */

jas_matrix_t *jas_matrix_create(int numrows, int numcols)
{
	jas_matrix_t *matrix;
	int i;
	if (numrows < 0 || numcols < 0) {
		return 0;
	}
	if (!(matrix = (jas_matrix_t *)malloc(sizeof(jas_matrix_t)))) {
		return 0;
	}
	matrix->flags_ = 0;
	matrix->xstart_ = 0;
	matrix->ystart_ = 0;
	matrix->xend_ = numcols;
	matrix->yend_ = numrows;
	matrix->numrows_ = numrows;
	matrix->numcols_ = numcols;
	matrix->maxrows_ = numrows;
	matrix->rows_ = 0;
	matrix->data_ = 0;
	matrix->datasize_ = (int_fast32_t)numrows * (int_fast32_t)numcols;
	if (matrix->maxrows_ > 0) {
		if (!(matrix->rows_ = (jas_seqent_t **)malloc(sizeof(jas_seqent_t *) * (size_t)matrix->maxrows_))) {
			free(matrix);
			return 0;
		}
	}
	if (matrix->datasize_ > 0) {
		if (!(matrix->data_ = (jas_seqent_t *)calloc((size_t)matrix->datasize_, sizeof(jas_seqent_t)))) {
			free(matrix->rows_);
			free(matrix);
			return 0;
		}
	}
	for (i = 0; i < numrows; ++i) {
		matrix->rows_[i] = matrix->data_ ? &matrix->data_[(size_t)i * (size_t)numcols] : 0;
	}
	return matrix;
}

void jas_matrix_destroy(jas_matrix_t *matrix)
{
	if (!matrix) {
		return;
	}
	if (matrix->data_) {
		free(matrix->data_);
		matrix->data_ = 0;
	}
	if (matrix->rows_) {
		free(matrix->rows_);
		matrix->rows_ = 0;
	}
	free(matrix);
}

/* attacker-influenced sample source for jas_image_readcmpt's synthetic pixel fill
 * (only reached by SAFE inputs -- TRIGGER inputs crash before any of this runs). Varies
 * the corpus; has no bearing on the crash mechanism itself. */
static const unsigned char *g_pixseed;
static size_t g_pixseed_len;

int jas_image_readcmpt(jas_image_t *image, int cmptno, jas_image_coord_t x,
  jas_image_coord_t y, jas_image_coord_t width, jas_image_coord_t height,
  jas_matrix_t *data)
{
	int_fast32_t need;
	int i;
	if (cmptno < 0 || cmptno >= image->numcmpts_) {
		return -1;
	}
	if (data->numrows_ != height || data->numcols_ != width) {
		if (data->data_) { free(data->data_); data->data_ = 0; }
		if (data->rows_) { free(data->rows_); data->rows_ = 0; }
		need = (int_fast32_t)height * (int_fast32_t)width;
		data->numrows_ = height;
		data->numcols_ = width;
		data->maxrows_ = height;
		data->datasize_ = need;
		if (height > 0) {
			data->rows_ = (jas_seqent_t **)malloc(sizeof(jas_seqent_t *) * (size_t)height);
		}
		if (need > 0) {
			data->data_ = (jas_seqent_t *)calloc((size_t)need, sizeof(jas_seqent_t));
		}
		for (i = 0; i < height; ++i) {
			data->rows_[i] = data->data_ ? &data->data_[(size_t)i * (size_t)width] : 0;
		}
	}
	if (g_pixseed_len > 0) {
		for (i = 0; i < (int)width; ++i) {
			data->rows_[0][i] = (jas_seqent_t)(g_pixseed[(size_t)(cmptno + x + y + i) % g_pixseed_len] & 0xff);
		}
	} else {
		for (i = 0; i < (int)width; ++i) {
			data->rows_[0][i] = 0;
		}
	}
	return 0;
}

int jas_stream_putc(jas_stream_t *out, int c)
{
	(void)out;
	return c & 0xff;   /* synthetic sink: every write "succeeds" */
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the crash keeps its own stack frame (dc_batch requires the target function
 * name in the ASAN backtrace). */
__attribute__((noinline))
static int ras_putdatastd(jas_stream_t *out, ras_hdr_t *hdr, jas_image_t *image,  int numcmpts, int *cmpts)
{
	int rowsize;
	int pad;
	unsigned int z;
	int nz;
	int c;
	int x;
	int y;
	int v;
	jas_matrix_t *data[3];
	int i;

	for (i = 0; i < numcmpts; ++i) {
		data[i] = jas_matrix_create(jas_image_height(image), jas_image_width(image));
		assert(data[i]);
	}

	rowsize = RAS_ROWSIZE(hdr);
	pad = rowsize - (hdr->width * hdr->depth + 7) / 8;

	hdr->length = hdr->height * rowsize;

	for (y = 0; y < hdr->height; y++) {
		for (i = 0; i < numcmpts; ++i) {
			if (jas_image_readcmpt(image, cmpts[i], 0, y,
					jas_image_width(image), 1, data[i])) {
				return -1;
			}
		}
		z = 0;
		nz = 0;
		for (x = 0; x < hdr->width; x++) {
			z <<= hdr->depth;
			if (RAS_ISRGB(hdr)) {
				v = RAS_RED((jas_matrix_getv(data[0], x))) |
				  RAS_GREEN((jas_matrix_getv(data[1], x))) |
				  RAS_BLUE((jas_matrix_getv(data[2], x)));
			} else {
				v = (jas_matrix_getv(data[0], x));
			}
			z |= v & RAS_ONES(hdr->depth);
			nz += hdr->depth;
			while (nz >= 8) {
				c = (z >> (nz - 8)) & 0xff;
				if (jas_stream_putc(out, c) == EOF) {
					return -1;
				}
				nz -= 8;
				z &= RAS_ONES(nz);
			}
		}
		if (nz > 0) {
			c = (z >> (8 - nz)) & RAS_ONES(nz);
			if (jas_stream_putc(out, c) == EOF) {
				return -1;
			}
		}
		if (pad % 2) {
			if (jas_stream_putc(out, 0) == EOF) {
				return -1;
			}
		}
	}

	for (i = 0; i < numcmpts; ++i) {
		jas_matrix_destroy(data[i]);
	}

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

	unsigned char *data = (unsigned char *)malloc(n + 1);   /* HEAP input, ASAN-guarded */
	if (!data) { fclose(fp); return 2; }
	size_t got = fread(data, 1, n, fp);
	fclose(fp);
	data[got] = 0;

	unsigned char b0 = got > 0 ? data[0] : 0;
	unsigned char b1 = got > 1 ? data[1] : 0;
	unsigned char b2 = got > 2 ? data[2] : 0;
	unsigned char b3 = got > 3 ? data[3] : 0;

	int trigger = ((b0 & 1) == 0);            /* even mode byte -> TRIGGER */
	int numcmpts = trigger ? (4 + (b1 % 5))   /* 4..8: overruns the fixed data[3] slot */
	                       : (1 + (b1 % 3));  /* 1..3: the real ras_encode contract */
	int width  = 1 + (b2 % 6);
	int height = 1 + (b3 % 4);

	/* per-input sample source for jas_image_readcmpt's synthetic pixel fill (SAFE inputs
	 * only reach it; TRIGGER inputs crash before this ever runs) -- the input bytes past
	 * the 4-byte header above, or the header bytes themselves as a fallback. */
	if (got > 4) { g_pixseed = data + 4; g_pixseed_len = got - 4; }
	else { g_pixseed = data; g_pixseed_len = got > 0 ? got : 1; }

	/* jas_image_t whose bounding box gives (width x height) and whose numcmpts_ is the
	 * ATTACKER-CONTROLLED numcmpts -- exactly the value ras_putdatastd trusts without
	 * re-checking against its own fixed data[3]. Heap-allocated like every real jasper
	 * image (jas_image_create always mallocs). */
	jas_image_t *image = (jas_image_t *)malloc(sizeof(jas_image_t));
	memset(image, 0, sizeof(*image));
	image->tlx_ = 0;
	image->tly_ = 0;
	image->brx_ = width;
	image->bry_ = height;
	image->numcmpts_ = numcmpts;
	image->maxcmpts_ = numcmpts;
	image->cmpts_ = 0;              /* jas_image_readcmpt (above) never dereferences this */
	image->clrspc_ = 0;
	image->cmprof_ = 0;
	image->inmem_ = false;

	ras_hdr_t *hdr = (ras_hdr_t *)malloc(sizeof(ras_hdr_t));
	memset(hdr, 0, sizeof(*hdr));
	hdr->magic = RAS_MAGIC;
	hdr->width = width;
	hdr->height = height;
	hdr->depth = (numcmpts == 3) ? 24 : 8;    /* 24 -> RAS_ISRGB path; else the plain path */
	hdr->type = RAS_TYPE_STD;
	hdr->maptype = RAS_MT_NONE;
	hdr->maplength = 0;

	jas_stream_t *out = (jas_stream_t *)malloc(sizeof(jas_stream_t));
	memset(out, 0, sizeof(*out));

	int *cmpts = (int *)malloc(sizeof(int) * (size_t)numcmpts);
	int i;
	for (i = 0; i < numcmpts; ++i) {
		cmpts[i] = i;     /* image->numcmpts_ == numcmpts, so every index is in range */
	}

	/* volatile function pointer: forbid the compiler from proving the call away / folding
	 * ras_putdatastd into main's own frame despite __attribute__((noinline)). */
	int (* volatile fn)(jas_stream_t *, ras_hdr_t *, jas_image_t *, int, int *) = ras_putdatastd;
	int rc = fn(out, hdr, image, numcmpts, cmpts);
	(void)rc;

	free(cmpts);
	free(out);
	free(hdr);
	free(image);
	free(data);
	return 0;
}
