/*
 * cve_barebone direct-call harness for FreeRDP gdi_Bitmap_Decompress
 * (CVE-2018-8787, fixed by 09b9d4f1994a674c4ec85b4947aa656eda1aed8a).
 *
 * Bug: gdi_Bitmap_Decompress (libfreerdp/gdi/graphics.c) computed
 *      bitmap->length = DstWidth * DstHeight * GetBytesPerPixel(bitmap->format);
 *   entirely in UINT32 arithmetic, with NO overflow check, before allocating
 *   bitmap->data = _aligned_malloc(bitmap->length, 16).  DstWidth/DstHeight are
 *   attacker-controlled bitmap dimensions from the RDP wire format, so a pair of
 *   dimensions whose true (unwrapped) product is >= 2^32 makes bitmap->length wrap
 *   to a small value while the *decoder* that immediately follows still fills a
 *   buffer sized DstWidth x DstHeight pixels -> heap buffer overflow (CWE-787,
 *   write). The fix (not present in this vulnerable snapshot) adds an explicit
 *   overflow guard before the multiplication.
 *
 * Isolation strategy: gdi_Bitmap_Decompress itself is reproduced BYTE-FOR-BYTE
 * from data_cve/cve_a444d3fc/target/original_function.c. Every type it touches
 * (rdpBitmap/rdpGdi/rdpContext/rdpCodecs/gdiPalette) is reproduced with its REAL
 * field names, trimmed to just the fields this function reads/writes (the rest of
 * the real structs carry GUI/codec-plumbing state this isolated test never
 * touches). GetBitsPerPixel/GetBytesPerPixel/PIXEL_FORMAT_BGRA32 are copied
 * verbatim from include/freerdp/codec/color.h (they are `static INLINE`, i.e.
 * pure header code with no link-time dependency), as is gdi_get_pixel_format's
 * body (libfreerdp/gdi/gdi.c, logging call dropped -- unreachable here).
 *
 * interleaved_decompress is the callee that actually performs the fatal write.
 * The real implementation (libfreerdp/codec/interleaved.c) is a ~530-line RLE
 * bitstream decoder with further internal helpers -- its *exact decode algorithm*
 * is incidental to this vulnerability: ANY correct implementation must, given
 * (nDstWidth, nDstHeight, DstFormat), write nDstWidth*nDstHeight pixels into
 * pDstData starting at (nXDst, nYDst). That write FOOTPRINT -- not the RLE
 * bitstream grammar -- is what the missing overflow check in gdi_Bitmap_Decompress
 * fails to bound, so a minimal stub reproducing exactly that footprint (real
 * signature, real per-pixel addressing arithmetic) faithfully reproduces the
 * memory-safety bug without inlining an unrelated bitstream codec. planar_decompress
 * and freerdp_image_copy are never reached by any crafted input here (compressed
 * is always TRUE and bpp is always < 32, so gdi_Bitmap_Decompress's own branching
 * always selects interleaved_decompress) -- they are provided as trivial linkage
 * stubs purely so the verbatim function body compiles.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- winpr primitive types (Linux/non-Windows sizes) ---- */
typedef int32_t  INT32;
typedef uint32_t UINT32;
typedef uint16_t UINT16;
typedef int32_t  BOOL;
typedef unsigned char BYTE;
typedef uint32_t DWORD;
#define TRUE  1
#define FALSE 0

/* ---- include/freerdp/codec/color.h (verbatim macros/inline fns needed) ---- */
#define FREERDP_PIXEL_FORMAT_TYPE_BGRA  4
#define FREERDP_PIXEL_FORMAT(_bpp, _type, _a, _r, _g, _b) \
	((_bpp << 24) | (_type << 16) | (_a << 12) | (_r << 8) | (_g << 4) | (_b))
#define PIXEL_FORMAT_BGRA32  FREERDP_PIXEL_FORMAT(32, FREERDP_PIXEL_FORMAT_TYPE_BGRA, 8, 8, 8, 8)
#define FREERDP_FLIP_VERTICAL 1

static inline UINT32 GetBitsPerPixel(UINT32 format)
{
	return (((format) >> 24) & 0x3F);
}

static inline UINT32 GetBytesPerPixel(UINT32 format)
{
	return (GetBitsPerPixel(format) + 7) / 8;
}

struct gdi_palette
{
	UINT32 format;
	UINT32 palette[256];
};
typedef struct gdi_palette gdiPalette;

/* ---- minimal real-named structs (only the fields gdi_Bitmap_Decompress touches) ---- */
typedef struct rdp_bitmap rdpBitmap;
struct rdp_bitmap
{
	UINT32 format;
	UINT32 length;
	BYTE*  data;
	BOOL   compressed;
};

typedef struct _BITMAP_INTERLEAVED_CONTEXT BITMAP_INTERLEAVED_CONTEXT; /* opaque, real name */
typedef struct _BITMAP_PLANAR_CONTEXT BITMAP_PLANAR_CONTEXT;           /* opaque, real name */

