/*
 * cve_barebone direct-call harness for freerdp / ntlm_read_message_fields_buffer
 *
 * Bug (fix commit 2ee663f39dc8dac3d9988e847db19b2d7e3ac8c6): the bounds check
 *
 *     if ((fields->BufferOffset + fields->Len) > Stream_Length(s))
 *
 * adds a UINT32 (BufferOffset) and a UINT16 (Len, promoted to UINT32) using
 * 32-bit unsigned arithmetic. If BufferOffset is close to UINT32_MAX, the sum
 * wraps around modulo 2^32 and can land <= Stream_Length(s) even though the
 * real (unwrapped) BufferOffset is far outside the stream. The check then
 * passes and the function does:
 *
 *     Stream_SetPosition(s, fields->BufferOffset);   // s->pointer = s->buffer + BufferOffset (huge)
 *     Stream_Read(s, fields->Buffer, fields->Len);    // memcpy() reads from that wild pointer
 *
 * -> an out-of-bounds / wild-pointer READ entirely inside
 *    ntlm_read_message_fields_buffer's own body. The fix widens the addition
 *    to UINT64 before comparing.
 *
 * All type/struct/callee definitions below are copied verbatim (real names,
 * unmodified) from:
 *   - winpr/include/winpr/wtypes.h.in  (BYTE/UINT16/UINT32/PBYTE/DWORD/BOOL aliases)
 *   - winpr/include/winpr/winpr.h      (INLINE macro, non-MSVC branch)
 *   - winpr/include/winpr/stream.h     (struct _wStream + Stream_Seek/Stream_Read/
 *                                        Stream_Length/Stream_SetPosition)
 *   - winpr/libwinpr/sspi/NTLM/ntlm.h  (struct _NTLM_MESSAGE_FIELDS)
 * ntlm_read_message_fields_buffer itself is pasted byte-for-byte from
 * data_cve/cve_5368104e/target/original_function.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- winpr/include/winpr/wtypes.h.in (verbatim aliases, non-Windows branch) ---- */
typedef uint8_t  __uint8;
typedef uint16_t __uint16;
typedef uint32_t __uint32;

typedef __uint8  BYTE;
typedef BYTE     byte, *PBYTE, *LPBYTE;

typedef __uint16 UINT16, *PUINT16;
typedef __uint32 UINT32, *PUINT32;

typedef __uint32 DWORD, DWORD32, *PDWORD, *LPDWORD, *PDWORD32;

typedef int32_t BOOL;

/* ---- winpr/include/winpr/winpr.h ---- */
#define INLINE inline

/* ---- winpr/include/winpr/stream.h (verbatim) ---- */
typedef struct _wStreamPool wStreamPool;

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

static INLINE void Stream_Seek(wStream* s, size_t _offset)
{
	s->pointer += (_offset);
}

static INLINE void Stream_Read(wStream* _s, void* _b, size_t _n)
{
	memcpy(_b, (_s->pointer), (_n));
	Stream_Seek(_s, _n);
}

static INLINE size_t Stream_Length(wStream* _s)
{
	return _s->length;
}

static INLINE void Stream_SetPosition(wStream* _s, size_t _p)
{
	_s->pointer = _s->buffer + (_p);
}

/* ---- winpr/libwinpr/sspi/NTLM/ntlm.h (verbatim) ---- */
struct _NTLM_MESSAGE_FIELDS
{
	UINT16 Len;
	UINT16 MaxLen;
	PBYTE Buffer;
	UINT32 BufferOffset;
};
typedef struct _NTLM_MESSAGE_FIELDS NTLM_MESSAGE_FIELDS;

/* ==== FUNCTION UNDER TEST (verbatim from target/original_function.c) ==== */
int ntlm_read_message_fields_buffer(wStream* s, NTLM_MESSAGE_FIELDS* fields)
{
	if (fields->Len > 0)
	{
		if ((fields->BufferOffset + fields->Len) > Stream_Length(s))
			return -1;

		fields->Buffer = (PBYTE) malloc(fields->Len);

		if (!fields->Buffer)
			return -1;

		Stream_SetPosition(s, fields->BufferOffset);
		Stream_Read(s, fields->Buffer, fields->Len);
	}

	return 1;
}
/* ==== END FUNCTION UNDER TEST ==== */

/*
 * Driver: reads a HEAP-allocated seed file.
 *   byte[0..1] -> fields.Len          (UINT16, little-endian)
 *   byte[2..5] -> fields.BufferOffset (UINT32, little-endian)
 * and calls ntlm_read_message_fields_buffer against a small heap-allocated
 * "received NTLM message" stream (mirrors the real caller: a wStream wrapping
 * the network-received message bytes, whose ->length is the real received
 * size). This reproduces the CVE exactly as it manifests at the call site:
 * attacker controls Len/BufferOffset (both come straight off the wire in the
 * real NTLM message header), Stream_Length(s) is the real, legitimate size of
 * the received buffer.
 */
#define STREAM_LEN 64

int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	FILE* f = fopen(argv[1], "rb");
	if (!f)
		return 0;

	fseek(f, 0, SEEK_END);
	long sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (sz < 6)
	{
		fclose(f);
		return 0;
	}

	unsigned char* buf = (unsigned char*) malloc((size_t) sz);
	if (!buf)
	{
		fclose(f);
		return 0;
	}
	size_t nread = fread(buf, 1, (size_t) sz, f);
	fclose(f);
	if (nread != (size_t) sz)
	{
		free(buf);
		return 0;
	}

	UINT16 len_val = (UINT16) (buf[0] | (buf[1] << 8));
	UINT32 bufoff_val = (UINT32) (buf[2] | (buf[3] << 8) | (buf[4] << 16) |
	                               ((UINT32) buf[5] << 24));
	free(buf);

	/* the "received NTLM message" -- heap allocated, ASAN-guarded */
	BYTE* msg = (BYTE*) malloc(STREAM_LEN);
	if (!msg)
		return 0;
	memset(msg, 0x41, STREAM_LEN);

	wStream s;
	memset(&s, 0, sizeof(s));
	s.buffer = msg;
	s.pointer = msg;
	s.length = STREAM_LEN;
	s.capacity = STREAM_LEN;

	NTLM_MESSAGE_FIELDS fields;
	memset(&fields, 0, sizeof(fields));
	fields.Len = len_val;
	fields.MaxLen = 0;
	fields.Buffer = NULL;
	fields.BufferOffset = bufoff_val;

	int rc = ntlm_read_message_fields_buffer(&s, &fields);
	(void) rc;

	if (fields.Buffer)
		free(fields.Buffer);
	free(msg);
	return 0;
}
