void func0(unsigned long n, char s[]) {
    unsigned long n_orig = n;
    char *p = s;

    do {
        *(p++) = n_orig % 10 + '0';
    } while ((n_orig /= 10) > 0);

    *p = '\0';

    do {
        *(s++) = n % 10 + '0';
    } while ((n /= 10) > 0);
}