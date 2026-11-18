char *intToString(char *s, unsigned int n) {
    int i;
    s[9] = '\0';
    for (i = 8; i >= 0; i--) {
        if (n == 0)
            break;
        s[i] = (n % 10) + '0';
        n = n / 10;
    }
    return s + i + 1;
}