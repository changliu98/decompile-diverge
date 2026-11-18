/* cve_barebone direct-call harness for CVE-2026-33987 (FreeRDP persistent bitmap cache)
 * Target: persistent_cache_read_entry_v3  (libfreerdp/cache/persistent.c)
 * Bug class: CWE-476 NULL-pointer dereference (WRITE), reachable entirely inside the target
 * function's own body via two direct calls on the same (attacker-controlled) cache stream.
 * See the top-of-file comment in gen_dc_cve_12eb5fb5.py for the full derivation; short version:
 * a first call whose (width,height) forces winpr_aligned_recalloc() to fail leaves
 * persistent->bmpSize nonzero while persistent->bmpData stays NULL (both pre- and post-fix code
 * order the bmpSize-write before the allocation-failure check); a second, smaller-sized call on
 * the SAME persistent then skips the realloc branch and calls fread(NULL, entry->size, 1, fp).
 * This mirrors the REAL caller convention in libfreerdp/core/activation.c's
 * GetBitmapPersistentCacheKeys(), whose read loop does `continue` (not break/return) on a failed
 * persistent_cache_read_entry() -- i.e. production FreeRDP really does call this function again,
 * on the same persistent/stream, right after a failed call.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

/* ---- real WinPR fixed-width type aliases (winpr/include/winpr/wtypes.h, verbatim values) ---- */
typedef uint8_t  BYTE;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef int32_t  BOOL;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* ---- incidental WinPR macros: minimal faithful stand-ins (winpr/include/winpr/assert-api.h,
 * winpr/include/winpr/platform.h) -- neither is part of the crash logic. WINPR_ASSERT's real
 * expansion ultimately aborts on a false condition via winpr_internal_assert(); assert() is the
 * standard-library equivalent. WINPR_C_ARRAY_INIT's non-C23 expansion (the common case here) is
 * literally `{0}`. ---- */
#define WINPR_ASSERT(cond) assert(cond)
#define WINPR_C_ARRAY_INIT {0}

/* ---- real struct layouts, copied verbatim from source_code/include/freerdp/cache/persistent.h
 * (PERSISTENT_CACHE_ENTRY_V3 / PERSISTENT_CACHE_ENTRY) and source_code/libfreerdp/cache/
 * persistent.c (struct rdp_persistent_cache, the VULNERABLE pre-fix layout with UINT32 bmpSize)
 * ---- */
#pragma pack(push, 1)
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

struct rdp_persistent_cache
{
	FILE* fp;
	BOOL write;
	int version;
	int count;
	char* filename;
	BYTE* bmpData;
	UINT32 bmpSize;
};
typedef struct rdp_persistent_cache rdpPersistentCache;

/* ---- incidental callee: winpr_aligned_recalloc (winpr/include/winpr/crt.h declares
 *   WINPR_API void* winpr_aligned_recalloc(void* memblock, size_t num, size_t size, size_t alignment);
 * ). Off the crash path itself (it's the allocator FreeRDP links against, not code under test),
 * so a minimal faithful stub: honours the real signature/NULL-on-failure contract. For a
 * "reasonable" request it does a real (aligned-enough, ASAN-tracked) realloc; for a request
 * bigger than VB_ALLOC_FAIL_THRESHOLD it returns NULL WITHOUT attempting the allocation --
 * exactly how a real allocator legitimately rejects an oversized attacker-driven request (this
 * function's own `size > UINT32_MAX` guard shows the authors already knew attacker (width,height)
 * can demand multi-GB buffers), just without burning multiple seconds/GB per test run. ---- */
#define VB_ALLOC_FAIL_THRESHOLD ((size_t)4 * 1024 * 1024)   /* 4 MiB */
static void* winpr_aligned_recalloc(void* memblock, size_t num, size_t size, size_t alignment)
{
	(void)alignment;
	size_t total = num * size;
	if (total > VB_ALLOC_FAIL_THRESHOLD)
		return NULL;   /* faithful: a real allocator can and does fail large requests */
	void* nb = realloc(memblock, total ? total : 1);
	if (!nb)
		return NULL;
	memset(nb, 0, total ? total : 1);   /* recalloc = realloc + zero (winpr_aligned_calloc's contract) */
	return nb;
}

