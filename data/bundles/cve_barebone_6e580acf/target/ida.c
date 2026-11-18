Window __cdecl xf_Pointer_get_window(xfContext *xfc)
{
  if ( !xfc )
    return 0LL;
  if ( xfc->remote_app )
  {
    if ( xfc->appWindow )
      return xfc->appWindow->handle;
    else
      return 0LL;
  }
  else if ( xfc->window )
  {
    return xfc->window->handle;
  }
  else
  {
    return 0LL;
  }
}