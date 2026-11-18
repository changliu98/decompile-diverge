/* cve_barebone direct-call harness for CVE-2026-25942 (FreeRDP)
 * Target: xf_rail_server_execute_result   (client/X11/xf_rail.c)
 * Bug class: global-buffer-overflow READ (CWE-125)
 *
 * Root cause (visible directly in target/original_function.c, unchanged):
 *   static const char* error_code_names[] = { ... 7 entries ... };
 *   ...
 *   if (execResult->execResult != RAIL_EXEC_S_OK)
 *   {
 *       WLog_ERR(TAG, "RAIL exec error: execResult=%s NtError=0x%X\n",
 *                error_code_names[execResult->execResult], execResult->rawResult);
 *       ...
 *   }
 *
 * `execResult->execResult` is a UINT16 taken straight off an incoming
 * TS_RAIL_ORDER_EXEC_RESULT PDU (server-controlled -- the X11 client is the
 * RDP *client*, so this is attacker-controlled input from a malicious/
 * compromised RDP server) and used to index `error_code_names` with NO
 * bounds check. The array has exactly 7 entries (valid indices 0..6); any
 * value >= 7 reads a `const char*` past the end of the global array --
 * ASAN "global-buffer-overflow READ of size 8" -- and the wild pointer then
 * flows into WLog_ERR's "%s" formatting. Fixed by upstream commit
 * 9362a0bf8dda04eedbca07d5dfaec1044e67cc6b, which replaces the table with a
 * bounds-checked switch (error_code2str()).
 *
 * The OOB read is literally the subscript expression written inside
 * xf_rail_server_execute_result's own body (it fires while the compiler
 * evaluates WLog_ERR's arguments, strictly before the call it expands to is
 * ever entered) -- so the fault is unambiguously in the target function
 * itself, not a callee.
 *
 * This file assembles:
 *   1. Minimal-but-faithful standalone re-declarations of the real
 *      WinPR/FreeRDP types and macros the function needs -- fixed-width
 *      type aliases (winpr/wtypes.h), WINPR_ASSERT (winpr/assert-api.h,
 *      reduced to its non-verbose-build expansion, plain assert()),
 *      CLIENT_TAG/TAG (freerdp/log.h), the WLog_ERR macro + the real
 *      WLog_Print_dbg_tag signature it expands to (winpr/wlog.h) --
 *      stubbed body (formats+emits a log record; irrelevant to the crash,
 *      which fires while evaluating its arguments, before it is entered),
 *      RAIL_EXEC_RESULT_ORDER/RAIL_UNICODE_STRING/RAIL_EXEC_* (freerdp/
 *      rail.h), RailClientContext trimmed to the one field the function
 *      reads (`custom`; the omitted members are ~30 unrelated
 *      channel-callback function pointers this function never touches),
 *      and rdpContext/rdpClientContext/xfContext trimmed to the
 *      first-field chain the function walks (xfc->common.context) --
 *      freerdp_abort_connect_context is a real FREERDP_API (freerdp/
 *      freerdp.h) stubbed here since it is unreachable in every input
 *      (the crash above it always fires first).
 *      error_code_names itself is copied VERBATIM (client/X11/xf_rail.c
 *      lines 40-46) -- it's the vulnerable object.
 *   2. VERBATIM real FreeRDP source: data_cve/cve_481f3abb/target/
 *      original_function.c byte-for-byte (the target function itself,
 *      UNCHANGED -- no logic/name/signature edits).
 *   3. main(): reads argv[1] into a HEAP buffer (required so ASAN
 *      instruments it), decodes the first 2 bytes (LE) as
 *      execResult->execResult (the OOB index) and the next 4 bytes (LE) as
 *      execResult->rawResult (inert -- only ever %X-printed), builds the
 *      RailClientContext/xfContext/RAIL_EXEC_RESULT_ORDER scaffolding, and
 *      calls xf_rail_server_execute_result() directly, exactly once.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

/* ---------------------------------------------------------------------
 * winpr/include/winpr/wtypes.h -- fixed-width type aliases (verbatim)
 * --------------------------------------------------------------------- */
