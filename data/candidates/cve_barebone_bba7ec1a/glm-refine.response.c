void __cdecl __noreturn cgi_execute_child(
        connection_t *connection_prop,
        string_t *post_param,
        char *executor,
        char *real_basedir,
        int *wpipe,
        int *ipipe)
{
  char *filename; // Target script filename obtained after chdir

  // 1. Close the parent's write end of the pipe and redirect stdout (fd 1)
  //    to the child's write end.
  close(*wpipe);
  close(STDOUT_FILENO);
  
  if (dup(wpipe[1]) != -1)
  {
    // 2. If there is no POST data, stdin is closed and not redirected.
    //    If there IS POST data, close stdin and redirect it to the read pipe.
    if (!post_param->data || (close(STDIN_FILENO), dup(*ipipe) != -1))
    {
      // 3. Clear the environment variables for a clean CGI execution
      environ = NULL;

      // 4. If no specific executor was provided, allocate and copy the target filename
      //    from the connection properties. (Note: original code lacks null-termination)
      if (!strlen(executor))
      {
        executor = (char *)malloc(connection_prop->strfile_len + 1);
        strncpy(executor, connection_prop->strfile, connection_prop->strfile_len);
      }

      // 5. Setup CGI environment variables
      cgi_set_http_env_vars(connection_prop->http_param);
      cgi_set_SERVER_ADDR_PORT(myio_getfd(connection_prop->sock));
      cgi_set_env_vars(connection_prop, real_basedir);
      cgi_set_env_content_length();

      // 6. Change directory to the script's location and get its filename
      filename = cgi_child_chdir(connection_prop);

      // 7. Set a 30-second execution timeout alarm
      alarm(30);

      // 8. Execute the CGI script
      execl(executor, executor, filename, NULL);
    }
  }
  
  // If any setup or redirection fails, terminate the child process
  exit(EXIT_FAILURE);
}