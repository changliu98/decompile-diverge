int func0(char *s, int n) {
    char *t;
    int rv;
    char *p;
    char *q;

    p = s;
    q = s + (n < 0? -n : n);
    t = s;
    if (n < 0)
        rv = -n;
    else
        rv = n;
    do {
        *q = '0' + rv % 10;
        rv /= 10;
    } while (rv);
    if (n < 0)
        *q = '-';
    else
        q++;
    while (q < s + n) {
        *p++ = *q++;
    }
    *p = '\0';
    return p - s;
}