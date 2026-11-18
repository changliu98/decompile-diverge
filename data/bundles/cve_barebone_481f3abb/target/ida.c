UINT __cdecl xf_rail_server_execute_result(RailClientContext *context, const RAIL_EXEC_RESULT_ORDER *execResult)
{
  xfContext *xfc; // [rsp+18h] [rbp-18h]

  if ( !context )
    __assert_fail(
      "context",
      "/work/harness.c",
      0xDCu,
      "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");
  if ( !execResult )
    __assert_fail(
      "execResult",
      "/work/harness.c",
      0xDDu,
      "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");
  xfc = (xfContext *)context->custom;
  if ( !xfc )
    __assert_fail(
      "xfc",
      "/work/harness.c",
      0xE0u,
      "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER *)");
  if ( execResult->execResult )
  {
    WLog_Print_dbg_tag(
      "com.freerdp.client.x11",
      4u,
      0xE5uLL,
      "/work/harness.c",
      "xf_rail_server_execute_result",
      "RAIL exec error: execResult=%s NtError=0x%X\n",
      (&error_code_names)[execResult->execResult],
      execResult->rawResult);
    freerdp_abort_connect_context(&xfc->common.context);
  }
  return 0;
}