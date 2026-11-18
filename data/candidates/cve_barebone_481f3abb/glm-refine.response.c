UINT xf_rail_server_execute_result(RailClientContext *context, const RAIL_EXEC_RESULT_ORDER *execResult)
{
    xfContext *xfc;

    // Validate essential pointers
    if (!context)
        __assert_fail("context", "/work/harness.c", 0xDCu, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");
    if (!execResult)
        __assert_fail("execResult", "/work/harness.c", 0xDDu, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");

    xfc = (xfContext *)context->custom;
    if (!xfc)
        __assert_fail("xfc", "/work/harness.c", 0xE0u, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");

    // Check if the remote execution failed
    if (execResult->execResult)
    {
        WLog_Print_dbg_tag(
            "com.freerdp.client.x11",
            WLOG_ERROR, // 4u corresponds to WLOG_ERROR in FreeRDP
            0xE5uLL,
            "/work/harness.c",
            "xf_rail_server_execute_result",
            "RAIL exec error: execResult=%s NtError=0x%X\n",
            error_code_names[execResult->execResult], // Cleaned up array access
            execResult->rawResult);

        freerdp_abort_connect_context(&xfc->common.context);
    }

    return 0;
}