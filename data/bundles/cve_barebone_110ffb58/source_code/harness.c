/* Direct-call harness -- cvf_110ffb58 (libgd, CVE-2016-9933, CWE-674 uncontrolled recursion).
 *
 * gdImageFillToBorder() recursively floods a palette (non-truecolor) gdImage.
 * For such an image the pixel store is `unsigned char **pixels`, so
 * gdImageSetPixel()'s write `im->pixels[y][x] = color;` silently TRUNCATES an
 * out-of-[0,255] `color` argument to its low byte. Every later
 * gdImageGetPixel() re-read of a "painted" pixel therefore returns the
 * truncated byte, which never again equals the untruncated `color` used in
 * the fill's own termination comparisons ("!= border && != color"). The
 * flood-fill can never recognize its own paint as already-filled, so instead
 * of converging it keeps re-invoking itself once per still-open row above
 * and below -- recursion depth explodes and the process dies to ASAN
 * stack-overflow. A `color` value inside [0,255] round-trips exactly and the
 * same algorithm converges normally (bounded recursion, no crash) -- that is
 * the differentiator this corpus exploits.
 *
 * Target function `gdImageFillToBorder` is embedded VERBATIM below (byte-
 * identical to dataset/cvf_110ffb58/target/original_function.c).
 *
 * Callees embedded VERBATIM because the fault mechanism lives in them:
 *   - gdImageGetPixel  (src/gd.c) -- trivial, no further deps.
 *   - gdImageSetPixel  (src/gd.c) -- the truncating write is the mechanism;
 *     its `switch(color)` textually calls gdImageBrushApply/gdImageTileApply
 *     (gdBrushed/gdTiled sentinels, both negative and never produced by this
 *     corpus) and, on the trueColor path (never taken -- this harness always
 *     builds a palette image), gdAlphaBlend/gdLayerOverlay/gdLayerMultiply.
 *     gdAlphaBlend/gdLayerOverlay/gdLayerMultiply are pure int math with no
 *     further deps, so they too are embedded VERBATIM (src/gd.c) for full
 *     fidelity. gdImageBrushApply/gdImageTileApply pull in a *second*
 *     gdImagePtr (im->brush / im->tile) and a large recompositing routine
 *     that this corpus can never reach (color is never the gdBrushed(-3) /
 *     gdTiled(-5) sentinel) -- those two are stubbed as no-ops, documented
 *     below, purely to satisfy the linker for that dead switch arm.
 *
 * gdImageStruct (aka gdImage/gdImagePtr) and every macro/enum gdImageGetPixel/
 * gdImageSetPixel/gdImageFillToBorder reference are copied VERBATIM (names +
 * values) from src/gd.h / src/gd.c so the target function sees the REAL
 * layout and REAL constants, not a reduced stand-in.
 *
 * main() builds a fresh palette gdImage by hand (mirrors gdImageCreate(),
 * src/gd.c:161, using plain calloc/malloc instead of gd's internal
 * overflow-checked allocator -- struct bring-up only, not part of the bug),
 * reads argv[1] into a HEAP buffer, and calls gdImageFillToBorder() ONCE.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- src/gd.h: BGD_DECLARE is just a DLL-export/calling-convention
 * decorator upstream (BGD_EXPORT_DATA_PROT rt BGD_STDCALL); it does not
 * affect the target function's logic, so it is defined to a no-op here. */
#define BGD_DECLARE(rt) rt

/* ---- src/gd.h macros/enums used by the embedded functions (verbatim
 * names+values). ---- */
#define gdMaxColors 256

#define gdEffectReplace 0
#define gdEffectAlphaBlend 1
#define gdEffectNormal 2
#define gdEffectOverlay 3
#define gdEffectMultiply 4

#define gdStyled (-2)
#define gdBrushed (-3)
#define gdStyledBrushed (-4)
#define gdTiled (-5)
#define gdTransparent (-6)
#define gdAntiAliased (-7)

