char *func0(char *s) {
    static char buf[1024];
    int i;

    strcpy(buf, s);
    for (i = 0;; i++) {
        if (buf[i] == 0)
            break;
        if (buf[i] =='' || buf[i] == ',' || buf[i] == '.')
            buf[i] = ':';
    }
    return buf;
}