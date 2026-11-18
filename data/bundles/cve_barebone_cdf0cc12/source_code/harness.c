/*
 * cve_barebone direct-call harness for FreeRDP update_read_bitmap_update
 * (libfreerdp/core/update.c). CVE fixed by 445a5a42c500ceb80f8fa7f2c11f3682538033f3.
 *
 * Bug: `bitmapUpdate->number` (attacker-controlled UINT16 read off the wire) is
 * doubled into a local `UINT16 count` to size the `rectangles` realloc:
 *
 *     UINT16 count;
 *     count = bitmapUpdate->number * 2;
 *     newdata = realloc(bitmapUpdate->rectangles, sizeof(BITMAP_DATA) * count);
 *
 * For number >= 0x8000 the multiplication overflows the 16-bit `count`
 * (2*number wraps mod 65536), so the array is allocated far smaller than
 * `number` elements. The subsequent loop `for (i = 0; i < bitmapUpdate->number; i++)`
 * then walks update_read_bitmap_data() past the end of the undersized heap
 * buffer -> heap-buffer-overflow WRITE (CWE-787) inside update_read_bitmap_data's
 * very first field write (`bitmapData->destLeft = ...`), reached directly from
 * update_read_bitmap_update's own body. No project state beyond the wStream
 * byte buffer is needed to reach it.
 *
 * All type/struct/macro definitions below are copied verbatim (real names,
 * real field layouts) from the FreeRDP source tree at the vulnerable commit:
 *   - include/freerdp/update.h        (BITMAP_DATA, BITMAP_UPDATE)
 *   - winpr/include/winpr/stream.h    (_wStream + the Stream_* macros/inlines
 *                                       actually used by the target + callee)
 *   - libfreerdp/core/update.h        (BITMAP_COMPRESSION, NO_BITMAP_COMPRESSION_HDR)
 *   - libfreerdp/core/update.c        (update_read_bitmap_data: the real callee
 *                                       on the crash path, verbatim)
 *   - libfreerdp/cache/bitmap.c       (free_bitmap_data/free_bitmap_update: the
 *                                       real cleanup helpers used on update_read_bitmap_update's
 *                                       fail path, verbatim)
 *
 * `rdpUpdate`/`rdpContext`/`wLog` are opaque in real FreeRDP (forward-declared,
 * defined in private headers pulling in the whole settings/context graph).
 * Neither field is on the crash path here: `update->log` only feeds a
 * WLog_Print() trace call (stubbed to a no-op, matching its real no-op-when-
 * below-log-level behaviour) and `update->context` is passed to
 * free_bitmap_update() but never dereferenced there (verified against the
 * verbatim body below). So they are minimal opaque stand-ins, not invented
 * behaviour.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

/* ---- WinPR primitive typedefs (winpr/include/winpr/wtypes.h.in), verbatim widths ---- */
typedef uint8_t  BYTE;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint32_t DWORD;
typedef int32_t  BOOL;
#define TRUE 1
#define FALSE 0

/* ---- wStream (winpr/include/winpr/stream.h), verbatim field layout ---- */
typedef struct _wStreamPool wStreamPool; /* opaque, never dereferenced on this path */

struct _wStream
{
	BYTE* buffer;
	BYTE* pointer;
	size_t length;
	size_t capacity;

	DWORD count;
	wStreamPool* pool;
	BOOL isAllocatedStream;
	BOOL isOwner;
};
typedef struct _wStream wStream;

/* winpr/include/winpr/winpr.h: #define INLINE inline (C99 path) */
#define INLINE inline

static INLINE void Stream_Seek(wStream* s, size_t _offset)
{
	s->pointer += (_offset);
}

#define _stream_read_n16_le(_t, _s, _v, _p) do { \
		_v = \
		     (_t)(*_s->pointer) + \
		     (_t)(((_t)(*(_s->pointer + 1))) << 8); \
		if (_p) Stream_Seek(_s, sizeof(_t)); } while (0)

#define Stream_Read_UINT16(_s, _v) _stream_read_n16_le(UINT16, _s, _v, TRUE)

