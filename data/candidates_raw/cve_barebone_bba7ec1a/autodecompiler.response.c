static void cgi_child(connection_t *cp, post_t *pp, char *prog, char *basedir,
 int wpipe[], int ipipe[])
{
 char *path;
 char *errormsg = NULL;

 close(wpipe[0]);
 close(1);
 if (dup(wpipe[1]) == -1) {
  errormsg = "dup() failed";
  goto error;
 }

 if (pp->is_form) {
  close(0);
  if (dup(ipipe[0]) == -1) {
   errormsg = "dup() failed";
   goto error;
  }
 } else {

  environ_ptr[0] = NULL;

  if (strlen(prog) == 0) {
   prog = malloc(cp->req.pathlen + 1);
   strncpy(prog, cp->req.path, cp->req.pathlen);
  }

  cgi_set_http_env_vars(cp->req.headers);
  cgi_set_SERVER_ADDR_PORT(myio_getfd(cp->client));
  cgi_set_env_vars(cp, basedir);
  cgi_set_env_content_length(cp);

  path = cgi_child_chdir(cp);

  alarm(30);
  execl(prog, prog, path, (char *)0);
 } error:
 exit(1);
}