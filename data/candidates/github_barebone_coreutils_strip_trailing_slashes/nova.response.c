int strip_trailing_slashes(char *s) {
    char *p = trim(s);
    if (*p == '\0')
        p = s;
    char *q = p + strlen(p) - 1;
    int r = *q!= '\0';
    *q = '\0';
    return r & 1;
}