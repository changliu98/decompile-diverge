void resp_request_init(struct resp_request *request)
{
  if (request == ((void *)0))
    return;
  request->state = RESP_ST_IN_KEY;
  request->cur_argc = 0;
  request->argc = 0;
  if (request->argv != ((void *)0))
    free(request->argv);
  request->argv = ((void *)0);
  request->used_size = 0;
  request->pos = 0;
  request->skip_str = 0;
}