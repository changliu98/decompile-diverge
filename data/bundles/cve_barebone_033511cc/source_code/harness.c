/* cve_barebone direct-call harness for libgd gdImageClone()
 * CVE fix commit: a93eac0e843148dc2d631c3ba80af17e9c8c860f
 *
 * Bug (present in vul_commit 2e886046f86d0d6bfc14aab94a881259a081e3f4):
 * gdImageClone() manually copies src->style[] into dst->style[] via
 *     if (src->styleLength > 0) {
 *         dst->styleLength = src->styleLength;
 *         dst->stylePos    = src->stylePos;
 *         for (i = 0; i < src->styleLength; i++) {
 *             dst->style[i] = src->style[i];
 *         }
 *     }
 * BEFORE dst->style has ever been allocated -- gdImageCreate() /
 * gdImageCreateTrueColor() both explicitly zero-initialize im->style
 * (see below, copied verbatim), and the ONLY call that allocates
 * dst->style is gdImageSetStyle(), which happens LATER in the function
 * body, guarded by `if (src->style)`. So whenever a caller clones an
 * image that has had a line style set (src->styleLength > 0), this
 * loop writes through dst->style, which is still NULL -- a NULL
 * pointer WRITE (CWE-476) at the very first iteration (i = 0, address
 * 0x0). The fix drops this manual loop entirely and instead relies on
 * gdImageSetStyle() (called further down) to both allocate dst->style
 * AND copy the contents, restoring dst->stylePos afterwards.
 *
 * This harness builds a `src` gdImage directly (mirroring what a real
 * caller does: create an image, then gdImageSetStyle() it) and calls
 * gdImageClone(src) -- exactly the public API entry point the bug
 * lives behind. All types/callees below are copied VERBATIM (by name
 * and body) from source_code/src/gd.h and source_code/src/gd.c /
 * gd_security.c / gdhelpers.c; only cosmetic export macros are
 * stubbed to a no-op (BGD_DECLARE) since this is a single freestanding
 * translation unit, not a shared library, and gd_error_ex() (a
 * printf-only diagnostic sink, not on any memory-safety path) is
 * stubbed to a no-op varargs function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* ---- verbatim from source_code/src/gd.h ---- */

#define gdMaxColors 256
#define GD_RESOLUTION 96 /* pixels per inch */

typedef enum {
	GD_DEFAULT = 0,
	GD_BELL,
	GD_BESSEL,
	GD_BILINEAR_FIXED,
	GD_BICUBIC,
	GD_BICUBIC_FIXED,
	GD_BLACKMAN,
	GD_BOX,
	GD_BSPLINE,
	GD_CATMULLROM,
	GD_GAUSSIAN,
	GD_GENERALIZED_CUBIC,
	GD_HERMITE,
	GD_HAMMING,
	GD_HANNING,
	GD_MITCHELL,
	GD_NEAREST_NEIGHBOUR,
	GD_POWER,
	GD_QUADRATIC,
	GD_SINC,
	GD_TRIANGLE,
	GD_WEIGHTED4,
	GD_LINEAR,
	GD_METHOD_COUNT = 23
} gdInterpolationMethod;

typedef double (* interpolation_method )(double);

typedef struct gdImageStruct {
	/* Palette-based image pixels */
	unsigned char **pixels;
	int sx;
	int sy;
	int colorsTotal;
	int red[gdMaxColors];
	int green[gdMaxColors];
	int blue[gdMaxColors];
	int open[gdMaxColors];
	int transparent;
	int *polyInts;
	int polyAllocated;
	struct gdImageStruct *brush;
	struct gdImageStruct *tile;
	int brushColorMap[gdMaxColors];
	int tileColorMap[gdMaxColors];
	int styleLength;
	int stylePos;
	int *style;
	int interlace;
	int thick;
	int alpha[gdMaxColors];
	int trueColor;
	int **tpixels;
	int alphaBlendingFlag;
	int saveAlphaFlag;
	int AA;
	int AA_color;
	int AA_dont_blend;
	int cx1;
	int cy1;
	int cx2;
	int cy2;
	unsigned int res_x;
	unsigned int res_y;
	int paletteQuantizationMethod;
	int paletteQuantizationSpeed;
	int paletteQuantizationMinQuality;
	int paletteQuantizationMaxQuality;
	gdInterpolationMethod interpolation_id;
	interpolation_method interpolation;
}
gdImage;

