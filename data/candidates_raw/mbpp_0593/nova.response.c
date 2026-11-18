char *func0(char *string) {
    regex_t re;
    regmatch_t rm[1];
    char *p, *q, *r;
    int n;
    char buf[MAX_BUF];

    memcpy(buf, REGEX, sizeof(REGEX));
    r = (char *)malloc(strlen(string) + 1);
    regcomp(&re, buf, REG_EXTENDED);
    strcpy(r, string);
    p = r;
    while (1) {
        n = regexec(&re, p, 1, rm, 0);
        if (n!= 0)
            break;
        q = (char *)malloc(strlen(p));
        memcpy(q, p + rm[0].rm_so, rm[0].rm_eo - rm[0].rm_so + 1);
        p += rm[0].rm_eo + 1;
    }
    regfree(&re);
    return r;
}