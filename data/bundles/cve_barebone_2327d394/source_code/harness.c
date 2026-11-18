/* cve_barebone direct-call harness for cve_2327d394 (FreeRDP, CVE-2026-24683)
 * Target: ainput_send_input_event  (channels/ainput/client/ainput_main.c)
 * Bug class: heap-use-after-free (CWE-416) reading GENERIC_CHANNEL_CALLBACK::channel through a
 * stale AINPUT_PLUGIN::base.listener_callback->channel_callback pointer that ainput_on_close()
 * frees without ever clearing (fix commit d9ca272dce7a776ab475e9b1a8e8c3d2968c8486 adds a lock
 * around both sides). See the module docstring of scripts/gen_dc_cve_2327d394.py for the full
 * mechanism, the exact crash statement, and the provenance of every real name below.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <assert.h>

/* ==== subset of winpr/wtypes.h's POSIX-branch (!_WIN32) fixed-width typedefs (verbatim
 * values/aliases: BOOL=int32_t, TRUE/FALSE=stdbool true/false, BYTE=uint8_t, UINT/ULONG/
 * DWORD=uint32_t, UINT16=uint16_t, UINT64/ULONGLONG=uint64_t, INT32=int32_t) -- only the
 * names ainput_send_input_event's own call graph actually uses. ==== */
typedef int32_t BOOL;
#define FALSE false
#define TRUE true
typedef uint8_t BYTE;
typedef uint32_t UINT;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef int32_t INT32;
typedef uint32_t ULONG;
typedef uint32_t DWORD;
typedef uint64_t ULONGLONG;

/* ==== winpr/assert-api.h WINPR_ASSERT: real default (non-WITH_VERBOSE_WINPR_ASSERT) expansion
 * is plain assert(cond); the pragma-push/Coverity-annotation wrapping around it is a no-op on
 * any real compiler. ==== */
#define WINPR_ASSERT(cond) assert(cond)

/* ==== winpr/stream.h line 39 + 41-52: wStreamPool fwd-decl (opaque; wStream::pool is never
 * dereferenced) + wStream (verbatim) ==== */
typedef struct s_wStreamPool wStreamPool;
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

/* ==== freerdp/dvc.h lines 65-153: the six DVC interface structs (verbatim). wStream must
 * precede this block: s_IWTSVirtualChannelCallback::OnDataReceived takes a `wStream* data`. ==== */
	typedef struct s_IWTSVirtualChannelManager IWTSVirtualChannelManager;
	typedef struct s_IWTSListener IWTSListener;
	typedef struct s_IWTSVirtualChannel IWTSVirtualChannel;

	typedef struct s_IWTSPlugin IWTSPlugin;
	typedef struct s_IWTSListenerCallback IWTSListenerCallback;
	typedef struct s_IWTSVirtualChannelCallback IWTSVirtualChannelCallback;

	struct s_IWTSListener
	{
		/* Retrieves the listener-specific configuration. */
		UINT (*GetConfiguration)(IWTSListener* pListener, void** ppPropertyBag);

		void* pInterface;
	};

	struct s_IWTSVirtualChannel
	{
		/* Starts a write request on the channel. */
		UINT(*Write)
		(IWTSVirtualChannel* pChannel, ULONG cbSize, const BYTE* pBuffer, void* pReserved);
		/* Closes the channel. */
		UINT (*Close)(IWTSVirtualChannel* pChannel);
	};

	struct s_IWTSVirtualChannelManager
	{
		/* Returns an instance of a listener object that listens on a specific
		   endpoint, or creates a static channel. */
		UINT(*CreateListener)
		(IWTSVirtualChannelManager* pChannelMgr, const char* pszChannelName, ULONG ulFlags,
		 IWTSListenerCallback* pListenerCallback, IWTSListener** ppListener);
		/* Find the channel or ID to send data to a specific endpoint. */
		UINT32 (*GetChannelId)(IWTSVirtualChannel* channel);
		IWTSVirtualChannel* (*FindChannelById)(IWTSVirtualChannelManager* pChannelMgr,
		                                       UINT32 ChannelId);
		const char* (*GetChannelName)(IWTSVirtualChannel* channel);
		UINT (*DestroyListener)(IWTSVirtualChannelManager* pChannelMgr, IWTSListener* ppListener);
	};

	struct s_IWTSPlugin
	{
		/* Used for the first call that is made from the client to the plug-in. */
		UINT (*Initialize)(IWTSPlugin* pPlugin, IWTSVirtualChannelManager* pChannelMgr);
		/* Notifies the plug-in that the Remote Desktop Connection (RDC) client
		   has successfully connected to the Remote Desktop Session Host (RD
		   Session Host) server. */
		UINT (*Connected)(IWTSPlugin* pPlugin);
		/* Notifies the plug-in that the Remote Desktop Connection (RDC) client
		   has disconnected from the RD Session Host server. */
		UINT (*Disconnected)(IWTSPlugin* pPlugin, DWORD dwDisconnectCode);
		/* Notifies the plug-in that the Remote Desktop Connection (RDC) client
		   has terminated. */
		UINT (*Terminated)(IWTSPlugin* pPlugin);

		UINT (*Attached)(IWTSPlugin* pPlugin);

		UINT (*Detached)(IWTSPlugin* pPlugin);

		/* Extended */

		void* pInterface;
	};

	struct s_IWTSListenerCallback
	{
		/* Accepts or denies a connection request for an incoming connection to
		   the associated listener. */
		UINT(*OnNewChannelConnection)
		(IWTSListenerCallback* pListenerCallback, IWTSVirtualChannel* pChannel, BYTE* Data,
		 BOOL* pbAccept, IWTSVirtualChannelCallback** ppCallback);

		void* pInterface;
	};

	struct s_IWTSVirtualChannelCallback
	{
		UINT(*OnDataReceived)
		(IWTSVirtualChannelCallback* pChannelCallback,
		 wStream* data); /**< Notifies the user about data that is being received. */
		UINT(*OnOpen)
		(IWTSVirtualChannelCallback*
		     pChannelCallback); /**< Notifies the user that the channel has been opened. */
		UINT(*OnClose)
		(IWTSVirtualChannelCallback*
		     pChannelCallback); /**< Notifies the user that the channel has been closed. */

		void* pInterface;
	};

