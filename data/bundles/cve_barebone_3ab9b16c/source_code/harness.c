/*
 * Direct-call crash harness for CVE-2016-3183 (openjpeg) — sycc420_to_rgb()
 * heap-buffer-overflow READ (CWE-125), src/bin/common/color.c:223.
 *
 * The target function is embedded VERBATIM (see target/original_function.c),
 * along with its real callee sycc_to_rgb() (also from color.c, VERBATIM),
 * and the real opj_image_t / opj_image_comp_t struct layouts (verbatim
 * field order/types from src/lib/openjp2/openjpeg.h).
 *
 * Root cause: sycc420_to_rgb() walks the Cb/Cr (chroma) component buffers
 * using loop bounds derived ONLY from the Y (luma) component's w/h
 * (img->comps[0].w / .h), never checking that img->comps[1]/[2].data are
 * actually large enough to hold ceil(w/2)*ceil(h/2) samples. A caller that
 * hands it a Y plane whose w/h implies a bigger 4:2:0 chroma plane than what
 * was actually allocated for comps[1]/[2] causes an out-of-bounds heap READ
 * on cb/cr inside sycc_to_rgb(offset, upb, *y, *cb, *cr, ...).
 *
 * argv[1] is read into a HEAP buffer (malloc) and used to derive:
 *   - maxw, maxh   : the Y (luma) component's declared width/height
 *   - cb_w, cb_h   : the ACTUAL allocated width/height of the Cb/Cr planes
 *   - prec         : the component bit precision (drives offset/upb)
 * A "safe" input sizes cb_w*cb_h correctly (>= ceil(maxw/2)*ceil(maxh/2));
 * a "triggering" input undersizes it, reproducing the exact same
 * heap-buffer-overflow READ as the real decoder-driven PoC.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

/* ---- real type aliases, verbatim from src/lib/openjp2/openjpeg.h ---- */
typedef int32_t  OPJ_INT32;
typedef uint32_t OPJ_UINT32;
typedef unsigned char OPJ_BYTE;
typedef unsigned short OPJ_UINT16;

/* verbatim (trimmed to the members sycc420_to_rgb touches; enum values match) */
typedef enum COLOR_SPACE {
	OPJ_CLRSPC_UNKNOWN = -1,
	OPJ_CLRSPC_UNSPECIFIED = 0,
	OPJ_CLRSPC_SRGB = 1,
	OPJ_CLRSPC_GRAY = 2,
	OPJ_CLRSPC_SYCC = 3,
	OPJ_CLRSPC_EYCC = 4,
	OPJ_CLRSPC_CMYK = 5
} OPJ_COLOR_SPACE;

/* verbatim field order/types from openjpeg.h:629 */
typedef struct opj_image_comp {
	OPJ_UINT32 dx;
	OPJ_UINT32 dy;
	OPJ_UINT32 w;
	OPJ_UINT32 h;
	OPJ_UINT32 x0;
	OPJ_UINT32 y0;
	OPJ_UINT32 prec;
	OPJ_UINT32 bpp;
	OPJ_UINT32 sgnd;
	OPJ_UINT32 resno_decoded;
	OPJ_UINT32 factor;
	OPJ_INT32 *data;
	OPJ_UINT16 alpha;
} opj_image_comp_t;

/* verbatim field order/types from openjpeg.h:661 */
typedef struct opj_image {
	OPJ_UINT32 x0;
	OPJ_UINT32 y0;
	OPJ_UINT32 x1;
	OPJ_UINT32 y1;
	OPJ_UINT32 numcomps;
	OPJ_COLOR_SPACE color_space;
	opj_image_comp_t *comps;
	OPJ_BYTE *icc_profile_buf;
	OPJ_UINT32 icc_profile_len;
} opj_image_t;

/* ---- real callee, VERBATIM from src/bin/common/color.c (~line 74) ---- */
static void sycc_to_rgb(int offset, int upb, int y, int cb, int cr,
	int *out_r, int *out_g, int *out_b)
{
	int r, g, b;

	cb -= offset; cr -= offset;
	r = y + (int)(1.402 * (float)cr);
	if(r < 0) r = 0; else if(r > upb) r = upb; *out_r = r;

	g = y - (int)(0.344 * (float)cb + 0.714 * (float)cr);
	if(g < 0) g = 0; else if(g > upb) g = upb; *out_g = g;

	b = y + (int)(1.772 * (float)cb);
	if(b < 0) b = 0; else if(b > upb) b = upb; *out_b = b;
}

