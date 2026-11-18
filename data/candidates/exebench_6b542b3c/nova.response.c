char *trim(char *s, const char *bad) {
    char *p;
    char c;
    char *r;

    if (s == 0)
        return 0;

    for (p = s;; p++) {
        c = *p;
        if (c == 0)
            break;
        if (strchr(bad, c)!= 0) {
            *p = 0;
        } else {
            p--;
            break;
        }
    }

    r = s;
    return r;
}