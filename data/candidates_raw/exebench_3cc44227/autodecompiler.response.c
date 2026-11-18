char *itoa(char *buf, unsigned int d)
{
    char *str = buf;
    char tmp[16];
    unsigned int i = 0;

    while(1) {
        if (d == 0) break;
        tmp[i++] = d%10 + '0';
        d /= 10;
    }

    if (i == 0) tmp[i++] = '0';

    while(i > 0) {
        *str++ = tmp[--i];
    }
    *str = '\0';
    return buf;
}