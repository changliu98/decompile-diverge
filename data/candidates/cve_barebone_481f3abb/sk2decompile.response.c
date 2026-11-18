BOOL xf_rail_server_execute_result(xf_rail_t* rail,
                                   const RAIL_EXECUTE_RESULT* execResult) {
  xf_server_t server;
  assert(rail);
  assert(execResult);
  server = (xf_server_t)rail->pRailServer;
  assert(server);
  if (execResult->error) {
    WLog_Print_dbg_tag("com.freerdp.client.x11", 4, 229, "/work/harness.c",
                       "xf_rail_server_execute_result",
                       "RAIL exec error: execResult=%s NtError=0x%X\n",
                       rail_error_strings[execResult->error],
                       execResult->ntError);
    freerdp_abort_connect_context(&server->context);
  }
  return 0;
}