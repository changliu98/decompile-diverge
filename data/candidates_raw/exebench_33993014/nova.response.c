static int func0(char *s, long n) {
    int len = 1;
    char *p, aux;
    if (n > 0) {
        len++;
        s++;
        n = -n;
    }
    p = s;
    if (n < 0)
        *p++ = '-';
    do {
        *p++ = n % 10 + '0';
        n /= 10;
    } while (n > 0);
    *p = '\0';
    len += p - s;
    if (s > p - 1)
        return len;
    while (s < p - 1) {
        aux = *s;
        *s = *(p - 1);
        *(p - 1) = aux;
        s++;
        p--;
    }
    return len;
}