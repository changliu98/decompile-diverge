/* Direct-call crash harness for openjpeg imagetopnm
 * (CVE-2016-9573, CWE-125, src/bin/jp2/convert.c).
 *
 * imagetopnm() writes a PNM/PAM file from a decoded opj_image_t. When the
 * image is 2-component GRAYA (or dx/dy/prec-matched RGBA), it takes its
 * OUTPUT loop bound `wr*hr` from comps[0]'s (the gray/red component's) OWN
 * dimensions:
 *
 *     wr = (int)image->comps[0].w; hr = (int)image->comps[0].h;
 *     ...
 *     for(i = 0; i < wr * hr; ++i)
 *     {
 *         v = *red++;                      // comps[0].data -- always sized wr*hr
 *         ...
 *         if(has_alpha)
 *         {
 *             v = *alpha++;                // comps[ncomp-1].data  <- convert.c:1885
 *             ...
 *         }
 *     }
 *
 * but `alpha = image->comps[ncomp - 1].data` (the LAST/alpha component) is
 * an INDEPENDENT heap allocation, sized by the real decoder from THAT
 * component's own (possibly forged-smaller, or legitimately
 * dx/dy-subsampled) tile dimensions -- there is no check anywhere in this
 * function that the alpha component actually holds >= wr*hr elements.
 * Worse, for the ncomp==2 (GRAYA) case the gate that lets us into this
 * branch:
 *
 *     if ((force_split == 0) &&
 *         (ncomp == 2 || (ncomp > 2 && comps[0..2] dx/dy/prec all match)))
 *
 * does not compare comps[0] against comps[1] (the alpha component) AT ALL
 * when ncomp==2 -- so a 2-component (gray+alpha) image whose alpha
 * component is smaller than the gray component sails straight through with
 * zero validation. If alpha's allocation is smaller than wr*hr, the loop
 * walks straight past the end of that allocation -> heap-buffer-overflow
 * READ, matching baseline.summary "AddressSanitizer: heap-buffer-overflow
 * .../convert.c:1885:21 in imagetopnm" and baseline.cwe CWE-125 exactly.
 *
 * main() mimics the real caller (opj_decompress() in
 * src/bin/jp2/opj_decompress.c, which calls imagetopnm(image, outfile,
 * force_split) directly on the opj_image_t produced by opj_decode()): it
 * reads the whole input file into a malloc'd heap buffer, uses those bytes
 * to derive comps[0]'s (gray) dimensions/precision and the alpha
 * component's OWN, independently-sized allocation (mirroring how a real --
 * or forged -- codestream can hand the decoder a too-small alpha tile),
 * allocates comps[0].data to the full wr*hr (it is the component the loop
 * bound is derived FROM, so it is never short) and comps[1].data
 * (alpha) to that attacker-influenced cell count, and calls
 * imagetopnm(&image, outfile, 0) once, directly.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- minimal but faithful type/struct defs the function needs ---- */
/* (real names verbatim from src/lib/openjp2/openjpeg.h) */

typedef int OPJ_BOOL;
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

/* opj_version() is a real callee (only used to format a comment string in
 * the PNM/PAM header) -- stub with the real signature, content irrelevant
 * to the bug. */
const char *opj_version(void)
{
    return "2.1.1";
}

