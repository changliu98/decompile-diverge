/* cve_barebone harness: CVE-2016-6214 libgd gdImageCreateFromTgaCtx (CWE-125 heap READ overflow).
 * Self-contained: real type/callee definitions copied verbatim from libgd source; the target
 * function is spliced byte-for-byte from target/original_function.c. Links with only -lm. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>

/* --- macros copied verbatim from gd.h --- */
#define BGD_DECLARE(rt) rt
#define gdMaxColors 256
#define gdAlphaMax 127
#define GD_RESOLUTION           96      /* pixels per inch */
#define gdTrueColor(r, g, b) (((r) << 16) + \
			      ((g) << 8) +  \
			      (b))
#define gdTrueColorAlpha(r, g, b, a) (((a) << 24) + \
				      ((r) << 16) + \
				      ((g) << 8) +  \
				      (b))
/* gd_errors.h */
#define GD_WARNING 4

/* --- incidental logging callees: faithful no-op stubs --- */
static void gd_error(const char *format, ...) { (void)format; }
static void gd_error_ex(int priority, const char *format, ...) { (void)priority; (void)format; }

/* --- gd memory wrappers: gd* thinly wrap libc (gdhelpers.c) --- */
void *gdMalloc(size_t size) { return malloc(size); }
void *gdCalloc(size_t nmemb, size_t size) { return calloc(nmemb, size); }
void *gdRealloc(void *ptr, size_t size) { return realloc(ptr, size); }
void gdFree(void *ptr) { free(ptr); }

/* --- gdInterpolationMethod / interpolation_method (gd.h) --- */
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
	GD_LINEAR,
	GD_METHOD_COUNT = 23
} gdInterpolationMethod;

typedef double (* interpolation_method )(double);

/* --- gdImageStruct / gdImagePtr (gd.h) --- */
typedef struct gdImageStruct {
	/* Palette-based image pixels */
	unsigned char **pixels;
	int sx;
	int sy;
	/* These are valid in palette images only. See also
	   'alpha', which appears later in the structure to
	   preserve binary backwards compatibility */
	int colorsTotal;
	int red[gdMaxColors];
	int green[gdMaxColors];
	int blue[gdMaxColors];
	int open[gdMaxColors];
	/* For backwards compatibility, this is set to the
	   first palette entry with 100% transparency,
	   and is also set and reset by the
	   gdImageColorTransparent function. Newer
	   applications can allocate palette entries
	   with any desired level of transparency; however,
	   bear in mind that many viewers, notably
	   many web browsers, fail to implement
	   full alpha channel for PNG and provide
	   support for full opacity or transparency only. */
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
	/* New in 2.0: thickness of line. Initialized to 1. */
	int thick;
	/* New in 2.0: alpha channel for palettes. Note that only
	   Macintosh Internet Explorer and (possibly) Netscape 6
	   really support multiple levels of transparency in
	   palettes, to my knowledge, as of 2/15/01. Most
	   common browsers will display 100% opaque and
	   100% transparent correctly, and do something
	   unpredictable and/or undesirable for levels
	   in between. TBB */
	int alpha[gdMaxColors];
	/* Truecolor flag and pixels. New 2.0 fields appear here at the
	   end to minimize breakage of existing object code. */
	int trueColor;
	int **tpixels;
	/* Should alpha channel be copied, or applied, each time a
	   pixel is drawn? This applies to truecolor images only.
	   No attempt is made to alpha-blend in palette images,
	   even if semitransparent palette entries exist.
	   To do that, build your image as a truecolor image,
	   then quantize down to 8 bits. */
	int alphaBlendingFlag;
	/* Should the alpha channel of the image be saved? This affects
	   PNG at the moment; other future formats may also
	   have that capability. JPEG doesn't. */
	int saveAlphaFlag;

	/* There should NEVER BE ACCESSOR MACROS FOR ITEMS BELOW HERE, so this
	   part of the structure can be safely changed in new releases. */

	/* 2.0.12: anti-aliased globals. 2.0.26: just a few vestiges after
	  switching to the fast, memory-cheap implementation from PHP-gd. */
	int AA;
	int AA_color;
	int AA_dont_blend;

	/* 2.0.12: simple clipping rectangle. These values
	  must be checked for safety when set; please use
	  gdImageSetClip */
	int cx1;
	int cy1;
	int cx2;
	int cy2;

	/* 2.1.0: allows to specify resolution in dpi */
	unsigned int res_x;
	unsigned int res_y;

	/* Selects quantization method, see gdImageTrueColorToPaletteSetMethod() and gdPaletteQuantizationMethod enum. */
	int paletteQuantizationMethod;
	/* speed/quality trade-off. 1 = best quality, 10 = best speed. 0 = method-specific default.
	   Applicable to GD_QUANT_LIQ and GD_QUANT_NEUQUANT. */
	int paletteQuantizationSpeed;
	/* Image will remain true-color if conversion to palette cannot achieve given quality.
	   Value from 1 to 100, 1 = ugly, 100 = perfect. Applicable to GD_QUANT_LIQ.*/
	int paletteQuantizationMinQuality;
	/* Image will use minimum number of palette colors needed to achieve given quality. Must be higher than paletteQuantizationMinQuality
	   Value from 1 to 100, 1 = ugly, 100 = perfect. Applicable to GD_QUANT_LIQ.*/
	int paletteQuantizationMaxQuality;
	gdInterpolationMethod interpolation_id;
	interpolation_method interpolation;
}
gdImage;
typedef gdImage *gdImagePtr;