/* ---- TARGET FUNCTION, VERBATIM from target/original_function.c ---- */
static void sycc420_to_rgb(opj_image_t *img)
{
	int *d0, *d1, *d2, *r, *g, *b, *nr, *ng, *nb;
	const int *y, *cb, *cr, *ny;
	unsigned int maxw, maxh, max;
	int offset, upb;
	unsigned int i, j;

	upb = (int)img->comps[0].prec;
	offset = 1<<(upb - 1); upb = (1<<upb)-1;

	maxw = (unsigned int)img->comps[0].w; maxh = (unsigned int)img->comps[0].h;
	max = maxw * maxh;

	y = img->comps[0].data;
	cb = img->comps[1].data;
	cr = img->comps[2].data;

	d0 = r = (int*)malloc(sizeof(int) * (size_t)max);
	d1 = g = (int*)malloc(sizeof(int) * (size_t)max);
	d2 = b = (int*)malloc(sizeof(int) * (size_t)max);

	if(r == NULL || g == NULL || b == NULL) goto fails;

	for(i=0U; i < (maxh & ~(unsigned int)1U); i += 2U)
	{
		ny = y + maxw;
		nr = r + maxw; ng = g + maxw; nb = b + maxw;

		for(j=0; j < (maxw & ~(unsigned int)1U); j += 2U)
		{
			sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);
			++y; ++r; ++g; ++b;
			sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);
			++y; ++r; ++g; ++b;

			sycc_to_rgb(offset, upb, *ny, *cb, *cr, nr, ng, nb);
			++ny; ++nr; ++ng; ++nb;
			sycc_to_rgb(offset, upb, *ny, *cb, *cr, nr, ng, nb);
			++ny; ++nr; ++ng; ++nb; ++cb; ++cr;
		}
		if(j < maxw)
		{
			sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);
			++y; ++r; ++g; ++b;

			sycc_to_rgb(offset, upb, *ny, *cb, *cr, nr, ng, nb);
			++ny; ++nr; ++ng; ++nb; ++cb; ++cr;
		}
		y += maxw; r += maxw; g += maxw; b += maxw;
	}
	if(i < maxh)
	{
		for(j=0U; j < (maxw & ~(unsigned int)1U); j += 2U)
		{
			sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);

			++y; ++r; ++g; ++b;

			sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);

			++y; ++r; ++g; ++b; ++cb; ++cr;
		}
		if(j < maxw)
		{
			sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);
		}
	}

	free(img->comps[0].data); img->comps[0].data = d0;
	free(img->comps[1].data); img->comps[1].data = d1;
	free(img->comps[2].data); img->comps[2].data = d2;

#if defined(USE_JPWL) || defined(USE_MJ2)
	img->comps[1].w = maxw; img->comps[1].h = maxh;
	img->comps[2].w = maxw; img->comps[2].h = maxh;
#else
	img->comps[1].w = (OPJ_UINT32)maxw; img->comps[1].h = (OPJ_UINT32)maxh;
	img->comps[2].w = (OPJ_UINT32)maxw; img->comps[2].h = (OPJ_UINT32)maxh;
#endif
	img->comps[1].dx = img->comps[0].dx;
	img->comps[2].dx = img->comps[0].dx;
	img->comps[1].dy = img->comps[0].dy;
	img->comps[2].dy = img->comps[0].dy;
	return;

fails:
	if(r) free(r);
	if(g) free(g);
	if(b) free(b);

}

/* ---------------------------------------------------------------------
 * main(): parse a 20-byte little-endian header out of a HEAP-allocated
 * copy of argv[1], build a real opj_image_t/opj_image_comp_t[3] exactly
 * as color_sycc_to_rgb()'s caller would (dx/dy=1 for luma, 2/2 for
 * 4:2:0 chroma), and call sycc420_to_rgb() ONCE.
 *
 * header (all OPJ_UINT32 / uint32_t, little-endian):
 *   [0]  maxw   - luma (Y) component width
 *   [4]  maxh   - luma (Y) component height
 *   [8]  cb_w   - ACTUAL allocated width of the Cb/Cr planes
 *   [12] cb_h   - ACTUAL allocated height of the Cb/Cr planes
 *   [16] prec   - component bit precision (2..24)
 * remaining bytes seed the pixel payload (attacker-controlled, heap-resident).
 * ------------------------------------------------------------------- */
