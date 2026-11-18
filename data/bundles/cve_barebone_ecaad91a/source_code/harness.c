/*
 * cve_ecaad91a -- freerdp clear_decompress_subcodecs_data direct-call ASAN harness.
 *
 * CVE-2026-26955 (fix commit 7d8fdce2d0ef337cb86cb37fc0c436c905e04d77, vulnerable at
 * 341b52ad96b41a4cde8190ce13aa0692684f80e1): for each ClearCodec "subcodec" tile,
 * clear_decompress_subcodecs_data() bounds-checks the tile's destination rectangle
 * (nXDstRel = nXDst + xStart, width; nYDstRel = nYDst + yStart, height) against the
 * codec's *nominal* surface dimensions nWidth/nHeight:
 *
 *     if (1ull * nXDstRel + width > nWidth)   return FALSE;   // BUG: should be nDstWidth
 *     if (1ull * nYDstRel + height > nHeight) return FALSE;   // BUG: should be nDstHeight
 *
 * instead of the *actual* destination-buffer dimensions nDstWidth/nDstHeight that the
 * caller separately supplies. The fix (7d8fdce2) simply swaps the comparand:
 *
 *     if (1ull * nXDstRel + width > nDstWidth)   return FALSE;
 *     if (1ull * nYDstRel + height > nDstHeight) return FALSE;
 *
 * Pre-fix, a caller whose nominal nWidth/nHeight is larger than the real nDstWidth/
 * nDstHeight (exactly what this harness's fixed call-site parameters model) lets
 * nXDstRel run past nDstWidth while still satisfying the (wrong) check. Execution then
 * reaches convert_color(), which re-clips against the *real* nDstWidth/nDstHeight:
 *
 *     if (nWidth + nXDst > nDstWidth) nWidth = nDstWidth - nXDst;
 *
 * Since nXDst (== nXDstRel) already exceeds nDstWidth here, this UINT32 subtraction
 * itself underflows to a huge wrapped value, which is then handed to the pixel-copy
 * primitive (freerdp_image_copy_no_overlap(), stubbed below -- see that stub's own
 * comment) as the number of pixels to copy per row: an out-of-bounds read starting
 * from the small, attacker-sized subcodec payload buffer.
 *
 * This harness calls clear_decompress_subcodecs_data() directly with a fixed
 * "vulnerable configuration" (nominal nWidth/nHeight far larger than the real
 * nDstWidth/nDstHeight destination surface -- a legitimate combination the function's
 * own parameters allow and never itself validates) and lets the input FILE supply the
 * wire-format subcodec record (xStart/yStart/width/height/bitmapDataByteCount/
 * subcodecId + payload bytes) exactly as clear_decompress_subcodecs_data's own
 * Stream_Get_* calls would parse it from the network.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

/* ---- minimal WinPR type aliases (real widths used throughout FreeRDP; winpr/wtypes.h
 * itself is not vendored in this checkout's include tree) ---- */
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;
typedef unsigned int DWORD;
#define TRUE 1
#define FALSE 0
#define PRIuz "zu"

#define WINPR_RESTRICT
#define WINPR_ASSERTING_INT_CAST(t, v) ((t)(v))

/* ---- winpr/stream.h: real wStream struct field layout + the exact Stream_* helpers
 * clear_decompress_subcodecs_data uses, faithfully reimplemented (bounds-checked
 * little-endian reads that advance ->pointer, exactly like the real inline functions in
 * winpr/include/winpr/stream.h) -- logging (WLog) is the only part elided. ---- */
typedef struct s_wStreamPool wStreamPool; /* forward-declared only in the real header too */

typedef struct
{
	BYTE* buffer;
	BYTE* pointer;
	size_t length;
	size_t capacity;

	DWORD count;
	wStreamPool* pool;
	BOOL isAllocatedStream;
	BOOL isOwner;
} wStream;

static inline size_t Stream_GetRemainingLength(const wStream* _s)
{
	size_t cur = (size_t)(_s->pointer - _s->buffer);
	if (cur > _s->length)
		return 0;
	return _s->length - cur;
}

