static regex_t *
func0(const char *pattern, const char *modifiers) {
    static regex_t regex;
    static char errbuf[100];
    int eval;
    char *p;

    if (strstr(pattern, modifiers)!= NULL) {
        return &regex;
    }

    memset(errbuf, 0, sizeof(errbuf));
    errbuf[0] = '^';
    strcat(errbuf, pattern);
    regcomp(&regex, errbuf, 0);

    eval = regexec(&regex, pattern, 0, NULL, 0);
    if (eval == 0) {
        p = &s00;
    } else {
        p = &s01;
    }
    return &regex;
}