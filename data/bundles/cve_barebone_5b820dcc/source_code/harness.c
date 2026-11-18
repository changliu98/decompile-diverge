/* cve_barebone direct-call harness for CVE-2026-24679 (freerdp)
 * Target: libusb_udev_select_interface  (channels/urbdrc/client/libusb/libusb_udevice.c)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * The fix (freerdp/freerdp@2d563a50be17c1b407ca448b1321378c0726dd31) adds
 *     if (InterfaceNumber >= MsConfig->NumInterfaces) return -2;
 * before the vulnerable code indexes `MsConfig->MsInterfaces[InterfaceNumber]`. The
 * attacker-controlled `InterfaceNumber` (a raw BYTE taken off the RDP USB-redirection
 * wire by the caller, urbdrc_process_udev_select_interface) is never checked against
 * how many interfaces the client's MSUSB_CONFIG_DESCRIPTOR actually has, so any
 * InterfaceNumber >= NumInterfaces reads one pointer-sized slot past the end of the
 * heap-allocated `MsInterfaces` pointer array -- the OOB happens on the very first
 * access, `MsInterfaces[InterfaceNumber]`, entirely inside the target function's own
 * body (before the value that was read is ever dereferenced).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------------
 * Minimal real type definitions the target function needs -- names/fields copied
 * verbatim from the vulnerable tree (source_code/):
 *   winpr/include/winpr/wlog.h                          (WLOG_* level constants)
 *   channels/urbdrc/common/msusb.h                       (MSUSB_*_DESCRIPTOR)
 *   channels/urbdrc/client/urbdrc_main.h                 (IUDEVICE, URBDRC_PLUGIN)
 *   channels/urbdrc/client/libusb/libusb_udevice.h        (UDEVICE)
 * URBDRC_PLUGIN / UDEVICE keep only the fields libusb_udev_select_interface actually
 * touches (urbdrc, MsConfig, libusb_handle, log) under their real names/types --
 * struct layout is entirely local to this translation unit (the target function was
 * compiled against exactly these definitions, in the same file), so the untouched
 * real fields (IWTSPlugin iface, wArrayList* request_queue, ...) -- which would drag
 * in the whole winpr/libusb/channel-manager type graph -- change nothing observable
 * by omitting them.
 * ------------------------------------------------------------------- */

typedef unsigned char BYTE;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef int BOOL;
typedef uint32_t DWORD;

#define WLOG_TRACE 0
#define WLOG_DEBUG 1
#define WLOG_INFO 2
#define WLOG_WARN 3
#define WLOG_ERROR 4
#define WLOG_FATAL 5

/* opaque winpr logger handle -- the target function only ever passes it through as a
 * pointer, never dereferences it */
typedef struct wLog wLog;

/* opaque libusb device handle -- same, only ever passed through */
typedef struct libusb_device_handle LIBUSB_DEVICE_HANDLE;

/* channels/urbdrc/common/msusb.h -- verbatim */
typedef struct
{
	UINT16 MaximumPacketSize;
	UINT32 MaximumTransferSize;
	UINT32 PipeFlags;
	UINT32 PipeHandle;
	BYTE bEndpointAddress;
	BYTE bInterval;
	BYTE PipeType;
	int InitCompleted;
} MSUSB_PIPE_DESCRIPTOR;

typedef struct
{
	UINT16 Length;
	UINT16 NumberOfPipesExpected;
	BYTE InterfaceNumber;
	BYTE AlternateSetting;
	UINT32 NumberOfPipes;
	UINT32 InterfaceHandle;
	BYTE bInterfaceClass;
	BYTE bInterfaceSubClass;
	BYTE bInterfaceProtocol;
	MSUSB_PIPE_DESCRIPTOR** MsPipes;
	int InitCompleted;
} MSUSB_INTERFACE_DESCRIPTOR;

typedef struct
{
	UINT16 wTotalLength;
	BYTE bConfigurationValue;
	UINT32 ConfigurationHandle;
	UINT32 NumInterfaces;
	MSUSB_INTERFACE_DESCRIPTOR** MsInterfaces;
	int InitCompleted;
	int MsOutSize;
} MSUSB_CONFIG_DESCRIPTOR;

