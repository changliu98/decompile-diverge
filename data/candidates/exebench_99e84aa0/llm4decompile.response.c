char *_xtoa(unsigned long v, char *string, int radix, int is_neg)
{
    static const char *digits = "0123456789abcdef";
    char buf[32];
    char *p = buf;
    char *firstdig = string;

    do {
        *p++ = digits[v % radix];
    } while (v /= radix);

    if (is_neg) {
        *p++ = '-';
    }

    do {
        *string++ = *--p;
    } while (p != buf);

    *string = '\0';

    return firstdig;
}