typedef uint8_t  BYTE;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint32_t UINT;
typedef uint32_t DWORD;
typedef int      BOOL;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* ---------------------------------------------------------------------
 * winpr/include/winpr/assert-api.h -- WINPR_ASSERT. Verbatim reduction of
 * the default (WITH_VERBOSE_WINPR_ASSERT off) expansion path, which is
 * plain assert(cond).
 * --------------------------------------------------------------------- */
#define WINPR_ASSERT(cond) assert(cond)

/* ---------------------------------------------------------------------
 * include/freerdp/log.h (verbatim)
 * --------------------------------------------------------------------- */
#define FREERDP_TAG(tag) "com.freerdp." tag
#define CLIENT_TAG(tag) FREERDP_TAG("client.") tag
#define TAG CLIENT_TAG("x11")

/* ---------------------------------------------------------------------
 * winpr/include/winpr/wtsapi.h (verbatim)
 * --------------------------------------------------------------------- */
#define CHANNEL_RC_OK 0

/* ---------------------------------------------------------------------
 * winpr/include/winpr/wlog.h -- WLog_ERR (verbatim macro) and the real
 * signature of WLog_Print_dbg_tag it expands to (a `static inline` there).
 * Stub body: the real one formats+emits through wLog; this one formats
 * through vfprintf instead, which is the faithful minimal stand-in (same
 * observable effect on the "%s"/execResult->execResult argument -- it
 * gets read and formatted either way) and, unlike a fully no-op stub,
 * genuinely uses its arguments so the compiler can't prove the call (and
 * the OOB array read feeding it) is dead and delete it at -O1. Never
 * actually reached on a triggering input: the array subscript below is
 * evaluated (and ASan traps it) while building this call's arguments,
 * strictly before WLog_Print_dbg_tag is entered.
 * --------------------------------------------------------------------- */
#define WLOG_ERROR 4
static void WLog_Print_dbg_tag(const char* tag, DWORD log_level, size_t line,
                                const char* file, const char* fkt, const char* fmt, ...)
{
    (void)tag; (void)log_level; (void)line; (void)file; (void)fkt;
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}
#define WLog_ERR(tag, ...) \
    WLog_Print_dbg_tag(tag, WLOG_ERROR, __LINE__, __FILE__, __func__, __VA_ARGS__)

/* ---------------------------------------------------------------------
 * include/freerdp/rail.h -- RAIL_EXEC_RESULT_ORDER + RAIL_EXEC_* codes
 * (verbatim).
 * --------------------------------------------------------------------- */
#define RAIL_EXEC_S_OK 0x0000
#define RAIL_EXEC_E_HOOK_NOT_LOADED 0x0001
#define RAIL_EXEC_E_DECODE_FAILED 0x0002
#define RAIL_EXEC_E_NOT_IN_ALLOWLIST 0x0003
#define RAIL_EXEC_E_FILE_NOT_FOUND 0x0005
#define RAIL_EXEC_E_FAIL 0x0006
#define RAIL_EXEC_E_SESSION_LOCKED 0x0007

typedef struct
{
    UINT16 length;
    BYTE* string;
} RAIL_UNICODE_STRING;

typedef struct
{
    UINT16 flags;
    UINT16 execResult;
    UINT32 rawResult;
    RAIL_UNICODE_STRING exeOrFile;
} RAIL_EXEC_RESULT_ORDER;

/* ---------------------------------------------------------------------
 * include/freerdp/client/rail.h -- RailClientContext (verbatim, trimmed to
 * the field the target function reads: `custom`. The omitted members are
 * ~30 unrelated pcRailClient / pcRailServer channel-callback function
 * pointers this function never touches).
 * --------------------------------------------------------------------- */
typedef struct s_rail_client_context
{
    void* handle;
    void* custom;
} RailClientContext;

