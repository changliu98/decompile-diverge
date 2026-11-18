/*
 * cve_barebone direct-call harness for CVE-2026-25953 (FreeRDP)
 * Target: xf_Pointer_get_window   (client/X11/xf_graphics.c)
 * Bug class: heap-use-after-free READ (CWE-416)
 *
 * Root cause (fixed upstream in commit
 * 1994e9844212a6dfe0ff12309fef520e888986b5): xf_Pointer_get_window() is the
 * X11 client's "which window handle should the incoming pointer/cursor
 * update apply to" helper. In the RemoteApp path it does a bare
 * check-then-use on the *cached* pointer `xfc->appWindow`:
 *
 *     if (!xfc->appWindow) { ...; return 0; }
 *     return xfc->appWindow->handle;
 *
 * `xfc->appWindow` is a raw cache of whichever xfAppWindow the X11 event
 * thread last focused (client/X11/xf_event.c, e.g. EnterNotify). The
 * corresponding xfAppWindow objects live in xfc->railWindows, a hash table
 * mutated from a *different* thread as RAIL_ORDER window-delete PDUs arrive
 * from the (attacker-controlled, since this is the RDP *client*) server --
 * xf_rail_del_window() -> HashTable_Remove() frees the xfAppWindow the
 * moment a delete order is processed, but nothing on that path clears the
 * separate xfc->appWindow cache pointer. So a delete-window order racing a
 * pointer-update order leaves xfc->appWindow dangling at exactly the read
 * above: heap-use-after-free. The fix wraps the whole check-then-use in
 * HashTable_Lock(xfc->railWindows)/HashTable_Unlock(), serializing it
 * against the hash-table removal that does the freeing.
 *
 * We cannot spin up real racing X11-event/channel threads in a
 * self-contained harness, so -- exactly as this benchmark's
 * cve_barebone_1152b033 (hci_req_sync, the same "unsynchronized
 * check-then-use races a concurrent free" shape) does -- we reproduce the
 * identical fault deterministically, single-threaded: heap-allocate the
 * xfAppWindow xfc->appWindow points to, then free() it exactly as the
 * racing xf_rail_del_window()/HashTable_Remove() teardown would, leaving
 * xfc->appWindow dangling, then invoke xf_Pointer_get_window() on it
 * exactly as the (formerly racing) pointer-update caller would. Its
 * `return xfc->appWindow->handle;` then reads freed heap memory: the same
 * read, same source line, same fault class the real concurrent bug
 * produces, without needing actual threads.
 *
 * Type vocabulary is copied real-named from this checkout:
 *   - xfContext (client/X11/xfreerdp.h struct xf_context) trimmed to the
 *     three members xf_Pointer_get_window's own body reads: `window`,
 *     `appWindow`, `remote_app`. The real struct additionally carries ~130
 *     unrelated members (X11 Display/GC/Colormap/Screen/Visual/..., the
 *     embedded rdpClientContext, RAIL channel plumbing, keyboard/touch
 *     state, ...) untouched by this function.
 *   - xfAppWindow (client/X11/xf_window.h struct xf_app_window) and xfWindow
 *     (struct xf_window) both trimmed to their `handle` member (type
 *     Window) -- the only field either struct exposes to this function; the
 *     real structs additionally carry ~25/~10 unrelated geometry/RAIL-state
 *     members respectively.
 *   - Window/XID: X11/X.h's core-protocol resource-id typedefs (verbatim,
 *     stable for decades: XID is `unsigned long`, Window is an XID). Xlib
 *     itself is a system library this trimmed checkout does not vendor, so
 *     it is reproduced from that well-known public definition rather than
 *     included.
 *   - BOOL/TRUE/FALSE (winpr/wtypes.h) and the WLog_WARN(tag, ...) logging
 *     macro chain (freerdp/log.h CLIENT_TAG/TAG; winpr/wlog.h WLOG_WARN +
 *     WLog_Print_dbg_tag) -- same verbatim macros/real signature this
 *     benchmark's cve_barebone_481f3abb (also an xfContext/X11-client
 *     target) already established for this codebase, with the same stubbed
 *     body (formats through vfprintf instead of the real wLog backend --
 *     irrelevant to the fault, and on the TRIGGER input never even reached:
 *     the UAF read is the ONE line after the guard, not inside it).
 *
 * Compiles + links standalone:
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* ---------------------------------------------------------------------
 * winpr/include/winpr/wtypes.h (verbatim)
 * --------------------------------------------------------------------- */