typedef gdImage *gdImagePtr;

/* real macro decorates with export/calling-convention attributes for the
 * shared library build; irrelevant to a single freestanding TU. */
#define BGD_DECLARE(rt) rt

/* ---- verbatim from source_code/src/gdhelpers.c ---- */

void * gdCalloc (size_t nmemb, size_t size)
{
	return calloc (nmemb, size);
}

void *
gdMalloc (size_t size)
{
	return malloc (size);
}

BGD_DECLARE(void) gdFree (void *ptr)
{
	free (ptr);
}

/* ---- verbatim from source_code/src/gd_security.c, EXCEPT the
 * gd_error_ex() diagnostic call (printf-only, not on a memory-safety
 * path) is dropped since it requires gd_errors.c's error-handler
 * machinery; the overflow arithmetic/logic is unchanged. ---- */

int overflow2(int a, int b)
{
	if (a <= 0 || b <= 0) {
		return 1;
	}
	if (a > INT_MAX / b) {
		return 1;
	}
	return 0;
}

/* ---- verbatim from source_code/src/gd.c ---- */

BGD_DECLARE(gdImagePtr) gdImageCreate (int sx, int sy)
{
	int i;
	gdImagePtr im;

	if (overflow2(sx, sy)) {
		return NULL;
	}

	if (overflow2(sizeof (unsigned char *), sy)) {
		return NULL;
	}
	if (overflow2(sizeof (unsigned char), sx)) {
		return NULL;
	}

	im = (gdImage *) gdCalloc(1, sizeof(gdImage));
	if (!im) {
		return NULL;
	}

	/* Row-major ever since gd 1.3 */
	im->pixels = (unsigned char **) gdMalloc (sizeof (unsigned char *) * sy);
	if (!im->pixels) {
		gdFree(im);
		return NULL;
	}

	im->polyInts = 0;
	im->polyAllocated = 0;
	im->brush = 0;
	im->tile = 0;
	im->style = 0;
	for (i = 0; (i < sy); i++) {
		/* Row-major ever since gd 1.3 */
		im->pixels[i] = (unsigned char *) gdCalloc (sx, sizeof (unsigned char));
		if (!im->pixels[i]) {
			for (--i ; i >= 0; i--) {
				gdFree(im->pixels[i]);
			}
			gdFree(im->pixels);
			gdFree(im);
			return NULL;
		}

	}
	im->sx = sx;
	im->sy = sy;
	im->colorsTotal = 0;
	im->transparent = (-1);
	im->interlace = 0;
	im->thick = 1;
	im->AA = 0;
	for (i = 0; (i < gdMaxColors); i++) {
		im->open[i] = 1;
	};
	im->trueColor = 0;
	im->tpixels = 0;
	im->cx1 = 0;
	im->cy1 = 0;
	im->cx2 = im->sx - 1;
	im->cy2 = im->sy - 1;
	im->res_x = GD_RESOLUTION;
	im->res_y = GD_RESOLUTION;
	im->interpolation = NULL;
	im->interpolation_id = GD_BILINEAR_FIXED;
	return im;
}

BGD_DECLARE(gdImagePtr) gdImageCreateTrueColor (int sx, int sy)
{
	int i;
	gdImagePtr im;

	if (overflow2(sx, sy)) {
		return NULL;
	}
	if (overflow2(sizeof (int *), sy)) {
		return 0;
	}
	if (overflow2(sizeof(int), sx)) {
		return NULL;
	}

	im = (gdImage *) gdMalloc (sizeof (gdImage));
	if (!im) {
		return 0;
	}
	memset (im, 0, sizeof (gdImage));

	im->tpixels = (int **) gdMalloc (sizeof (int *) * sy);
	if (!im->tpixels) {
		gdFree(im);
		return 0;
	}
	im->polyInts = 0;
	im->polyAllocated = 0;
	im->brush = 0;
	im->tile = 0;
	im->style = 0;
	for (i = 0; (i < sy); i++) {
		im->tpixels[i] = (int *) gdCalloc (sx, sizeof (int));
		if (!im->tpixels[i]) {
			/* 2.0.34 */
			i--;
			while (i >= 0) {
				gdFree(im->tpixels[i]);
				i--;
			}
			gdFree(im->tpixels);
			gdFree(im);
			return 0;
		}
	}
	im->sx = sx;
	im->sy = sy;
	im->transparent = (-1);
	im->interlace = 0;
	im->trueColor = 1;
	im->saveAlphaFlag = 0;
	im->alphaBlendingFlag = 1;
	im->thick = 1;
	im->AA = 0;
	im->cx1 = 0;
	im->cy1 = 0;
	im->cx2 = im->sx - 1;
	im->cy2 = im->sy - 1;
	im->res_x = GD_RESOLUTION;
	im->res_y = GD_RESOLUTION;
	im->interpolation = NULL;
	im->interpolation_id = GD_BILINEAR_FIXED;
	return im;
}

