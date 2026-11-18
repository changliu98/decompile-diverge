char *func0(int n, int m) {
    char *str;
    int i;
    if (n > m)
        str = (char *)malloc(33);
    else
        str = (char *)malloc(33 + m + n / 2);
    str[0] = '\0';
    i = 32;
    str[i--] = '\0';
    while (m > 0) {
        str[i--] = m % 2 + '0';
        m /= 2;
    }
    str = &str[i + 1];
    return str;
}