/* cve_barebone direct-call harness for CVE-2026-23948 (FreeRDP RDP server logon info)
 * Target: rdp_write_logon_info_v2  (libfreerdp/core/info.c)
 * Bug class: CWE-476 NULL-pointer dereference (READ), reachable entirely inside the target
 * function's own body: strnlen(info->domain, 256) / strnlen(info->username, 256) are called on
 * the info struct's domain/username fields with NO NULL check. The upstream fix
 * (4d44e3c097656a8b9ec696353647b0888ca45860) wraps both calls in "if (info->domain)" /
 * "if (info->username)" guards -- i.e. the two missing checks ARE the entire bug.
 *
 * Is a NULL domain/username realistic? Yes -- logon_info (include/freerdp/session.h) is a plain
 * `{ UINT32 sessionId; char* username; char* domain; }` populated by the RDP SERVER side before
 * sending a Save Session Info PDU (rdp_send_save_session_info -> rdp_write_logon_info_v2, via the
 * INFO_TYPE_LOGON_LONG branch). A server with no domain configured (a very common workgroup/
 * local-account deployment), or any code path that forgets to default domain/username to an empty
 * string, reaches this call with a NULL pointer -- exactly the class of bug the upstream fix
 * acknowledges by adding a plain NULL check, not some contrived harness-only state.
 *
 * struct rdp_logon_info (logon_info) is copied VERBATIM (include/freerdp/session.h). The wStream
 * writer helpers (Stream_EnsureRemainingCapacity/Stream_Write_UINT16/Stream_Write_UINT32/
 * Stream_Seek/Stream_Write_UTF16_String_From_UTF8) are real WinPR API names/signatures
 * (winpr/include/winpr/stream.h) with minimal faithful stand-in bodies -- they are OFF the crash
 * path (the crash fires at the very first strnlen(info->domain,...) call, before any stream write
 * happens, for a NULL-domain trigger) but must behave correctly for the SAFE inputs where domain/
 * username are both non-NULL, so this stand-in is an auto-growing heap buffer (real
 * Stream_EnsureCapacity's grow-by-doubling realloc body, just invoked a bit more eagerly than the
 * genuine caller-preallocates-once convention) -- never itself the source of a spurious overflow.
 * logonInfoV2Size / logonInfoV2ReservedSize / logonInfoV2TotalSize / SAVE_SESSION_PDU_VERSION_ONE
 * are copied VERBATIM (libfreerdp/core/info.c line 40-42 / info.h line 59).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

/* ---- real WinPR fixed-width type aliases (winpr/include/winpr/wtypes.h, verbatim values) ---- */
typedef uint8_t  BYTE;
typedef uint16_t WCHAR;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef int32_t  BOOL;
typedef ssize_t  SSIZE_T;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* ---- real struct layout: source_code/include/freerdp/session.h, VERBATIM ---- */
struct rdp_logon_info
{
	UINT32 sessionId;
	char* username;
	char* domain;
};
typedef struct rdp_logon_info logon_info;

/* ---- real macros: source_code/libfreerdp/core/info.c:40-42 / info.h:59, VERBATIM ---- */
#define logonInfoV2Size (2u + 4u + 4u + 4u + 4u)
#define logonInfoV2ReservedSize 558u
#define logonInfoV2TotalSize (logonInfoV2Size + logonInfoV2ReservedSize)
#define SAVE_SESSION_PDU_VERSION_ONE 0x0001

/* ---- wStream: real field layout (winpr/include/winpr/stream.h); the pool/count/isOwner/
 * isAllocatedStream bookkeeping fields are dropped -- rdp_write_logon_info_v2 never touches
 * them. ---- */
typedef struct
{
	BYTE* buffer;
	BYTE* pointer;
	size_t length;
	size_t capacity;
} wStream;

static size_t Stream_GetPosition(const wStream* s) { return (size_t)(s->pointer - s->buffer); }
static size_t Stream_Capacity(const wStream* s) { return s->capacity; }
static size_t Stream_GetRemainingCapacity(const wStream* s)
{
	return s->capacity - Stream_GetPosition(s);
}

/* Real Stream_New()-style init: always allocates up front so buffer/pointer are valid non-NULL
 * (winpr/libwinpr/utils/stream.c Stream_New). */
static void vb_stream_init(wStream* s, size_t size)
{
	s->buffer = (BYTE*)malloc(size ? size : 1);
	s->pointer = s->buffer;
	s->capacity = size ? size : 1;
	s->length = 0;
}

