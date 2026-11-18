static char func0(char *str) {
    char c;
    char *p;

    if (!str ||!*str)
        return '\0';

    p = str;
    while (*p)
        p++;
    p--;

    c = *p;
    *p = '\0';

    return c;
}