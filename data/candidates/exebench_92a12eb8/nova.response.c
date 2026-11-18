void itoa(int n, char *s) {
    char *t = s;
    char c;
    int m;

    if (n < 1) {
        m = -n;
        *t++ = '-';
    } else {
        m = n;
    }
    do {
        *t++ = m % 10 + '0';
    } while ((m /= 10)!= 0);
    *t = '\0';
    reverse(s, t - 1);
}