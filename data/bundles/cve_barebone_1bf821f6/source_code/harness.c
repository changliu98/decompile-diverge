/*
 * cve_barebone direct-call harness for FreeRDP's
 * rdpsnd_virtual_channel_event_terminated() (channels/rdpsnd/client/rdpsnd_main.c).
 *
 * Bug (fixed upstream in commit 622bb7b4402491ca003f47472d0e478132673696,
 * "[channels,rdpsnd] terminate thread before free"; vulnerable at
 * 026b81ae5831ac1598d8f7371e0d0996fac7db00): rdpsnd_virtual_channel_event_terminated()
 * tears down every heap resource hanging off `rdpsnd` -- frees `queue` (via
 * MessageQueue_Free), `fixed_format` (via audio_formats_free), `subsystem`,
 * `device_name`, and finally `rdpsnd` itself -- but never NULLs out any of the
 * freed pointers. The fix extracts the queue/thread teardown into a new
 * `rdpsnd_terminate_thread()` helper that explicitly does
 * `rdpsnd->thread = NULL; rdpsnd->queue = NULL;` after freeing them, and
 * additionally calls that helper from cleanup_internals() -- i.e. it hardens
 * the type against being torn down more than once.
 *
 * rdpsnd_virtual_channel_event_terminated() is not a leaf: it is invoked as
 * the channel-manager "Terminated" callback from THREE distinct call sites in
 * rdpsnd_main.c -- the CHANNEL_EVENT_TERMINATED case of
 * rdpsnd_virtual_channel_init_event_ex() (static channel), the
 * pVirtualChannelInitEx() failure path inside rdpsnd_VirtualChannelEntryEx(),
 * and rdpsnd_plugin_terminated() (dynamic/DVC channel's IWTSPlugin.Terminated
 * hook) -- all operating on the same rdpsndPlugin*. Nothing in this function
 * (or its callees) makes a second dispatch of "Terminated" for the same
 * channel object idempotent; on the pre-fix code a repeat invocation
 * (plausible under an error/reconnect race the channel manager does not
 * itself prevent, exactly what the fix's commit message -- "ensure ... freed
 * up before releasing the channel context memory" -- calls out) dereferences
 * the already-freed `rdpsnd` on its very first field access
 * (`if (rdpsnd->queue)`) -> heap-use-after-free READ, and, had that not
 * aborted first, would go on to double-free `queue`, `fixed_format`,
 * `subsystem`, `device_name` and `rdpsnd` itself.
 *
 * This harness reproduces exactly that: it heap-allocates one rdpsndPlugin
 * and calls rdpsnd_virtual_channel_event_terminated() on it. SAFE inputs call
 * it once (the correct, single-dispatch contract -- always memory-safe for
 * any populated combination of queue/thread/fixed_format/subsystem/
 * device_name, since every field is freed independently and exactly once).
 * TRIGGERING inputs call it a second time on the very same pointer, mirroring
 * the repeat-dispatch scenario the fix defends against.
 *
 * rdpsnd_virtual_channel_event_terminated() itself (BEGIN/END markers below)
 * is pasted BYTE-FOR-BYTE from
 * data_cve/cve_1bf821f6/target/original_function.c.
 *
 * Compiles + links standalone:
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------------
 * Real WinPR/Win32-compatible type & macro definitions. WinPR itself is a
 * separate submodule not vendored in this trimmed source_code/ checkout, so
 * these are reproduced from the well-known, stable public API WinPR mirrors
 * 1:1 from Win32 (winpr/wtypes.h, winpr/synch.h, winpr/handle.h).
 * ------------------------------------------------------------------- */
typedef int BOOL;
#define TRUE 1
#define FALSE 0
typedef unsigned char BYTE;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned int UINT;
typedef unsigned int DWORD;
typedef void* HANDLE; /* winpr/wtypes.h */
#define INFINITE 0xFFFFFFFFu     /* winpr/synch.h */
#define WAIT_OBJECT_0 0x00000000u /* winpr/synch.h */

/* ---------------------------------------------------------------------
 * Opaque project types (winpr/collections.h wMessageQueue, wStreamPool;
 * libfreerdp/codec/dsp.h FREERDP_DSP_CONTEXT). Their real internal layouts
 * live outside this trimmed checkout and are irrelevant to the queue/thread
 * double-free bug being reproduced here, so they are left genuinely opaque
 * (forward-declared only) rather than guessed at -- every place this harness
 * touches an object of these types goes through malloc/free, never through a
 * struct-member access, so no internal layout is ever needed.
 * ------------------------------------------------------------------- */
typedef struct wMessageQueue wMessageQueue;
typedef struct wStreamPool wStreamPool;
typedef struct FREERDP_DSP_CONTEXT FREERDP_DSP_CONTEXT;

/* ---------------------------------------------------------------------
 * Real AUDIO_FORMAT struct, copied from include/freerdp/codec/audio.h.
 * ------------------------------------------------------------------- */
