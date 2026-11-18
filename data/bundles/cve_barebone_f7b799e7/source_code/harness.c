/* Direct-call crash harness for openjpeg color_cmyk_to_rgb
 * (CVE-2016-4796, CWE-125, src/bin/common/color.c).
 *
 * color_cmyk_to_rgb() takes the loop bound `max` from comps[0]'s OWN
 * dimensions:
 *
 *     w = image->comps[0].w;
 *     h = image->comps[0].h;
 *     max = w * h;
 *     for (i = 0; i < max; ++i) {
 *         C = (float)(image->comps[0].data[i]) * sC;
 *         M = (float)(image->comps[1].data[i]) * sM;   <- color.c:871
 *         Y = (float)(image->comps[2].data[i]) * sY;
 *         K = (float)(image->comps[3].data[i]) * sK;
 *         ...
 *
 * but each component's `data` buffer is independently sized from ITS OWN
 * w/h by the real decoder (tile-components can legitimately differ in
 * size under dx/dy subsampling, or be forged to differ by a malformed
 * codestream). There is no check anywhere in this function that
 * comps[1]/comps[2]/comps[3] actually hold >= max elements. If any of
 * them is smaller than max, the loop walks straight past the end of that
 * component's heap allocation -> heap-buffer-overflow READ, matching
 * baseline.summary "AddressSanitizer: heap-buffer-overflow
 * .../color.c:871:15 in color_cmyk_to_rgb" and baseline.cwe CWE-125
 * exactly.
 *
 * main() mimics the real caller (opj_decompress() in
 * src/bin/jp2/opj_decompress.c, which calls color_cmyk_to_rgb(image)
 * directly on the opj_image_t produced by opj_decode()/
 * opj_get_decoded_tile()): it reads the whole input file into a malloc'd
 * heap buffer, uses those bytes to derive per-component dimensions/
 * precisions and EACH component's OWN allocation size (mirroring how
 * a real -- or forged -- codestream can hand the decoder mismatched
 * per-component tile sizes), allocates every comps[i].data buffer on
 * the heap sized to ITS OWN (possibly-too-small) count, and calls
 * color_cmyk_to_rgb(&image) once, directly.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- minimal but faithful type/struct defs the function needs ---- */
/* (real names verbatim from src/lib/openjp2/openjpeg.h) */

typedef uint16_t OPJ_UINT16;
typedef int32_t  OPJ_INT32;
typedef uint32_t OPJ_UINT32;
typedef unsigned char OPJ_BYTE;

/** Supported image color spaces (openjpeg.h, verbatim) */
typedef enum COLOR_SPACE {
    OPJ_CLRSPC_UNKNOWN = -1,	/**< not supported by the library */
    OPJ_CLRSPC_UNSPECIFIED = 0,	/**< not specified in the codestream */
    OPJ_CLRSPC_SRGB = 1,		/**< sRGB */
    OPJ_CLRSPC_GRAY = 2,		/**< grayscale */
    OPJ_CLRSPC_SYCC = 3,		/**< YUV */
    OPJ_CLRSPC_EYCC = 4,        /**< e-YCC */
    OPJ_CLRSPC_CMYK = 5         /**< CMYK */
} OPJ_COLOR_SPACE;

/**
 * Defines a single image component (openjpeg.h, verbatim)
 * */
typedef struct opj_image_comp {
	/** XRsiz: horizontal separation of a sample of ith component with respect to the reference grid */
	OPJ_UINT32 dx;
	/** YRsiz: vertical separation of a sample of ith component with respect to the reference grid */
	OPJ_UINT32 dy;
	/** data width */
	OPJ_UINT32 w;
	/** data height */
	OPJ_UINT32 h;
	/** x component offset compared to the whole image */
	OPJ_UINT32 x0;
	/** y component offset compared to the whole image */
	OPJ_UINT32 y0;
	/** precision */
	OPJ_UINT32 prec;
	/** image depth in bits */
	OPJ_UINT32 bpp;
	/** signed (1) / unsigned (0) */
	OPJ_UINT32 sgnd;
	/** number of decoded resolution */
	OPJ_UINT32 resno_decoded;
	/** number of division by 2 of the out image compared to the original size of image */
	OPJ_UINT32 factor;
	/** image component data */
	OPJ_INT32 *data;
  /** alpha channel */
  OPJ_UINT16 alpha;
} opj_image_comp_t;

/**
 * Defines image data and characteristics (openjpeg.h, verbatim)
 * */