static uint32_t rd_u32le(const unsigned char *p)
{
	return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

int main(int argc, char **argv)
{
	if (argc < 2) return 1;
	FILE *f = fopen(argv[1], "rb");
	if (!f) return 1;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	long fsz = ftell(f);
	if (fsz < 20) { fclose(f); return 1; }
	fseek(f, 0, SEEK_SET);

	/* attacker data lives on the HEAP, never stack/global */
	unsigned char *buf = (unsigned char *)malloc((size_t)fsz);
	if (!buf) { fclose(f); return 1; }
	size_t rd = fread(buf, 1, (size_t)fsz, f);
	fclose(f);
	if (rd != (size_t)fsz) { free(buf); return 1; }

	uint32_t maxw = rd_u32le(buf + 0);
	uint32_t maxh = rd_u32le(buf + 4);
	uint32_t cb_w = rd_u32le(buf + 8);
	uint32_t cb_h = rd_u32le(buf + 12);
	uint32_t prec = rd_u32le(buf + 16);

	/* clamp the luma plane to a small, always-allocatable range */
	maxw = (maxw % 40) + 2;
	maxh = (maxh % 40) + 2;
	if (prec < 2) prec = 2; if (prec > 24) prec = ((prec % 23) + 2);
	/* clamp the DECLARED chroma plane dims independently -- this is the
	 * attacker-controlled quantity that decides trigger vs. safe */
	cb_w = cb_w % 64;
	cb_h = cb_h % 64;

	opj_image_t img;
	memset(&img, 0, sizeof(img));
	opj_image_comp_t comps[3];
	memset(comps, 0, sizeof(comps));
	img.numcomps = 3;
	img.comps = comps;
	img.color_space = OPJ_CLRSPC_SYCC;
	img.x0 = 0; img.y0 = 0; img.x1 = maxw; img.y1 = maxh;

	comps[0].dx = 1; comps[0].dy = 1;
	comps[0].w = maxw; comps[0].h = maxh; comps[0].prec = prec; comps[0].sgnd = 0;
	size_t y_n = (size_t)maxw * (size_t)maxh;
	comps[0].data = (OPJ_INT32 *)malloc(sizeof(OPJ_INT32) * y_n);
	if (!comps[0].data) { free(buf); return 1; }
	for (size_t k = 0; k < y_n; k++)
		comps[0].data[k] = (OPJ_INT32)buf[(k + 20) % (size_t)fsz];

	/* real 4:2:0 sub-sample factors, as color_sycc_to_rgb() requires
	 * before it will dispatch to sycc420_to_rgb() at all */
	comps[1].dx = 2; comps[1].dy = 2;
	comps[2].dx = 2; comps[2].dy = 2;
	comps[1].w = cb_w; comps[1].h = cb_h; comps[1].prec = prec; comps[1].sgnd = 0;
	comps[2].w = cb_w; comps[2].h = cb_h; comps[2].prec = prec; comps[2].sgnd = 0;

	size_t chroma_n = (size_t)cb_w * (size_t)cb_h;
	if (chroma_n == 0) chroma_n = 1; /* keep malloc() well-defined; the loop
	                                    still walks past it if maxw/maxh imply
	                                    a non-empty chroma plane */
	comps[1].data = (OPJ_INT32 *)malloc(sizeof(OPJ_INT32) * chroma_n);
	comps[2].data = (OPJ_INT32 *)malloc(sizeof(OPJ_INT32) * chroma_n);
	if (!comps[1].data || !comps[2].data) {
		free(buf); free(comps[0].data);
		free(comps[1].data); free(comps[2].data);
		return 1;
	}
	for (size_t k = 0; k < chroma_n; k++) {
		comps[1].data[k] = (OPJ_INT32)buf[k % (size_t)fsz];
		comps[2].data[k] = (OPJ_INT32)buf[(k + 7) % (size_t)fsz];
	}

	sycc420_to_rgb(&img); /* the single direct call under test */

	/* only reached if sycc420_to_rgb() did NOT crash: on success it already
	 * freed the original comps[0..2].data and replaced them with its own
	 * r/g/b buffers, so free those once here. */
	free(img.comps[0].data);
	free(img.comps[1].data);
	free(img.comps[2].data);
	free(buf);
	return 0;
}
