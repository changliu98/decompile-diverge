int util_read_dec(char *str, int *nb) {
    int i;
    int neg;
    long n;

    i = 0;
    neg = 0;
    *nb = 0;
    if (str[i] == '-') {
        neg = 1;
        i++;
    }
    n = 0;
    while (str[i]!= '\0') {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        n *= 10;
        n += str[i] - '0';
        if (n > 2147483647)
            return (0);
        i++;
    }
    if (neg) {
        if (i == 1)
            return (0);
        *nb = -n;
    } else
        *nb = n;
    return (i);
}