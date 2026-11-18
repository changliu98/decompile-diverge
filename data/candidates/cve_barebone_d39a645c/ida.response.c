void __cdecl xf_AppWindowDestroyImage(xfAppWindow *appWindow)
{
  if ( appWindow->image )
  {
    appWindow->image->data = 0LL;
    ossCloseThread(appWindow->image);
    appWindow->image = 0LL;
  }
}