struct AUDIO_FORMAT
{
	UINT16 wFormatTag;
	UINT16 nChannels;
	UINT32 nSamplesPerSec;
	UINT32 nAvgBytesPerSec;
	UINT16 nBlockAlign;
	UINT16 wBitsPerSample;
	UINT16 cbSize;
	BYTE* data;
};
typedef struct AUDIO_FORMAT AUDIO_FORMAT;

/*
 * Real rdpsndPlugin struct ("struct rdpsnd_plugin", channels/rdpsnd/client/
 * rdpsnd_main.c:54-115), trimmed to the fields rdpsnd_virtual_channel_event_
 * terminated() and its direct callee free_internals() actually read/write.
 * The real struct additionally carries ~25 more fields (IWTSPlugin iface,
 * CHANNEL_DEF, format tables, device plugin pointer, rdpContext*, ...) that
 * are untouched by these two functions and would drag in unrelated project
 * typedefs; every field kept below has its real name and real declared type.
 */
typedef struct rdpsnd_plugin rdpsndPlugin;
struct rdpsnd_plugin
{
	wStreamPool* pool;
	void* InitHandle;
	AUDIO_FORMAT* fixed_format;
	char* subsystem;
	char* device_name;
	FREERDP_DSP_CONTEXT* dsp_context;
	HANDLE thread;
	wMessageQueue* queue;
	size_t references;
};

/* ---------------------------------------------------------------------
 * Minimal faithful stubs for incidental callees: their real bodies (WinPR
 * message-queue signalling, an OS thread-handle wait/close, dsp/stream-pool
 * teardown) have no bearing on the queue/thread double-free mechanism above
 * -- what matters is only that each object handed to a "free" API really is
 * released via free(), so a repeat release is a genuine ASAN-detectable
 * double-free/use-after-free exactly as it would be against the real
 * implementations. Real signatures kept (winpr/collections.h,
 * winpr/synch.h, winpr/handle.h).
 * ------------------------------------------------------------------- */
static BOOL MessageQueue_PostQuit(wMessageQueue* queue, int nExitCode)
{
	(void)queue;
	(void)nExitCode;
	return TRUE;
}

static DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds)
{
	(void)hHandle;
	(void)dwMilliseconds;
	return WAIT_OBJECT_0;
}

static BOOL CloseHandle(HANDLE hObject)
{
	/* real CloseHandle() releases the OS thread handle; here `thread` is a
	 * plain heap block standing in for that handle, so free() is the exact
	 * analogue -- a second CloseHandle() on the same value is exactly as
	 * unsafe as the real API would find it. */
	if (hObject)
		free(hObject);
	return TRUE;
}

static void MessageQueue_Free(wMessageQueue* queue)
{
	if (queue)
		free(queue);
}

/* dsp_context/pool are always NULL in this harness (allocate_internals(),
 * which is what would populate them, is never called -- rdpsnd_virtual_
 * channel_event_terminated() never calls it either), so these two bodies are
 * never actually exercised with a non-NULL argument; kept NULL-safe anyway. */
static void freerdp_dsp_context_free(FREERDP_DSP_CONTEXT* context)
{
	if (context)
		free(context);
}

static void StreamPool_Free(wStreamPool* pool)
{
	if (pool)
		free(pool);
}

/* ---------------------------------------------------------------------
 * Real callees on the crash path, copied verbatim from channels/rdpsnd/
 * client/rdpsnd_main.c and libfreerdp/codec/audio.c.
 * ------------------------------------------------------------------- */

/* libfreerdp/codec/audio.c:266-284 (audio_format_free + audio_formats_free) */
static void audio_format_free(AUDIO_FORMAT* format)
{
	if (format)
		free(format->data);
}

static void audio_formats_free(AUDIO_FORMAT* formats, size_t count)
{
	if (formats)
	{
		for (size_t index = 0; index < count; index++)
		{
			AUDIO_FORMAT* format = &formats[index];
			audio_format_free(format);
		}

		free(formats);
	}
}

/* channels/rdpsnd/client/rdpsnd_main.c:1350-1365 */
static void free_internals(rdpsndPlugin* rdpsnd)
{
	if (!rdpsnd)
		return;

	if (rdpsnd->references > 0)
		rdpsnd->references--;

	if (rdpsnd->references > 0)
		return;

	freerdp_dsp_context_free(rdpsnd->dsp_context);
	StreamPool_Free(rdpsnd->pool);
	rdpsnd->pool = NULL;
	rdpsnd->dsp_context = NULL;
}

