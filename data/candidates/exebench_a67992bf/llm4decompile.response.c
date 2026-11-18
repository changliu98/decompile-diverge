size_t itoa(char *buf, int32_t d)
{
    char *p = buf;
    size_t n;
    char tmp[12];
    char *end = tmp + 11;
    int negative = 0;

    if (d < 0) {
        negative = 1;
        d = -d;
    }

    do {
        *end-- = '0' + (d % 10);
        d /= 10;
    } while (d);

    if (negative) {
        *end-- = '-';
    }

    n = (tmp + 11) - end;
    while (end < tmp + 12) {
        *p++ = *end++;
    }
    *p = '\0';

    return n;
}