/* channels/urbdrc/client/urbdrc_main.h -- real code only ever forward-declares this
 * (`typedef struct S_IUDEVICE IUDEVICE;`) and the target function only ever uses it
 * through a bare pointer cast `(UDEVICE*)idev`, so it stays incomplete here too. */
typedef struct S_IUDEVICE IUDEVICE;

/* real field name `log` kept (the only URBDRC_PLUGIN field the target touches) */
typedef struct
{
	wLog* log;
} URBDRC_PLUGIN;

/* real field names kept (the only UDEVICE fields the target touches) */
typedef struct
{
	LIBUSB_DEVICE_HANDLE* libusb_handle;
	MSUSB_CONFIG_DESCRIPTOR* MsConfig;
	URBDRC_PLUGIN* urbdrc;
} UDEVICE;

/* ---------------------------------------------------------------------
 * Minimal faithful stubs for callees NOT on the memory-safety bug's own crash path.
 * The OOB read (MsInterfaces[InterfaceNumber]) happens purely inside the target
 * function's own body and, when it faults, aborts the process immediately -- none of
 * these ever run on a triggering input. They only run on in-bounds ("safe") calls.
 * ------------------------------------------------------------------- */

/* real declaration (winpr/include/winpr/wlog.h) is a macro that expands to a
 * WLog_IsLevelActive guard + WLog_PrintTextMessage(...), which ultimately formats the
 * varargs with vsnprintf-family code. Replaced with a real variadic function that
 * actually formats into a local buffer with vsnprintf (an opaque libc call the
 * optimizer cannot prove is side-effect-free) and folds one byte of the result into a
 * `volatile` sink -- this is a closer functional stand-in for the real formatter (it
 * genuinely consumes every vararg, it just never writes them anywhere observable) and
 * it is what keeps -O1 from proving the whole call, and thus the load that computes
 * one of its vararg values, is dead and eliding it -- C requires the load to happen
 * when it is genuinely used, so this only restores the language-mandated evaluation
 * rather than adding a new one. */
static volatile unsigned char vb_dc_sink;

static void WLog_Print(wLog* log, DWORD level, const char* fmt, ...)
{
	(void)log;
	(void)level;
	char buffer[256];
	va_list ap;
	va_start(ap, fmt);
	int wrote = vsnprintf(buffer, sizeof(buffer), fmt, ap);
	va_end(ap);
	if (wrote > 0)
		vb_dc_sink ^= (unsigned char)buffer[0];
}

/* real signature (libusb.h): int libusb_set_interface_alt_setting(libusb_device_handle*,
 * int, int); -- off the crash path (only reached after a valid, in-bounds
 * MsInterfaces[InterfaceNumber] read found diff=1). Stub always "succeeds". */
static int libusb_set_interface_alt_setting(LIBUSB_DEVICE_HANDLE* dev_handle,
                                             int interface_number, int alternate_setting)
{
	(void)dev_handle;
	(void)interface_number;
	(void)alternate_setting;
	return 0;
}

/* real signature (libusb.h): const char* libusb_error_name(int); only reachable
 * inside log_libusb_result_'s dead `error < 0` branch, since the stub above always
 * returns 0. */
static const char* libusb_error_name(int error)
{
	(void)error;
	return "LIBUSB_SUCCESS";
}

/* real callee (channels/urbdrc/client/libusb/libusb_udevice.c): log_libusb_result_ /
 * the log_libusb_result(...) macro wrapping it. Off the crash path; minimal faithful
 * stub (drops the __func__/__FILE__/__LINE__ diagnostic plumbing, keeps the
 * error-code -> bool contract). */
static BOOL log_libusb_result_(wLog* log, DWORD lvl, const char* fmt, int error)
{
	(void)log;
	(void)lvl;
	(void)fmt;
	if (error < 0)
	{
		(void)libusb_error_name(error);
		return 1;
	}
	return 0;
}
#define log_libusb_result(log, lvl, fmt, error) log_libusb_result_((log), (lvl), (fmt), (error))

