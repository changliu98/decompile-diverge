void reset_request(RespRequest *req)
{
  if (req) {
    req->state = 0;
    req->cur_argc = 0;
    req->argc = 0;
    free(req->argv);
    req->argv = NULL;
    req->used_size = 0;
    req->pos = 0;
    req->skip_str = 0;
  }
}