typedef struct opj_image {
	/** XOsiz: horizontal offset from the origin of the reference grid to the left side of the image area */
	OPJ_UINT32 x0;
	/** YOsiz: vertical offset from the origin of the reference grid to the top side of the image area */
	OPJ_UINT32 y0;
	/** Xsiz: width of the reference grid */
	OPJ_UINT32 x1;
	/** Ysiz: height of the reference grid */
	OPJ_UINT32 y1;
	/** number of components in the image */
	OPJ_UINT32 numcomps;
	/** color space: sRGB, Greyscale or YUV */
	OPJ_COLOR_SPACE color_space;
	/** image components */
	opj_image_comp_t *comps;
	/** 'restricted' ICC profile */
	OPJ_BYTE *icc_profile_buf;
	/** size of ICC profile */
	OPJ_UINT32 icc_profile_len;
} opj_image_t;

/* ---- verbatim target function (target/original_function.c), unchanged ---- */
void color_cmyk_to_rgb(opj_image_t *image)
{
	float C, M, Y, K;
	float sC, sM, sY, sK;
	unsigned int w, h, max, i;

	w = image->comps[0].w;
	h = image->comps[0].h;

	if(image->numcomps < 4) return;

	max = w * h;
	
	sC = 1.0F / (float)((1 << image->comps[0].prec) - 1);
	sM = 1.0F / (float)((1 << image->comps[1].prec) - 1);
	sY = 1.0F / (float)((1 << image->comps[2].prec) - 1);
	sK = 1.0F / (float)((1 << image->comps[3].prec) - 1);

	for(i = 0; i < max; ++i)
	{
		/* CMYK values from 0 to 1 */
		C = (float)(image->comps[0].data[i]) * sC;
		M = (float)(image->comps[1].data[i]) * sM;
		Y = (float)(image->comps[2].data[i]) * sY;
		K = (float)(image->comps[3].data[i]) * sK;
		
		/* Invert all CMYK values */
		C = 1.0F - C;
		M = 1.0F - M;
		Y = 1.0F - Y;
		K = 1.0F - K;

		/* CMYK -> RGB : RGB results from 0 to 255 */
		image->comps[0].data[i] = (int)(255.0F * C * K); /* R */
		image->comps[1].data[i] = (int)(255.0F * M * K); /* G */
		image->comps[2].data[i] = (int)(255.0F * Y * K); /* B */
	}

	free(image->comps[3].data); image->comps[3].data = NULL;
	image->comps[0].prec = 8;
	image->comps[1].prec = 8;
	image->comps[2].prec = 8;
	image->numcomps -= 1;
	image->color_space = OPJ_CLRSPC_SRGB;
	
	for (i = 3; i < image->numcomps; ++i) {
		memcpy(&(image->comps[i]), &(image->comps[i+1]), sizeof(image->comps[i]));
	}

}
/* ---- end verbatim target function ---- */

/* little-endian field readers over the raw (attacker) input buffer,
 * bounds-checked against the ACTUAL file length so short/empty input
 * files degrade to 0 instead of the harness itself reading past `raw`
 * (that would be a bug in the harness, not the target). */
static unsigned char rd_u8(const unsigned char *buf, size_t len, size_t off)
{
	return (off < len) ? buf[off] : 0;
}