#define gdAlphaMax 127
#define gdAlphaOpaque 0
#define gdAlphaTransparent 127
#define gdRedMax 255
#define gdGreenMax 255
#define gdBlueMax 255
#define gdTrueColorGetAlpha(c) (((c) & 0x7F000000) >> 24)
#define gdTrueColorGetRed(c) (((c) & 0xFF0000) >> 16)
#define gdTrueColorGetGreen(c) (((c) & 0x00FF00) >> 8)
#define gdTrueColorGetBlue(c) ((c) & 0x0000FF)

/* src/gd.h:215 (verbatim) */
typedef enum {
	GD_DEFAULT          = 0,
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
	GD_METHOD_COUNT = 21
} gdInterpolationMethod;

typedef double (* interpolation_method )(double);

/* src/gd.h:267 gdImageStruct (verbatim). */
typedef struct gdImageStruct {
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

/* src/gd.c:22 (verbatim) */
#define gdImageBoundsSafeMacro(im, x, y) (!((((y) < (im)->cy1) || ((y) > (im)->cy2)) || (((x) < (im)->cx1) || ((x) > (im)->cx2))))

/* src/gd.c:128-129 forward decls (verbatim). */
static void gdImageBrushApply (gdImagePtr im, int x, int y);
static void gdImageTileApply (gdImagePtr im, int x, int y);

/* ---- src/gd.c: gdImageGetPixel, VERBATIM. ---- */
BGD_DECLARE(int) gdImageGetPixel (gdImagePtr im, int x, int y)
{
	if (gdImageBoundsSafeMacro (im, x, y)) {
		if (im->trueColor) {
			return im->tpixels[y][x];
		} else {
			return im->pixels[y][x];
		}
	} else {
		return 0;
	}
}

/* ---- src/gd.c: gdImageSetPixel, VERBATIM (this is where the CVE-2016-9933
 * truncating write lives: `im->pixels[y][x] = color;` in the `default:`
 * case's non-trueColor branch). ---- */
BGD_DECLARE(void) gdImageSetPixel (gdImagePtr im, int x, int y, int color)
{
	int p;
	switch (color) {
	case gdStyled:
		if (!im->style) {
			/* Refuse to draw if no style is set. */
			return;
		} else {
			p = im->style[im->stylePos++];
		}
		if (p != (gdTransparent)) {
			gdImageSetPixel (im, x, y, p);
		}
		im->stylePos = im->stylePos % im->styleLength;
		break;
	case gdStyledBrushed:
		if (!im->style) {
			/* Refuse to draw if no style is set. */
			return;
		}
		p = im->style[im->stylePos++];
		if ((p != gdTransparent) && (p != 0)) {
			gdImageSetPixel (im, x, y, gdBrushed);
		}
		im->stylePos = im->stylePos % im->styleLength;
		break;
	case gdBrushed:
		gdImageBrushApply (im, x, y);
		break;
	case gdTiled:
		gdImageTileApply (im, x, y);
		break;
	case gdAntiAliased:
		/* This shouldn't happen (2.0.26) because we just call
		  gdImageAALine now, but do something sane. */
		gdImageSetPixel(im, x, y, im->AA_color);
		break;
	default:
		if (gdImageBoundsSafeMacro (im, x, y)) {
			if (im->trueColor) {
				switch (im->alphaBlendingFlag) {
					default:
					case gdEffectReplace:
						im->tpixels[y][x] = color;
						break;
					case gdEffectAlphaBlend:
					case gdEffectNormal:
						im->tpixels[y][x] = gdAlphaBlend(im->tpixels[y][x], color);
						break;
					case gdEffectOverlay :
						im->tpixels[y][x] = gdLayerOverlay(im->tpixels[y][x], color);
						break;
					case gdEffectMultiply :
						im->tpixels[y][x] = gdLayerMultiply(im->tpixels[y][x], color);
						break;
				}
			} else {
				im->pixels[y][x] = color;
			}
		}
		break;
	}
}

/* ---- src/gd.c: gdAlphaBlend / gdLayerOverlay (+ its static helper
 * gdAlphaOverlayColor) / gdLayerMultiply, VERBATIM. Only reachable from
 * gdImageSetPixel's trueColor branch, which this harness's corpus never
 * takes (every image built by main() has trueColor=0) -- included anyway
 * for full fidelity since they are pure int math with no further deps. */
BGD_DECLARE(int) gdAlphaBlend (int dst, int src)
{
	int src_alpha = gdTrueColorGetAlpha(src);
	int dst_alpha, alpha, red, green, blue;
	int src_weight, dst_weight, tot_weight;

	if( src_alpha == gdAlphaOpaque )
		return src;

	dst_alpha = gdTrueColorGetAlpha(dst);
	if( src_alpha == gdAlphaTransparent )
		return dst;
	if( dst_alpha == gdAlphaTransparent )
		return src;

	src_weight = gdAlphaTransparent - src_alpha;
	dst_weight = (gdAlphaTransparent - dst_alpha) * src_alpha / gdAlphaMax;
	tot_weight = src_weight + dst_weight;

	alpha = src_alpha * dst_alpha / gdAlphaMax;

	red = (gdTrueColorGetRed(src) * src_weight
	       + gdTrueColorGetRed(dst) * dst_weight) / tot_weight;
	green = (gdTrueColorGetGreen(src) * src_weight
	         + gdTrueColorGetGreen(dst) * dst_weight) / tot_weight;
	blue = (gdTrueColorGetBlue(src) * src_weight
	        + gdTrueColorGetBlue(dst) * dst_weight) / tot_weight;

	return ((alpha << 24) + (red << 16) + (green << 8) + blue);
}

static int gdAlphaOverlayColor (int src, int dst, int max );
BGD_DECLARE(int) gdLayerOverlay (int dst, int src)
{
	int a1, a2;
	a1 = gdAlphaMax - gdTrueColorGetAlpha(dst);
	a2 = gdAlphaMax - gdTrueColorGetAlpha(src);
	return ( ((gdAlphaMax - a1*a2/gdAlphaMax) << 24) +
		(gdAlphaOverlayColor( gdTrueColorGetRed(src), gdTrueColorGetRed(dst), gdRedMax ) << 16) +
		(gdAlphaOverlayColor( gdTrueColorGetGreen(src), gdTrueColorGetGreen(dst), gdGreenMax ) << 8) +
		(gdAlphaOverlayColor( gdTrueColorGetBlue(src), gdTrueColorGetBlue(dst), gdBlueMax ))
		);
}

static int gdAlphaOverlayColor (int src, int dst, int max )
{
	dst = dst << 1;
	if( dst > max ) {
		return dst + (src << 1) - (dst * src / max) - max;
	} else {
		return dst * src / max;
	}
}

BGD_DECLARE(int) gdLayerMultiply (int dst, int src)
{
	int a1, a2, r1, r2, g1, g2, b1, b2;
	a1 = gdAlphaMax - gdTrueColorGetAlpha(src);
	a2 = gdAlphaMax - gdTrueColorGetAlpha(dst);

	r1 = gdRedMax - (a1 * (gdRedMax - gdTrueColorGetRed(src))) / gdAlphaMax;
	r2 = gdRedMax - (a2 * (gdRedMax - gdTrueColorGetRed(dst))) / gdAlphaMax;
	g1 = gdGreenMax - (a1 * (gdGreenMax - gdTrueColorGetGreen(src))) / gdAlphaMax;
	g2 = gdGreenMax - (a2 * (gdGreenMax - gdTrueColorGetGreen(dst))) / gdAlphaMax;
	b1 = gdBlueMax - (a1 * (gdBlueMax - gdTrueColorGetBlue(src))) / gdAlphaMax;
	b2 = gdBlueMax - (a2 * (gdBlueMax - gdTrueColorGetBlue(dst))) / gdAlphaMax ;

	a1 = gdAlphaMax - a1;
	a2 = gdAlphaMax - a2;
	return ( ((a1*a2/gdAlphaMax) << 24) +
			 ((r1*r2/gdRedMax) << 16) +
			 ((g1*g2/gdGreenMax) << 8) +
			 ((b1*b2/gdBlueMax))
		);
}

/* NOT verbatim: gdImageBrushApply/gdImageTileApply in the real src/gd.c pull
 * in a second gdImagePtr (im->brush / im->tile) and a full recompositing
 * routine. gdImageSetPixel's `switch(color)` only dispatches to these when
 * color equals the gdBrushed(-3)/gdTiled(-5) sentinel, which this harness's
 * corpus never produces (every crafted `color` is a plain fill value, never
 * one of gd.h's negative special-color constants) -- these bodies are
 * therefore dead code for every input in io/input/, kept only so the
 * (unmodified) gdImageSetPixel switch statement still links. */
static void gdImageBrushApply (gdImagePtr im, int x, int y)
{
	(void) im; (void) x; (void) y;
}
static void gdImageTileApply (gdImagePtr im, int x, int y)
{
	(void) im; (void) x; (void) y;
}

/* ==== TARGET FUNCTION -- VERBATIM, byte-identical to
 * dataset/cvf_110ffb58/target/original_function.c. Do not edit. ==== */
BGD_DECLARE(void) gdImageFillToBorder (gdImagePtr im, int x, int y, int border, int color)
{
	int lastBorder;
	/* Seek left */
	int leftLimit, rightLimit;
	int i;
	int restoreAlphaBleding;

	if (border < 0) {
		/* Refuse to fill to a non-solid border */
		return;
	}

	leftLimit = (-1);

	restoreAlphaBleding = im->alphaBlendingFlag;
	im->alphaBlendingFlag = 0;

	if (x >= im->sx) {
		x = im->sx - 1;
	} else if (x < 0) {
		x = 0;
	}
	if (y >= im->sy) {
		y = im->sy - 1;
	} else if (y < 0) {
		y = 0;
	}
	
	for (i = x; (i >= 0); i--) {
		if (gdImageGetPixel (im, i, y) == border) {
			break;
		}
		gdImageSetPixel (im, i, y, color);
		leftLimit = i;
	}
	if (leftLimit == (-1)) {
		im->alphaBlendingFlag = restoreAlphaBleding;
		return;
	}
	/* Seek right */
	rightLimit = x;
	for (i = (x + 1); (i < im->sx); i++) {
		if (gdImageGetPixel (im, i, y) == border) {
			break;
		}
		gdImageSetPixel (im, i, y, color);
		rightLimit = i;
	}
	/* Look at lines above and below and start paints */
	/* Above */
	if (y > 0) {
		lastBorder = 1;
		for (i = leftLimit; (i <= rightLimit); i++) {
			int c;
			c = gdImageGetPixel (im, i, y - 1);
			if (lastBorder) {
				if ((c != border) && (c != color)) {
					gdImageFillToBorder (im, i, y - 1, border, color);
					lastBorder = 0;
				}
			} else if ((c == border) || (c == color)) {
				lastBorder = 1;
			}
		}
	}
	/* Below */
	if (y < ((im->sy) - 1)) {
		lastBorder = 1;
		for (i = leftLimit; (i <= rightLimit); i++) {
			int c = gdImageGetPixel (im, i, y + 1);
			if (lastBorder) {
				if ((c != border) && (c != color)) {
					gdImageFillToBorder (im, i, y + 1, border, color);
					lastBorder = 0;
				}
			} else if ((c == border) || (c == color)) {
				lastBorder = 1;
			}
		}
	}
	im->alphaBlendingFlag = restoreAlphaBleding;
}
/* ==== END TARGET FUNCTION ==== */

int main(int argc, char **argv)
{
	if (argc < 2) {
		return 0;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		return 0;
	}
	if (fseek(f, 0, SEEK_END) != 0) {
		fclose(f);
		return 0;
	}
	long sz = ftell(f);
	if (sz < 24) {
		fclose(f);
		return 0;
	}
	rewind(f);

	/* Attacker data MUST live in a heap allocation (not a stack/global
	 * buffer) so ASAN's heap redzones cover it. */
	unsigned char *buf = (unsigned char *) malloc((size_t) sz);
	if (!buf) {
		fclose(f);
		return 0;
	}
	size_t n = fread(buf, 1, (size_t) sz, f);
	fclose(f);
	if (n < 24) {
		free(buf);
		return 0;
	}

	/* Layout: 6 x little-endian int32 -- width, height, x, y, border, color.
	 * (Same field order the bundle's whole-project PoC-crafting harness --
	 * dataset/cvf_110ffb58/source_code/harness.c -- used.) Any trailing
	 * bytes beyond offset 24 are ignored (kept, not read, so files longer
	 * than 24 bytes are valid corpus entries too). */
	int32_t width, height, x, y, border, color;
	memcpy(&width,  buf +  0, 4);
	memcpy(&height, buf +  4, 4);
	memcpy(&x,      buf +  8, 4);
	memcpy(&y,      buf + 12, 4);
	memcpy(&border, buf + 16, 4);
	memcpy(&color,  buf + 20, 4);
	free(buf);

	/* width/height are not the vulnerable fields (border/color are) --
	 * clamp them to a small sane range so every input allocates a tiny,
	 * fast-to-fill canvas instead of stressing an unrelated huge-alloc
	 * path. */
	if (width  < 2)  width  = 2;
	if (width  > 64) width  = 64;
	if (height < 2)  height = 2;
	if (height > 64) height = 64;

	/* Hand-build a palette (non-truecolor) gdImage, mirroring
	 * gdImageCreate() (src/gd.c:161): a calloc'd struct (background pixels
	 * start at byte 0 = a valid, allocatable-looking palette index), a
	 * malloc'd row-pointer table, one calloc'd row per scanline, and the
	 * same cx1/cy1/cx2/cy2 clip rectangle / trueColor=0 gdImageCreate sets.
	 * This is struct bring-up, not part of the vulnerable logic. */
	gdImagePtr im = (gdImagePtr) calloc(1, sizeof(gdImage));
	if (!im) {
		return 0;
	}
	im->pixels = (unsigned char **) malloc(sizeof(unsigned char *) * (size_t) height);
	if (!im->pixels) {
		free(im);
		return 0;
	}
	for (int32_t i = 0; i < height; i++) {
		im->pixels[i] = (unsigned char *) calloc((size_t) width, 1);
		if (!im->pixels[i]) {
			for (int32_t j = 0; j < i; j++) {
				free(im->pixels[j]);
			}
			free(im->pixels);
			free(im);
			return 0;
		}
	}
	im->sx = width;
	im->sy = height;
	im->trueColor = 0;
	im->tpixels = NULL;
	im->style = NULL;
	im->brush = NULL;
	im->tile = NULL;
	im->alphaBlendingFlag = 0;
	im->cx1 = 0;
	im->cy1 = 0;
	im->cx2 = im->sx - 1;
	im->cy2 = im->sy - 1;

	gdImageFillToBorder(im, (int) x, (int) y, (int) border, (int) color);

	/* Only reached if the recursion converged/returned early (SAFE
	 * inputs) -- TRIGGERING inputs stack-overflow inside the call above
	 * and never get here. */
	for (int32_t i = 0; i < height; i++) {
		free(im->pixels[i]);
	}
	free(im->pixels);
	free(im);
	return 0;
}
