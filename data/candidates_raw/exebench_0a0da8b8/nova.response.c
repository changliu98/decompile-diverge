void func0(char *s) {
    char *p = s;
    char tmp;
    while (*p)
        p++;
    while (s < p) {
        tmp = *s;
        *s++ = *--p;
        *p = tmp;
    }
}