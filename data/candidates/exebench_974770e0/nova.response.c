char *envstring(char *s) {
    char *p = s;
    for (;;) {
        if (*p == 0) {
            break;
        }
        if (*p == '-') {
            *p = '_';
        } else if ('a' <= *p && *p <= 'z') {
            *p = *p - 'a' + 'A';
        } else if ('A' <= *p && *p <= 'Z') {
            *p = *p - 'A' + 'a';
        } else {
            *s = 0;
            break;
        }
        p++;
    }
    return s;
}