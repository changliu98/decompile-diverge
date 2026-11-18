int func0(char *s, long long *x) {
    size_t i = 0;
    long long n = 0;
    int digit;
    while (1) {
        digit = s[i] - '0';
        if (digit < 0 || digit > 9)
            break;
        n = n * 10 + digit;
        i++;
    }
    *x = n;
    return i;
}