/* --- gdIOCtx (gd_io.h) --- */
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

/* --- oTga (gd_tga.h) --- */
typedef struct oTga_ {
	uint8_t  identsize;	// size of ID field that follows 18 uint8_t header (0 usually)
	uint8_t  colormaptype;	// type of colour map 0=none, 1=has palette					[IGNORED] Adrian requested no support
	uint8_t  imagetype;	// type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed

	int colormapstart;	// first colour map entry in palette						[IGNORED] Adrian requested no support
	int colormaplength;	// number of colours in palette								[IGNORED] Adrian requested no support
	uint8_t  colormapbits;	// number of bits per palette entry 15,16,24,32				[IGNORED] Adrian requested no support

	int xstart;			// image x origin
	int ystart;			// image y origin
	int width;			// image width in pixels
	int height;			// image height in pixels
	uint8_t  bits;			// image bits per pixel 8,16,24,32
	uint8_t alphabits;		// alpha bits (low 4bits of header 17)
	uint8_t fliph;			// horizontal or vertical
	uint8_t flipv;			// flip
	char *ident;		// identifcation tag string
	int *bitmap;		// bitmap data

} oTga;

/* --- TGA #defines copied verbatim from gd_tga.h --- */
#define TGA_TYPE_RGB							2
#define TGA_TYPE_RGB_RLE						10
#define TGA_BPP_8	8
#define TGA_BPP_16	16
#define TGA_BPP_24	24
#define TGA_BPP_32	32
#define TGA_RLE_FLAG	128

/* --- gdGetBuf (gd_io.c, verbatim) --- */
int gdGetBuf(void *buf, int size, gdIOCtx *ctx)
{
	return (ctx->getBuf)(ctx, buf, size);
}


/* --- in-memory gdIOCtx scaffolding (mirrors gd_io_dp.c dynamicGetbuf) --- */
typedef struct {
	gdIOCtx ctx;
	unsigned char *data;
	int pos;
	int logicalSize;
} memIOCtx;

static int memGetbuf(gdIOCtx *c, void *buf, int len)
{
	memIOCtx *m = (memIOCtx *) c;
	int remain = m->logicalSize - m->pos;
	int rlen;
	if (remain >= len) {
		rlen = len;
	} else {
		if (remain == 0)
			return 0;
		rlen = remain;
	}
	memcpy(buf, m->data + m->pos, rlen);
	m->pos += rlen;
	return rlen;
}

static int memGetchar(gdIOCtx *c)
{
	unsigned char b;
	int rv = memGetbuf(c, &b, 1);
	if (rv != 1)
		return EOF;
	return b;
}

/* --- overflow2 (gd_security.c, verbatim) --- */
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


/* --- gdImageCreateTrueColor (gd.c, verbatim) --- */
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
	/* 2.0.2: alpha blending is now on by default, and saving of alpha is
	   off by default. This allows font antialiasing to work as expected
	   on the first try in JPEGs -- quite important -- and also allows
	   for smaller PNGs when saving of alpha channel is not really
	   desired, which it usually isn't! */
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