/* real macro: Stream_CheckAndLogRequiredLength(tag,s,len) ==
 * Stream_CheckAndLogRequiredLengthOfSize(tag,s,len,1) -> ...Ex(tag,WLOG_WARN,s,len,1,...)
 * whose body is `(Stream_GetRemainingLength(s) / 1) >= len` (winpr/libwinpr/utils/stream.c) */
static inline BOOL Stream_CheckAndLogRequiredLength(const char* tag, wStream* s, size_t len)
{
	(void)tag;
	return Stream_GetRemainingLength(s) >= len;
}

static inline void Stream_Seek(wStream* s, size_t _offset)
{
	s->pointer += _offset;
}

static inline void* Stream_Pointer(wStream* _s)
{
	return _s->pointer;
}

static inline UINT8 Stream_Get_UINT8(wStream* _s)
{
	const UINT8 v = (UINT8)_s->pointer[0];
	Stream_Seek(_s, 1);
	return v;
}

static inline UINT16 Stream_Get_UINT16(wStream* _s)
{
	const UINT16 v = (UINT16)(_s->pointer[0] | (_s->pointer[1] << 8));
	Stream_Seek(_s, 2);
	return v;
}

static inline UINT32 Stream_Get_UINT32(wStream* _s)
{
	const UINT32 v = (UINT32)_s->pointer[0] | ((UINT32)_s->pointer[1] << 8) |
	                 ((UINT32)_s->pointer[2] << 16) | ((UINT32)_s->pointer[3] << 24);
	Stream_Seek(_s, 4);
	return v;
}

/* ---- freerdp/log.h ---- */
#define TAG "codec.clear"
#define WLog_ERR(tag, ...) ((void)0)

/* ---- freerdp/codec/color.h: real pixel-format encoding + gdiPalette, verbatim ---- */
#define FREERDP_PIXEL_FORMAT_TYPE_ABGR 2
#define FREERDP_PIXEL_FORMAT_TYPE_BGRA 4
#define FREERDP_PIXEL_FORMAT(_bpp, _type, _a, _r, _g, _b) \
	((_bpp << 24) | (_type << 16) | (_a << 12) | (_r << 8) | (_g << 4) | (_b))
#define PIXEL_FORMAT_BGRX32 FREERDP_PIXEL_FORMAT(32, FREERDP_PIXEL_FORMAT_TYPE_BGRA, 0, 8, 8, 8)
#define PIXEL_FORMAT_BGR24 FREERDP_PIXEL_FORMAT(24, FREERDP_PIXEL_FORMAT_TYPE_ABGR, 0, 8, 8, 8)

enum FREERDP_IMAGE_FLAGS
{
	FREERDP_FLIP_NONE = 0,
	FREERDP_FLIP_VERTICAL = 1,
	FREERDP_FLIP_HORIZONTAL = 2,
	FREERDP_KEEP_DST_ALPHA = 4
};

struct gdi_palette
{
	UINT32 format;
	UINT32 palette[256];
};
typedef struct gdi_palette gdiPalette;

static inline UINT32 FreeRDPGetBitsPerPixel(UINT32 format)
{
	return (((format) >> 24) & 0x3F);
}

static inline UINT32 FreeRDPGetBytesPerPixel(UINT32 format)
{
	return (FreeRDPGetBitsPerPixel(format) + 7) / 8;
}

