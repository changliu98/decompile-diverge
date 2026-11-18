/*
 * cve_barebone direct-call harness for freerdp persistent_cache_read_entry_v3
 * (libfreerdp/cache/persistent.c)
 *
 * Bug (fixed in a48dbde2c8a5b8b70a9d1c045d969a71afd6284c): the vulnerable
 * persistent_cache_new() allocates persistent->bmpData with plain calloc(),
 * but persistent_cache_read_entry_v3() later grows that SAME buffer via
 * winpr_aligned_recalloc(), which assumes its memblock argument was produced
 * by the WinPR "aligned" allocator (a hidden WINPR_ALIGNED_MEM header living
 * sizeof(WINPR_ALIGNED_MEM) == 24 bytes immediately before the returned
 * pointer). Because bmpData was NOT allocated that way, the very first thing
 * winpr_aligned_offset_recalloc() does is dereference memory 24 bytes BEFORE
 * the calloc'd chunk to check pMem->sig -- a heap-buffer-overflow READ
 * (buffer underflow, CWE-125) reachable purely by calling
 * persistent_cache_read_entry_v3() with an attacker-controlled entry
 * width/height large enough to force the "size > persistent->bmpSize" growth
 * branch. The fix (winpr_aligned_calloc for the initial allocation) is
 * deliberately NOT applied here -- this harness reproduces the pre-fix
 * (vulnerable) allocation pairing.
 *
 * All types/macros/allocator code below are copied verbatim (real names) from
 * this project's own headers/sources:
 *   - include/freerdp/cache/persistent.h  (PERSISTENT_CACHE_ENTRY_V3, PERSISTENT_CACHE_ENTRY)
 *   - libfreerdp/cache/persistent.c       (struct rdp_persistent_cache)
 *   - winpr/libwinpr/crt/alignment.c      (WINPR_ALIGNED_MEM + winpr_aligned_* family --
 *                                          this IS the buggy callee, kept faithful)
 *   - winpr/include/winpr/{assert-api.h,platform.h,cast.h} (WINPR_ASSERT / WINPR_C_ARRAY_INIT /
 *                                          WINPR_ASSERTING_INT_CAST -- trivialized to their
 *                                          real in-range behaviour; logging (WLog_ERR) is a
 *                                          no-op stub, it fires only AFTER the OOB read that
 *                                          ASAN already caught and is not on the crash path)
 *
 * The target function persistent_cache_read_entry_v3 itself is pasted BYTE-FOR-BYTE
 * (via `cat`) from data_cve/cve_f14d0c66/target/original_function.c -- see below.
 *
 * Compile: clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

/* ---- minimal WinPR primitive types (real names, standard-width typedefs) ---- */
typedef uint8_t BYTE;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef int BOOL;

#ifndef nullptr
#define nullptr NULL
#endif

/* ---- winpr/include/winpr/assert-api.h (trivialized: real semantics, no logging plumbing) ---- */
#define WINPR_ASSERT(cond) assert(cond)

/* ---- winpr/include/winpr/platform.h ---- */
#define WINPR_C_ARRAY_INIT { 0 }

/* ---- winpr/include/winpr/cast.h (trivialized: for in-range values this IS the real cast) ---- */
#define WINPR_ASSERTING_INT_CAST(type, ivar) ((type)(ivar))

/* ---- include/freerdp/cache/persistent.h (verbatim) ---- */
#pragma pack(push, 1)

/* 12 bytes */
typedef struct
{
	UINT64 key64;
	UINT16 width;
	UINT16 height;
} PERSISTENT_CACHE_ENTRY_V3;

#pragma pack(pop)

typedef struct
{
	UINT64 key64;
	UINT16 width;
	UINT16 height;
	UINT32 size;
	UINT32 flags;
	BYTE* data;
} PERSISTENT_CACHE_ENTRY;

/* ---- libfreerdp/cache/persistent.c (verbatim) ---- */
struct rdp_persistent_cache
{
	FILE* fp;
	BOOL write;
	int version;
	int count;
	char* filename;
	BYTE* bmpData;
	size_t bmpSize;
};
typedef struct rdp_persistent_cache rdpPersistentCache;

/* ---- winpr/libwinpr/crt/alignment.c (verbatim, non-_WIN32 branch; WLog_ERR -> no-op) ---- */
#define WLog_ERR(tag, ...) ((void)0)
#define TAG "crt"

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

