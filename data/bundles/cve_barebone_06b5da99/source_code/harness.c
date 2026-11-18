/*
 * cve_06b5da99 -- freerdp zgfx_decompress_segment direct-call ASAN harness.
 *
 * CVE-2018-8784: zgfx_decompress_segment() copies an attacker-supplied
 * "segment" of `cbSegment = segmentSize - 1` bytes straight into the
 * fixed-size zgfx->OutputBuffer[65536] (the ZGFX_CONTEXT.OutputBuffer field)
 * with NO bounds check against sizeof(OutputBuffer) whenever the segment's
 * header flags byte does not have PACKET_COMPRESSED (0x20) set:
 *
 *     CopyMemory(zgfx->OutputBuffer, pbSegment, cbSegment);
 *
 * The fix (17c363a5162fd4dc77b1df54e48d7bd9bf6b3be7) adds:
 *     if (cbSegment > sizeof(zgfx->OutputBuffer)) return FALSE;
 * right before that copy (plus equivalent guards on the compressed-token
 * paths, not exercised here).
 *
 * This harness calls zgfx_decompress_segment() directly on a heap-allocated
 * ZGFX_CONTEXT (mirroring the real zgfx_context_new() initialization) and a
 * heap-allocated wStream wrapping an attacker-sized segment buffer, so ASAN
 * flags the write once it runs past the end of the whole ZGFX_CONTEXT heap
 * allocation (OutputBuffer is followed in-struct by OutputCount and the
 * 2.5MB HistoryBuffer, so the overflow must clear that entire tail to leave
 * the allocation and hit an ASAN redzone).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- minimal WinPR type aliases (real widths used throughout FreeRDP;
 * winpr/wtypes.h itself is not vendored in this checkout's include tree) ---- */
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned char UINT8;
typedef signed char INT8;
typedef unsigned short UINT16;
typedef short INT16;
typedef unsigned int UINT32;
typedef int INT32;
typedef unsigned long long UINT64;
typedef long long INT64;
typedef unsigned int DWORD;
#define TRUE 1
#define FALSE 0

/* winpr/crt.h */
#define CopyMemory(Destination, Source, Length) memcpy((Destination), (Source), (Length))
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

/* ---- winpr/stream.h: real struct + the exact macros/inline fns that
 * zgfx_decompress_segment uses, copied verbatim ---- */
typedef struct _wStreamPool wStreamPool; /* forward-declared only in the real header too */

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

static inline void Stream_Seek(wStream* s, size_t _offset)
{
	s->pointer += (_offset);
}

#define _stream_read_n8(_t, _s, _v, _p) do { \
		_v = \
		     (_t)(*_s->pointer); \
		if (_p) Stream_Seek(_s, sizeof(_t)); } while (0)

#define Stream_Read_UINT8(_s, _v) _stream_read_n8(UINT8, _s, _v, TRUE)

static inline BYTE* Stream_Pointer(wStream* _s)
{
	return _s->pointer;
}

static inline size_t Stream_GetRemainingLength(wStream* _s)
{
	return (_s->length - (_s->pointer - _s->buffer));
}

/* ---- freerdp/codec/bulk.h ---- */
#define PACKET_COMPRESSED 0x20

/* ============================================================
 * Everything below this point is copied verbatim from the
 * vulnerable libfreerdp/codec/zgfx.c (commit d1112c279bd1a327e8e4d0b5f371458bf2579659)
 * -- the ZGFX_TOKEN table, ZGFX_CONTEXT struct, and every callee on
 * zgfx_decompress_segment's crash path -- so its body needs zero edits.
 * ============================================================ */

struct _ZGFX_TOKEN
{
	UINT32 prefixLength;
	UINT32 prefixCode;
	UINT32 valueBits;
	UINT32 tokenType;
	UINT32 valueBase;
};
typedef struct _ZGFX_TOKEN ZGFX_TOKEN;

struct _ZGFX_CONTEXT
{
	BOOL Compressor;

