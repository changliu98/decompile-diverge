int stb_appendchar(char *src, char app, int maxlen) {
    int len;
    if (!src) {
        int z = 0;
        ((void)0);
        return 0;
    }
    len = 0;
    while (src[len]) {
        ++len;
    }
    if (len >= maxlen - 1) {
        int z = 0;
        ((void)0);
        return 0;
    }
    src[len] = app;
    src[len + 1] = 0;
    return 1;
}