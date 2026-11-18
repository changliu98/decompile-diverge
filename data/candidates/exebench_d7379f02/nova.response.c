void itoa(unsigned short n, char *s) {
    unsigned short i = 0, j;
    char buf[MAX_DIGITS];

    if (n == 0) {
        s[i++] = '0';
        s[i] = '\0';
        return;
    }

    while (n) {
        buf[i++] = n % 10 + '0';
        n /= 10;
    }

    for (j = i; i > 0; i--)
        s[--j] = buf[i - 1];
    s[j] = '\0';
}