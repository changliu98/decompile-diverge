void reset_request(RespRequest *request)

{
  RespRequest *r;
  RespRequest *request_local;
  
  if (request != (RespRequest *)0x0) {
    request->state = 0;
    request->cur_argc = 0;
    request->argc = 0;
    if (request->argv != (RespSlice *)0x0) {
      free(request->argv);
    }
    request->argv = (RespSlice *)0x0;
    request->used_size = 0;
    request->pos = 0;
    request->skip_str = 0;
  }
  return;
}