void messageAddArgument(struct Message *msg, const char *arg) {
    assert(msg != NULL);
    
    if (arg == NULL) {
        return;
    }
    
    // Skip leading whitespace
    while (isspace((unsigned char)*arg)) {
        arg++;
    }
    
    if (*arg == '\0' || !usefulArg(arg)) {
        return;
    }
    
    int i = 0;
    while (i < msg->arg_count && msg->arguments[i] != NULL) {
        if (strcasecmp(arg, msg->arguments[i]) == 0) {
            return;
        }
        i++;
    }
    
    if (i == msg->arg_count) {
        msg->arg_count++;
        char **new_args = cli_realloc(msg->arguments, msg->arg_count * sizeof(char *));
        if (new_args == NULL) {
            msg->arg_count--;
            return;
        }
        msg->arguments = new_args;
    }
    
    char *parsed_arg = rfc2231(arg);
    msg->arguments[i] = parsed_arg;
    
    if (parsed_arg == NULL) {
        return;
    }
    
    if (strchr(parsed_arg, '=') == NULL) {
        if (strncmp(parsed_arg, "boundary", 8) == 0) {
            parsed_arg[8] = '=';
        } else if (*parsed_arg == '\0') {
            free(msg->arguments[i]);
            msg->arguments[i] = NULL;
            return;
        }
    }
    
    if (strncasecmp(parsed_arg, "charset", 9) == 0 || strncasecmp(parsed_arg, "name", 5) == 0) {
        if (messageGetMimeType(msg) == 0) {
            messageSetMimeType(msg, "text/plain");
        }
    }
}