	const BYTE* pbInputCurrent;
	const BYTE* pbInputEnd;

	UINT32 bits;
	UINT32 cBitsRemaining;
	UINT32 BitsCurrent;
	UINT32 cBitsCurrent;

	BYTE OutputBuffer[65536];
	UINT32 OutputCount;

	BYTE HistoryBuffer[2500000];
	UINT32 HistoryIndex;
	UINT32 HistoryBufferSize;
};
typedef struct _ZGFX_CONTEXT ZGFX_CONTEXT;

static const ZGFX_TOKEN ZGFX_TOKEN_TABLE[] =
{
	// len code vbits type  vbase
	{  1,    0,   8,   0,           0 },    // 0
	{  5,   17,   5,   1,           0 },    // 10001
	{  5,   18,   7,   1,          32 },    // 10010
	{  5,   19,   9,   1,         160 },    // 10011
	{  5,   20,  10,   1,         672 },    // 10100
	{  5,   21,  12,   1,        1696 },    // 10101
	{  5,   24,   0,   0,  0x00       },    // 11000
	{  5,   25,   0,   0,  0x01       },    // 11001
	{  6,   44,  14,   1,        5792 },    // 101100
	{  6,   45,  15,   1,       22176 },    // 101101
	{  6,   52,   0,   0,  0x02       },    // 110100
	{  6,   53,   0,   0,  0x03       },    // 110101
	{  6,   54,   0,   0,  0xFF       },    // 110110
	{  7,   92,  18,   1,       54944 },    // 1011100
	{  7,   93,  20,   1,      317088 },    // 1011101
	{  7,  110,   0,   0,  0x04       },    // 1101110
	{  7,  111,   0,   0,  0x05       },    // 1101111
	{  7,  112,   0,   0,  0x06       },    // 1110000
	{  7,  113,   0,   0,  0x07       },    // 1110001
	{  7,  114,   0,   0,  0x08       },    // 1110010
	{  7,  115,   0,   0,  0x09       },    // 1110011
	{  7,  116,   0,   0,  0x0A       },    // 1110100
	{  7,  117,   0,   0,  0x0B       },    // 1110101
	{  7,  118,   0,   0,  0x3A       },    // 1110110
	{  7,  119,   0,   0,  0x3B       },    // 1110111
	{  7,  120,   0,   0,  0x3C       },    // 1111000
	{  7,  121,   0,   0,  0x3D       },    // 1111001
	{  7,  122,   0,   0,  0x3E       },    // 1111010
	{  7,  123,   0,   0,  0x3F       },    // 1111011
	{  7,  124,   0,   0,  0x40       },    // 1111100
	{  7,  125,   0,   0,  0x80       },    // 1111101
	{  8,  188,  20,   1,     1365664 },    // 10111100
	{  8,  189,  21,   1,     2414240 },    // 10111101
	{  8,  252,   0,   0,  0x0C       },    // 11111100
	{  8,  253,   0,   0,  0x38       },    // 11111101
	{  8,  254,   0,   0,  0x39       },    // 11111110
	{  8,  255,   0,   0,  0x66       },    // 11111111
	{  9,  380,  22,   1,     4511392 },    // 101111100
	{  9,  381,  23,   1,     8705696 },    // 101111101
	{  9,  382,  24,   1,    17094304 },    // 101111110
	{ 0 }
};

static inline BOOL zgfx_GetBits(ZGFX_CONTEXT* _zgfx, UINT32 _nbits)
{
	if (!_zgfx)
		return FALSE;

	while (_zgfx->cBitsCurrent < _nbits)
	{
		_zgfx->BitsCurrent <<= 8;

		if (_zgfx->pbInputCurrent < _zgfx->pbInputEnd)
			_zgfx->BitsCurrent += *(_zgfx->pbInputCurrent)++;

		_zgfx->cBitsCurrent += 8;
	}

	_zgfx->cBitsRemaining -= _nbits;
	_zgfx->cBitsCurrent -= _nbits;
	_zgfx->bits = _zgfx->BitsCurrent >> _zgfx->cBitsCurrent;
	_zgfx->BitsCurrent &= ((1 << _zgfx->cBitsCurrent) - 1);
}