typedef int BOOL;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* ---------------------------------------------------------------------
 * X11/X.h -- core-protocol resource-id typedefs (verbatim, stable public
 * definition; see file header comment).
 * --------------------------------------------------------------------- */
typedef unsigned long XID;
typedef XID Window;

/* ---------------------------------------------------------------------
 * include/freerdp/log.h (verbatim)
 * --------------------------------------------------------------------- */
#define FREERDP_TAG(tag) "com.freerdp." tag
#define CLIENT_TAG(tag) FREERDP_TAG("client.") tag
#define TAG CLIENT_TAG("x11")

/* ---------------------------------------------------------------------
 * winpr/include/winpr/wlog.h -- WLog_WARN (verbatim macro) and the real
 * signature of WLog_Print_dbg_tag it expands to (a `static inline` there).
 * Stub body: the real one formats+emits through wLog (level-gated via
 * WLog_IsLevelActive); this one formats through vfprintf instead, which is
 * the faithful minimal stand-in and genuinely consumes its arguments so the
 * compiler cannot prove the call is dead. Not on the TRIGGER path at all
 * (that path's fault fires one line after its own WLog_WARN guard, on the
 * unconditional `return xfc->appWindow->handle;`); reached only by the SAFE
 * "invalid appWindow/window" sub-cases below.
 * --------------------------------------------------------------------- */
typedef unsigned int DWORD;
#define WLOG_WARN 3
static void WLog_Print_dbg_tag(const char* tag, DWORD log_level, size_t line,
                                const char* file, const char* fkt, const char* fmt, ...)
{
	(void)tag; (void)log_level; (void)line; (void)file; (void)fkt;
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
}
#define WLog_WARN(tag, ...) \
	WLog_Print_dbg_tag(tag, WLOG_WARN, __LINE__, __FILE__, __func__, __VA_ARGS__)

/* ---------------------------------------------------------------------
 * client/X11/xf_window.h struct xf_app_window / struct xf_window, trimmed
 * to their `handle` member (see file header comment).
 * --------------------------------------------------------------------- */
typedef struct xf_app_window
{
	Window handle;
} xfAppWindow;

typedef struct xf_window
{
	Window handle;
} xfWindow;

/* ---------------------------------------------------------------------
 * client/X11/xfreerdp.h struct xf_context, trimmed to the three members
 * xf_Pointer_get_window's own body reads (see file header comment).
 * --------------------------------------------------------------------- */
typedef struct xf_context
{
	xfWindow* window;
	xfAppWindow* appWindow;
	BOOL remote_app;
} xfContext;

/* =========================================================================
 * client/X11/xf_graphics.c:247-272 -- xf_Pointer_get_window, BYTE-FOR-BYTE
 * from data_cve/cve_9b3d0b0d/target/original_function.c.
 * ========================================================================= */
static Window xf_Pointer_get_window(xfContext* xfc)
{
	if (!xfc)
	{
		WLog_WARN(TAG, "xf_Pointer: Invalid context");
		return 0;
	}
	if (xfc->remote_app)
	{
		if (!xfc->appWindow)
		{
			WLog_WARN(TAG, "xf_Pointer: Invalid appWindow");
			return 0;
		}
		return xfc->appWindow->handle;
	}
	else
	{
		if (!xfc->window)
		{
			WLog_WARN(TAG, "xf_Pointer: Invalid window");
			return 0;
		}
		return xfc->window->handle;
	}
}
/* ==== end verbatim ==== */

/* ---------------------------------------------------------------------
 * main(): read argv[1] into a HEAP buffer, use its bytes to select one of
 * six deterministic scenarios (1 TRIGGER + 5 SAFE), build a heap-allocated
 * xfContext accordingly, and call xf_Pointer_get_window() on it exactly
 * once via an indirect (volatile function pointer) call -- keeps the target
 * a real, non-inlined frame so it appears by name in the ASAN crash stack.
 * ------------------------------------------------------------------- */