/*
 * Minimal faithful stand-in for freerdp_image_copy_no_overlap() (libfreerdp/codec/
 * color.c, which just forwards to the registered libfreerdp/primitives backend's
 * copy_no_overlap -- generic_image_copy_no_overlap_memcpy() for this harness's
 * same-format BGR24->BGR24 case, per libfreerdp/primitives/prim_copy.c): a per-row
 * copy of nWidth*Bpp bytes from src to dst at the given strides/offsets -- the same
 * memory-access shape the real fast path performs. This is deliberately INCIDENTAL
 * scaffolding relative to clear_decompress_subcodecs_data's own bug (the diff this CVE
 * fixes never touches color.c/primitives): the real function's dynamic CPU-feature
 * (SSE4.1/AVX2) dispatch and its `nWidth/nHeight > INT32_MAX` defensive sanity guard
 * are dropped as not part of the documented "copy nWidth x nHeight pixels" contract.
 * The copy is a manual byte loop (not memcpy) purely so a huge, wrapped nWidth reads
 * past the small source buffer at a small, deterministic byte offset -- calling libc
 * memcpy with a multi-gigabyte length here would make ASAN's own overlap pre-check
 * (comparing [dst,dst+n) against [src,src+n) for two ordinarily-unrelated, nearby heap
 * allocations) misreport "memcpy-param-overlap" instead of the real bug.
 */
static BOOL freerdp_image_copy_no_overlap(BYTE* WINPR_RESTRICT pDstData, UINT32 DstFormat,
                                          UINT32 nDstStep, UINT32 nXDst, UINT32 nYDst,
                                          UINT32 nWidth, UINT32 nHeight,
                                          const BYTE* WINPR_RESTRICT pSrcData, UINT32 SrcFormat,
                                          UINT32 nSrcStep, UINT32 nXSrc, UINT32 nYSrc,
                                          const gdiPalette* WINPR_RESTRICT palette, UINT32 flags)
{
	(void)palette;
	(void)flags;
	const int64_t dstByte = (int64_t)FreeRDPGetBytesPerPixel(DstFormat);
	const int64_t srcByte = (int64_t)FreeRDPGetBytesPerPixel(SrcFormat);
	const int64_t copyWidth = (int64_t)nWidth * dstByte;
	const int64_t xSrcOffset = (int64_t)nXSrc * srcByte;
	const int64_t xDstOffset = (int64_t)nXDst * dstByte;

	for (int64_t y = 0; y < (int64_t)nHeight; y++)
	{
		const volatile BYTE* srcLine = (const volatile BYTE*)&pSrcData[(int64_t)(y + nYSrc) * nSrcStep];
		volatile BYTE* dstLine = (volatile BYTE*)&pDstData[(int64_t)(y + nYDst) * nDstStep];

		for (int64_t i = 0; i < copyWidth; i++)
			dstLine[xDstOffset + i] = srcLine[xSrcOffset + i];
	}
	return TRUE;
}

/* ============================================================
 * Everything below this point is copied verbatim from the vulnerable
 * libfreerdp/codec/clear.c (commit 341b52ad96b41a4cde8190ce13aa0692684f80e1) --
 * the CLEAR_CONTEXT struct, clear_resize_buffer(), convert_color(), and
 * clear_decompress_subcodecs_data() itself -- so its body needs zero edits.
 * clear_decompress_nscodec()/clear_decompress_subcode_rlex() are declared with their
 * real signatures but given trivial `return FALSE;` bodies: every crafted input in this
 * harness's corpus forces subcodecId == 0 (the "Uncompressed" case), so those two
 * branches are provably never entered -- they exist only so the verbatim switch inside
 * clear_decompress_subcodecs_data's body still compiles and links.
 * ============================================================ */

#define CLEARCODEC_VBAR_SIZE 32768
#define CLEARCODEC_VBAR_SHORT_SIZE 16384

typedef struct S_NSC_CONTEXT NSC_CONTEXT; /* opaque: never dereferenced (matches the real
                                            * forward-declare in include/freerdp/codec/nsc.h) */

typedef struct
{
	UINT32 size;
	UINT32 count;
	UINT32* pixels;
} CLEAR_GLYPH_ENTRY;

typedef struct
{
	UINT32 size;
	UINT32 count;
	BYTE* pixels;
} CLEAR_VBAR_ENTRY;

