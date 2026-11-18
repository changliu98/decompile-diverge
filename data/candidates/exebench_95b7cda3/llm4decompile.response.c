void itoa(char *buf, int base, long d)
{
    char *p1, *p2;
    int remainder, divisor;

    divisor = 10;
    if (base == 100) {
        if (d < 0) {
            *buf++ = '-';
            d *= -1;
        }
    } else if (base == 120) {
        divisor = 16;
    }

    p1 = buf;
    do {
        remainder = (d % divisor);
        if (remainder < 10) {
            *p1++ = remainder + '0';
        } else {
            *p1++ = remainder - 10 + 'a';
        }
    } while (d = d / divisor);

    *p1 = '\0';

    p2 = p1 - 1;
    while (buf < p2) {
        remainder = *buf;
        *buf++ = *p2;
        *p2-- = remainder;
    }
}