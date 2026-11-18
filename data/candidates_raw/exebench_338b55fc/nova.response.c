void func0(char *s) {
    char *p = s;
    char *q = s;
    while (*p)
        p++;
    p--;
    while (q < p) {
        *q ^= *p;
        *p ^= *q;
        *q ^= *p;
        q++;
        p--;
    }
}