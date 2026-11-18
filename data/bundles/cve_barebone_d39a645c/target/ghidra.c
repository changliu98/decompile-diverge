void xf_AppWindowDestroyImage(xfAppWindow *appWindow)

{
  xfAppWindow *appWindow_local;
  
  if (appWindow->image != (XImage *)0x0) {
    appWindow->image->data = (char *)0x0;
    XDestroyImage(appWindow->image);
    appWindow->image = (XImage *)0x0;
  }
  return;
}