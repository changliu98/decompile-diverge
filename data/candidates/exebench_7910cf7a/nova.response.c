char *strset(char *s, int c) {
    char *t = s;
    for (;;) {
        if (*t == '\0') {
            return s;
        }
        *t = c;
        t++;
    }
}