static INLINE BYTE* Stream_Pointer(wStream* _s)
{
	return _s->pointer;
}

static INLINE size_t Stream_GetRemainingLength(wStream* _s)
{
	return (_s->length - (_s->pointer - _s->buffer));
}

/* winpr/include/winpr/crt.h, verbatim */
#define ZeroMemory(Destination, Length)			memset((Destination), 0, (Length))

/* ---- libfreerdp/core/update.h ---- */
#define BITMAP_COMPRESSION		0x0001
#define NO_BITMAP_COMPRESSION_HDR	0x0400

/* ---- include/freerdp/update.h, verbatim ---- */
struct _BITMAP_DATA
{
	UINT32 destLeft;
	UINT32 destTop;
	UINT32 destRight;
	UINT32 destBottom;
	UINT32 width;
	UINT32 height;
	UINT32 bitsPerPixel;
	UINT32 flags;
	UINT32 bitmapLength;
	UINT32 cbCompFirstRowSize;
	UINT32 cbCompMainBodySize;
	UINT32 cbScanWidth;
	UINT32 cbUncompressedSize;
	BYTE* bitmapDataStream;
	BOOL compressed;
};
typedef struct _BITMAP_DATA BITMAP_DATA;

struct _BITMAP_UPDATE
{
	UINT32 count;
	UINT32 number;
	BITMAP_DATA* rectangles;
	BOOL skipCompression;
};
typedef struct _BITMAP_UPDATE BITMAP_UPDATE;

/* ---- opaque context types (real names, minimal stand-ins — see file header) ---- */
typedef struct rdpContext rdpContext; /* forward-declared only in real FreeRDP too */
struct rdp_update
{
	void* log;       /* stands in for wLog*; only fed to the stubbed WLog_Print below */
	rdpContext* context;
};
typedef struct rdp_update rdpUpdate;

#define WLOG_TRACE 0
/* real WLog_Print is a no-op below the configured log level; we pin that behaviour */
#define WLog_Print(_log, _level, ...) ((void)0)

/* ---- libfreerdp/cache/bitmap.c, verbatim (the fail-path cleanup helpers) ---- */
static void free_bitmap_data(BITMAP_DATA* data, size_t count)
{
	size_t x;

	if (!data)
		return;

	for (x = 0; x < count; x++)
		free(data[x].bitmapDataStream);

	free(data);
}

void free_bitmap_update(rdpContext* context, BITMAP_UPDATE* pointer)
{
	if (!pointer)
		return;

	free_bitmap_data(pointer->rectangles, pointer->number);
	free(pointer);
}

/* ---- libfreerdp/core/update.c, verbatim (the real callee on the crash path) ---- */
static BOOL update_read_bitmap_data(rdpUpdate* update, wStream* s,
                                    BITMAP_DATA* bitmapData)
{
	if (Stream_GetRemainingLength(s) < 18)
		return FALSE;

	Stream_Read_UINT16(s, bitmapData->destLeft);
	Stream_Read_UINT16(s, bitmapData->destTop);
	Stream_Read_UINT16(s, bitmapData->destRight);
	Stream_Read_UINT16(s, bitmapData->destBottom);
	Stream_Read_UINT16(s, bitmapData->width);
	Stream_Read_UINT16(s, bitmapData->height);
	Stream_Read_UINT16(s, bitmapData->bitsPerPixel);
	Stream_Read_UINT16(s, bitmapData->flags);
	Stream_Read_UINT16(s, bitmapData->bitmapLength);

	if (bitmapData->flags & BITMAP_COMPRESSION)
	{
		if (!(bitmapData->flags & NO_BITMAP_COMPRESSION_HDR))
		{
			Stream_Read_UINT16(s,
			                   bitmapData->cbCompFirstRowSize); /* cbCompFirstRowSize (2 bytes) */
			Stream_Read_UINT16(s,
			                   bitmapData->cbCompMainBodySize); /* cbCompMainBodySize (2 bytes) */
			Stream_Read_UINT16(s, bitmapData->cbScanWidth); /* cbScanWidth (2 bytes) */
			Stream_Read_UINT16(s,
			                   bitmapData->cbUncompressedSize); /* cbUncompressedSize (2 bytes) */
			bitmapData->bitmapLength = bitmapData->cbCompMainBodySize;
		}

		bitmapData->compressed = TRUE;
	}
	else
		bitmapData->compressed = FALSE;

	if (Stream_GetRemainingLength(s) < bitmapData->bitmapLength)
		return FALSE;

	if (bitmapData->bitmapLength > 0)
	{
		bitmapData->bitmapDataStream = malloc(bitmapData->bitmapLength);

		if (!bitmapData->bitmapDataStream)
			return FALSE;

		memcpy(bitmapData->bitmapDataStream, Stream_Pointer(s), bitmapData->bitmapLength);
		Stream_Seek(s, bitmapData->bitmapLength);
	}

	return TRUE;
}