static uint32_t rd_u32(const unsigned char *buf, size_t len, size_t off)
{
	uint32_t v = 0;
	int k;
	for (k = 0; k < 4; ++k) {
		v |= ((uint32_t)rd_u8(buf, len, off + (size_t)k)) << (8 * k);
	}
	return v;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) {
		perror("fopen");
		return 1;
	}
	if (fseek(fp, 0, SEEK_END) != 0) {
		perror("fseek");
		fclose(fp);
		return 1;
	}
	long flen = ftell(fp);
	if (flen < 0) {
		perror("ftell");
		fclose(fp);
		return 1;
	}
	rewind(fp);

	/* Attacker-controlled input, HEAP allocated (never stack/global) so
	 * ASAN's redzones bound it precisely. */
	size_t alloc_len = (size_t)flen > 0 ? (size_t)flen : 1;
	unsigned char *raw = (unsigned char *)malloc(alloc_len);
	if (!raw) {
		perror("malloc");
		fclose(fp);
		return 1;
	}
	if (flen > 0 && fread(raw, (size_t)flen, 1, fp) != 1) {
		fprintf(stderr, "short read\n");
		fclose(fp);
		free(raw);
		return 1;
	}
	fclose(fp);
	size_t rlen = (size_t)flen;

	/* Field layout (24 bytes, little-endian, missing bytes read as 0):
	 *   off 0..3   : prec0,prec1,prec2,prec3     (u8 each, clamped 1..16)
	 *   off 4..7   : w0   (u32, clamped 1..32)   -- comps[0].w
	 *   off 8..11  : h0   (u32, clamped 1..32)   -- comps[0].h
	 *   off 12..15 : alloc1 (u32, capped 4096)   -- # OPJ_INT32 cells actually
	 *                                                malloc'd for comps[1].data
	 *   off 16..19 : alloc2 (u32, capped 4096)   -- comps[2].data cell count
	 *   off 20..23 : alloc3 (u32, capped 4096)   -- comps[3].data cell count
	 *
	 * comps[0].w/h (hence `max`, the loop bound) are always honored by
	 * comps[0]'s OWN allocation (sized exactly `max`, never short) -- the
	 * real bug is that comps[1..3] are each independently sized, so
	 * whichever of alloc1/alloc2/alloc3 is < max reproduces the exact
	 * over-read the target function has no guard against.
	 */
	unsigned int prec0 = (rd_u8(raw, rlen, 0) % 16) + 1;
	unsigned int prec1 = (rd_u8(raw, rlen, 1) % 16) + 1;
	unsigned int prec2 = (rd_u8(raw, rlen, 2) % 16) + 1;
	unsigned int prec3 = (rd_u8(raw, rlen, 3) % 16) + 1;
	unsigned int w0 = (rd_u32(raw, rlen, 4) % 32) + 1;
	unsigned int h0 = (rd_u32(raw, rlen, 8) % 32) + 1;
	unsigned int alloc1 = rd_u32(raw, rlen, 12); if (alloc1 > 4096) alloc1 = 4096;
	unsigned int alloc2 = rd_u32(raw, rlen, 16); if (alloc2 > 4096) alloc2 = 4096;
	unsigned int alloc3 = rd_u32(raw, rlen, 20); if (alloc3 > 4096) alloc3 = 4096;

	unsigned int max = w0 * h0;

	/* Build the opj_image_t the way the real decoder hands it to
	 * color_cmyk_to_rgb(): numcomps components (>=4, else the target
	 * returns immediately without touching anything), comps array itself
	 * heap-allocated (mirrors opj_image_create()), each comps[i].data a
	 * SEPARATE heap allocation whose element count is that component's
	 * OWN, independently-derived size. */
	opj_image_t image;
	memset(&image, 0, sizeof(image));
	image.numcomps = 4;
	image.color_space = OPJ_CLRSPC_CMYK;

	opj_image_comp_t *comps = (opj_image_comp_t *)calloc(image.numcomps, sizeof(opj_image_comp_t));
	if (!comps) { perror("calloc"); free(raw); return 1; }
	image.comps = comps;

	comps[0].w = w0; comps[0].h = h0; comps[0].prec = prec0;
	comps[1].w = w0; comps[1].h = h0; comps[1].prec = prec1;
	comps[2].w = w0; comps[2].h = h0; comps[2].prec = prec2;
	comps[3].w = w0; comps[3].h = h0; comps[3].prec = prec3;

	/* comps[0] is always allocated to the FULL loop bound -- it is the
	 * component the loop bound is derived FROM, so it is never short. */
	comps[0].data = (OPJ_INT32 *)calloc(max, sizeof(OPJ_INT32));
	/* comps[1..3] are each allocated to THEIR OWN (attacker-influenced,
	 * possibly-too-small) element count -- the actual vulnerability. */
	comps[1].data = (OPJ_INT32 *)calloc(alloc1 > 0 ? alloc1 : 1, sizeof(OPJ_INT32));
	comps[2].data = (OPJ_INT32 *)calloc(alloc2 > 0 ? alloc2 : 1, sizeof(OPJ_INT32));
	comps[3].data = (OPJ_INT32 *)calloc(alloc3 > 0 ? alloc3 : 1, sizeof(OPJ_INT32));
	if (!comps[0].data || !comps[1].data || !comps[2].data || !comps[3].data) {
		perror("calloc");
		free(comps[0].data); free(comps[1].data); free(comps[2].data); free(comps[3].data);
		free(comps); free(raw);
		return 1;
	}
	/* alloc1/2/3==0 means a genuine 0-element heap allocation (glibc/ASAN
	 * hand back a valid, zero-usable-size pointer) -- any read at all is
	 * then an immediate heap-buffer-overflow, which is a legitimate
	 * (extreme) instance of the same bug, not a harness artifact. */

	color_cmyk_to_rgb(&image);

	/* Only reached on the safe path (no crash). The target function
	 * already freed+NULLed comps[3].data itself; free(NULL) is a no-op. */
	free(comps[0].data);
	free(comps[1].data);
	free(comps[2].data);
	free(comps[3].data);
	free(comps);
	free(raw);

	printf("color_cmyk_to_rgb done, w0=%u h0=%u max=%u alloc1=%u alloc2=%u alloc3=%u\n",
	       w0, h0, max, alloc1, alloc2, alloc3);
	return 0;
}
