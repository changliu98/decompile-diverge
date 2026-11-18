UINT xf_rail_server_execute_result(RailClientContext* context, const RAIL_EXEC_RESULT_ORDER* execResult)
{
    rdpContext* rdp;
    xfContext* xfc;

    do { if (!(context)) { __assert_fail("context", "/work/harness.c", 220, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)"); } } while (0);
    do { if (!(execResult)) { __assert_fail("execResult", "/work/harness.c", 221, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)"); } } while (0);

    rdp = context->custom;
    do { if (!(rdp)) { __assert_fail("rdp", "/work/harness.c", 224, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)"); } } while (0);

    xfc = (xfContext*)rdp->xwin;
    do { if (!(xfc)) { __assert_fail("xfc", "/work/harness.c", 224, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)"); } } while (0);

    if (execResult->execResult != 0)
    {
        WLog_Print_dbg_tag("com.freerdp.client.x11", 4, 229, "/work/harness.c", "xf_rail_server_execute_result", "RAIL exec error: execResult=%s NtError=0x%X\n", error_code_names[execResult->execResult], execResult->rawResult);
        freerdp_abort_connect_context(rdp);
    }

    return 0;
}