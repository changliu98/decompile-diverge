Window xf_Pointer_get_window(xfContext *xfc)

{
  xfContext *xfc_local;
  Window local_10;
  
  if (xfc == (xfContext *)0x0) {
    WLog_Print_dbg_tag("com.freerdp.client.x11",3,0xa0,"/work/harness.c","xf_Pointer_get_window",
                       "xf_Pointer: Invalid context");
    local_10 = 0;
  }
  else if (xfc->remote_app == 0) {
    if (xfc->window == (xfWindow *)0x0) {
      WLog_Print_dbg_tag("com.freerdp.client.x11",3,0xb0,"/work/harness.c","xf_Pointer_get_window",
                         "xf_Pointer: Invalid window");
      local_10 = 0;
    }
    else {
      local_10 = xfc->window->handle;
    }
  }
  else if (xfc->appWindow == (xfAppWindow *)0x0) {
    WLog_Print_dbg_tag("com.freerdp.client.x11",3,0xa7,"/work/harness.c","xf_Pointer_get_window",
                       "xf_Pointer: Invalid appWindow");
    local_10 = 0;
  }
  else {
    local_10 = xfc->appWindow->handle;
  }
  return local_10;
}