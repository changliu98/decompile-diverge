void cgi_execute_child(connection_t *connection_prop, string_t *post_param, char *executor, char *real_basedir, int *wpipe, int *ipipe)
{
    char *filename;
    char *errormsg;
    char *content_length;
    static char *environ[] = { NULL };

    close(wpipe[0]);
    close(1);
    if (-1 == dup(wpipe[1])) {
        exit(1);
    }

    if (post_param->data) {
        close(0);
        if (-1 == dup(ipipe[0])) {
            exit(1);
        }
    }

    environ[0] = NULL;

    if (strlen(executor) == 0) {
        executor = malloc(connection_prop->strfile_len + 1);
        strncpy(executor, connection_prop->strfile, connection_prop->strfile_len);
    }

    cgi_set_http_env_vars(connection_prop->http_param);
    cgi_set_SERVER_ADDR_PORT(myio_getfd(connection_prop->sock));
    cgi_set_env_vars(connection_prop, real_basedir);
    cgi_set_env_content_length(post_param);

    filename = cgi_child_chdir(connection_prop);

    alarm(30);
    execl(executor, executor, filename, NULL);
    exit(1);
}