typedef struct wLog wLog;           /* opaque; GENERIC_DYNVC_PLUGIN::log is never dereferenced */
typedef struct rdp_context rdpContext;     /* opaque fwd-decl, only appears in an unused fn-ptr
                                             * typedef's parameter list below (real name) */
typedef struct rdp_settings rdpSettings;   /* opaque fwd-decl, ditto */

/* ==== freerdp/client/channels.h lines 34-68: GENERIC_CHANNEL_CALLBACK / GENERIC_LISTENER_CALLBACK
 * / GENERIC_DYNVC_PLUGIN (verbatim) ==== */
	typedef struct
	{
		IWTSVirtualChannelCallback iface;
		IWTSPlugin* plugin;
		IWTSVirtualChannelManager* channel_mgr;
		IWTSVirtualChannel* channel;
	} GENERIC_CHANNEL_CALLBACK;

	typedef struct
	{
		IWTSListenerCallback iface;
		IWTSPlugin* plugin;
		IWTSVirtualChannelManager* channel_mgr;
		IWTSVirtualChannel* channel;
		GENERIC_CHANNEL_CALLBACK* channel_callback;
	} GENERIC_LISTENER_CALLBACK;

	typedef struct GENERIC_DYNVC_PLUGIN GENERIC_DYNVC_PLUGIN;
	typedef UINT (*DYNVC_PLUGIN_INIT_FN)(GENERIC_DYNVC_PLUGIN* plugin, rdpContext* context,
	                                     rdpSettings* settings);
	typedef void (*DYNVC_PLUGIN_TERMINATE_FN)(GENERIC_DYNVC_PLUGIN* plugin);

	struct GENERIC_DYNVC_PLUGIN
	{
		IWTSPlugin iface;
		GENERIC_LISTENER_CALLBACK* listener_callback;
		IWTSListener* listener;
		BOOL attached;
		BOOL initialized;
		wLog* log;
		char* dynvc_name;
		size_t channelCallbackSize;
		const IWTSVirtualChannelCallback* channel_callbacks;
		DYNVC_PLUGIN_TERMINATE_FN terminatePluginFn;
	};