struct S_CLEAR_CONTEXT
{
	BOOL Compressor;
	NSC_CONTEXT* nsc;
	UINT32 seqNumber;
	BYTE* TempBuffer;
	size_t TempSize;
	UINT32 nTempStep;
	UINT32 TempFormat;
	UINT32 format;
	CLEAR_GLYPH_ENTRY GlyphCache[4000];
	UINT32 VBarStorageCursor;
	CLEAR_VBAR_ENTRY VBarStorage[CLEARCODEC_VBAR_SIZE];
	UINT32 ShortVBarStorageCursor;
	CLEAR_VBAR_ENTRY ShortVBarStorage[CLEARCODEC_VBAR_SHORT_SIZE];
};
typedef struct S_CLEAR_CONTEXT CLEAR_CONTEXT;

/* winpr/aligned.h: realloc-with-alignment. Alignment is dropped (incidental --
 * clear_resize_buffer only needs correctly-sized, zeroed storage); this harness always
 * calls it exactly once against a fresh (NULL, 0) TempBuffer/TempSize, so a plain
 * realloc()+memset(0) is exactly recalloc's observable behavior here (not merely an
 * approximation of "zero the newly grown tail"). */
static void* winpr_aligned_recalloc(void* ptr, size_t count, size_t size, size_t alignment)
{
	(void)alignment;
	size_t total = count * size;
	void* p = realloc(ptr, total);
	if (p)
		memset(p, 0, total);
	return p;
}

static BOOL clear_decompress_nscodec(NSC_CONTEXT* WINPR_RESTRICT nsc, UINT32 width, UINT32 height,
                                     wStream* WINPR_RESTRICT s, UINT32 bitmapDataByteCount,
                                     BYTE* WINPR_RESTRICT pDstData, UINT32 DstFormat,
                                     UINT32 nDstStep, UINT32 nXDstRel, UINT32 nYDstRel)
{
	(void)nsc; (void)width; (void)height; (void)s; (void)bitmapDataByteCount;
	(void)pDstData; (void)DstFormat; (void)nDstStep; (void)nXDstRel; (void)nYDstRel;
	return FALSE;
}

static BOOL clear_decompress_subcode_rlex(wStream* WINPR_RESTRICT s, UINT32 bitmapDataByteCount,
                                          UINT32 width, UINT32 height,
                                          BYTE* WINPR_RESTRICT pDstData, UINT32 DstFormat,
                                          UINT32 nDstStep, UINT32 nXDstRel, UINT32 nYDstRel,
                                          UINT32 nDstWidth, UINT32 nDstHeight)
{
	(void)s; (void)bitmapDataByteCount; (void)width; (void)height; (void)pDstData;
	(void)DstFormat; (void)nDstStep; (void)nXDstRel; (void)nYDstRel; (void)nDstWidth;
	(void)nDstHeight;
	return FALSE;
}

static BOOL clear_resize_buffer(CLEAR_CONTEXT* WINPR_RESTRICT clear, UINT32 width, UINT32 height)
{
	if (!clear)
		return FALSE;

	const UINT64 size = 1ull * (width + 16ull) * (height + 16ull);
	const size_t bpp = FreeRDPGetBytesPerPixel(clear->format);
	if (size > UINT32_MAX / bpp)
		return FALSE;

	if (size > clear->TempSize / bpp)
	{
		BYTE* tmp = (BYTE*)winpr_aligned_recalloc(clear->TempBuffer,
		                                          WINPR_ASSERTING_INT_CAST(size_t, size), bpp, 32);

		if (!tmp)
		{
			WLog_ERR(TAG, "clear->TempBuffer winpr_aligned_recalloc failed for %" PRIu64 " bytes",
			         size);
			return FALSE;
		}

		clear->TempSize = WINPR_ASSERTING_INT_CAST(size_t, size* bpp);
		clear->TempBuffer = tmp;
	}

	return TRUE;
}