/* --- gdImageAlphaBlending / gdImageSaveAlpha (gd.c, verbatim) --- */
BGD_DECLARE(void) gdImageAlphaBlending (gdImagePtr im, int alphaBlendingArg)
{
	im->alphaBlendingFlag = alphaBlendingArg;
}

BGD_DECLARE(void) gdImageSaveAlpha (gdImagePtr im, int saveAlphaArg)
{
	im->saveAlphaFlag = saveAlphaArg;
}


/* --- flip helpers (gd_transform.c, verbatim) --- */
BGD_DECLARE(void) gdImageFlipVertical(gdImagePtr im)
{
	register int x, y;

	if (im->trueColor) {
		for (y = 0; y < im->sy / 2; y++) {
			int *row_dst = im->tpixels[y];
			int *row_src = im->tpixels[im->sy - 1 - y];
			for (x = 0; x < im->sx; x++) {
				register int p;
				p = row_dst[x];
				row_dst[x] = im->tpixels[im->sy - 1 - y][x];
				row_src[x] = p;
			}
		}
	} else {
		unsigned char p;
		for (y = 0; y < im->sy / 2; y++) {
			for (x = 0; x < im->sx; x++) {
				p = im->pixels[y][x];
				im->pixels[y][x] =	im->pixels[im->sy - 1 - y][x];
				im->pixels[im->sy - 1 - y][x] = p;
			}
		}
	}
	return;
}

BGD_DECLARE(void) gdImageFlipHorizontal(gdImagePtr im)
{

	int x, y;

	if (im->trueColor) {
		int *px1, *px2, tmp;

		for (y = 0; y < im->sy; y++) {
			px1 = im->tpixels[y];
			px2 = im->tpixels[y] + im->sx - 1;
			for (x = 0; x < (im->sx >> 1); x++) {
				tmp = *px1;
				*px1 = *px2;
				*px2 = tmp;
				px1++;
				px2--;
			}
		}
	} else {
		unsigned char *px1, *px2, tmp;

		for (y = 0; y < im->sy; y++) {
			px1 = im->pixels[y];
			px2 = im->pixels[y] + im->sx - 1;
			for (x = 0; x < (im->sx >> 1); x++) {
				tmp = *px1;
				*px1 = *px2;
				*px2 = tmp;
				px1++;
				px2--;
			}
		}
	}
}

BGD_DECLARE(void) gdImageFlipBoth(gdImagePtr im)
{
	gdImageFlipVertical(im);
	gdImageFlipHorizontal(im);
}


/* --- read_header_tga (gd_tga.c, verbatim) --- */
int read_header_tga(gdIOCtx *ctx, oTga *tga)
{

	unsigned char header[18];

	if (gdGetBuf(header, sizeof(header), ctx) < 18) {
		gd_error("fail to read header");
		return -1;
	}

	tga->identsize = header[0];
	tga->colormaptype = header[1];
	tga->imagetype = header[2];
	tga->colormapstart = header[3] + (header[4] << 8);
	tga->colormaplength = header[5] + (header[6] << 8);
	tga->colormapbits = header[7];
	tga->xstart = header[8] + (header[9] << 8);
	tga->ystart = header[10] + (header[11] << 8);
	tga->width = header[12] + (header[13] << 8);
	tga->height = header[14] + (header[15] << 8);
	tga->bits = header[16];
	tga->alphabits = header[17] & 0x0f;
	tga->fliph = (header[17] & 0x10) ? 1 : 0;
	tga->flipv = (header[17] & 0x20) ? 0 : 1;

#if DEBUG
	printf("format bps: %i\n", tga->bits);
	printf("flip h/v: %i / %i\n", tga->fliph, tga->flipv);
	printf("alpha: %i\n", tga->alphabits);
	printf("wxh: %i %i\n", tga->width, tga->height);
#endif

	switch(tga->bits) {
	case 8:
	case 16:
	case 24:
	case 32:
		break;
	default:
		gd_error("bps %i not supported", tga->bits);
		return -1;
		break;
	}

	tga->ident = NULL;

	if (tga->identsize > 0) {
		tga->ident = (char *) gdMalloc(tga->identsize * sizeof(char));
		if(tga->ident == NULL) {
			return -1;
		}

		gdGetBuf(tga->ident, tga->identsize, ctx);
	}

	return 1;
}