void* winpr_aligned_malloc(size_t size, size_t alignment)
{
	extern void* winpr_aligned_offset_malloc(size_t size, size_t alignment, size_t offset);
	return winpr_aligned_offset_malloc(size, alignment, 0);
}

void* winpr_aligned_calloc(size_t count, size_t size, size_t alignment)
{
	extern void* winpr_aligned_recalloc(void* memblock, size_t num, size_t size, size_t alignment);
	return winpr_aligned_recalloc(nullptr, count, size, alignment);
}

void* winpr_aligned_recalloc(void* memblock, size_t num, size_t size, size_t alignment)
{
	extern void* winpr_aligned_offset_recalloc(void* memblock, size_t num, size_t size,
	                                            size_t alignment, size_t offset);
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

static inline size_t cMIN(size_t a, size_t b)
{
	if (a > b)
		return b;
	return a;
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
			memset(newMemblock, 0, pNewMem->size);
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
		memset(newMemblock + csize, 0, pNewMem->size - csize);
	}
fail:
	winpr_aligned_free(memblock);
	return newMemblock;
}

/* ---- target function, pasted byte-for-byte from
 *      data_cve/cve_f14d0c66/target/original_function.c below ---- */
static int persistent_cache_read_entry_v3(rdpPersistentCache* persistent,
                                          PERSISTENT_CACHE_ENTRY* entry)
{
	PERSISTENT_CACHE_ENTRY_V3 entry3 = WINPR_C_ARRAY_INIT;

	WINPR_ASSERT(persistent);
	WINPR_ASSERT(entry);

	if (fread(&entry3, sizeof(entry3), 1, persistent->fp) != 1)
		return -1;

	entry->key64 = entry3.key64;
	entry->width = entry3.width;
	entry->height = entry3.height;
	const UINT64 size = 4ull * entry3.width * entry3.height;
	if (size > UINT32_MAX)
		return -1;
	entry->flags = 0;

	if (size > persistent->bmpSize)
	{
		persistent->bmpSize = size;
		BYTE* bmpData = (BYTE*)winpr_aligned_recalloc(persistent->bmpData, persistent->bmpSize,
		                                              sizeof(BYTE), 32);

		if (!bmpData)
			return -1;

		persistent->bmpData = bmpData;
	}
	entry->size = WINPR_ASSERTING_INT_CAST(UINT32, size);

	entry->data = persistent->bmpData;

	if (fread((void*)entry->data, entry->size, 1, persistent->fp) != 1)
		return -1;

	return 1;
}

/* ---- driver: read argv[1] into a heap buffer, feed it to the function via
 *      fmemopen() as persistent->fp (exactly the FILE* the real function
 *      freads from), with persistent->bmpData allocated by PLAIN calloc()
 *      (the pre-fix persistent_cache_new() behaviour that pairs badly with
 *      winpr_aligned_recalloc() below the "size > persistent->bmpSize" branch). ---- */
int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	FILE* in = fopen(argv[1], "rb");
	if (!in)
		return 0;

	if (fseek(in, 0, SEEK_END) != 0)
	{
		fclose(in);
		return 0;
	}
	long fsz = ftell(in);
	if (fsz < 0)
		fsz = 0;
	if (fseek(in, 0, SEEK_SET) != 0)
	{
		fclose(in);
		return 0;
	}

	size_t heap_len = (size_t)fsz;
	unsigned char* buf = (unsigned char*)malloc(heap_len > 0 ? heap_len : 1);
	if (!buf)
	{
		fclose(in);
		return 0;
	}

	size_t nread = (heap_len > 0) ? fread(buf, 1, heap_len, in) : 0;
	fclose(in);

	FILE* fp = fmemopen(buf, nread, "rb");
	if (!fp)
	{
		free(buf);
		return 0;
	}

	rdpPersistentCache persistent;
	memset(&persistent, 0, sizeof(persistent));
	persistent.fp = fp;
	persistent.bmpSize = 0x4000;
	/* plain calloc, mirroring the VULNERABLE persistent_cache_new() (pre-a48dbde2) */
	persistent.bmpData = (BYTE*)calloc(1, persistent.bmpSize);
	if (!persistent.bmpData)
	{
		fclose(fp);
		free(buf);
		return 0;
	}

	PERSISTENT_CACHE_ENTRY entry;
	memset(&entry, 0, sizeof(entry));

	int rc = persistent_cache_read_entry_v3(&persistent, &entry);
	(void)rc;

	fclose(fp);
	free(persistent.bmpData);
	free(buf);
	return 0;
}
