void __cdecl reset_request(RespRequest *request)
{
  if ( request )
  {
    request->state = 0;
    request->cur_argc = 0;
    request->argc = 0;
    if ( request->argv )
      free(request->argv);
    request->argv = 0LL;
    request->used_size = 0;
    request->pos = 0;
    request->skip_str = 0;
  }
}