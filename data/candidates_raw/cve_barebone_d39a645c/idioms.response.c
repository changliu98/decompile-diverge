void xfaDestroyAppWindow(struct _xfAppWindow *appWindow)
{
 if (appWindow->image)
 {
  appWindow->image->data = ((void *)0);
  ossCloseThread(&appWindow->image->thread);
  appWindow->image = ((void *)0);
 }
}