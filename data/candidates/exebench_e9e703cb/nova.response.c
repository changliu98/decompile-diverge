char *int2str(int n, char *s, int base) {
    static char digits[] = "0123456789ABCDEF";
    char buf[33], *p;
    int i;

    memset(buf, 0, sizeof(buf));
    p = buf + sizeof(buf);
    i = n;
    if (base < 2 || base > 16) {
        *s = '\0';
        return s;
    }
    do {
        *--p = digits[i % base];
        i /= base;
    } while (i!= 0);
    if (n < 0 && base == 10)
        *--p = '-';
    while ((*s++ = *++p)!= '\0')
        ;
    *s = '\0';
    return s;
}