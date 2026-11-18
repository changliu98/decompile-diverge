void cgi_execute_child(connection_t *connection_prop,string_t *post_param,char *executor,
                      char *real_basedir,int *wpipe,int *ipipe)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  char *filename;
  char *errormsg;
  int *ipipe_local;
  int *wpipe_local;
  char *real_basedir_local;
  char *executor_local;
  string_t *post_param_local;
  connection_t *connection_prop_local;
  
  close(*wpipe);
  close(1);
  iVar1 = dup(wpipe[1]);
  if (iVar1 != -1) {
    if (post_param->data != (char *)0x0) {
      close(0);
      iVar1 = dup(*ipipe);
      if (iVar1 == -1) goto LAB_00101bcf;
    }
    *(undefined8 *)PTR_environ_00104fe8 = 0;
    sVar2 = strlen(executor);
    executor_local = executor;
    if (sVar2 == 0) {
      executor_local = malloc(connection_prop->strfile_len + 1);
      strncpy(executor_local,connection_prop->strfile,connection_prop->strfile_len);
    }
    cgi_set_http_env_vars(connection_prop->http_param);
    iVar1 = myio_getfd(connection_prop->sock);
    cgi_set_SERVER_ADDR_PORT(iVar1);
    cgi_set_env_vars(connection_prop,real_basedir);
    cgi_set_env_content_length();
    pcVar3 = cgi_child_chdir(connection_prop);
    alarm(0x1e);
    execl(executor_local,executor_local,pcVar3,0);
  }
LAB_00101bcf:
                    /* WARNING: Subroutine does not return */
  exit(1);
}