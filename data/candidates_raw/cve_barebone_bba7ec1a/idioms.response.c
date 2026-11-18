void *http_post(void *arg)
{
  struct connection *connection = (connection *)arg;
  char *strfile;
  int *pipe;
  int i;
  int ret;
  int status;
  int *wpipe = (int *)pipe;
  int *ipipe = (int *)pipe + 1;
  close_pipe(*wpipe);
  close_pipe(1);
  if (write_to_pipe(wpipe[1]) == -1)
    return ((void *)0);
  if (post_param->data == ((void *)0))
  {
    close_pipe(0);
    if (write_to_pipe(*ipipe) == -1)
      return ((void *)0);
  }
  environ = ((void *)0);
  if (is_cgi(executor) == 0)
  {
    strfile = (char *)malloc(sizeof(char) * (connection->strfile_len + 1));
    get_strfile(strfile, connection->strfile, connection->strfile_len);
    executor = strfile;
  }
  get_http_param(connection->http_param);
  ret = get_http_sock(connection->sock);
  get_http_header(ret);
  get_http_body(connection, real_basedir);
  get_http_post(connection);
  strfile = get_http_strfile(connection);
  set_http_strfile(30);
  exec_http(strfile, executor, strfile, ((void *)0));
  return ((void *)0);
}