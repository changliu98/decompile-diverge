static unsigned long xf_Pointer_get_window(struct xfContext *xfc)
{
  if (xfc == ((void *)0))
  {
    xf_log("com.freerdp.client.x11", 3, 160, "/work/harness.c", __FUNCTION__, "xf_Pointer: Invalid context");
    return 0;
  }
  if (xfc->remote_app == ((void *)0))
  {
    if (xfc->window == ((void *)0))
    {
      xf_log("com.freerdp.client.x11", 3, 176, "/work/harness.c", __FUNCTION__, "xf_Pointer: Invalid window");
      return 0;
    }
    return xfc->window->handle;
  }
  if (xfc->appWindow == ((void *)0))
  {
    xf_log("com.freerdp.client.x11", 3, 167, "/work/harness.c", __FUNCTION__, "xf_Pointer: Invalid appWindow");
    return 0;
  }
  return xfc->appWindow->handle;
}