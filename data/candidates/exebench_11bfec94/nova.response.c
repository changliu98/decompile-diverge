void to_hex(long n, char s[]) {
    int i, sign;
    char *hex = "0123456789ABCDEF";

    sign = n;
    i = 3;
    do {
        s[i--] = hex[n % 16];
        n = n / 16;
    } while (i >= 0);
    s[4] = '\0';
}