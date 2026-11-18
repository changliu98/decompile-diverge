char *int2str(int val, char *str, int base)
{
    char buf[33], *p;
    int sign;

    memset(buf, 0, sizeof(buf));

    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }

    sign = 0;
    if (val < 0 && base == 10) {
        sign = 1;
        val = -val;
    }

    p = buf;
    do {
        *p++ = int2str::tab[val % base];
    } while ((val /= base) != 0);

    if (sign) {
        *p++ = '-';
    }

    do {
        *str++ = *--p;
    } while (p >= buf && *p);

    *str = '\0';

    return str;
}