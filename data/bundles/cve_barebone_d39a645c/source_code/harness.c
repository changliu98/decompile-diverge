/*
 * cve_d39a645c -- FreeRDP client/X11/xf_window.c: xf_AppWindowDestroyImage
 * direct-call ASAN harness.
 *
 * CWE-476 (NULL pointer dereference).
 *
 * Upstream fix commit 169d358734509e82663a0d6a0085ae726d439d8e
 * (client/X11/xf_gfx.c) adds a brand new RDPGFX callback,
 * xf_UnmapWindowForSurface(), and is careful to guard its call into
 * xf_AppWindowDestroyImage():
 *
 *     xfAppWindow* appWindow = xf_rail_get_window(xfc, windowID);
 *     if (appWindow)
 *         xf_AppWindowDestroyImage(appWindow);
 *
 * i.e. the fix commit's own new caller treats "appWindow may be NULL" as the
 * thing that must be checked before calling xf_AppWindowDestroyImage() --
 * that missing-NULL-check IS the trigger condition this harness reproduces.
 * xf_AppWindowDestroyImage() itself (unchanged by the fix, byte-for-byte
 * below) has no defense of its own against a NULL argument beyond
 * WINPR_ASSERT(appWindow):
 *
 *     winpr/include/winpr/assert-api.h:
 *       #define WINPR_ASSERT(cond) WINPR_ASSERT_AT((cond), __FILE__, __func__, __LINE__)
 *       -> winpr_internal_assert(cond, ...) -> assert(cond)   [WITH_VERBOSE_WINPR_ASSERT off]
 *
 * plain libc assert() compiles to a no-op once NDEBUG is defined, which is
 * how FreeRDP actually ships (Release / RelWithDebInfo packaging is the
 * norm) -- so in a real, deployed client, nothing stops the function from
 * immediately dereferencing a NULL appWindow at `appWindow->image`. This
 * harness reproduces exactly that shipped (NDEBUG) semantics.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- minimal WinPR typedefs (real names, winpr/include/winpr/wtypes.h) --- */
typedef int BOOL;
typedef unsigned char BYTE;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef int32_t INT32;

/* ---- WINPR_ASSERT: reproduce the shipped (NDEBUG) no-op semantics -------- */
#define WINPR_ASSERT(cond) ((void)0)

/* ---- minimal X11 stand-ins (real names, Xlib.h / Xdefs.h) ----------------
 * xf_AppWindowDestroyImage only ever touches appWindow->image->data and
 * hands the pointer to XDestroyImage(); the rest of real Xlib is incidental
 * to the crash, so these are minimal faithful stand-ins, not real Xlib.
 */
typedef unsigned long XID;
typedef XID Window;
typedef XID Pixmap;
typedef struct _XGC* GC;

typedef struct _XImage
{
	char* data;
} XImage;

static int XDestroyImage(XImage* image)
{
	/* Real Xlib frees image->data (unless a custom destroy_image hook is
	 * installed) then frees the XImage struct itself. The target function
	 * always NULLs ->data before calling this, so there is nothing left for
	 * XDestroyImage to free but the struct -- matches real XDestroyImage's
	 * net effect on this call path. */
	free(image);
	return 1;
}

/* ---- RECTANGLE_16 (winpr/include/winpr/wtypes.h) --------------------------
 * xfAppWindow only stores pointers to it; xf_AppWindowDestroyImage never
 * dereferences them, so an incomplete type is faithful and sufficient. */
typedef struct RECTANGLE_16 RECTANGLE_16;

/* ---- xfContext (client/X11/xf_client.h) -----------------------------------
 * Only ever referenced as a pointer field here; opaque is sufficient. */
typedef struct xf_context xfContext;

/* ---- xf_localmove (client/X11/xf_window.h, verbatim) ---------------------- */
enum xf_localmove_state
{
	LMS_NOT_ACTIVE,
	LMS_STARTING,
	LMS_ACTIVE,
	LMS_TERMINATING
};

typedef struct xf_localmove
{
	int root_x;
	int root_y;
	int window_x;
	int window_y;
	enum xf_localmove_state state;
	int direction;
} xfLocalMove;

