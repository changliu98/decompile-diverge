UINT xf_rail_server_execute_result(RailClientContext *context,RAIL_EXEC_RESULT_ORDER *execResult)

{
  rdpContext *context_00;
  xfContext *xfc;
  RAIL_EXEC_RESULT_ORDER *execResult_local;
  RailClientContext *context_local;
  
  if (context == (RailClientContext *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("context","/work/harness.c",0xdc,
                  "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)"
                 );
  }
  if (execResult != (RAIL_EXEC_RESULT_ORDER *)0x0) {
    context_00 = context->custom;
    if (context_00 != (rdpContext *)0x0) {
      if (execResult->execResult != 0) {
        WLog_Print_dbg_tag("com.freerdp.client.x11",4,0xe5,"/work/harness.c",
                           "xf_rail_server_execute_result",
                           "RAIL exec error: execResult=%s NtError=0x%X\n",
                           error_code_names[execResult->execResult],execResult->rawResult);
        freerdp_abort_connect_context(context_00);
      }
      return 0;
    }
                    /* WARNING: Subroutine does not return */
    __assert_fail("xfc","/work/harness.c",0xe0,
                  "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)"
                 );
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("execResult","/work/harness.c",0xdd,
                "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)"
               );
}