UINT xf_rail_server_execute_result(RailClientContext *rail_client_ctx, RAIL_EXEC_RESULT_ORDER *rail_exec_result)
{
    // Validate that the context pointer is not NULL
    if (rail_client_ctx == (RailClientContext *)0x0) {
        __assert_fail("context", "/work/harness.c", 0xdc,
                      "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");
    }
    
    // Check if execResult pointer is valid
    if (rail_exec_result != (RAIL_EXEC_RESULT_ORDER *)0x0) {
        // Retrieve the custom RDP context from the RailClientContext
        rdpContext *rdp_ctx = rail_client_ctx->custom;
        
        // Validate that the custom context is not NULL
        if (rdp_ctx != (rdpContext *)0x0) {
            // Check if the execution result indicates an error (non-zero execResult)
            if (rail_exec_result->execResult != 0) {
                // Log the RAIL execution error details including error code and NT error
                WLog_Print_dbg_tag("com.freerdp.client.x11", 4, 0xe5, "/work/harness.c",
                                   "xf_rail_server_execute_result",
                                   "RAIL exec error: execResult=%s NtError=0x%X\n",
                                   error_code_names[rail_exec_result->execResult], rail_exec_result->rawResult);
                // Abort the connection due to the error
                freerdp_abort_connect_context(rdp_ctx);
            }
            // Return success status
            return 0;
        }
        // Assert failure if custom context is NULL
        __assert_fail("xfc", "/work/harness.c", 0xe0,
                      "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");
    }
    // Assert failure if execResult pointer is NULL
    __assert_fail("execResult", "/work/harness.c", 0xdd,
                  "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");
}