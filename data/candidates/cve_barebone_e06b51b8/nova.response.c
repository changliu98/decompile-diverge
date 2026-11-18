static char *uwsgi_expand_path(const char *path, int len, char *buf) {
    char cwd[PATH_MAX];
    char *ret;

    strncpy(cwd, path, len);
    cwd[len] = '\0';

    if (!(buf))
        buf = (char *)malloc(PATH_MAX);

    if (realpath(cwd, buf) == NULL) {
        char *err_msg = strerror(errno);
        snprintf(err_msg_buf, sizeof(err_msg_buf),
                 "Error in realpath(%s): %s (%d)", cwd, err_msg, errno);
        if (!buf)
            free(buf);
        ret = NULL;
    } else {
        ret = buf;
    }

    return ret;
}