char *func0(char *s) {
    static char buf[10000];
    int i, j;
    for (i = 0, j = 0;; i++) {
        if (i >= strlen(s))
            break;
        if (i % 2 == 0)
            buf[j++] = s[i];
    }
    buf[j] = '\0';
    return buf;
}