/* ==== freerdp/channels/ainput.h lines 36-64: eAInputMsgType / AInputEventFlags enums, the
 * AInputClientContext forward-typedef, AINPUT_VERSION_MAJOR/MINOR (verbatim) ==== */
	typedef enum
	{
		MSG_AINPUT_VERSION = 0x01,
		MSG_AINPUT_MOUSE = 0x02
	} eAInputMsgType;

	typedef enum
	{
		AINPUT_FLAGS_WHEEL = 0x0001,
		AINPUT_FLAGS_MOVE = 0x0004,
		AINPUT_FLAGS_DOWN = 0x0008,

		AINPUT_FLAGS_REL = 0x0010,
		AINPUT_FLAGS_HAVE_REL = 0x0020,

		/* Pointer Flags */
		AINPUT_FLAGS_BUTTON1 = 0x1000, /* left */
		AINPUT_FLAGS_BUTTON2 = 0x2000, /* right */
		AINPUT_FLAGS_BUTTON3 = 0x4000, /* middle */

		/* Extended Pointer Flags */
		AINPUT_XFLAGS_BUTTON1 = 0x0100,
		AINPUT_XFLAGS_BUTTON2 = 0x0200
	} AInputEventFlags;

	typedef struct ainput_client_context AInputClientContext;

#define AINPUT_VERSION_MAJOR 1
#define AINPUT_VERSION_MINOR 0

/* ==== freerdp/client/ainput.h lines 33-42: pcAInputSendInputEvent + struct
 * ainput_client_context (verbatim) ==== */
	typedef UINT (*pcAInputSendInputEvent)(AInputClientContext* context, UINT64 flags, INT32 x,
	                                       INT32 y);

	struct ainput_client_context
	{
		void* handle;
		void* custom;

		pcAInputSendInputEvent AInputSendInputEvent;
	};

/* ==== channels/ainput/client/ainput_main.c lines 41-48: AINPUT_PLUGIN (verbatim) ==== */
typedef struct AINPUT_PLUGIN_ AINPUT_PLUGIN;
struct AINPUT_PLUGIN_
{
	GENERIC_DYNVC_PLUGIN base;
	AInputClientContext* context;
	UINT32 MajorVersion;
	UINT32 MinorVersion;
};

/* ==== winpr/wtsapi.h: CHANNEL_RC_OK / CHANNEL_RC_UNSUPPORTED_VERSION (verbatim) ==== */
#define CHANNEL_RC_OK 0
#define CHANNEL_RC_UNSUPPORTED_VERSION 19

/* TAG / STREAM_TAG: the real macros (CHANNELS_TAG("ainput.client") / WINPR_TAG("wStream")) just
 * build a constant log-tag string; only ever handed to the discarded-argument WLog_* / backtrace
 * stand-ins below, so a literal is behaviorally exact. */
#define TAG "channels.ainput.client"
#define STREAM_TAG "com.winpr.stream"

/* winpr/wlog.h lines 42-48 (verbatim): log-level constants. Only WLOG_FATAL is referenced (by
 * Stream_GetRemainingCapacity/Stream_SealLength's dead error branches, as a plain int argument
 * to the winpr_log_backtrace stand-in below -- its value is never inspected). */
#define WLOG_TRACE 0
#define WLOG_DEBUG 1
#define WLOG_INFO 2
#define WLOG_WARN 3
#define WLOG_ERROR 4
#define WLOG_FATAL 5
#define WLOG_OFF 6

/* ==== WLog_WARN/WLog_VRB/WLog_FATAL + winpr_log_backtrace: minimal faithful stand-ins for
 * WinPR's logging backend (never on the crash path -- see module docstring). vb_wlog_stub is a
 * vararg FUNCTION (not a macro that drops its arguments), so callers' arguments -- including
 * ainput_flags_to_string(...) inside ainput_send_input_event's own WLog_VRB call -- are still
 * eagerly evaluated exactly as the real WLog_Print_dbg_tag(tag, level, line, file, func, fmt, ...)
 * call would; the text itself is simply never formatted/printed anywhere. ==== */
static void vb_wlog_stub(const char *tag, const char *fmt, ...)
{
	(void)tag;
	(void)fmt;
}
#define WLog_WARN(tag, ...) vb_wlog_stub((tag), __VA_ARGS__)
#define WLog_VRB(tag, ...) vb_wlog_stub((tag), __VA_ARGS__)
#define WLog_FATAL(tag, ...) vb_wlog_stub((tag), __VA_ARGS__)
static void winpr_log_backtrace(const char *tag, DWORD level, int depth)
{
	(void)tag;
	(void)level;
	(void)depth;
}

