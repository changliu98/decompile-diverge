int util_read_dec(char *str, int *result)
{
    int i;
    int neg;
    long res;

    *result = 0;
    neg = 0;
    if (*str == '-') {
        neg = 1;
        str++;
    }
    for (i = 0; *str != 0; i++) {
        int digit;

        digit = *str - '0';
        if (digit < 0 || digit > 9)
            break;
        res = *result * 10 + digit;
        if (res < 0)
            break;
        *result = res;
        str++;
    }
    if (neg && i > 1)
        *result = -*result;
    return i;
}