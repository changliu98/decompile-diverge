char *func0(char *s, char *t) {
    char *r = s;

    while (1) {
        *s++ = *t++;
        if (*s == '\0')
            return r;
    }
}