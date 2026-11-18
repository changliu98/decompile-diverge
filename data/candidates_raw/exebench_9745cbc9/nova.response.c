static int func0(char *buf, int n) {
    char *p, *e;
    int x, sign;

    e = p = buf + BUFSIZE - 1;
    if (n < 0)
        x = -n;
    else
        x = n;
    do {
        *e = x % 10 + '0';
        x /= 10;
    } while (x);
    if (n < 0)
        *e = '-';
    else
        e++;
    while (e < buf + BUFSIZE) {
        *e = *p;
        p++;
        e++;
    }
    *e = '\0';
    return e - buf;
}