/* ---- verbatim target function (target/original_function.c), unchanged ---- */
int imagetopnm(opj_image_t * image, const char *outfile, int force_split)
{
    int *red, *green, *blue, *alpha;
    int wr, hr, max;
    int i;
    unsigned int compno, ncomp;
    int adjustR, adjustG, adjustB, adjustA;
    int fails, two, want_gray, has_alpha, triple;
    int prec, v;
    FILE *fdest = NULL;
    const char *tmp = outfile;
    char *destname;

    alpha = NULL;

    if((prec = (int)image->comps[0].prec) > 16)
    {
        fprintf(stderr,"%s:%d:imagetopnm\n\tprecision %d is larger than 16"
                "\n\t: refused.\n",__FILE__,__LINE__,prec);
        return 1;
    }
    two = has_alpha = 0; fails = 1;
    ncomp = image->numcomps;

    while (*tmp) ++tmp; tmp -= 2;
    want_gray = (*tmp == 'g' || *tmp == 'G');
    ncomp = image->numcomps;

    if(want_gray) ncomp = 1;

    if ((force_split == 0) &&
				(ncomp == 2 /* GRAYA */
            || (ncomp > 2 /* RGB, RGBA */
                && image->comps[0].dx == image->comps[1].dx
                && image->comps[1].dx == image->comps[2].dx
                && image->comps[0].dy == image->comps[1].dy
                && image->comps[1].dy == image->comps[2].dy
                && image->comps[0].prec == image->comps[1].prec
                && image->comps[1].prec == image->comps[2].prec
                )))
		{
        fdest = fopen(outfile, "wb");

        if (!fdest)
        {
            fprintf(stderr, "ERROR -> failed to open %s for writing\n", outfile);
            return fails;
        }
        two = (prec > 8);
        triple = (ncomp > 2);
        wr = (int)image->comps[0].w; hr = (int)image->comps[0].h;
        max = (1<<prec) - 1; has_alpha = (ncomp == 4 || ncomp == 2);

        red = image->comps[0].data;

        if(triple)
        {
            green = image->comps[1].data;
            blue = image->comps[2].data;
        }
        else green = blue = NULL;

        if(has_alpha)
        {
            const char *tt = (triple?"RGB_ALPHA":"GRAYSCALE_ALPHA");

            fprintf(fdest, "P7\n# OpenJPEG-%s\nWIDTH %d\nHEIGHT %d\nDEPTH %u\n"
                    "MAXVAL %d\nTUPLTYPE %s\nENDHDR\n", opj_version(),
                    wr, hr, ncomp, max, tt);
            alpha = image->comps[ncomp - 1].data;
            adjustA = (image->comps[ncomp - 1].sgnd ?
                        1 << (image->comps[ncomp - 1].prec - 1) : 0);
        }
        else
        {
            fprintf(fdest, "P6\n# OpenJPEG-%s\n%d %d\n%d\n",
                    opj_version(), wr, hr, max);
            adjustA = 0;
        }
        adjustR = (image->comps[0].sgnd ? 1 << (image->comps[0].prec - 1) : 0);

        if(triple)
        {
            adjustG = (image->comps[1].sgnd ? 1 << (image->comps[1].prec - 1) : 0);
            adjustB = (image->comps[2].sgnd ? 1 << (image->comps[2].prec - 1) : 0);
        }
        else adjustG = adjustB = 0;

        for(i = 0; i < wr * hr; ++i)
        {
            if(two)
            {
                v = *red + adjustR; ++red;
                if(v > 65535) v = 65535; else if(v < 0) v = 0;

                /* netpbm: */
                fprintf(fdest, "%c%c",(unsigned char)(v>>8), (unsigned char)v);

                if(triple)
                {
                    v = *green + adjustG; ++green;
                    if(v > 65535) v = 65535; else if(v < 0) v = 0;

                    /* netpbm: */
                    fprintf(fdest, "%c%c",(unsigned char)(v>>8), (unsigned char)v);

                    v =  *blue + adjustB; ++blue;
                    if(v > 65535) v = 65535; else if(v < 0) v = 0;

                    /* netpbm: */
                    fprintf(fdest, "%c%c",(unsigned char)(v>>8), (unsigned char)v);

                }/* if(triple) */

                if(has_alpha)
                {
                    v = *alpha + adjustA; ++alpha;
                    if(v > 65535) v = 65535; else if(v < 0) v = 0;

                    /* netpbm: */
                    fprintf(fdest, "%c%c",(unsigned char)(v>>8), (unsigned char)v);
                }
                continue;

            }	/* if(two) */

            /* prec <= 8: */
            v = *red++;
            if(v > 255) v = 255; else if(v < 0) v = 0;

            fprintf(fdest, "%c", (unsigned char)v);
            if(triple)
            {
                v = *green++;
                if(v > 255) v = 255; else if(v < 0) v = 0;

                fprintf(fdest, "%c", (unsigned char)v);
                v = *blue++;
                if(v > 255) v = 255; else if(v < 0) v = 0;

                fprintf(fdest, "%c", (unsigned char)v);
						}
            if(has_alpha)
            {
                v = *alpha++;
                if(v > 255) v = 255; else if(v < 0) v = 0;

                fprintf(fdest, "%c", (unsigned char)v);
            }
        }	/* for(i */

        fclose(fdest); return 0;
    }

    /* YUV or MONO: */

    if (image->numcomps > ncomp)
    {
        fprintf(stderr,"WARNING -> [PGM file] Only the first component\n");
        fprintf(stderr,"           is written to the file\n");
    }
    destname = (char*)malloc(strlen(outfile) + 8);
    if(destname == NULL){
        fprintf(stderr, "imagetopnm: memory out\n");
        return 1;
    }
    for (compno = 0; compno < ncomp; compno++)
    {
        if (ncomp > 1)
        {
            /*sprintf(destname, "%d.%s", compno, outfile);*/
            const size_t olen = strlen(outfile);
            const size_t dotpos = olen - 4;

            strncpy(destname, outfile, dotpos);
            sprintf(destname+dotpos, "_%u.pgm", compno);
        }
        else
            sprintf(destname, "%s", outfile);

        fdest = fopen(destname, "wb");
        if (!fdest)
        {
            fprintf(stderr, "ERROR -> failed to open %s for writing\n", destname);
            free(destname);
            return 1;
        }
        wr = (int)image->comps[compno].w; hr = (int)image->comps[compno].h;
        prec = (int)image->comps[compno].prec;
        max = (1<<prec) - 1;

        fprintf(fdest, "P5\n#OpenJPEG-%s\n%d %d\n%d\n",
                opj_version(), wr, hr, max);

        red = image->comps[compno].data;
        adjustR =
                (image->comps[compno].sgnd ? 1 << (image->comps[compno].prec - 1) : 0);

        if(prec > 8)
        {
            for (i = 0; i < wr * hr; i++)
            {
                v = *red + adjustR; ++red;
                if(v > 65535) v = 65535; else if(v < 0) v = 0;

                /* netpbm: */
                fprintf(fdest, "%c%c",(unsigned char)(v>>8), (unsigned char)v);

                if(has_alpha)
                {
                    v = *alpha++;
                    if(v > 65535) v = 65535; else if(v < 0) v = 0;

                    /* netpbm: */
                    fprintf(fdest, "%c%c",(unsigned char)(v>>8), (unsigned char)v);
                }
            }/* for(i */
        }
        else /* prec <= 8 */
        {
            for(i = 0; i < wr * hr; ++i)
            {
                v = *red + adjustR; ++red;
                if(v > 255) v = 255; else if(v < 0) v = 0;

                fprintf(fdest, "%c", (unsigned char)v);
            }
        }
        fclose(fdest);
    } /* for (compno */
    free(destname);

    return 0;
}/* imagetopnm() */
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

	/* Field layout (16 bytes, little-endian, missing bytes read as 0):
	 *   off 0     : prec0  (u8, actual = (raw % 8) + 1, always <= 8 so the
	 *                        target's "prec <= 8" / has_alpha branch --
	 *                        the exact one containing convert.c:1885 --
	 *                        is always the one exercised)
	 *   off 4..7  : w0     (u32, clamped 1..64)  -- comps[0].w (gray)
	 *   off 8..11 : h0     (u32, clamped 1..64)  -- comps[0].h (gray)
	 *   off 12..15: alloc1 (u32, capped 8192)    -- # OPJ_INT32 cells
	 *                        actually malloc'd for comps[1].data (alpha)
	 *
	 * comps[0].w/h (hence wr*hr, the OUTPUT loop bound) are always
	 * honored by comps[0]'s OWN allocation (sized exactly wr*hr, never
	 * short) -- the real bug is that the alpha component (comps[1], the
	 * last component for our fixed ncomp==2/GRAYA image) is independently
	 * sized, so alloc1 < wr*hr reproduces the exact over-read the target
	 * function has no guard against for the GRAYA case.
	 */
	unsigned int prec0 = (rd_u8(raw, rlen, 0) % 8) + 1;
	unsigned int w0 = (rd_u32(raw, rlen, 4) % 64) + 1;
	unsigned int h0 = (rd_u32(raw, rlen, 8) % 64) + 1;
	unsigned int alloc1 = rd_u32(raw, rlen, 12); if (alloc1 > 8192) alloc1 = 8192;

	unsigned int wrhr = w0 * h0;

	/* Build the opj_image_t the way the real decoder hands it to
	 * imagetopnm() (see opj_decompress() in src/bin/jp2/opj_decompress.c,
	 * which calls imagetopnm(image, outfile, force_split) directly on the
	 * decoded opj_image_t): numcomps == 2 (a real GRAYA image -- gray +
	 * alpha, no forced split), comps array itself heap-allocated (mirrors
	 * opj_image_create()), each comps[i].data a SEPARATE heap allocation
	 * whose element count is that component's OWN, independently-derived
	 * size. */
	opj_image_t image;
	memset(&image, 0, sizeof(image));
	image.numcomps = 2;
	image.color_space = OPJ_CLRSPC_GRAY;

	opj_image_comp_t *comps = (opj_image_comp_t *)calloc(image.numcomps, sizeof(opj_image_comp_t));
	if (!comps) { perror("calloc"); free(raw); return 1; }
	image.comps = comps;

	comps[0].dx = 1; comps[0].dy = 1;
	comps[0].w = w0; comps[0].h = h0; comps[0].prec = prec0; comps[0].sgnd = 0;
	comps[1].dx = 1; comps[1].dy = 1;
	/* comps[1].w/h are what a real (possibly dx/dy-subsampled, or forged)
	 * alpha tile WOULD report -- imagetopnm() never reads them for the
	 * GRAYA loop bound, only image->comps[0].w/h, so they are purely
	 * informational here; the ACTUAL vulnerability is comps[1].data's
	 * independently-sized allocation below. */
	comps[1].w = w0; comps[1].h = h0; comps[1].prec = prec0; comps[1].sgnd = 0;

	/* comps[0] (gray) is always allocated to the FULL loop bound -- it is
	 * the component wr*hr is derived FROM, so it is never short. */
	comps[0].data = (OPJ_INT32 *)calloc(wrhr, sizeof(OPJ_INT32));
	/* comps[1] (alpha) is allocated to its OWN (attacker-influenced,
	 * possibly-too-small) element count -- the actual vulnerability. */
	comps[1].data = (OPJ_INT32 *)calloc(alloc1 > 0 ? alloc1 : 1, sizeof(OPJ_INT32));
	if (!comps[0].data || !comps[1].data) {
		perror("calloc");
		free(comps[0].data); free(comps[1].data);
		free(comps); free(raw);
		return 1;
	}
	/* alloc1==0 means a genuine 0-element heap allocation (glibc/ASAN
	 * hand back a valid, zero-usable-size pointer) -- any read at all is
	 * then an immediate heap-buffer-overflow, which is a legitimate
	 * (extreme) instance of the same bug, not a harness artifact. */

	/* outfile: fixed, NOT attacker-controlled (imagetopnm's own
	 * want_gray sniff looks at outfile[len-2]; using a fixed ".pnm" name
	 * keeps want_gray false so ncomp stays == image->numcomps == 2, the
	 * real GRAYA path). force_split == 0, matching the real
	 * opj_decompress default (no -split flag). */
	const char *outfile = "/tmp/vb_dc_imagetopnm_out.pnm";

	int rc = imagetopnm(&image, outfile, 0);

	/* Only reached on the safe path (no crash). */
	free(comps[0].data);
	free(comps[1].data);
	free(comps);
	free(raw);
	remove(outfile);

	printf("imagetopnm done, rc=%d w0=%u h0=%u wrhr=%u alloc1=%u\n",
	       rc, w0, h0, wrhr, alloc1);
	return 0;
}
