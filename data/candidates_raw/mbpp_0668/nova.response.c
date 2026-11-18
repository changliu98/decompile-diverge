char *func0(char *str, char *regex) {
    regex_t re;
    regmatch_t rm[1];
    size_t n = 0;
    char *p, *r;
    if (regcomp(&re, regex, REG_EXTENDED))
        return NULL;
    while (!regexec(&re, str, 1, rm, 0)) {
        p = str + n;
        r = (char *)alloca(strlen(p) + rm[0].rm_eo + 1);
        memcpy(r, p + rm[0].rm_so, strlen(p + rm[0].rm_so) - rm[0].rm_eo + 1);
        n = rm[0].rm_so + 1;
    }
    regfree(&re);
    return p;
}