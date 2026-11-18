char *itoa(int n, char *s, int b) {
    static char r[] = "0123456789ABCDEFGHIJ";
    char *p, *q;
    int d;

    if (b < 2 || b > 36) {
        *s = '\0';
        return s;
    }
    p = s;
    q = s;
    if (n < 0)
        *p++ = '-';
    do {
        d = n % b;
        *p++ = r[d];
        n /= b;
    } while (n!= 0);
    *p-- = '\0';
    while (q < p) {
        d = *q;
        *q++ = *p;
        *p-- = d;
    }
    return s;
}