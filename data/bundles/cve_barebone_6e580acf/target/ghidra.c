Window xf_Pointer_get_window(xfContext *xfc)

{
  xfContext *xfc_local;
  Window local_10;
  
  if (xfc == (xfContext *)0x0) {
    local_10 = 0;
  }
  else if (xfc->remote_app == 0) {
    if (xfc->window == (xfWindow *)0x0) {
      local_10 = 0;
    }
    else {
      local_10 = xfc->window->handle;
    }
  }
  else if (xfc->appWindow == (xfAppWindow *)0x0) {
    local_10 = 0;
  }
  else {
    local_10 = xfc->appWindow->handle;
  }
  return local_10;
}