int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	FILE* f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long fsz = ftell(f);
	if (fsz < 0) { fclose(f); return 0; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	/* HEAP-allocated, ASAN-guarded attacker-controlled input buffer */
	unsigned char* buf = (unsigned char*)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if (!buf) { fclose(f); return 0; }
	size_t n = (fsz > 0) ? fread(buf, 1, (size_t)fsz, f) : 0;
	fclose(f);

	unsigned char mode = (n > 0) ? buf[0] : 0;
	/* attacker-controlled Window handle payload (LE), threaded into every
	 * live xfAppWindow/xfWindow this harness constructs below -- inert data
	 * that only ever flows into the function's return value, never into
	 * control flow. */
	Window handle_val = 0;
	if (n > 1) handle_val |= (Window)buf[1];
	if (n > 2) handle_val |= (Window)buf[2] << 8;
	if (n > 3) handle_val |= (Window)buf[3] << 16;
	if (n > 4) handle_val |= (Window)buf[4] << 24;
	free(buf);

	/* indirect call through a volatile pointer keeps xf_Pointer_get_window
	 * a real, non-inlined frame so it appears by name in the ASAN crash
	 * stack. */
	Window (*volatile call_get_window)(xfContext*) = xf_Pointer_get_window;

	xfContext* xfc = (xfContext*)calloc(1, sizeof(xfContext));
	if (!xfc)
		return 0;

	if (mode & 1)
	{
		/*
		 * TRIGGER (CVE-2026-25953): simulate the racing RAIL delete-window
		 * order that the missing HashTable_Lock let through -- allocate
		 * the xfAppWindow xfc->appWindow points to, then free() it exactly
		 * like xf_rail_del_window()/HashTable_Remove() would, WITHOUT
		 * clearing xfc->appWindow (that omission is the bug). The
		 * (formerly racing) pointer-update caller then runs
		 * xf_Pointer_get_window() on the now-dangling cache pointer.
		 */
		xfAppWindow* win = (xfAppWindow*)malloc(sizeof(xfAppWindow));
		if (!win) { free(xfc); return 0; }
		win->handle = handle_val;

		xfc->remote_app = TRUE;
		xfc->appWindow = win;
		xfc->window = NULL;

		free(win); /* the racing xf_rail_del_window() teardown */

		call_get_window(xfc);
		/* unreachable on a genuine trigger: ASan aborts on the
		 * heap-use-after-free read inside xf_Pointer_get_window above. */
		free(xfc);
		return 0;
	}

	/*
	 * SAFE: five scenarios that exercise every non-buggy branch of
	 * xf_Pointer_get_window without ever touching freed or undersized
	 * memory -- (mode>>1) picks one of them, independent of the low bit
	 * that only ever selects SAFE here.
	 */
	unsigned char safe_case = (unsigned char)((mode >> 1) % 5);
	Window result = 0;

	switch (safe_case)
	{
		case 0:
			/* xfc itself NULL -> the function's very first guard. */
			free(xfc);
			result = call_get_window(NULL);
			(void)result;
			return 0;

		case 1:
			/* remote_app path, appWindow NULL -> "Invalid appWindow" guard. */
			xfc->remote_app = TRUE;
			xfc->appWindow = NULL;
			xfc->window = NULL;
			break;

		case 2:
		{
			/* remote_app path, appWindow present and LIVE (never freed) ->
			 * successful read of a real, valid xfAppWindow. */
			xfAppWindow* win = (xfAppWindow*)malloc(sizeof(xfAppWindow));
			if (!win) { free(xfc); return 0; }
			win->handle = handle_val;
			xfc->remote_app = TRUE;
			xfc->appWindow = win;
			xfc->window = NULL;
			result = call_get_window(xfc);
			fprintf(stderr, "safe case=2 handle=%lu\n", (unsigned long)result);
			free(win);
			free(xfc);
			return 0;
		}

		case 3:
			/* local (non-RemoteApp) path, window NULL -> "Invalid window"
			 * guard. */
			xfc->remote_app = FALSE;
			xfc->appWindow = NULL;
			xfc->window = NULL;
			break;

		case 4:
		default:
		{
			/* local (non-RemoteApp) path, window present and LIVE (never
			 * freed) -> successful read of a real, valid xfWindow. */
			xfWindow* win = (xfWindow*)malloc(sizeof(xfWindow));
			if (!win) { free(xfc); return 0; }
			win->handle = handle_val;
			xfc->remote_app = FALSE;
			xfc->appWindow = NULL;
			xfc->window = win;
			result = call_get_window(xfc);
			fprintf(stderr, "safe case=4 handle=%lu\n", (unsigned long)result);
			free(win);
			free(xfc);
			return 0;
		}
	}

	result = call_get_window(xfc);
	fprintf(stderr, "safe case=%u handle=%lu\n", (unsigned)safe_case, (unsigned long)result);
	free(xfc);
	return 0;
}
