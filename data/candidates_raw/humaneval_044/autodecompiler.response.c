void itob(int n, int base, char s[])
{
    int i, j, sign;
    char t[50];

    if ((sign = n) < 0)
        n = -n;

    i = 0;
    do {
        t[i++] = n % base + '0';
    } while ((n /= base) > 0);

    if (sign < 0)
        t[i++] = '-';

    j = 0;
    while (i > 0)
        s[j++] = t[--i];
    s[j] = '\0';
}