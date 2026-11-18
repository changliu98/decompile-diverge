static char *regtilde(char *p, int is_regexp) {
    char *q, *r;
    char *s = p;

    for (;;) {
        if (*s == '\0')
            break;
        if (*s == '~' &&!is_regexp)
            break;
        if (*s == '\\' && *(s + 1) == '~' &&!is_regexp) {
            s++;
            continue;
        }
        if (*s == '\\' && *(s + 1) == '\0') {
            s++;
            continue;
        }
        if (is_regexp)
            s += strlen(s);
        else
            s += strlen(s) + 1;
    }
    for (;;) {
        if (*s == '\\' && *(s + 1) == '\0') {
            s++;
            continue;
        }
        if (is_regexp)
            q = strdup(s);
        else
            q = strdup(s + 1);
        if (is_regexp)
            r = strdup(s);
        else
            r = strdup(s + 1);
        if (is_regexp)
            strcpy(s, r);
        else
            strcpy(s + 1, r);
        if (is_regexp)
            strcpy(s + 1, q);
        else
            strcpy(s, q);
        if (p == s)
            break;
        s = p;
        s += strlen(s) + 1;
    }
    free(p);
    return s;
}