static void zgfx_history_buffer_ring_write(ZGFX_CONTEXT* zgfx, const BYTE* src, size_t count)
{
	UINT32 front;

	if (count <= 0)
		return;

	if (count > zgfx->HistoryBufferSize)
	{
		const size_t residue = count - zgfx->HistoryBufferSize;
		count = zgfx->HistoryBufferSize;
		src += residue;
		zgfx->HistoryIndex = (zgfx->HistoryIndex + residue) % zgfx->HistoryBufferSize;
	}

	if (zgfx->HistoryIndex + count <= zgfx->HistoryBufferSize)
	{
		CopyMemory(&(zgfx->HistoryBuffer[zgfx->HistoryIndex]), src, count);

		if ((zgfx->HistoryIndex += count) == zgfx->HistoryBufferSize)
			zgfx->HistoryIndex = 0;
	}
	else
	{
		front = zgfx->HistoryBufferSize - zgfx->HistoryIndex;
		CopyMemory(&(zgfx->HistoryBuffer[zgfx->HistoryIndex]), src, front);
		CopyMemory(zgfx->HistoryBuffer, &src[front], count - front);
		zgfx->HistoryIndex = count - front;
	}
}

static void zgfx_history_buffer_ring_read(ZGFX_CONTEXT* zgfx, int offset, BYTE* dst, UINT32 count)
{
	UINT32 front;
	UINT32 index;
	UINT32 bytes;
	UINT32 valid;
	UINT32 bytesLeft;
	BYTE* dptr = dst;
	BYTE* origDst = dst;

	if (count <= 0)
		return;

	bytesLeft = count;
	index = (zgfx->HistoryIndex + zgfx->HistoryBufferSize - offset) % zgfx->HistoryBufferSize;
	bytes = MIN(bytesLeft, offset);

	if ((index + bytes) <= zgfx->HistoryBufferSize)
	{
		CopyMemory(dptr, &(zgfx->HistoryBuffer[index]), bytes);
	}
	else
	{
		front = zgfx->HistoryBufferSize - index;
		CopyMemory(dptr, &(zgfx->HistoryBuffer[index]), front);
		CopyMemory(&dptr[front], zgfx->HistoryBuffer, bytes - front);
	}

	if ((bytesLeft -= bytes) == 0)
		return;

	dptr += bytes;
	valid = bytes;

	do
	{
		bytes = valid;

		if (bytes > bytesLeft)
			bytes = bytesLeft;

		CopyMemory(dptr, origDst, bytes);
		dptr += bytes;
		valid <<= 1;
	}
	while ((bytesLeft -= bytes) > 0);
}

void zgfx_context_reset(ZGFX_CONTEXT* zgfx, BOOL flush)
{
	zgfx->HistoryIndex = 0;
}

ZGFX_CONTEXT* zgfx_context_new(BOOL Compressor)
{
	ZGFX_CONTEXT* zgfx;
	zgfx = (ZGFX_CONTEXT*) calloc(1, sizeof(ZGFX_CONTEXT));

	if (zgfx)
	{
		zgfx->Compressor = Compressor;
		zgfx->HistoryBufferSize = sizeof(zgfx->HistoryBuffer);
		zgfx_context_reset(zgfx, FALSE);
	}

	return zgfx;
}

void zgfx_context_free(ZGFX_CONTEXT* zgfx)
{
	free(zgfx);
}

/* ---- target function, pasted BYTE-FOR-BYTE from
 * data_cve/cve_06b5da99/target/original_function.c ---- */