BGD_DECLARE(void) gdImageDestroy (gdImagePtr im)
{
	int i;
	if (im->pixels) {
		for (i = 0; (i < im->sy); i++) {
			gdFree (im->pixels[i]);
		}
		gdFree (im->pixels);
	}
	if (im->tpixels) {
		for (i = 0; (i < im->sy); i++) {
			gdFree (im->tpixels[i]);
		}
		gdFree (im->tpixels);
	}
	if (im->polyInts) {
		gdFree (im->polyInts);
	}
	if (im->style) {
		gdFree (im->style);
	}
	gdFree (im);
}

BGD_DECLARE(void) gdImageSetStyle (gdImagePtr im, int *style, int noOfPixels)
{
	if (im->style) {
		gdFree (im->style);
	}
	if (overflow2(sizeof (int), noOfPixels)) {
		return;
	}
	im->style = (int *) gdMalloc (sizeof (int) * noOfPixels);
	if (!im->style) {
		return;
	}
	memcpy (im->style, style, sizeof (int) * noOfPixels);
	im->styleLength = noOfPixels;
	im->stylePos = 0;
}

/* ==== VERBATIM from data_cve/cve_033511cc/target/original_function.c ==== */
BGD_DECLARE(gdImagePtr) gdImageClone (gdImagePtr src) {
	gdImagePtr dst;
	register int i, x;

	if (src->trueColor) {
		dst = gdImageCreateTrueColor(src->sx , src->sy);
	} else {
		dst = gdImageCreate(src->sx , src->sy);
	}

	if (dst == NULL) {
		return NULL;
	}

	if (src->trueColor == 0) {
		dst->colorsTotal = src->colorsTotal;
		for (i = 0; i < gdMaxColors; i++) {
			dst->red[i]   = src->red[i];
			dst->green[i] = src->green[i];
			dst->blue[i]  = src->blue[i];
			dst->alpha[i] = src->alpha[i];
			dst->open[i]  = src->open[i];
		}
		for (i = 0; i < src->sy; i++) {
			for (x = 0; x < src->sx; x++) {
				dst->pixels[i][x] = src->pixels[i][x];
			}
		}
	} else {
		for (i = 0; i < src->sy; i++) {
			for (x = 0; x < src->sx; x++) {
				dst->tpixels[i][x] = src->tpixels[i][x];
			}
		}
	}

	if (src->styleLength > 0) {
		dst->styleLength = src->styleLength;
		dst->stylePos    = src->stylePos;
		for (i = 0; i < src->styleLength; i++) {
			dst->style[i] = src->style[i];
		}
	}

	dst->interlace   = src->interlace;

	dst->alphaBlendingFlag = src->alphaBlendingFlag;
	dst->saveAlphaFlag     = src->saveAlphaFlag;
	dst->AA                = src->AA;
	dst->AA_color          = src->AA_color;
	dst->AA_dont_blend     = src->AA_dont_blend;

	dst->cx1 = src->cx1;
	dst->cy1 = src->cy1;
	dst->cx2 = src->cx2;
	dst->cy2 = src->cy2;

	dst->res_x = src->res_x;
	dst->res_y = src->res_y;

	dst->paletteQuantizationMethod     = src->paletteQuantizationMethod;
	dst->paletteQuantizationSpeed      = src->paletteQuantizationSpeed;
	dst->paletteQuantizationMinQuality = src->paletteQuantizationMinQuality;
	dst->paletteQuantizationMinQuality = src->paletteQuantizationMinQuality;

	dst->interpolation_id = src->interpolation_id;
	dst->interpolation    = src->interpolation;

	if (src->brush) {
		dst->brush = gdImageClone(src->brush);
	}

	if (src->tile) {
		dst->tile = gdImageClone(src->tile);
	}

	if (src->style) {
		gdImageSetStyle(dst, src->style, src->styleLength);
	}

	for (i = 0; i < gdMaxColors; i++) {
		dst->brushColorMap[i] = src->brushColorMap[i];
		dst->tileColorMap[i] = src->tileColorMap[i];
	}

	if (src->polyAllocated > 0) {
		dst->polyAllocated = src->polyAllocated;
		for (i = 0; i < src->polyAllocated; i++) {
			dst->polyInts[i] = src->polyInts[i];
		}
	}

	return dst;
}

