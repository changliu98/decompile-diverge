char* read_prefix(char *str, int *is_redir, int *is_pipe, int *is_background, int *is_and, int *is_or, int *is_semicolon) {
    *is_redir = 0;
    *is_pipe = 0;
    *is_and = 0;
    *is_or = 1;
    *is_background = 0;
    *is_semicolon = 0;
    *is_or = 0; // Note: overwritten due to argument order/initialization sequence

    while (1) {
        char c = *str;
        if (c == '<') {
            *is_redir = 1;
            *is_and = 1;
        } else if (c == '>') {
            *is_redir = 1;
            *is_pipe = 1;
        } else if (c == '&') {
            *is_redir = 1;
            *is_and = 1;
            *is_pipe = 1;
        } else if (c == '+') {
            *is_or = 0;
        } else if (c == ':') {
            *is_redir = 1;
            *is_and = 1;
            *is_or = 0;
            *is_or = 1; // Overwritten
        } else if (c == '#') {
            *is_background = 1;
        } else if (c == '!') {
            *is_semicolon = 1;
        } else {
            break;
        }
        str++;
    }
    
    return str;
}