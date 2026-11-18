char *strjoinv(char **args, int count) {
    int i;
    int len = 0;
    for (i = 0; ; i++) {
        if (i >= count) break;
        len += strlen(args[i]);
    }
    char *buf = malloc(len + 1);
    if (!buf) {
        goto err;
    }
    buf[0] = '\0';
    for (i = 0; ; i++) {
        if (i >= count) break;
        strcat(buf, args[i]);
    }
    return buf;

err:
    return NULL;
}