/* ======================================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_12eb5fb5/target/original_function.c */
/* ======================================================================================== */
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
	entry->size = (UINT32)size;
	entry->flags = 0;

	if (entry->size > persistent->bmpSize)
	{
		persistent->bmpSize = entry->size;
		BYTE* bmpData = (BYTE*)winpr_aligned_recalloc(persistent->bmpData, persistent->bmpSize,
		                                              sizeof(BYTE), 32);

		if (!bmpData)
			return -1;

		persistent->bmpData = bmpData;
	}

	entry->data = persistent->bmpData;

	if (fread((void*)entry->data, entry->size, 1, persistent->fp) != 1)
		return -1;

	return 1;
}
/* ==== end verbatim target function ==== */

/* ---- driver -----------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded), then presents that SAME heap buffer
 * as persistent->fp via fmemopen() -- persistent_cache_read_entry_v3 reads its arguments (the
 * PERSISTENT_CACHE_ENTRY_V3 header, then the bitmap payload) via fread(persistent->fp), so the
 * stream must be a real FILE*; fmemopen backs it directly with the attacker-controlled heap
 * bytes, no extra copy.
 *
 * The call loop mirrors libfreerdp/core/activation.c's GetBitmapPersistentCacheKeys() real
 * usage: repeated direct calls on the SAME persistent (same open stream), continuing regardless
 * of an individual call's return value -- exactly what lets a failed call #1 corrupt state that
 * a subsequent call #2 then dereferences. Each iteration's (width,height,key64) come straight
 * from the next 12 bytes of the input file (the on-disk PERSISTENT_CACHE_ENTRY_V3 record), i.e.
 * every call's arguments are attacker-controlled input, not hardcoded. */
int main(int argc, char **argv)
{
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
	FILE *rf = fopen(argv[1], "rb");
	if (!rf) { perror("fopen"); return 64; }
	if (fseek(rf, 0, SEEK_END) != 0) { fclose(rf); return 64; }
	long fsz = ftell(rf);
	if (fsz < 0) { fclose(rf); return 64; }
	if (fseek(rf, 0, SEEK_SET) != 0) { fclose(rf); return 64; }

	size_t n = (size_t)fsz;
	unsigned char *ibuf = (unsigned char *)malloc(n ? n : 1);   /* HEAP input buffer, ASAN-guarded */
	if (!ibuf) { fclose(rf); return 64; }
	size_t got = n ? fread(ibuf, 1, n, rf) : 0;
	fclose(rf);

	FILE *stream = fmemopen(ibuf, got, "rb");
	if (!stream) { free(ibuf); return 64; }

	rdpPersistentCache persistent;
	memset(&persistent, 0, sizeof(persistent));   /* == a fresh persistent_cache_new(): bmpData=NULL, bmpSize=0 */
	persistent.fp = stream;
	persistent.write = FALSE;
	persistent.version = 3;

	/* Call through a volatile function pointer so this `static`, multiply-invoked function
	 * can't be inlined away into main() and disappear as a distinct ASAN backtrace frame --
	 * changes nothing about how it's called or its own bytes. */
	int (*volatile vb_call)(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *) = persistent_cache_read_entry_v3;

	for (int i = 0; i < 4; i++)
	{
		PERSISTENT_CACHE_ENTRY cacheEntry;
		memset(&cacheEntry, 0, sizeof(cacheEntry));
		(void)vb_call(&persistent, &cacheEntry);   /* return value intentionally ignored -- see
		                                             * activation.c's `continue` above */
	}

	/* Only reached on a SAFE run (a triggering run aborts inside the loop above). */
	if (persistent.bmpData)
		free(persistent.bmpData);
	fclose(stream);
	free(ibuf);
	return 0;
}