/* ==== winpr/endian.h: WINPR_ENDIAN_CAST is WINPR_CXX_COMPAT_CAST's real C-mode (non-
 * __cplusplus) expansion, a plain cast (winpr/cast.h: "#define WINPR_CXX_COMPAT_CAST(t, val)
 * (t)(val)"). winpr_Data_Write_UINT16/UINT32/UINT64/INT32 (verbatim little-endian byte writers,
 * the ones Stream_Write_UINT16/UINT64/INT32 below call). ==== */
#define WINPR_ENDIAN_CAST(t, val) ((t)(val))
	static inline void winpr_Data_Write_UINT16(void* d, UINT16 v)
	{
		WINPR_ASSERT(d);
		BYTE* b = WINPR_ENDIAN_CAST(BYTE*, d);
		b[0] = v & 0xFF;
		b[1] = (v >> 8) & 0xFF;
	}

	static inline void winpr_Data_Write_UINT32(void* d, UINT32 v)
	{
		WINPR_ASSERT(d);
		BYTE* b = WINPR_ENDIAN_CAST(BYTE*, d);
		winpr_Data_Write_UINT16(b, v & 0xFFFF);
		winpr_Data_Write_UINT16(b + 2, (v >> 16) & 0xFFFF);
	}

	static inline void winpr_Data_Write_UINT64(void* d, UINT64 v)
	{
		WINPR_ASSERT(d);
		BYTE* b = WINPR_ENDIAN_CAST(BYTE*, d);
		winpr_Data_Write_UINT32(b, v & 0xFFFFFFFF);
		winpr_Data_Write_UINT32(b + 4, (v >> 32) & 0xFFFFFFFF);
	}

	static inline void winpr_Data_Write_INT32(void* d, INT32 v)
	{
		WINPR_ASSERT(d);
		BYTE* b = WINPR_ENDIAN_CAST(BYTE*, d);
		winpr_Data_Write_UINT16(b, v & 0xFFFF);
		winpr_Data_Write_UINT16(b + 2, (v >> 16) & 0xFFFF);
	}

/* ==== winpr/libwinpr/crt/string.c lines 156-171: winpr_str_append (verbatim, real WINPR_API
 * body -- ainput_flags_to_string's only non-libc dependency). _snprintf is winpr/string.h's real
 * POSIX alias for snprintf. ==== */
#define _snprintf snprintf
BOOL winpr_str_append(const char* what, char* buffer, size_t size, const char* separator)
{
	const size_t used = strnlen(buffer, size);
	const size_t add = strnlen(what, size);
	const size_t sep_len = separator ? strnlen(separator, size) : 0;
	const size_t sep = (used > 0) ? sep_len : 0;

	if (used + add + sep >= size)
		return FALSE;

	if ((used > 0) && (sep_len > 0))
		strncat(buffer, separator, sep_len);

	strncat(buffer, what, add);
	return TRUE;
}

/* ==== channels/ainput/common/ainput_common.h lines 28-57: ainput_flags_to_string (verbatim,
 * real callee on ainput_send_input_event's WLog_VRB line -- see module docstring for why it is
 * eagerly evaluated regardless of the WLog_* stand-ins above). ==== */
static inline const char* ainput_flags_to_string(UINT64 flags, char* buffer, size_t size)
{
	char number[32] = { 0 };

	if (flags & AINPUT_FLAGS_HAVE_REL)
		winpr_str_append("AINPUT_FLAGS_HAVE_REL", buffer, size, "|");
	if (flags & AINPUT_FLAGS_WHEEL)
		winpr_str_append("AINPUT_FLAGS_WHEEL", buffer, size, "|");
	if (flags & AINPUT_FLAGS_MOVE)
		winpr_str_append("AINPUT_FLAGS_MOVE", buffer, size, "|");
	if (flags & AINPUT_FLAGS_DOWN)
		winpr_str_append("AINPUT_FLAGS_DOWN", buffer, size, "|");
	if (flags & AINPUT_FLAGS_REL)
		winpr_str_append("AINPUT_FLAGS_REL", buffer, size, "|");
	if (flags & AINPUT_FLAGS_BUTTON1)
		winpr_str_append("AINPUT_FLAGS_BUTTON1", buffer, size, "|");
	if (flags & AINPUT_FLAGS_BUTTON2)
		winpr_str_append("AINPUT_FLAGS_BUTTON2", buffer, size, "|");
	if (flags & AINPUT_FLAGS_BUTTON3)
		winpr_str_append("AINPUT_FLAGS_BUTTON3", buffer, size, "|");
	if (flags & AINPUT_XFLAGS_BUTTON1)
		winpr_str_append("AINPUT_XFLAGS_BUTTON1", buffer, size, "|");
	if (flags & AINPUT_XFLAGS_BUTTON2)
		winpr_str_append("AINPUT_XFLAGS_BUTTON2", buffer, size, "|");

	_snprintf(number, sizeof(number), "[0x%08" PRIx64 "]", flags);
	winpr_str_append(number, buffer, size, " ");

	return buffer;
}