typedef struct rdp_codecs rdpCodecs;
struct rdp_codecs
{
	BITMAP_INTERLEAVED_CONTEXT* interleaved;
	BITMAP_PLANAR_CONTEXT*      planar;
};

typedef struct rdp_gdi rdpGdi;
struct rdp_gdi
{
	UINT32    dstFormat;
	gdiPalette palette;
};

typedef struct rdp_context rdpContext;
struct rdp_context
{
	rdpGdi*    gdi;
	rdpCodecs* codecs;
};

/* ---- winpr/crt.h: _aligned_malloc (real name, minimal portable body) ---- */
static void* _aligned_malloc(size_t size, size_t alignment)
{
	void* p = NULL;
	if (posix_memalign(&p, alignment, size) != 0)
		return NULL;
	return p;
}

/* ---- libfreerdp/gdi/gdi.c: gdi_get_pixel_format (verbatim body, logging dropped) ---- */
static UINT32 gdi_get_pixel_format(UINT32 bitsPerPixel)
{
	UINT32 format;

	switch (bitsPerPixel)
	{
		case 32:
			format = PIXEL_FORMAT_BGRA32;
			break;

		default:
			/* unreachable for the fixed bpp=16 used by every crafted input here */
			format = 0;
			break;
	}

	return format;
}

/* ---- libfreerdp/codec/interleaved.h prototype (real signature) ---- */
static BOOL interleaved_decompress(BITMAP_INTERLEAVED_CONTEXT* interleaved,
                                   const BYTE* pSrcData, UINT32 SrcSize,
                                   UINT32 nSrcWidth, UINT32 nSrcHeight,
                                   UINT32 bpp,
                                   BYTE* pDstData, UINT32 DstFormat,
                                   UINT32 nDstStep, UINT32 nXDst, UINT32 nYDst,
                                   UINT32 nDstWidth, UINT32 nDstHeight,
                                   const gdiPalette* palette)
{
	(void)interleaved; (void)pSrcData; (void)SrcSize; (void)nSrcWidth; (void)nSrcHeight;
	(void)bpp; (void)palette;
	/* Faithful write-footprint stub -- see file header comment. */
	const UINT32 bypp = GetBytesPerPixel(DstFormat);
	const UINT32 step = nDstStep ? nDstStep : nDstWidth * bypp;
	UINT32 x, y;
	for (y = 0; y < nDstHeight; y++)
	{
		for (x = 0; x < nDstWidth; x++)
		{
			BYTE* px = pDstData + (size_t)(nYDst + y) * step + (size_t)(nXDst + x) * bypp;
			UINT32 c;
			for (c = 0; c < bypp; c++)
				px[c] = (BYTE)0x41;
		}
	}
	return TRUE;
}

/* ---- libfreerdp/codec/planar.h prototype -- never exercised (bpp is always < 32
 * for every crafted input, so gdi_Bitmap_Decompress's own `if (bpp < 32)` always
 * selects interleaved_decompress above); trivial linkage-only stub. ---- */
static BOOL planar_decompress(BITMAP_PLANAR_CONTEXT* planar,
                              const BYTE* pSrcData, UINT32 SrcSize,
                              UINT32 nSrcWidth, UINT32 nSrcHeight,
                              BYTE* pDstData, UINT32 DstFormat,
                              UINT32 nDstStep, UINT32 nXDst, UINT32 nYDst,
                              UINT32 nDstWidth, UINT32 nDstHeight, BOOL vFlip)
{
	(void)planar; (void)pSrcData; (void)SrcSize; (void)nSrcWidth; (void)nSrcHeight;
	(void)pDstData; (void)DstFormat; (void)nDstStep; (void)nXDst; (void)nYDst;
	(void)nDstWidth; (void)nDstHeight; (void)vFlip;
	return TRUE;
}

/* ---- include/freerdp/codec/color.h prototype -- never exercised (`compressed`
 * is always TRUE for every crafted input, so gdi_Bitmap_Decompress's own
 * `if (compressed)` always takes the interleaved/planar branch above); trivial
 * linkage-only stub. ---- */
static BOOL freerdp_image_copy(BYTE* pDstData, DWORD DstFormat,
                               UINT32 nDstStep, UINT32 nXDst, UINT32 nYDst,
                               UINT32 nWidth, UINT32 nHeight,
                               const BYTE* pSrcData, DWORD SrcFormat,
                               UINT32 nSrcStep, UINT32 nXSrc, UINT32 nYSrc,
                               const gdiPalette* palette, UINT32 flags)
{
	(void)pDstData; (void)DstFormat; (void)nDstStep; (void)nXDst; (void)nYDst;
	(void)nWidth; (void)nHeight; (void)pSrcData; (void)SrcFormat; (void)nSrcStep;
	(void)nXSrc; (void)nYSrc; (void)palette; (void)flags;
	return TRUE;
}

