char *func0(char *s) {
    static char buf[11808];
    int i, j;
    for (i = 0, j = 1;; j++) {
        if (j >= strlen(s))
            j = 0;
        if (j % 2 == 0)
            buf[i++] = s[j - 1];
    }
    buf[i] = '\0';
    return buf;
}