/* ==== winpr/sysinfo.h: GetTickCount64 (real macro aliases winpr_GetTickCount64). The real body
 * reads CLOCK_MONOTONIC; the value only feeds a Stream_Write_UINT64 payload byte and a discarded
 * WLog_VRB argument, no bearing on the crash -- minimal faithful stand-in. ==== */
static ULONGLONG winpr_GetTickCount64(void)
{
	return 0x1234567890ULL;
}
#define GetTickCount64 winpr_GetTickCount64

/* ==== winpr/libwinpr/utils/stream.c lines 251-265: Stream_GetRemainingCapacity (verbatim). Its
 * `cur > capacity` branch is dead here (ainput_send_input_event writes 26 of 32 bytes) but must
 * still compile; it calls the WLog_FATAL/winpr_log_backtrace stand-ins above. ==== */
size_t Stream_GetRemainingCapacity(const wStream* _s)
{
	size_t cur = 0;
	WINPR_ASSERT(_s);
	WINPR_ASSERT(_s->buffer <= _s->pointer);
	cur = (size_t)(_s->pointer - _s->buffer);
	WINPR_ASSERT(cur <= _s->capacity);
	if (cur > _s->capacity)
	{
		WLog_FATAL(STREAM_TAG, "wStream API misuse: stream was written out of bounds");
		winpr_log_backtrace(STREAM_TAG, WLOG_FATAL, 20);
		return 0;
	}
	return (_s->capacity - cur);
}

/* ==== winpr/libwinpr/utils/stream.c lines 139-154: Stream_StaticInit (verbatim) ==== */
wStream* Stream_StaticInit(wStream* s, BYTE* buffer, size_t size)
{
	const wStream empty = { 0 };

	WINPR_ASSERT(s);
	WINPR_ASSERT(buffer);

	*s = empty;
	s->buffer = s->pointer = buffer;
	s->capacity = s->length = size;
	s->pool = NULL;
	s->count = 1;
	s->isAllocatedStream = FALSE;
	s->isOwner = FALSE;
	return s;
}

/* ==== winpr/stream.h lines 875-881 + 891-899: Stream_Write_UINT16 macro + _unchecked
 * (verbatim) ==== */
#define Stream_Write_UINT16(s, v)                \
	do                                           \
	{                                            \
		WINPR_ASSERT((v) <= UINT16_MAX);         \
		WINPR_ASSERT((v) >= 0);                  \
		Stream_Write_UINT16_unchecked((s), (v)); \
	} while (0)

	static inline void Stream_Write_UINT16_unchecked(wStream* _s, UINT16 _v)
	{
		WINPR_ASSERT(_s);
		WINPR_ASSERT(_s->pointer);
		WINPR_ASSERT(Stream_GetRemainingCapacity(_s) >= 2);

		winpr_Data_Write_UINT16(_s->pointer, _v);
		_s->pointer += 2;
	}

/* ==== winpr/stream.h lines 1093-1101: Stream_Write_UINT64 (verbatim) ==== */
	static inline void Stream_Write_UINT64(wStream* _s, UINT64 _v)
	{
		WINPR_ASSERT(_s);
		WINPR_ASSERT(_s->pointer);
		WINPR_ASSERT(Stream_GetRemainingCapacity(_s) >= 8);

		winpr_Data_Write_UINT64(_s->pointer, _v);
		_s->pointer += 8;
	}

/* ==== winpr/stream.h lines 983-989 + 999-1007: Stream_Write_INT32 macro + _unchecked
 * (verbatim) ==== */