/* ---- libfreerdp/core/update.c: target/original_function.c, BYTE-FOR-BYTE ---- */
BITMAP_UPDATE* update_read_bitmap_update(rdpUpdate* update, wStream* s)
{
	UINT32 i;
	BITMAP_UPDATE* bitmapUpdate = calloc(1, sizeof(BITMAP_UPDATE));

	if (!bitmapUpdate)
		goto fail;

	if (Stream_GetRemainingLength(s) < 2)
		goto fail;

	Stream_Read_UINT16(s, bitmapUpdate->number); /* numberRectangles (2 bytes) */
	WLog_Print(update->log, WLOG_TRACE, "BitmapUpdate: %"PRIu32"", bitmapUpdate->number);

	if (bitmapUpdate->number > bitmapUpdate->count)
	{
		UINT16 count;
		BITMAP_DATA* newdata;
		count = bitmapUpdate->number * 2;
		newdata = (BITMAP_DATA*) realloc(bitmapUpdate->rectangles,
		                                 sizeof(BITMAP_DATA) * count);

		if (!newdata)
			goto fail;

		bitmapUpdate->rectangles = newdata;
		ZeroMemory(&bitmapUpdate->rectangles[bitmapUpdate->count],
		           sizeof(BITMAP_DATA) * (count - bitmapUpdate->count));
		bitmapUpdate->count = count;
	}

	/* rectangles */
	for (i = 0; i < bitmapUpdate->number; i++)
	{
		if (!update_read_bitmap_data(update, s, &bitmapUpdate->rectangles[i]))
			goto fail;
	}

	return bitmapUpdate;
fail:
	free_bitmap_update(update->context, bitmapUpdate);
	return NULL;
}

/* ---- driver ---- */
int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	FILE* f = fopen(argv[1], "rb");
	if (!f)
	{
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	long fsz = ftell(f);
	if (fsz < 0) { fclose(f); return 1; }
	rewind(f);

	/* Attacker-controlled bytes MUST live in a HEAP allocation sized exactly to
	 * the payload so the wire-format bytes themselves carry no extra slack; the
	 * bug under test is an OOB write into the separately-heap-allocated
	 * `rectangles` array, not into this buffer, but it must still be
	 * ASAN-visible heap memory to mirror how the real stream buffer is heap
	 * allocated (Stream_New). */
	unsigned char* raw = (unsigned char*)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if (!raw) { fclose(f); return 1; }
	size_t got = fread(raw, 1, (size_t)fsz, f);
	fclose(f);

	wStream stream;
	stream.buffer = raw;
	stream.pointer = raw;
	stream.length = got;
	stream.capacity = got;
	stream.count = 0;
	stream.pool = NULL;
	stream.isAllocatedStream = FALSE;
	stream.isOwner = TRUE;

	struct rdp_update upd;
	upd.log = NULL;
	upd.context = NULL;

	BITMAP_UPDATE* result = update_read_bitmap_update(&upd, &stream);
	if (result)
		free_bitmap_update(upd.context, result);

	free(raw);
	return 0;
}