/* --- read_image_tga (gd_tga.c, verbatim) --- */
int read_image_tga( gdIOCtx *ctx, oTga *tga )
{
	int pixel_block_size = (tga->bits / 8);
	int image_block_size = (tga->width * tga->height) * pixel_block_size;
	uint8_t* decompression_buffer = NULL;
	unsigned char* conversion_buffer = NULL;
	int buffer_caret = 0;
	int bitmap_caret = 0;
	int i = 0;
	int j = 0;
	uint8_t encoded_pixels;

	if(overflow2(tga->width, tga->height)) {
		return -1;
	}

	if(overflow2(tga->width * tga->height, pixel_block_size)) {
		return -1;
	}

	if(overflow2(image_block_size, sizeof(int))) {
		return -1;
	}

	/*! \todo Add more image type support.
	 */
	if (tga->imagetype != TGA_TYPE_RGB && tga->imagetype != TGA_TYPE_RGB_RLE)
		return -1;

	/*!	\brief Allocate memmory for image block
	 *  Allocate a chunk of memory for the image block to be passed into.
	 */
	tga->bitmap = (int *) gdMalloc(image_block_size * sizeof(int));
	if (tga->bitmap == NULL)
		return -1;

	switch (tga->imagetype) {
	case TGA_TYPE_RGB:
		/*! \brief Read in uncompressed RGB TGA
		 *  Chunk load the pixel data from an uncompressed RGB type TGA.
		 */
		conversion_buffer = (unsigned char *) gdMalloc(image_block_size * sizeof(unsigned char));
		if (conversion_buffer == NULL) {
			return -1;
		}

		if (gdGetBuf(conversion_buffer, image_block_size, ctx) != image_block_size) {
			gd_error("gd-tga: premature end of image data\n");
			gdFree(conversion_buffer);
			return -1;
		}

		while (buffer_caret < image_block_size) {
			tga->bitmap[buffer_caret] = (int) conversion_buffer[buffer_caret];
			buffer_caret++;
		}

		gdFree(conversion_buffer);
		break;

	case TGA_TYPE_RGB_RLE:
		/*! \brief Read in RLE compressed RGB TGA
		 *  Chunk load the pixel data from an RLE compressed RGB type TGA.
		 */
		decompression_buffer = (uint8_t*) gdMalloc(image_block_size * sizeof(uint8_t));
		if (decompression_buffer == NULL) {
			return -1;
		}
		conversion_buffer = (unsigned char *) gdMalloc(image_block_size * sizeof(unsigned char));
		if (conversion_buffer == NULL) {
			gd_error("gd-tga: premature end of image data\n");
			gdFree( decompression_buffer );
			return -1;
		}

		if (gdGetBuf(conversion_buffer, image_block_size, ctx) != image_block_size) {
			gdFree(conversion_buffer);
			gdFree(decompression_buffer);
			return -1;
		}

		buffer_caret = 0;

		while( buffer_caret < image_block_size) {
			decompression_buffer[buffer_caret] = (int)conversion_buffer[buffer_caret];
			buffer_caret++;
		}

		buffer_caret = 0;

		while( bitmap_caret < image_block_size ) {

			if ((decompression_buffer[buffer_caret] & TGA_RLE_FLAG) == TGA_RLE_FLAG) {
				encoded_pixels = ( ( decompression_buffer[ buffer_caret ] & 127 ) + 1 );
				buffer_caret++;

				for (i = 0; i < encoded_pixels; i++) {
					for (j = 0; j < pixel_block_size; j++, bitmap_caret++) {
						tga->bitmap[ bitmap_caret ] = decompression_buffer[ buffer_caret + j ];
					}
				}
				buffer_caret += pixel_block_size;
			} else {
				encoded_pixels = decompression_buffer[ buffer_caret ] + 1;
				buffer_caret++;

				for (i = 0; i < encoded_pixels; i++) {
					for( j = 0; j < pixel_block_size; j++, bitmap_caret++ ) {
						tga->bitmap[ bitmap_caret ] = decompression_buffer[ buffer_caret + j ];
					}
					buffer_caret += pixel_block_size;
				}
			}
		}
		gdFree( decompression_buffer );
		gdFree( conversion_buffer );
		break;
	}

	return 1;
}


