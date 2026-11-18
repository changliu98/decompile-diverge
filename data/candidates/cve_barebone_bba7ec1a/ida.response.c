void __cdecl __noreturn cgi_execute_child(
        connection_t *connection_prop,
        string_t *post_param,
        char *executor,
        char *real_basedir,
        int *wpipe,
        int *ipipe)
{
  int v6; // eax
  char *filename; // [rsp+0h] [rbp-40h]

  close(*wpipe);
  close(1);
  if ( dup(wpipe[1]) != -1 )
  {
    if ( !post_param->data || (close(0), dup(*ipipe) != -1) )
    {
      environ = 0LL;
      if ( !strlen(executor) )
      {
        executor = (char *)malloc(connection_prop->strfile_len + 1);
        strncpy(executor, connection_prop->strfile, connection_prop->strfile_len);
      }
      cgi_set_http_env_vars(connection_prop->http_param);
      v6 = myio_getfd(connection_prop->sock);
      cgi_set_SERVER_ADDR_PORT(v6);
      cgi_set_env_vars(connection_prop, real_basedir);
      cgi_set_env_content_length();
      filename = cgi_child_chdir(connection_prop);
      alarm(0x1Eu);
      execl(executor, executor, filename, 0LL);
    }
  }
  exit(1);
}