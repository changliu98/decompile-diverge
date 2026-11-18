char *func0(int n, char *s, int b) {
    static char r[] = "0123456789ABCDEF";
    char *p, *q;
    char *o;
    if (b < 2 || b > 36) {
        *s = 0;
        return s;
    }
    p = s;
    q = s;
    o = s;
    do {
        *p = r[n % b];
        n /= b;
    } while (n);
    *p-- = 0;
    while (q < p) {
        char t = *q;
        *q++ = *p;
        *p-- = t;
    }
    return o;
}