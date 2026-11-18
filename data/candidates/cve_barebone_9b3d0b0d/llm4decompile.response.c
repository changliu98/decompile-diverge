Window
xf_Pointer_get_window(xfContext *xfc)
{
  Window w;

  if (xfc == NULL)
  {
    WLog_Print_dbg_tag("com.freerdp.client.x11", 3, 160, "/work/harness.c", "xf_Pointer_get_window", "xf_Pointer: Invalid context");
    return 0;
  }

  if (xfc->remote_app)
  {
    if (xfc->appWindow == NULL)
    {
      WLog_Print_dbg_tag("com.freerdp.client.x11", 3, 167, "/work/harness.c", "xf_Pointer_get_window", "xf_Pointer: Invalid appWindow");
      return 0;
    }
    w = xfc->appWindow->handle;
  }
  else
  {
    if (xfc->window == NULL)
    {
      WLog_Print_dbg_tag("com.freerdp.client.x11", 3, 176, "/work/harness.c", "xf_Pointer_get_window", "xf_Pointer: Invalid window");
      return 0;
    }
    w = xfc->window->handle;
  }

  return w;
}