/* ============================================================
 * main() -- plays the role of a caller that creates an image, applies
 * a dashed-line style to it via the real public gdImageSetStyle() API
 * (exactly as libgd's own tests/gdimageclone/style.c does), and then
 * clones it via gdImageClone(). argv[1] is read into a HEAP buffer
 * (ASAN-guarded) and its bytes drive every parameter:
 *
 *   byte 0       : trueColor flag (bit 0)
 *   byte 1       : sx, mapped into [1, 16]
 *   byte 2       : sy, mapped into [1, 16]
 *   byte 3       : styleLength, mapped into [0, 32]
 *                    0  -> no style is set on src (styleLength stays 0)
 *                          => gdImageClone's vulnerable loop is not
 *                          entered at all: SAFE.
 *                    >0 -> gdImageSetStyle(src, style, styleLength) is
 *                          called first (so src->styleLength > 0 and
 *                          src->style is a real heap allocation,
 *                          exactly what a real caller does), then
 *                          gdImageClone(src) is called: the freshly
 *                          created dst has dst->style == NULL, so the
 *                          manual copy loop writes dst->style[0] at
 *                          address 0x0 => TRIGGERING (CWE-476 NULL
 *                          pointer WRITE).
 *   bytes 4..    : raw content for the style[] array (cycled if the
 *                  file is shorter than styleLength ints; defaults to
 *                  zero-fill if there are no bytes left at all).
 *
 * A short/empty file just falls back to the defaults baked into each
 * byte read (0), which is itself a valid SAFE case (styleLength byte
 * defaults to 0).
 * ============================================================ */
int
main(int argc, char **argv)
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

	/* Attacker-controlled bytes MUST live on the heap so ASAN redzones
	 * bound them on both sides. */
	unsigned char *buf = NULL;
	size_t n = 0;
	if (fsz > 0) {
		buf = (unsigned char *) malloc((size_t) fsz);
		if (!buf) {
			fclose(f);
			return 1;
		}
		n = fread(buf, 1, (size_t) fsz, f);
	}
	fclose(f);

	unsigned char b0 = n > 0 ? buf[0] : 0;
	unsigned char b1 = n > 1 ? buf[1] : 0;
	unsigned char b2 = n > 2 ? buf[2] : 0;
	unsigned char b3 = n > 3 ? buf[3] : 0;

	int trueColor  = b0 & 1;
	int sx         = (b1 % 16) + 1;
	int sy         = (b2 % 16) + 1;
	int styleLen   = b3 % 33; /* 0 .. 32 */

	gdImagePtr src = trueColor ? gdImageCreateTrueColor(sx, sy)
	                            : gdImageCreate(sx, sy);
	if (!src) {
		free(buf);
		return 1;
	}

	if (styleLen > 0) {
		int *style = (int *) malloc(sizeof(int) * (size_t) styleLen);
		for (int i = 0; i < styleLen; i++) {
			size_t off = 4 + (size_t) i;
			style[i] = (off < n) ? (int) buf[off] : 0;
		}
		/* Exactly what a real caller does before cloning: apply the
		 * style via the public API. This allocates src->style and
		 * sets src->styleLength/src->stylePos -- gdImageClone's own
		 * bug is what mishandles copying it into a freshly created
		 * dst. */
		gdImageSetStyle(src, style, styleLen);
		free(style);
	}

	gdImagePtr dst = gdImageClone(src);
	if (dst) {
		gdImageDestroy(dst);
	}
	gdImageDestroy(src);
	free(buf);
	return 0;
}