/* --- free_tga (gd_tga.c, verbatim) --- */
void free_tga(oTga * tga)
{
	if (tga) {
		if (tga->ident)
			gdFree(tga->ident);
		if (tga->bitmap)
			gdFree(tga->bitmap);
		gdFree(tga);
	}
}


/* --- TARGET FUNCTION (byte-for-byte from target/original_function.c) --- */
BGD_DECLARE(gdImagePtr) gdImageCreateFromTgaCtx(gdIOCtx* ctx)
{
	int bitmap_caret = 0;
	oTga *tga = NULL;
	/*	int pixel_block_size = 0;
		int image_block_size = 0; */
	volatile gdImagePtr image = NULL;
	int x = 0;
	int y = 0;

	tga = (oTga *) gdMalloc(sizeof(oTga));
	if (!tga) {
		return NULL;
	}

	tga->bitmap = NULL;
	tga->ident = NULL;

	if (read_header_tga(ctx, tga) < 0) {
		free_tga(tga);
		return NULL;
	}

	/*TODO: Will this be used?
		pixel_block_size = tga->bits / 8;
		image_block_size = (tga->width * tga->height) * pixel_block_size;
	*/

	if (read_image_tga(ctx, tga) < 0) {
		free_tga(tga);
		return NULL;
	}

	image = gdImageCreateTrueColor((int)tga->width, (int)tga->height );

	if (image == 0) {
		free_tga( tga );
		return NULL;
	}

	/*!	\brief Populate GD image object
	 *  Copy the pixel data from our tga bitmap buffer into the GD image
	 *  Disable blending and save the alpha channel per default
	 */
	if (tga->alphabits) {
		gdImageAlphaBlending(image, 0);
		gdImageSaveAlpha(image, 1);
	}

	/* TODO: use alphabits as soon as we support 24bit and other alpha bps (ie != 8bits) */
	for (y = 0; y < tga->height; y++) {
		register int *tpix = image->tpixels[y];
		for ( x = 0; x < tga->width; x++, tpix++) {
			if (tga->bits == TGA_BPP_24) {
				*tpix = gdTrueColor(tga->bitmap[bitmap_caret + 2], tga->bitmap[bitmap_caret + 1], tga->bitmap[bitmap_caret]);
				bitmap_caret += 3;
			} else if (tga->bits == TGA_BPP_32 || tga->alphabits) {
				register int a = tga->bitmap[bitmap_caret + 3];

				*tpix = gdTrueColorAlpha(tga->bitmap[bitmap_caret + 2], tga->bitmap[bitmap_caret + 1], tga->bitmap[bitmap_caret], gdAlphaMax - (a >> 1));
				bitmap_caret += 4;
			}
		}
	}

	if (tga->flipv && tga->fliph) {
		gdImageFlipBoth(image);
	} else if (tga->flipv) {
		gdImageFlipVertical(image);
	} else if (tga->fliph) {
		gdImageFlipHorizontal(image);
	}

	free_tga(tga);

	return image;
}
int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	FILE *f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	fseek(f, 0, SEEK_END);
	long sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (sz < 0) {
		fclose(f);
		return 0;
	}
	/* HEAP-allocate the input so ASAN guards it (never a stack/static buffer). */
	unsigned char *data = (unsigned char *) malloc(sz ? (size_t) sz : 1);
	if (!data) {
		fclose(f);
		return 0;
	}
	size_t got = fread(data, 1, (size_t) sz, f);
	fclose(f);

	memIOCtx mc;
	memset(&mc, 0, sizeof(mc));
	mc.ctx.getC = memGetchar;
	mc.ctx.getBuf = memGetbuf;
	mc.data = data;
	mc.pos = 0;
	mc.logicalSize = (int) got;

	gdImagePtr im = gdImageCreateFromTgaCtx(&mc.ctx);

	if (im) {
		int y;
		for (y = 0; y < im->sy; y++)
			free(im->tpixels[y]);
		free(im->tpixels);
		free(im);
	}
	free(data);
	return 0;
}
