static char *func0(char *s) {
    char *p;
    int i;
    static char buf[11701];

    p = s + strlen(s) - 2;
    for (i = p - 1; i > 0; i--) {
        if (strchr(B, *p) && strchr(B, *(p + 1)) && strchr(B, *(p - 1))) {
            buf[0] = *p;
            return buf;
        }
    }
    buf[0] = '\0';
    return buf;
}