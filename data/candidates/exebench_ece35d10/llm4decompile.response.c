char *itoa(int n, char *str, int radix)
{

    char digit[37];
    char *p1, *p2;
    int i;

    memcpy(digit, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", 37);

    if (str == NULL || radix < 2 || radix > 36)
        return str;

    if (n == 0) {
        *str = '0';
        *(str + 1) = '\0';
        return str;
    }

    p1 = str;
    if (radix == 10 && n < 0) {
        *p1 = '-';
        p1++;
        n = -n;
    }

    while (n != 0) {
        i = n % radix;
        *p1 = digit[i];
        p1++;
        n = n / radix;
    }

    *p1 = '\0';

    p1--;
    p2 = str;
    while (p1 > p2) {
        i = *p1;
        *p1 = *p2;
        *p2 = i;
        p1--;
        p2++;
    }

    return str;
}