static BOOL zgfx_decompress_segment(ZGFX_CONTEXT* zgfx, wStream* stream, size_t segmentSize)
{
	BYTE c;
	BYTE flags;
	UINT32 extra = 0;
	int opIndex;
	int haveBits;
	int inPrefix;
	UINT32 count;
	UINT32 distance;
	BYTE* pbSegment;
	size_t cbSegment = segmentSize - 1;

	if ((Stream_GetRemainingLength(stream) < segmentSize) || (segmentSize < 1))
		return FALSE;

	Stream_Read_UINT8(stream, flags); /* header (1 byte) */
	zgfx->OutputCount = 0;
	pbSegment = Stream_Pointer(stream);
	Stream_Seek(stream, cbSegment);

	if (!(flags & PACKET_COMPRESSED))
	{
		zgfx_history_buffer_ring_write(zgfx, pbSegment, cbSegment);
		CopyMemory(zgfx->OutputBuffer, pbSegment, cbSegment);
		zgfx->OutputCount = cbSegment;
		return TRUE;
	}

	zgfx->pbInputCurrent = pbSegment;
	zgfx->pbInputEnd = &pbSegment[cbSegment - 1];
	/* NumberOfBitsToDecode = ((NumberOfBytesToDecode - 1) * 8) - ValueOfLastByte */
	zgfx->cBitsRemaining = 8 * (cbSegment - 1) - *zgfx->pbInputEnd;
	zgfx->cBitsCurrent = 0;
	zgfx->BitsCurrent = 0;

	while (zgfx->cBitsRemaining)
	{
		haveBits = 0;
		inPrefix = 0;

		for (opIndex = 0; ZGFX_TOKEN_TABLE[opIndex].prefixLength != 0; opIndex++)
		{
			while (haveBits < ZGFX_TOKEN_TABLE[opIndex].prefixLength)
			{
				zgfx_GetBits(zgfx, 1);
				inPrefix = (inPrefix << 1) + zgfx->bits;
				haveBits++;
			}

			if (inPrefix == ZGFX_TOKEN_TABLE[opIndex].prefixCode)
			{
				if (ZGFX_TOKEN_TABLE[opIndex].tokenType == 0)
				{
					/* Literal */
					zgfx_GetBits(zgfx, ZGFX_TOKEN_TABLE[opIndex].valueBits);
					c = (BYTE)(ZGFX_TOKEN_TABLE[opIndex].valueBase + zgfx->bits);
					zgfx->HistoryBuffer[zgfx->HistoryIndex] = c;

					if (++zgfx->HistoryIndex == zgfx->HistoryBufferSize)
						zgfx->HistoryIndex = 0;

					zgfx->OutputBuffer[zgfx->OutputCount++] = c;
				}
				else
				{
					zgfx_GetBits(zgfx, ZGFX_TOKEN_TABLE[opIndex].valueBits);
					distance = ZGFX_TOKEN_TABLE[opIndex].valueBase + zgfx->bits;

					if (distance != 0)
					{
						/* Match */
						zgfx_GetBits(zgfx, 1);

						if (zgfx->bits == 0)
						{
							count = 3;
						}
						else
						{
							count = 4;
							extra = 2;
							zgfx_GetBits(zgfx, 1);

							while (zgfx->bits == 1)
							{
								count *= 2;
								extra++;
								zgfx_GetBits(zgfx, 1);
							}

							zgfx_GetBits(zgfx, extra);
							count += zgfx->bits;
						}

						zgfx_history_buffer_ring_read(zgfx, distance, &(zgfx->OutputBuffer[zgfx->OutputCount]), count);
						zgfx_history_buffer_ring_write(zgfx, &(zgfx->OutputBuffer[zgfx->OutputCount]), count);
						zgfx->OutputCount += count;
					}
					else
					{
						/* Unencoded */
						zgfx_GetBits(zgfx, 15);
						count = zgfx->bits;
						zgfx->cBitsRemaining -= zgfx->cBitsCurrent;
						zgfx->cBitsCurrent = 0;
						zgfx->BitsCurrent = 0;
						CopyMemory(&(zgfx->OutputBuffer[zgfx->OutputCount]), zgfx->pbInputCurrent, count);
						zgfx_history_buffer_ring_write(zgfx, zgfx->pbInputCurrent, count);
						zgfx->pbInputCurrent += count;
						zgfx->cBitsRemaining -= (8 * count);
						zgfx->OutputCount += count;
					}
				}

				break;
			}
		}
	}

	return TRUE;
}

