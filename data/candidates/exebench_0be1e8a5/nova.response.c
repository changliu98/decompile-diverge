void short_to_string(char *s, short n) {
    short i = 0;
    char digit;

    do {
        digit = n / 10000;
        n -= digit * 10000;
        *s++ = digit + '0';

        digit = n / 1000;
        n -= digit * 1000;
        *s++ = digit + '0';

        digit = n / 100;
        n -= digit * 100;
        *s++ = digit + '0';

        digit = n / 10;
        n -= digit * 10;
        *s++ = digit + '0';

        digit = n;
        n -= digit;
        *s++ = digit + '0';

        i++;
    } while (n!= 0);

    *s++ = '\0';
}