void itoa(int n, char *s)
{
    char *p = s;
    char *q = NULL;
    int m, c;

    if (n < 0) {
        m = -n;
        *p++ = '-';
    } else {
        m = n;
    }

    q = p;

    do {
        c = m % 10 + '0';
        *q = c;
        m /= 10;
        q++;
    } while (m);

    *q = '\0';

    while (p < --q) {
        c = *p;
        *p = *q;
        *q = c;
        p++;
    }
}