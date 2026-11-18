void itoa(int n, char *s, int base)
{
    char buf[33];
    int sign = n;
    char *digits = "0123456789ABCDEF";
    int i;

    if (n < 0)
        n = -n;

    i = 0;
    if (!n)
        buf[i++] = '0';
    while (n) {
        buf[i++] = digits[n % base];
        n /= base;
    }

    if (sign < 0)
        buf[i++] = '-';

    while (i--)
        *s++ = buf[i];

    *s = '\0';
}