static BOOL convert_color(BYTE* WINPR_RESTRICT dst, UINT32 nDstStep, UINT32 DstFormat, UINT32 nXDst,
                          UINT32 nYDst, UINT32 nWidth, UINT32 nHeight,
                          const BYTE* WINPR_RESTRICT src, UINT32 nSrcStep, UINT32 SrcFormat,
                          UINT32 nDstWidth, UINT32 nDstHeight,
                          const gdiPalette* WINPR_RESTRICT palette)
{
	if (nWidth + nXDst > nDstWidth)
		nWidth = nDstWidth - nXDst;

	if (nHeight + nYDst > nDstHeight)
		nHeight = nDstHeight - nYDst;

	return freerdp_image_copy_no_overlap(dst, DstFormat, nDstStep, nXDst, nYDst, nWidth, nHeight,
	                                     src, SrcFormat, nSrcStep, 0, 0, palette,
	                                     FREERDP_KEEP_DST_ALPHA);
}

static BOOL clear_decompress_subcodecs_data(CLEAR_CONTEXT* WINPR_RESTRICT clear,
                                            wStream* WINPR_RESTRICT s, UINT32 subcodecByteCount,
                                            UINT32 nWidth, UINT32 nHeight,
                                            BYTE* WINPR_RESTRICT pDstData, UINT32 DstFormat,
                                            UINT32 nDstStep, UINT32 nXDst, UINT32 nYDst,
                                            UINT32 nDstWidth, UINT32 nDstHeight,
                                            const gdiPalette* WINPR_RESTRICT palette)
{
	UINT32 suboffset = 0;

	if (!Stream_CheckAndLogRequiredLength(TAG, s, subcodecByteCount))
		return FALSE;

	while (suboffset < subcodecByteCount)
	{
		if (!Stream_CheckAndLogRequiredLength(TAG, s, 13))
			return FALSE;

		const UINT16 xStart = Stream_Get_UINT16(s);
		const UINT16 yStart = Stream_Get_UINT16(s);
		const UINT16 width = Stream_Get_UINT16(s);
		const UINT16 height = Stream_Get_UINT16(s);
		const UINT32 bitmapDataByteCount = Stream_Get_UINT32(s);
		const UINT8 subcodecId = Stream_Get_UINT8(s);
		suboffset += 13;

		if (!Stream_CheckAndLogRequiredLength(TAG, s, bitmapDataByteCount))
			return FALSE;

		const UINT32 nXDstRel = nXDst + xStart;
		const UINT32 nYDstRel = nYDst + yStart;
		if (1ull * nXDstRel + width > nWidth)
		{
			WLog_ERR(TAG, "nXDstRel %" PRIu16 " + width %" PRIu16 " > nWidth %" PRIu32 "", xStart,
			         width, nWidth);
			return FALSE;
		}
		if (1ull * nYDstRel + height > nHeight)
		{
			WLog_ERR(TAG, "nYDstRel %" PRIu16 " + height %" PRIu16 " > nHeight %" PRIu32 "", yStart,
			         height, nHeight);
			return FALSE;
		}

		if (1ull * xStart + width > nWidth)
		{
			WLog_ERR(TAG, "xStart %" PRIu16 " + width %" PRIu16 " > nWidth %" PRIu32 "", xStart,
			         width, nWidth);
			return FALSE;
		}
		if (1ull * yStart + height > nHeight)
		{
			WLog_ERR(TAG, "yStart %" PRIu16 " + height %" PRIu16 " > nHeight %" PRIu32 "", yStart,
			         height, nHeight);
			return FALSE;
		}

		if (!clear_resize_buffer(clear, width, height))
			return FALSE;

		switch (subcodecId)
		{
			case 0: /* Uncompressed */
			{
				const UINT32 nSrcStep = width * FreeRDPGetBytesPerPixel(PIXEL_FORMAT_BGR24);
				const size_t nSrcSize = 1ull * nSrcStep * height;

				if (bitmapDataByteCount != nSrcSize)
				{
					WLog_ERR(TAG, "bitmapDataByteCount %" PRIu32 " != nSrcSize %" PRIuz "",
					         bitmapDataByteCount, nSrcSize);
					return FALSE;
				}

				if (!convert_color(pDstData, nDstStep, DstFormat, nXDstRel, nYDstRel, width, height,
				                   Stream_Pointer(s), nSrcStep, PIXEL_FORMAT_BGR24, nDstWidth,
				                   nDstHeight, palette))
					return FALSE;

				Stream_Seek(s, bitmapDataByteCount);
			}
			break;

			case 1: /* NSCodec */
				if (!clear_decompress_nscodec(clear->nsc, width, height, s, bitmapDataByteCount,
				                              pDstData, DstFormat, nDstStep, nXDstRel, nYDstRel))
					return FALSE;

				break;

			case 2: /* CLEARCODEC_SUBCODEC_RLEX */
				if (!clear_decompress_subcode_rlex(s, bitmapDataByteCount, width, height, pDstData,
				                                   DstFormat, nDstStep, nXDstRel, nYDstRel,
				                                   nDstWidth, nDstHeight))
					return FALSE;

				break;

			default:
				WLog_ERR(TAG, "Unknown subcodec ID %" PRIu8 "", subcodecId);
				return FALSE;
		}

		suboffset += bitmapDataByteCount;
	}

	return TRUE;
}

