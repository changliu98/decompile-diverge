void itoa(int num, char *str, int base)
{
    int i = 0;
    char tmp[16];
    const char *digits = "0123456789ABCDEF";

    if (num < 0)
        num = -num;

    if (num == 0)
        tmp[i++] = '0';
    else
        while (num != 0) {
            tmp[i++] = digits[num % base];
            num = num / base;
        }

    if (num < 0)
        tmp[i++] = '-';

    while (i-- > 0)
        *str++ = tmp[i];

    *str = '\0';
}