/* ---- xfAppWindow (client/X11/xf_window.h, verbatim field set) ------------ */
typedef struct xf_app_window
{
	xfContext* xfc;

	int x;
	int y;
	int width;
	int height;
	char* title;

	UINT32 surfaceId;
	UINT64 windowId;
	UINT32 ownerWindowId;

	UINT32 dwStyle;
	UINT32 dwExStyle;
	UINT32 showState;

	INT32 clientOffsetX;
	INT32 clientOffsetY;
	UINT32 clientAreaWidth;
	UINT32 clientAreaHeight;

	INT32 windowOffsetX;
	INT32 windowOffsetY;
	INT32 windowClientDeltaX;
	INT32 windowClientDeltaY;
	UINT32 windowWidth;
	UINT32 windowHeight;
	UINT32 numWindowRects;
	RECTANGLE_16* windowRects;

	INT32 visibleOffsetX;
	INT32 visibleOffsetY;
	UINT32 numVisibilityRects;
	RECTANGLE_16* visibilityRects;

	UINT32 localWindowOffsetCorrX;
	UINT32 localWindowOffsetCorrY;

	UINT32 resizeMarginLeft;
	UINT32 resizeMarginTop;
	UINT32 resizeMarginRight;
	UINT32 resizeMarginBottom;

	GC gc;
	int shmid;
	Window handle;
	Window* xfwin;
	BOOL fullscreen;
	BOOL decorations;
	BOOL is_mapped;
	BOOL is_transient;
	xfLocalMove local_move;
	BYTE rail_state;
	BOOL maxVert;
	BOOL maxHorz;
	BOOL minimized;
	BOOL rail_ignore_configure;

	Pixmap pixmap;
	XImage* image;
} xfAppWindow;

/* ============================================================================
 * TARGET FUNCTION -- byte-for-byte from
 * data_cve/cve_d39a645c/target/original_function.c (do not edit).
 * ==========================================================================*/
static void xf_AppWindowDestroyImage(xfAppWindow* appWindow)
{
	WINPR_ASSERT(appWindow);
	if (appWindow->image)
	{
		appWindow->image->data = NULL;
		XDestroyImage(appWindow->image);
		appWindow->image = NULL;
	}
}
/* ========================================================================== */

int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	FILE* f = fopen(argv[1], "rb");
	if (!f)
		return 0;

	if (fseek(f, 0, SEEK_END) != 0)
	{
		fclose(f);
		return 0;
	}
	long sz = ftell(f);
	if (sz < 0)
		sz = 0;
	fseek(f, 0, SEEK_SET);

	unsigned char* buf = NULL;
	size_t n = 0;
	if (sz > 0)
	{
		buf = (unsigned char*)malloc((size_t)sz); /* heap-allocate the input, ASAN-guarded */
		if (!buf)
		{
			fclose(f);
			return 0;
		}
		n = fread(buf, 1, (size_t)sz, f);
	}
	fclose(f);

	/*
	 * Input byte 0 selects the call mode (this IS the attacker-controlled
	 * decision the upstream fix's missing-NULL-check guarded):
	 *   even, or an empty file -> appWindow == NULL           (triggering)
	 *   odd                    -> a real heap-allocated appWindow (safe)
	 */
	int null_mode = (n == 0) || ((buf[0] & 1) == 0);

	if (null_mode)
	{
		free(buf);
		xf_AppWindowDestroyImage(NULL); /* CWE-476: NULL deref at appWindow->image */
		return 0;
	}

	/* Safe path: build a real heap xfAppWindow. Byte 1 (if present) decides
	 * whether it carries a live image, so some safe inputs exercise the
	 * function's full body (image->data clear + XDestroyImage + NULL-out)
	 * and others exercise the empty-image no-op branch -- both must exit
	 * clean. */
	int with_image = (n > 1) && (buf[1] & 1);

	xfAppWindow* appWindow = (xfAppWindow*)calloc(1, sizeof(xfAppWindow));
	if (!appWindow)
	{
		free(buf);
		return 0;
	}

	if (with_image)
	{
		XImage* img = (XImage*)calloc(1, sizeof(XImage));
		if (img)
		{
			img->data = (char*)malloc(16);
			appWindow->image = img;
		}
	}

	free(buf);
	xf_AppWindowDestroyImage(appWindow);
	free(appWindow);
	return 0;
}
