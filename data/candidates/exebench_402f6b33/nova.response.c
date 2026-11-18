static void itoa(int n, char s[], int b) {
    int i, sign;
    char temp[MAX_LEN + 1];

    sign = n;
    i = 0;
    if (n < 0)
        n = -n;
    do {
        if (n == 0)
            temp[i++] = '0';
        else
            while (n > 0) {
                temp[i++] = digits[n % b];
                n /= b;
            }
    } while (0);
    if (sign < 0)
        temp[i++] = '-';
    while (i--)
        *s++ = temp[i];
    *s = '\0';
}