/* ---- driver: read argv[1], derive clear_decompress_subcodecs_data's arguments, call
 * it in isolation ---- */
int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	FILE* f = fopen(argv[1], "rb");
	if (!f)
		return 0;

	fseek(f, 0, SEEK_END);
	long fsz = ftell(f);
	fseek(f, 0, SEEK_SET);

	if (fsz < 13)
	{
		fclose(f);
		return 0;
	}

	unsigned char* filebuf = (unsigned char*)malloc((size_t)fsz);
	if (!filebuf)
	{
		fclose(f);
		return 0;
	}

	size_t rd = fread(filebuf, 1, (size_t)fsz, f);
	fclose(f);

	if (rd != (size_t)fsz)
	{
		free(filebuf);
		return 0;
	}

	/*
	 * Fixed "vulnerable configuration" call-site parameters, matching a real
	 * clear_decompress() caller whose nominal codec surface (nWidth/nHeight) is far
	 * larger than the actual destination bitmap (nDstWidth/nDstHeight) -- exactly the
	 * confusion CVE-2026-26955's fix (7d8fdce2) closes. The wire-format subcodec
	 * record (xStart/yStart/width/height/bitmapDataByteCount/subcodecId + payload)
	 * comes entirely from the input file, exactly as clear_decompress_subcodecs_data's
	 * own Stream_Get_* calls would parse it from the network.
	 */
	const UINT32 nDstWidth = 64;
	const UINT32 nDstHeight = 64;
	const UINT32 DstFormat = PIXEL_FORMAT_BGR24;
	const UINT32 nDstStep = nDstWidth * FreeRDPGetBytesPerPixel(DstFormat);
	const UINT32 nWidth = 0x7FFFFFFFu;
	const UINT32 nHeight = 0x7FFFFFFFu;
	const UINT32 nXDst = 0;
	const UINT32 nYDst = 0;

	BYTE* pDstData = (BYTE*)malloc((size_t)nDstStep * nDstHeight);
	if (!pDstData)
	{
		free(filebuf);
		return 0;
	}
	memset(pDstData, 0, (size_t)nDstStep * nDstHeight);

	CLEAR_CONTEXT* clear = (CLEAR_CONTEXT*)calloc(1, sizeof(CLEAR_CONTEXT));
	if (!clear)
	{
		free(pDstData);
		free(filebuf);
		return 0;
	}
	clear->format = PIXEL_FORMAT_BGRX32; /* mirrors clear_context_new()'s updateContextFormat() */

	wStream stream;
	stream.buffer = filebuf;
	stream.pointer = filebuf;
	stream.length = (size_t)fsz;
	stream.capacity = (size_t)fsz;
	stream.count = 0;
	stream.pool = NULL;
	stream.isAllocatedStream = FALSE;
	stream.isOwner = FALSE;

	clear_decompress_subcodecs_data(clear, &stream, (UINT32)fsz, nWidth, nHeight, pDstData,
	                                DstFormat, nDstStep, nXDst, nYDst, nDstWidth, nDstHeight, NULL);

	free(clear->TempBuffer);
	free(clear);
	free(pDstData);
	free(filebuf);
	return 0;
}
