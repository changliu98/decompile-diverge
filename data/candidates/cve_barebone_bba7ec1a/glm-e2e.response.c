void cgi_execute_child(struct request_ctx* ctx, struct fd_state* fd_state, char* arg3, void* arg4, int* arg5, int* arg6) {
    char* err_msg = NULL;
    char* exec_path = arg3;
    char* chdir_path = NULL;

    // Close original stdin and stdout
    close(fd_state->fd_in);
    close(1);

    // Dup the input fd to stdout
    if (dup(fd_state->fd_out) == -1) {
        err_msg = "dup error"; // String at 0x3034
        goto exit_err;
    }

    // If ctx->fds is not null, set up stdin
    if (ctx->fds != NULL) {
        close(0);
        if (dup(*arg5) == -1) {
            err_msg = "dup error";
            goto exit_err;
        }
    }

    // Clear environment variables
    if (environ != NULL) {
        environ[0] = NULL;
    }

    // If script_path is empty, allocate and copy from ctx fields
    if (strlen(exec_path) == 0) {
        exec_path = (char*)malloc(ctx->field_50 + 1);
        strncpy(exec_path, ctx->field_48, ctx->field_50);
    }

    cgi_set_http_env_vars(ctx->field_28);
    cgi_set_SERVER_ADDR_PORT(myio_getfd(ctx->field_0));
    cgi_set_env_vars(ctx, arg4);
    cgi_set_env_content_length();
    
    chdir_path = cgi_child_chdir(ctx);
    
    // Set an alarm for 30 seconds
    alarm(30);
    
    // Execute the CGI script
    // Note: execl is a variadic function. The assembly passes exec_path twice,
    // followed by chdir_path, and a 0 (NULL) to terminate the varargs.
    execl(exec_path, exec_path, chdir_path, NULL);

exit_err:
    exit(1);
}