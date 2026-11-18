static Window xf_Pointer_get_window(xfContext * xfc)
{
 Window window;

 if (!xfc)
 {
  WLog_Print_dbg_tag("com.freerdp.client.x11", 3, 160, "harness.c", "xf_Pointer_get_window", "xf_Pointer: Invalid context");
  window = 0;
 }
 else if (xfc->use_rdp5)
 {
  if (!xfc->rdp5)
  {
   WLog_Print_dbg_tag("com.freerdp.client.x11", 3, 167, "harness.c", "xf_Pointer_get_window", "xf_Pointer: Invalid appWindow");
   window = 0;
  }
  else
  {
   window = ((xfAppWindow*) xfc->rdp5)->window;
  }
 }
 else
 {
  if (!xfc->window)
  {
   WLog_Print_dbg_tag("com.freerdp.client.x11", 3, 176, "harness.c", "xf_Pointer_get_window", "xf_Pointer: Invalid window");
   window = 0;
  }
  else
  {
   window = ((xfWindow*) xfc->window)->handle;
  }
 }

 return window;
}