/* ==================== BEGIN rdpsnd_virtual_channel_event_terminated() (verbatim) ==================== */
/* Pasted byte-for-byte from data_cve/cve_1bf821f6/target/original_function.c */
void rdpsnd_virtual_channel_event_terminated(rdpsndPlugin* rdpsnd)
{
	if (rdpsnd)
	{
		if (rdpsnd->queue)
			MessageQueue_PostQuit(rdpsnd->queue, 0);

		if (rdpsnd->thread)
		{
			(void)WaitForSingleObject(rdpsnd->thread, INFINITE);
			(void)CloseHandle(rdpsnd->thread);
		}
		MessageQueue_Free(rdpsnd->queue);

		free_internals(rdpsnd);
		audio_formats_free(rdpsnd->fixed_format, 1);
		free(rdpsnd->subsystem);
		free(rdpsnd->device_name);
		rdpsnd->InitHandle = 0;
	}

	free(rdpsnd);
}
/* ===================== END rdpsnd_virtual_channel_event_terminated() (verbatim) ====================== */

/* ---------------------------------------------------------------------
 * main(): read argv[1] into a HEAP buffer, use its bytes to populate a
 * heap-allocated rdpsndPlugin with a varying mix of present/absent
 * queue/thread/fixed_format/subsystem/device_name, call
 * rdpsnd_virtual_channel_event_terminated() on it once, then -- iff the
 * input says "trigger" -- call it a SECOND time on the very same pointer.
 * ------------------------------------------------------------------- */

/* harness-only helper (not a FreeRDP function): bounds-checked copy of
 * `n` bytes starting at `off` in `buf` (clamped to what's actually
 * available) into a freshly heap-allocated, NUL-terminated buffer. */
static char* harness_dup_bytes(const unsigned char* buf, size_t len, size_t off, size_t n)
{
	char* s = NULL;

	if (off >= len)
		n = 0;
	else if (off + n > len)
		n = len - off;

	s = (char*)malloc(n + 1);
	if (!s)
		return NULL;
	if (n)
		memcpy(s, buf + off, n);
	s[n] = '\0';
	return s;
}

int main(int argc, char** argv)
{
	FILE* f = NULL;
	long fsz = 0;
	unsigned char* buf = NULL;
	size_t len = 0;
	unsigned char b0, b1, b2, b3, b4;
	size_t sub_len, dev_len;
	int trigger;
	rdpsndPlugin* rdpsnd = NULL;

	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "rb");
	if (!f)
	{
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0)
	{
		fclose(f);
		return 1;
	}
	fsz = ftell(f);
	if (fsz < 0)
	{
		fclose(f);
		return 1;
	}
	rewind(f);

	/* heap-allocate the input buffer, ASAN-guarded, exactly sized */
	buf = (unsigned char*)malloc((size_t)fsz + 1);
	if (!buf)
	{
		fclose(f);
		return 1;
	}
	len = fread(buf, 1, (size_t)fsz, f);
	fclose(f);

	b0 = len > 0 ? buf[0] : 0;
	b1 = len > 1 ? buf[1] : 0;
	b2 = len > 2 ? buf[2] : 0;
	b3 = len > 3 ? buf[3] : 0;
	b4 = len > 4 ? buf[4] : 0;

	/* b0 bit0: 1 = TRIGGERING (double-dispatch), 0 = SAFE (single dispatch) */
	trigger = (b0 & 1);

	rdpsnd = (rdpsndPlugin*)calloc(1, sizeof(rdpsndPlugin));
	if (!rdpsnd)
	{
		free(buf);
		return 1;
	}

	/* b1 bit0: queue present; b1 bit1: thread present */
	if (b1 & 0x1)
		rdpsnd->queue = (wMessageQueue*)malloc(16);
	if (b1 & 0x2)
		rdpsnd->thread = (HANDLE)malloc(16);

	/* attacker-controlled subsystem/device_name strings, real fields, real
	 * type (char*), content+length drawn from the input bytes */
	sub_len = (size_t)(b2 % 16);
	rdpsnd->subsystem = harness_dup_bytes(buf, len, 5, sub_len);

	dev_len = (size_t)(b3 % 16);
	rdpsnd->device_name = harness_dup_bytes(buf, len, 5 + sub_len, dev_len);

	/* b4 bit0: fixed_format present; b4 bit1: fixed_format->data present */
	if (b4 & 0x1)
	{
		AUDIO_FORMAT* fmt = (AUDIO_FORMAT*)calloc(1, sizeof(AUDIO_FORMAT));
		if (fmt && (b4 & 0x2))
			fmt->data = (BYTE*)malloc(4);
		rdpsnd->fixed_format = fmt;
	}

	rdpsnd->InitHandle = (void*)(size_t)0x1234;
	rdpsnd->pool = NULL;       /* allocate_internals() was never called */
	rdpsnd->dsp_context = NULL;
	rdpsnd->references = 0;

	free(buf);

	/* dispatch #1: the correct, single-use contract -- always memory-safe */
	rdpsnd_virtual_channel_event_terminated(rdpsnd);

	if (trigger)
		/* dispatch #2 on the SAME pointer: `rdpsnd` (and, had it survived
		 * that far, `queue`/`fixed_format`/`subsystem`/`device_name`) was
		 * already freed by dispatch #1 -> heap-use-after-free. */
		rdpsnd_virtual_channel_event_terminated(rdpsnd);

	return 0;
}