#define Stream_Write_INT32(s, v)                \
	do                                          \
	{                                           \
		WINPR_ASSERT((v) <= INT32_MAX);         \
		WINPR_ASSERT((v) >= INT32_MIN);         \
		Stream_Write_INT32_unchecked((s), (v)); \
	} while (0)

	static inline void Stream_Write_INT32_unchecked(wStream* _s, INT32 _v)
	{
		WINPR_ASSERT(_s);
		WINPR_ASSERT(_s->pointer);
		WINPR_ASSERT(Stream_GetRemainingCapacity(_s) >= 4);

		winpr_Data_Write_INT32(_s->pointer, _v);
		_s->pointer += 4;
	}

/* ==== winpr/libwinpr/utils/stream.c lines 203-218: Stream_SealLength (verbatim; its
 * `cur > capacity` branch is likewise dead here) ==== */
void Stream_SealLength(wStream* _s)
{
	size_t cur = 0;
	WINPR_ASSERT(_s);
	WINPR_ASSERT(_s->buffer <= _s->pointer);
	cur = (size_t)(_s->pointer - _s->buffer);
	WINPR_ASSERT(cur <= _s->capacity);
	if (cur <= _s->capacity)
		_s->length = cur;
	else
	{
		WLog_FATAL(STREAM_TAG, "wStream API misuse: stream was written out of bounds");
		winpr_log_backtrace(STREAM_TAG, WLOG_FATAL, 20);
		_s->length = 0;
	}
}

/* ==== winpr/stream.h lines 1286-1290 + 1230-1234: Stream_Length / Stream_Buffer (verbatim) ==== */
	static inline size_t Stream_Length(const wStream* _s)
	{
		WINPR_ASSERT(_s);
		return _s->length;
	}
	static inline BYTE* Stream_Buffer(wStream* _s)
	{
		WINPR_ASSERT(_s);
		return _s->buffer;
	}

/* ============================================================================================
 * ainput_send_input_event -- VERBATIM, byte-for-byte from data_cve/cve_2327d394/target/
 * original_function.c. Do not edit anything below this banner.
 * ============================================================================================ */
static UINT ainput_send_input_event(AInputClientContext* context, UINT64 flags, INT32 x, INT32 y)
{
	AINPUT_PLUGIN* ainput = NULL;
	GENERIC_CHANNEL_CALLBACK* callback = NULL;
	BYTE buffer[32] = { 0 };
	UINT64 time = 0;
	wStream sbuffer = { 0 };
	wStream* s = Stream_StaticInit(&sbuffer, buffer, sizeof(buffer));

	WINPR_ASSERT(s);
	WINPR_ASSERT(context);

	time = GetTickCount64();
	ainput = (AINPUT_PLUGIN*)context->handle;
	WINPR_ASSERT(ainput);

	if (ainput->MajorVersion != AINPUT_VERSION_MAJOR)
	{
		WLog_WARN(TAG, "Unsupported channel version %" PRIu32 ".%" PRIu32 ", aborting.",
		          ainput->MajorVersion, ainput->MinorVersion);
		return CHANNEL_RC_UNSUPPORTED_VERSION;
	}
	callback = ainput->base.listener_callback->channel_callback;
	WINPR_ASSERT(callback);

	{
		char ebuffer[128] = { 0 };
		WLog_VRB(TAG, "sending timestamp=0x%08" PRIx64 ", flags=%s, %" PRId32 "x%" PRId32, time,
		         ainput_flags_to_string(flags, ebuffer, sizeof(ebuffer)), x, y);
	}

	/* Message type */
	Stream_Write_UINT16(s, MSG_AINPUT_MOUSE);

	/* Event data */
	Stream_Write_UINT64(s, time);
	Stream_Write_UINT64(s, flags);
	Stream_Write_INT32(s, x);
	Stream_Write_INT32(s, y);
	Stream_SealLength(s);

	/* ainput back what we have received. AINPUT does not have any message IDs. */
	WINPR_ASSERT(callback->channel);
	WINPR_ASSERT(callback->channel->Write);
	return callback->channel->Write(callback->channel, (ULONG)Stream_Length(s), Stream_Buffer(s),
	                                NULL);
}
/* ============================================================================================
 * Harness scaffolding (below this line only): builds the AINPUT_PLUGIN / GENERIC_LISTENER_
 * CALLBACK / GENERIC_CHANNEL_CALLBACK / IWTSVirtualChannel graph freerdp_generic_DVCPluginEntry
 * + the DVC core would have wired up, then either frees the GENERIC_CHANNEL_CALLBACK before the
 * call (== exactly what ainput_on_close's unguarded `free(callback);` does -- the trigger corpus
 * half) or leaves it live (the safe corpus half, exercised end-to-end through a real Write call).
 * ============================================================================================ */