/* ---- Stream_EnsureCapacity / Stream_EnsureRemainingCapacity: real names+signatures
 * (winpr/libwinpr/utils/stream.c) -- grow-by-doubling realloc body matches the genuine
 * implementation (the isOwner/pool branch there is dropped: this harness's stream always owns
 * its own malloc'd buffer, exactly like every real caller that goes through Stream_New). ---- */
static BOOL Stream_EnsureCapacity(wStream* s, size_t size)
{
	if (s->capacity < size)
	{
		size_t position = Stream_GetPosition(s);
		size_t new_capacity = s->capacity ? s->capacity : 1;
		while (new_capacity < size)
			new_capacity *= 2;
		BYTE* new_buf = (BYTE*)realloc(s->buffer, new_capacity);
		if (!new_buf)
			return FALSE;
		s->buffer = new_buf;
		s->capacity = new_capacity;
		s->pointer = s->buffer + position;
	}
	return TRUE;
}

static BOOL Stream_EnsureRemainingCapacity(wStream* s, size_t size)
{
	if (Stream_GetPosition(s) + size > Stream_Capacity(s))
		return Stream_EnsureCapacity(s, Stream_Capacity(s) + size);
	return TRUE;
}

/* ---- Stream_Write_UINT16 / Stream_Write_UINT32: real names; little-endian store bodies match
 * winpr_Data_Write_UINT16/32's byte order (winpr/include/winpr/stream.h). ---- */
static void Stream_Write_UINT16(wStream* s, UINT16 v)
{
	s->pointer[0] = (BYTE)(v & 0xFF);
	s->pointer[1] = (BYTE)((v >> 8) & 0xFF);
	s->pointer += 2;
}

static void Stream_Write_UINT32(wStream* s, UINT32 v)
{
	s->pointer[0] = (BYTE)(v & 0xFF);
	s->pointer[1] = (BYTE)((v >> 8) & 0xFF);
	s->pointer[2] = (BYTE)((v >> 16) & 0xFF);
	s->pointer[3] = (BYTE)((v >> 24) & 0xFF);
	s->pointer += 4;
}

/* ---- Stream_Seek / Stream_Zero: real names+semantics (advance-only pointer bump / memset then
 * advance -- winpr/include/winpr/stream.h Stream_Seek/Stream_Fill/Stream_Zero). ---- */
static void Stream_Seek(wStream* s, size_t offset) { s->pointer += offset; }
static void Stream_Zero(wStream* s, size_t n)
{
	memset(s->pointer, 0, n);
	s->pointer += n;
}

/* ---- Stream_Write_UTF16_String_From_UTF8: real name+signature (winpr/include/winpr/stream.h).
 * Body is a minimal faithful stand-in (ASCII/Latin-1 widen instead of the real multi-byte UTF8
 * decoder ConvertUtf8NToWChar -- out of scope of this NULL-deref bug, and every domain/username
 * byte this harness ever feeds it is plain ASCII) that reproduces the real contract: writes up to
 * `length` converted WCHARs, then (if fill) zero-pads the rest of `wcharLength` WCHARs -- i.e. the
 * trailing NUL terminator -- and grows the stream itself so it can never be the source of a
 * spurious overflow on a SAFE run. ---- */
static SSIZE_T Stream_Write_UTF16_String_From_UTF8(wStream* s, size_t wcharLength, const char* src,
                                                     size_t length, BOOL fill)
{
	SSIZE_T rc = 0;
	if (length != 0)
	{
		if (!Stream_EnsureRemainingCapacity(s, wcharLength * sizeof(WCHAR)))
			return -1;
		WCHAR* str = (WCHAR*)s->pointer;
		size_t i;
		for (i = 0; i < length && i < wcharLength; i++)
			str[i] = (WCHAR)(unsigned char)src[i];
		rc = (SSIZE_T)i;
		Stream_Seek(s, (size_t)rc * sizeof(WCHAR));
	}
	if (fill)
	{
		if (!Stream_EnsureRemainingCapacity(s, (wcharLength - (size_t)rc) * sizeof(WCHAR)))
			return -1;
		Stream_Zero(s, (wcharLength - (size_t)rc) * sizeof(WCHAR));
	}
	return rc;
}

