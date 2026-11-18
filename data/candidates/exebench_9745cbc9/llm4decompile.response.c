int itoa(char *buf, int i)
{
    char *s = buf;
    char *se = buf;
    char *cp;
    char b[12];
    int sign = i;

    cp = &b[11];
    if (sign < 0) {
        sign = -sign;
    }
    do {
        *cp-- = sign % 10 + '0';
    } while ((sign /= 10) != 0);
    if (i < 0) {
        *cp-- = '-';
    }
    while (cp < &b[12]) {
        *s++ = *cp++;
    }
    *s = '\0';
    return s - se;
}