/* =====================================================================
 * data_cve/cve_a444d3fc/target/original_function.c -- copied VERBATIM.
 * ===================================================================== */
static BOOL gdi_Bitmap_Decompress(rdpContext* context, rdpBitmap* bitmap,
                                  const BYTE* pSrcData, UINT32 DstWidth, UINT32 DstHeight,
                                  UINT32 bpp, UINT32 length, BOOL compressed,
                                  UINT32 codecId)
{
	UINT32 SrcSize = length;
	rdpGdi* gdi = context->gdi;
	bitmap->compressed = FALSE;
	bitmap->format = gdi->dstFormat;
	bitmap->length = DstWidth * DstHeight * GetBytesPerPixel(bitmap->format);
	bitmap->data = (BYTE*) _aligned_malloc(bitmap->length, 16);

	if (!bitmap->data)
		return FALSE;

	if (compressed)
	{
		if (bpp < 32)
		{
			if (!interleaved_decompress(context->codecs->interleaved,
			                            pSrcData, SrcSize,
			                            DstWidth, DstHeight,
			                            bpp,
			                            bitmap->data, bitmap->format,
			                            0, 0, 0, DstWidth, DstHeight,
			                            &gdi->palette))
				return FALSE;
		}
		else
		{
			if (!planar_decompress(context->codecs->planar, pSrcData, SrcSize,
			                       DstWidth, DstHeight,
			                       bitmap->data, bitmap->format, 0, 0, 0,
			                       DstWidth, DstHeight, TRUE))
				return FALSE;
		}
	}
	else
	{
		const UINT32 SrcFormat = gdi_get_pixel_format(bpp);
		const size_t sbpp = GetBytesPerPixel(SrcFormat);
		const size_t dbpp = GetBytesPerPixel(bitmap->format);

		if ((sbpp == 0) || (dbpp == 0))
			return FALSE;
		else
		{
			const size_t dstSize = SrcSize * dbpp / sbpp;

			if (dstSize  < bitmap->length)
				return FALSE;
		}

		if (!freerdp_image_copy(bitmap->data, bitmap->format, 0, 0, 0,
		                        DstWidth, DstHeight, pSrcData, SrcFormat,
		                        0, 0, 0, &gdi->palette, FREERDP_FLIP_VERTICAL))
			return FALSE;
	}

	return TRUE;
}

/* ===================== driver ===================== */
static UINT32 rd32(const unsigned char* p)
{
	return (UINT32)p[0] | ((UINT32)p[1] << 8) | ((UINT32)p[2] << 16) | ((UINT32)p[3] << 24);
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 1;
	}

	FILE* f = fopen(argv[1], "rb");
	if (!f)
	{
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	fseek(f, 0, SEEK_END);
	long flen = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (flen < 0) flen = 0;

	/* Heap-allocate the source buffer (ASAN-guarded); pad up to 8 bytes so the
	 * DstWidth/DstHeight header always reads from harness-owned memory (never
	 * an out-of-bounds read of our own scaffolding). */
	size_t bufSize = (size_t)flen < 8 ? 8 : (size_t)flen;
	unsigned char* buf = (unsigned char*) malloc(bufSize);
	if (!buf) { fclose(f); return 1; }
	memset(buf, 0, bufSize);
	if (flen > 0)
		fread(buf, 1, (size_t)flen, f);
	fclose(f);

	UINT32 DstWidth  = rd32(buf + 0);
	UINT32 DstHeight = rd32(buf + 4);

	/* Fixed call shape: compressed bitmap, bpp < 32 -> always the
	 * interleaved_decompress branch of gdi_Bitmap_Decompress. */
	const UINT32 bpp = 16;
	const BOOL compressed = TRUE;
	const UINT32 codecId = 0;

	rdpGdi gdi;
	memset(&gdi, 0, sizeof(gdi));
	gdi.dstFormat = PIXEL_FORMAT_BGRA32;

	rdpCodecs codecs;
	memset(&codecs, 0, sizeof(codecs));
	codecs.interleaved = NULL; /* our stub never dereferences this */
	codecs.planar = NULL;

	rdpContext ctx;
	memset(&ctx, 0, sizeof(ctx));
	ctx.gdi = &gdi;
	ctx.codecs = &codecs;

	rdpBitmap bmp;
	memset(&bmp, 0, sizeof(bmp));

	BOOL ok = gdi_Bitmap_Decompress(&ctx, &bmp, buf, DstWidth, DstHeight,
	                                bpp, (UINT32) bufSize, compressed, codecId);

	free(buf);
	if (bmp.data)
		free(bmp.data);

	printf("gdi_Bitmap_Decompress -> %d (DstWidth=%u DstHeight=%u length=%u)\n",
	       (int) ok, DstWidth, DstHeight, bmp.length);
	return 0;
}
