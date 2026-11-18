void cgi_execute_child(cgi_t *cgi, cgi_conf_t *conf, char *cgi_path,
                       char *query_string, int *pipe_stdout, int *pipe_stdin) {
  char *cgi_dir;
  char *cgi_path_copy;
  close(pipe_stdout[0]);
  close(1);
  if (dup(pipe_stdout[1]) == -1) {
    exit(1);
  }
  if (conf->cgi_stdin) {
    close(0);
    if (dup(pipe_stdin[0]) == -1) {
      exit(1);
    }
  }
  environ = NULL;
  if (strlen(cgi_path) == 0) {
    cgi_path_copy = malloc(cgi->cgi_path_len + 1);
    strncpy(cgi_path_copy, cgi->cgi_path, cgi->cgi_path_len);
    cgi_path = cgi_path_copy;
  }
  cgi_set_http_env_vars(cgi->http_env_vars);
  cgi_set_SERVER_ADDR_PORT(myio_getfd(cgi->fd));
  cgi_set_env_vars(cgi, query_string);
  cgi_set_env_content_length();
  cgi_dir = cgi_child_chdir(cgi);
  alarm(30);
  execl(cgi_path, cgi_path, cgi_dir, NULL);
  exit(1);
}