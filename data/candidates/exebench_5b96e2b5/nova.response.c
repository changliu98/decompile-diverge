void reverse(char *s) {
    char *p = s;
    char tmp;
    while (*p)
        p++;
    p--;
    while (s < p) {
        tmp = *s;
        *s = *p;
        *p = tmp;
        s++;
        p--;
    }
}