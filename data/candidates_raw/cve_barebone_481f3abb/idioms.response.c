int xf_rail_server_execute_result(void *context, struct RAIL_EXEC_RESULT_ORDER *execResult)
{
    struct RailClientContext *railContext = (RailClientContext *)context;
    struct xfContext *xfc = ((void *)0);
    if (railContext == ((void *)0))
        log_fatal("context", "/work/harness.c", 220, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");
    if (execResult == ((void *)0))
        log_fatal("execResult", "/work/harness.c", 221, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");
    xfc = (struct xfContext *)railContext->custom;
    if (xfc == ((void *)0))
        log_fatal("xfc", "/work/harness.c", 224, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");
    if (execResult->execResult != RAIL_EXEC_OK)
    {
        log_error("com.freerdp.client.x11", X11_LOG_MODULE, X11_LOG_CATEGORY, "/work/harness.c", __FUNCTION__, "RAIL exec error: execResult=%s NtError=0x%X\n", error_code_names[execResult->execResult], execResult->rawResult);
        xf_rail_client_disconnect(&xfc->common);
    }
    return 0;
}