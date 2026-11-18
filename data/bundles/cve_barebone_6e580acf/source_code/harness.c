/* cve_barebone direct-call harness for cve_6e580acf (freerdp, CVE-2026-25952)
 * Target: xf_Pointer_get_window  (client/X11/xf_graphics.c)
 * Bug class: heap-use-after-free READ (CWE-416).
 *
 * See scripts/gen_dc_cve_6e580acf.py module docstring for the full mechanism trace
 * (fix_commit 1994e9844212a6dfe0ff12309fef520e888986b5, "[client,x11] lock appWindow").
 * In short: xfc->appWindow is a cache pointer another thread can free() (via
 * xf_rail_del_window's HashTable removal path) while xf_Pointer_get_window reads
 * xfc->appWindow->handle with no lock. This harness reproduces the exact final state
 * that race leaves -- appWindow freed, xfc->appWindow still pointing at it -- with a
 * plain single-threaded malloc()+free() before the call, then calls
 * xf_Pointer_get_window() directly.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* X11/Xlib.h (64-bit Linux/X11): typedef unsigned long XID; typedef XID Window; */
typedef unsigned long Window;

/* winpr/include/winpr/wtypes.h, non-_WIN32/non-__APPLE__ branch */
typedef int32_t BOOL;
#ifndef TRUE
#define TRUE true
#endif
#ifndef FALSE
#define FALSE false
#endif

/* client/X11/xf_graphics.c: #define TAG CLIENT_TAG("x11")
 * == FREERDP_TAG("client.") "x11" == "com.freerdp." "client." "x11" (include/freerdp/log.h) */
#define TAG "com.freerdp.client.x11"
/* WLog_WARN (winpr/include/winpr/wlog.h) is diagnostic-only on every path reachable
 * here -- never touches control flow or data -- stubbed to a no-op per the harness
 * rules for incidental callees. */
#define WLog_WARN(tag, ...) ((void)0)

/* client/X11/xf_window.h: typedef struct xf_app_window xfAppWindow; -- only the
 * ->handle field xf_Pointer_get_window itself dereferences is kept. */
typedef struct xf_app_window
{
	Window handle;
} xfAppWindow;

/* client/X11/xf_window.h: typedef struct xf_window xfWindow; -- same "only the field
 * this function touches" scoping. */
typedef struct xf_window
{
	Window handle;
} xfWindow;

/* client/X11/xfreerdp.h: typedef struct xf_context xfContext; struct xf_context {
 * ... xfWindow* window; xfAppWindow* appWindow; ... BOOL remote_app; ... } -- only the
 * three fields xf_Pointer_get_window itself reads are kept. */
typedef struct xf_context
{
	xfWindow* window;
	xfAppWindow* appWindow;
	BOOL remote_app;
} xfContext;

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the UAF read keeps its own stack frame (dc_batch requires the target
 * function name in the ASAN backtrace). */
__attribute__((noinline))
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

/* ================= driver ================= */
int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 2;
	}

	FILE* fp = fopen(argv[1], "rb");
	if (!fp)
	{
		perror("fopen");
		return 2;
	}
	fseek(fp, 0, SEEK_END);
	long ln = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (ln < 0)
		ln = 0;
	size_t n = (size_t)ln;

	unsigned char* data = (unsigned char*)malloc(n + 1); /* HEAP input, ASAN-guarded */
	if (!data)
	{
		fclose(fp);
		return 2;
	}
	size_t got = fread(data, 1, n, fp);
	fclose(fp);
	data[got] = '\0';

	unsigned char ctrl = (got > 0) ? data[0] : 0;
	/* remaining bytes seed the fabricated Window handle value -- attacker-controlled,
	 * but never itself the source of the fault (the fault is the STALE POINTER, not
	 * the handle value it would have read had the object still been live). */
	Window handle = 0;
	for (size_t i = 1; i < got && i <= sizeof(Window); i++)
		handle = (handle << 8) | data[i];

	int ctx_null = ctrl & 0x01;              /* xfc == NULL              -> safe (1st guard) */
	int remote_app = (ctrl >> 1) & 0x01;     /* xfc->remote_app                               */
	int target_null = (ctrl >> 2) & 0x01;    /* appWindow/window == NULL -> safe (2nd guard)  */
	int use_after_free = (ctrl >> 3) & 0x01; /* free() the target before the call -> TRIGGER  */

	/* volatile function pointer: forbid the compiler from proving any particular call
	 * away / folding xf_Pointer_get_window into main's own frame despite
	 * __attribute__((noinline)). */
	Window(*volatile fn)(xfContext*) = xf_Pointer_get_window;

	if (ctx_null)
	{
		Window r = fn(NULL);
		(void)r;
		free(data);
		return 0;
	}

	xfContext* xfc = (xfContext*)malloc(sizeof(xfContext));
	if (!xfc)
	{
		free(data);
		return 0;
	}
	xfc->window = NULL;
	xfc->appWindow = NULL;
	xfc->remote_app = remote_app ? TRUE : FALSE;

	xfAppWindow* aw = NULL;
	xfWindow* w = NULL;

	if (remote_app)
	{
		if (!target_null)
		{
			aw = (xfAppWindow*)malloc(sizeof(xfAppWindow));
			if (!aw)
			{
				free(xfc);
				free(data);
				return 0;
			}
			aw->handle = handle;
			xfc->appWindow = aw;

			if (use_after_free)
			{
				/* Reproduce xf_rail_del_window()'s HashTable_Remove()+free() of the
				 * SAME xfAppWindow xfc->appWindow still references -- the exact
				 * post-free state the race the fix commit's lock closes leaves
				 * behind. xfc->appWindow itself is never cleared (matching real
				 * behaviour -- nothing but the new lock protects this field), so
				 * it stays a non-NULL, DANGLING pointer going into the call below. */
				free(aw);
			}
		}
		/* else: xfc->appWindow stays NULL -> the function's own
		 * `if (!xfc->appWindow)` guard fires -> safe early return. */
	}
	else
	{
		if (!target_null)
		{
			w = (xfWindow*)malloc(sizeof(xfWindow));
			if (!w)
			{
				free(xfc);
				free(data);
				return 0;
			}
			w->handle = handle;
			xfc->window = w;
		}
		/* else: xfc->window stays NULL -> safe early return via the `else` guard. */
	}

	Window result = fn(xfc);
	(void)result;

	/* Only reached when xf_Pointer_get_window did NOT crash (the safe corpus half).
	 * aw was already freed above when use_after_free fired -- must not double-free. */
	if (aw && !use_after_free)
		free(aw);
	if (w)
		free(w);
	free(xfc);
	free(data);
	return 0;
}
