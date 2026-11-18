void itoa(int n, char s[])
{
    int i, j;
    char *p, *q, t;

    if (n < 0) {
        *s++ = '-';
        n = -n;
    }

    p = s;
    do {
        *s++ = n % 10 + '0';
    } while ((n /= 10) != 0);
    *s = '\0';

    q = p;
    while (q < --s) {
        t = *q;
        *q++ = *s;
        *s = t;
    }
}