/* ======================================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_89ca4c64/target/original_function.c */
/* ======================================================================================== */
static BOOL rdp_write_logon_info_v2(wStream* s, logon_info* info)
{
	size_t domainLen = 0;
	size_t usernameLen = 0;

	if (!Stream_EnsureRemainingCapacity(s, logonInfoV2TotalSize))
		return FALSE;

	Stream_Write_UINT16(s, SAVE_SESSION_PDU_VERSION_ONE);
	/* [MS-RDPBCGR] 2.2.10.1.1.2 Logon Info Version 2 (TS_LOGON_INFO_VERSION_2)
	 * should be logonInfoV2TotalSize
	 * but even MS server 2019 sends logonInfoV2Size
	 */
	Stream_Write_UINT32(s, logonInfoV2Size);
	Stream_Write_UINT32(s, info->sessionId);
	domainLen = strnlen(info->domain, 256); /* lmcons.h UNLEN */
	if (domainLen >= UINT32_MAX / sizeof(WCHAR))
		return FALSE;
	Stream_Write_UINT32(s, (UINT32)(domainLen + 1) * sizeof(WCHAR));
	usernameLen = strnlen(info->username, 256); /* lmcons.h UNLEN */
	if (usernameLen >= UINT32_MAX / sizeof(WCHAR))
		return FALSE;
	Stream_Write_UINT32(s, (UINT32)(usernameLen + 1) * sizeof(WCHAR));
	Stream_Seek(s, logonInfoV2ReservedSize);
	if (Stream_Write_UTF16_String_From_UTF8(s, domainLen + 1, info->domain, domainLen, TRUE) < 0)
		return FALSE;
	if (Stream_Write_UTF16_String_From_UTF8(s, usernameLen + 1, info->username, usernameLen, TRUE) <
	    0)
		return FALSE;
	return TRUE;
}
/* ==== end verbatim target function ==== */

/* ---- driver -----------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded). Every field of the logon_info this
 * harness passes to rdp_write_logon_info_v2 -- whether domain/username are present (a real heap
 * string, ASAN-guarded) or left NULL, their content, and sessionId -- comes straight from the
 * input file's bytes:
 *   byte 0             : flags -- bit0 = domain present (0 => info->domain stays NULL),
 *                                  bit1 = username present (0 => info->username stays NULL)
 *   bytes 1..4          : sessionId, little-endian UINT32
 *   [if domain  present] 1 length byte L (mod 200), then L content bytes -> heap string, domain
 *   [if username present] 1 length byte L (mod 200), then L content bytes -> heap string, username
 * A file with the domain or username flag bit cleared reproduces the real, in-production trigger:
 * a caller (e.g. a server with no domain configured) that reaches rdp_write_logon_info_v2 with
 * that field still NULL. */

static char* vb_read_string(const unsigned char* ibuf, size_t n, size_t* pos)
{
	size_t len = 0;
	if (*pos < n)
	{
		len = ibuf[*pos] % 200;
		(*pos)++;
	}
	char* s = (char*)malloc(len + 1);
	if (!s)
		return NULL;
	size_t i;
	for (i = 0; i < len; i++)
	{
		unsigned char b = (*pos < n) ? ibuf[(*pos)++] : (unsigned char)('a' + (i % 26));
		if (b == 0)
			b = (unsigned char)('a' + (i % 26)); /* keep it a genuine length-L string */
		s[i] = (char)b;
	}
	s[len] = '\0';
	return s;
}

int main(int argc, char** argv)
{
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
	FILE* fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 64; }
	if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
	long fsz = ftell(fp);
	if (fsz < 0) { fclose(fp); return 64; }
	if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }

	size_t n = (size_t)fsz;
	unsigned char* ibuf = (unsigned char*)malloc(n ? n : 1);   /* HEAP input buffer, ASAN-guarded */
	if (!ibuf) { fclose(fp); return 64; }
	size_t got = n ? fread(ibuf, 1, n, fp) : 0;
	fclose(fp);
	(void)got;

	size_t pos = 0;
	unsigned char flags = (pos < n) ? ibuf[pos++] : 0;

	UINT32 sessionId = 0;
	for (int i = 0; i < 4; i++)
		sessionId |= (UINT32)((pos < n) ? ibuf[pos++] : 0) << (8 * i);

	logon_info info;
	memset(&info, 0, sizeof(info));
	info.sessionId = sessionId;
	info.domain = (flags & 0x1u) ? vb_read_string(ibuf, n, &pos) : NULL;
	info.username = (flags & 0x2u) ? vb_read_string(ibuf, n, &pos) : NULL;

	wStream s;
	vb_stream_init(&s, 64);

	/* Call through a volatile function pointer so this `static`, single-call-site function can't
	 * be inlined into main() and disappear as a distinct ASAN backtrace frame -- changes nothing
	 * about how it's called or its own bytes. */
	BOOL (*volatile vb_call)(wStream*, logon_info*) = rdp_write_logon_info_v2;
	(void)vb_call(&s, &info);

	/* Only reached on a SAFE run (a triggering run aborts inside the call above). */
	free(ibuf);
	free(info.domain);
	free(info.username);
	free(s.buffer);
	return 0;
}
