static UINT xf_rail_server_execute_result(RailClientContext * rail, const RAIL_EXEC_RESULT_ORDER * execResult)
{
 freerdp *instance;
 do { if (!(context)) { ___assert_fail("context", "harness.c", 220, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER * execResult)"); } } while (0);
 do { if (!(execResult)) { ___assert_fail("execResult", "harness.c", 221, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER * execResult)"); } } while (0);

 instance = (freerdp *) rail->handle;

 do { if (!(instance)) { ___assert_fail("xfc", "harness.c", 224, "UINT xf_rail_server_execute_result(RailClientContext *, const RAIL_EXEC_RESULT_ORDER * execResult)"); } } while (0);

 if ((execResult->execResult & 0x0000FFFF) != 0x0000)
 {
  WLog_Print_dbg_tag("com.freerdp.client.x11", 4, 229, "harness.c", "xf_rail_server_execute_result",
       "RAIL exec error: execResult=%s NtError=0x%X\n",
       error_code_names[execResult->execResult & 0x0000FFFF], execResult->ntError);
  freerdp_abort_connect_context(instance);
 }

 return 0;
}