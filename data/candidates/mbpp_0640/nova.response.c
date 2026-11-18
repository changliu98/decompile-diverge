char *func0(const char *s) {
    int n, i, j;
    char *t, *p;
    regex_t re;
    regmatch_t rm[2];

    n = strlen(s);
    t = (char *)malloc(n + 1);
    strcpy(t, s);

    if (regcomp(&re, "\\(([^\\)]+)\\)", REG_EXTENDED) == 0) {
        while (regexec(&re, t, 2, rm, 0) == 0) {
            i = rm[0].rm_so;
            j = rm[0].rm_eo;
            p = (char *)malloc(n + 1);
            strncpy(p, t + i, j - i + 1);
            strcpy(t + i, t + strlen(t) - j + 1);
        }
        regfree(&re);
    }
    return t;
}