/* ---------------------------------------------------------------------
 * include/freerdp/freerdp.h -- rdpContext; include/freerdp/client.h --
 * rdpClientContext; client/X11/xfreerdp.h -- xfContext. Verbatim
 * first-field layout the target function walks (xfc->common.context);
 * the omitted members (X11 GC/Display/Pixmap/... in the real xfContext,
 * ~40 unrelated members in the real rdp_client_context/rdp_context) are
 * never touched by this function. freerdp_abort_connect_context is a real
 * FREERDP_API (declared freerdp/freerdp.h); stubbed here since it is
 * unreachable on every one of our inputs -- the OOB read in the line
 * above it always fires first.
 * --------------------------------------------------------------------- */
typedef struct rdp_context
{
    int dummy;
} rdpContext;

typedef struct rdp_client_context
{
    rdpContext context;
} rdpClientContext;

typedef struct xf_context
{
    rdpClientContext common;
} xfContext;

static BOOL freerdp_abort_connect_context(rdpContext* context)
{
    (void)context;
    return TRUE;
}

/* ---------------------------------------------------------------------
 * client/X11/xf_rail.c:40-46 -- the vulnerable lookup table, copied
 * verbatim. Exactly 7 entries (valid indices 0..6).
 * --------------------------------------------------------------------- */
static const char* error_code_names[] = { "RAIL_EXEC_S_OK",
	                                      "RAIL_EXEC_E_HOOK_NOT_LOADED",
	                                      "RAIL_EXEC_E_DECODE_FAILED",
	                                      "RAIL_EXEC_E_NOT_IN_ALLOWLIST",
	                                      "RAIL_EXEC_E_FILE_NOT_FOUND",
	                                      "RAIL_EXEC_E_FAIL",
	                                      "RAIL_EXEC_E_SESSION_LOCKED" };

/* =========================================================================
 * client/X11/xf_rail.c:1005-1022 -- xf_rail_server_execute_result,
 * BYTE-FOR-BYTE from data_cve/cve_481f3abb/target/original_function.c.
 * ========================================================================= */
static UINT xf_rail_server_execute_result(RailClientContext* context,
                                          const RAIL_EXEC_RESULT_ORDER* execResult)
{
	WINPR_ASSERT(context);
	WINPR_ASSERT(execResult);

	xfContext* xfc = (xfContext*)context->custom;
	WINPR_ASSERT(xfc);

	if (execResult->execResult != RAIL_EXEC_S_OK)
	{
		WLog_ERR(TAG, "RAIL exec error: execResult=%s NtError=0x%X\n",
		         error_code_names[execResult->execResult], execResult->rawResult);
		freerdp_abort_connect_context(&xfc->common.context);
	}

	return CHANNEL_RC_OK;
}
/* ==== end verbatim ==== */

int main(int argc, char** argv)
{
    if (argc < 2)
        return 0;
    FILE* f = fopen(argv[1], "rb");
    if (!f)
        return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* HEAP-allocate the raw input so ASAN instruments it. */
    unsigned char* buf = (unsigned char*)malloc((size_t)sz > 0 ? (size_t)sz : 1);
    if (!buf) { fclose(f); return 0; }
    size_t n = (sz > 0) ? fread(buf, 1, (size_t)sz, f) : 0;
    fclose(f);

    /* FDP-style argument construction: first 2 bytes (LE) -> the unchecked
     * OOB index (execResult->execResult); next 4 bytes (LE) -> rawResult
     * (inert, only ever %X-formatted, never used to index anything). */
    UINT16 exec_result = 0;
    UINT32 raw_result = 0;
    if (n >= 2)
        exec_result = (UINT16)(buf[0] | ((UINT16)buf[1] << 8));
    if (n >= 6)
        raw_result = (UINT32)buf[2] | ((UINT32)buf[3] << 8) |
                     ((UINT32)buf[4] << 16) | ((UINT32)buf[5] << 24);

    xfContext xfc;
    memset(&xfc, 0, sizeof(xfc));

    RailClientContext ctx;
    ctx.handle = NULL;
    ctx.custom = &xfc;

    RAIL_EXEC_RESULT_ORDER order;
    order.flags = 0;
    order.execResult = exec_result;
    order.rawResult = raw_result;
    order.exeOrFile.length = 0;
    order.exeOrFile.string = NULL;

    UINT rc = xf_rail_server_execute_result(&ctx, &order);
    (void)rc;

    free(buf);
    return 0;
}
