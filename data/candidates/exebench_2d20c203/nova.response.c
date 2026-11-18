char *str_rev(char *s) {
    char *p = s, *q = s;
    char c;
    while (*q++)
        ;
    for (--q; p < --q; p++) {
        c = *p;
        *p = *q;
        *q = c;
    }
    return s;
}