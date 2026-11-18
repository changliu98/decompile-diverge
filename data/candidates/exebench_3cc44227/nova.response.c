char *js_itoa(char *s, unsigned int n) {
    char *p = s;
    unsigned int i = 0;
    while (n) {
        *(s + i++) = (n % 10) + '0';
        n /= 10;
    }
    if (i == 0)
        *(s + i++) = '0';
    while (i > 0)
        *(s + --i) = *(s + i);
    *(s + i) = '\0';
    return p;
}