/* ==== VERBATIM from data_cve/cve_5b820dcc/target/original_function.c ==== */
static int libusb_udev_select_interface(IUDEVICE* idev, BYTE InterfaceNumber, BYTE AlternateSetting)
{
	int error = 0;
	int diff = 0;
	UDEVICE* pdev = (UDEVICE*)idev;
	URBDRC_PLUGIN* urbdrc = NULL;
	MSUSB_CONFIG_DESCRIPTOR* MsConfig = NULL;
	MSUSB_INTERFACE_DESCRIPTOR** MsInterfaces = NULL;

	if (!pdev || !pdev->urbdrc)
		return -1;

	urbdrc = pdev->urbdrc;
	MsConfig = pdev->MsConfig;

	if (MsConfig)
	{
		MsInterfaces = MsConfig->MsInterfaces;
		if (MsInterfaces)
		{
			WLog_Print(urbdrc->log, WLOG_INFO,
			           "select Interface(%" PRIu8 ") curr AlternateSetting(%" PRIu8
			           ") new AlternateSetting(%" PRIu8 ")",
			           InterfaceNumber, MsInterfaces[InterfaceNumber]->AlternateSetting,
			           AlternateSetting);

			if (MsInterfaces[InterfaceNumber]->AlternateSetting != AlternateSetting)
			{
				diff = 1;
			}
		}

		if (diff)
		{
			error = libusb_set_interface_alt_setting(pdev->libusb_handle, InterfaceNumber,
			                                         AlternateSetting);

			log_libusb_result(urbdrc->log, WLOG_ERROR, "libusb_set_interface_alt_setting", error);
		}
	}

	return error;
}
/* ==== end verbatim ==== */

/* ---------------------------------------------------------------------
 * main(): read argv[1] as attacker-controlled bytes into a HEAP buffer, build a
 * plausible client-side device object (one URBDRC_PLUGIN + a MsConfig describing the
 * single interface the device actually enumerated -- NumInterfaces=1, matching a
 * common real single-interface USB device), then call libusb_udev_select_interface
 * with InterfaceNumber/AlternateSetting straight from the input bytes -- exactly the
 * two BYTE fields the real dispatch (urbdrc_process_udev_select_interface) reads off
 * the RDP USB-redirection channel and forwards uninspected.
 * ------------------------------------------------------------------- */
int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;
	FILE* f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long sz = ftell(f);
	if (sz < 2) { fclose(f); return 0; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	BYTE* buf = (BYTE*)malloc((size_t)sz); /* heap, ASAN-guarded */
	if (!buf) { fclose(f); return 0; }
	size_t n = fread(buf, 1, (size_t)sz, f);
	fclose(f);
	if (n < 2) { free(buf); return 0; }

	BYTE InterfaceNumber = buf[0];
	BYTE AlternateSetting = buf[1];
	free(buf);

	/* one legitimate interface descriptor, referenced from MsInterfaces[0] */
	MSUSB_INTERFACE_DESCRIPTOR iface0;
	memset(&iface0, 0, sizeof(iface0));
	iface0.InterfaceNumber = 0;
	iface0.AlternateSetting = 0;

	/* heap-allocated pointer array, exactly NumInterfaces slots -- the buffer whose
	 * bounds the missing check in the real fix protects */
	MSUSB_INTERFACE_DESCRIPTOR** MsInterfaces =
	    (MSUSB_INTERFACE_DESCRIPTOR**)malloc(sizeof(MSUSB_INTERFACE_DESCRIPTOR*) * 1);
	if (!MsInterfaces)
		return 0;
	MsInterfaces[0] = &iface0;

	MSUSB_CONFIG_DESCRIPTOR MsConfig;
	memset(&MsConfig, 0, sizeof(MsConfig));
	MsConfig.NumInterfaces = 1;
	MsConfig.MsInterfaces = MsInterfaces;

	URBDRC_PLUGIN urbdrc;
	memset(&urbdrc, 0, sizeof(urbdrc));
	urbdrc.log = NULL;

	UDEVICE dev;
	memset(&dev, 0, sizeof(dev));
	dev.urbdrc = &urbdrc;
	dev.MsConfig = &MsConfig;
	dev.libusb_handle = NULL;

	int rc = libusb_udev_select_interface((IUDEVICE*)&dev, InterfaceNumber, AlternateSetting);
	(void)rc;

	free(MsInterfaces);
	return 0;
}
