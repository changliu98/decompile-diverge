static inline void cgi_execute_child(connection_t* connection_prop,string_t* post_param,char * executor,char* real_basedir,int *wpipe,int *ipipe) {
    char* errormsg = NULL;
    close(wpipe[0]); //Closes unused end of the pipe

    close(STDOUT);
    if (dup(wpipe[1]) == -1) { //Redirects the stdout
        errormsg = "dup() failed";
        goto error;
    }

#ifdef HIDE_CGI_ERRORS
    close(STDERR);
#endif
    //Redirecting standard input only if there is POST data
    if (post_param->data != NULL) {//Send post data to script's stdin
        close(STDIN);
        if (dup(ipipe[0]) == -1) {
            errormsg = "dup() failed";
            goto error;
        }
    }

    environ = NULL; //Clear env vars

    if (strlen(executor) == 0) {
        executor = malloc(connection_prop->strfile_len + 1);
        strncpy(executor, connection_prop->strfile, connection_prop->strfile_len);
    }

    cgi_set_http_env_vars(connection_prop->http_param);
    cgi_set_SERVER_ADDR_PORT(myio_getfd(connection_prop->sock));
    cgi_set_env_vars(connection_prop, real_basedir);
    cgi_set_env_content_length();
    char *filename = cgi_child_chdir(connection_prop);

    alarm(SCRPT_TIMEOUT); //Sets the timeout for the script
    execl(executor, executor, filename, (char *)0);
#ifdef SERVERDBG
    syslog(LOG_ERR,"Execution of %s failed", executor);
    perror("Execution of the page failed");
#endif
error:
#ifdef SERVERDBG
    if (errormsg)
        syslog(LOG_ERR, "%s", errormsg);
#endif
    exit(1);

}