/* Faithful minimal stand-in for the DRDYNVC transport backend behind IWTSVirtualChannel::Write
 * (wholly unrelated machinery to this CVE -- see module docstring). Reads every byte of the
 * Stream_Buffer/Stream_Length payload ainput_send_input_event hands it, so ASAN would also catch
 * any accidental OOB read on that side of a "safe" call. */
static UINT vb_channel_write(IWTSVirtualChannel *pChannel, ULONG cbSize, const BYTE *pBuffer,
                              void *pReserved)
{
	(void)pChannel;
	(void)pReserved;
	volatile BYTE sink = 0;
	for (ULONG i = 0; i < cbSize; i++)
		sink ^= pBuffer[i];
	(void)sink;
	return CHANNEL_RC_OK;
}

static UINT vb_channel_close(IWTSVirtualChannel *pChannel)
{
	(void)pChannel;
	return CHANNEL_RC_OK;
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	FILE *f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	fseek(f, 0, SEEK_END);
	long fsz = ftell(f);
	if (fsz < 0)
		fsz = 0;
	fseek(f, 0, SEEK_SET);

	/* Heap-allocate the attacker-controlled input (ASAN-guarded). */
	unsigned char *buf = (unsigned char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	size_t n = 0;
	if (fsz > 0 && buf)
		n = fread(buf, 1, (size_t)fsz, f);
	fclose(f);

	/* Input layout: byte[0] bit 0 selects trigger (1) vs safe (0); bytes[1..8] = flags
	 * (UINT64), bytes[9..12] = x (INT32), bytes[13..16] = y (INT32) -- all attacker-controlled
	 * and forwarded verbatim into ainput_send_input_event's own arguments, though (per the CVE
	 * mechanism above) only the mode bit governs whether the call crashes. */
	unsigned char mode = (n >= 1) ? buf[0] : 0;
	UINT64 flags = 0;
	INT32 x = 0, y = 0;
	if (n >= 9)
		memcpy(&flags, buf + 1, 8);
	if (n >= 13)
		memcpy(&x, buf + 9, 4);
	if (n >= 17)
		memcpy(&y, buf + 13, 4);

	/* Real DVC transport object (the fn only ever reaches it through a valid pointer, never
	 * allocates/frees it itself), wired to the write stand-in above. */
	IWTSVirtualChannel channel;
	channel.Write = vb_channel_write;
	channel.Close = vb_channel_close;

	/* GENERIC_CHANNEL_CALLBACK: the object ainput_on_close() frees in the real vulnerable
	 * code. Heap-allocated so ASAN tracks the free precisely. */
	GENERIC_CHANNEL_CALLBACK *cb = (GENERIC_CHANNEL_CALLBACK *)calloc(1, sizeof(*cb));
	if (!cb)
	{
		free(buf);
		return 0;
	}
	cb->channel = &channel;

	GENERIC_LISTENER_CALLBACK lcb;
	memset(&lcb, 0, sizeof(lcb));
	lcb.channel_callback = cb;

	AINPUT_PLUGIN ainput;
	memset(&ainput, 0, sizeof(ainput));
	ainput.base.listener_callback = &lcb;
	ainput.MajorVersion = AINPUT_VERSION_MAJOR; /* always pass the version gate, so every run
	                                              * reaches the callback access under test */
	ainput.MinorVersion = AINPUT_VERSION_MINOR;

	AInputClientContext ctx;
	memset(&ctx, 0, sizeof(ctx));
	ctx.handle = (void *)&ainput;
	ctx.AInputSendInputEvent = ainput_send_input_event;

	if (mode & 0x01)
	{
		/* TRIGGER: reproduce ainput_on_close()'s unguarded `free(callback);` racing ahead of
		 * this send -- lcb.channel_callback is left pointing at now-freed memory, exactly as
		 * the real close callback leaves it (it never clears the field, fix commit
		 * d9ca272dce7a776ab475e9b1a8e8c3d2968c8486 only adds a lock around both sides). */
		free(cb);
		(void)ainput_send_input_event(&ctx, flags, x, y);
	}
	else
	{
		/* SAFE: channel_callback stays live -- ainput_send_input_event runs end-to-end
		 * through a real Write call and returns cleanly. */
		(void)ainput_send_input_event(&ctx, flags, x, y);
		free(cb);
	}

	free(buf);
	return 0;
}