/* ---- driver: read argv[1], derive zgfx_decompress_segment's arguments,
 * call it in isolation ---- */
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

	if (fsz < 5)
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
	 * File layout (attacker-controlled bytes -> zgfx_decompress_segment's
	 * arguments):
	 *   [0]     flags-control byte (PACKET_COMPRESSED bit forced clear
	 *           below, so the vulnerable uncompressed-segment CopyMemory
	 *           path is always the one taken)
	 *   [1..4]  little-endian UINT32 requested cbSegment (the overflow
	 *           amount an attacker asks the decoder to copy)
	 *   [5..]   unused (kept only so a fuzzer/seed can vary the file)
	 */
	unsigned char flagsByte = filebuf[0] & (unsigned char)~PACKET_COMPRESSED;
	UINT32 cbSegment = ((UINT32)filebuf[1]) | ((UINT32)filebuf[2] << 8) |
	                   ((UINT32)filebuf[3] << 16) | ((UINT32)filebuf[4] << 24);

	/* Clamp to a workable range: large enough that the "triggering" class
	 * can clear the whole ~2.57MB ZGFX_CONTEXT heap allocation, small
	 * enough that this stays a fast, modest-size test. */
	const UINT32 CAP = 4u * 1024u * 1024u; /* 4 MiB */
	cbSegment = cbSegment % CAP;

	size_t segmentSize = (size_t)cbSegment + 1;

	/* Mirrors the real zgfx_context_new()'s initialization. */
	ZGFX_CONTEXT* zgfx = zgfx_context_new(FALSE);
	if (!zgfx)
	{
		free(filebuf);
		return 0;
	}

	/* Address-space spacer: kept alive alongside zgfx/segBuf purely so the
	 * two big allocations below land far apart in the heap. Without it,
	 * ASAN's generic memcpy interceptor can (depending on allocator layout)
	 * report a spurious "memcpy-param-overlap" for a huge N before it ever
	 * reaches the real out-of-bounds write this harness is trying to
	 * observe, since |dst-src| < N is enough to trip that unrelated check
	 * even for two independent, non-overlapping allocations. This changes
	 * no target behavior -- it only pushes the segment buffer's address far
	 * enough from zgfx's that the two truly-disjoint allocations aren't
	 * misread as overlapping. */
	const size_t SPACER = 256u * 1024u * 1024u;
	void* spacer = malloc(SPACER);

	/* The raw segment byte stream zgfx_decompress_segment reads through
	 * `stream`: [flags][cbSegment content bytes]. Content bytes are
	 * irrelevant to this bug (only the LENGTH matters), so they are
	 * zero-filled rather than taken from the file. */
	unsigned char* segBuf = (unsigned char*)malloc(segmentSize);
	if (!segBuf)
	{
		free(spacer);
		zgfx_context_free(zgfx);
		free(filebuf);
		return 0;
	}
	segBuf[0] = flagsByte;
	if (cbSegment > 0)
		memset(segBuf + 1, 0, cbSegment);

	wStream stream;
	stream.buffer = segBuf;
	stream.pointer = segBuf;
	stream.length = segmentSize;
	stream.capacity = segmentSize;
	stream.count = 0;
	stream.pool = NULL;
	stream.isAllocatedStream = FALSE;
	stream.isOwner = FALSE;

	zgfx_decompress_segment(zgfx, &stream, segmentSize);

	free(spacer);
	zgfx_context_free(zgfx);
	free(segBuf);
	free(filebuf);
	return 0;
}
