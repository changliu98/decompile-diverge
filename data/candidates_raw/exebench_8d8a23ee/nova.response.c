int func0(char *buf, unsigned int val, int base) {
    char *p, *q;
    char c;
    int len;
    char *hex = "0123456789ABCDEF";
    char *Hex = "0123456789abcdef";
    char *str;

    p = buf;
    q = buf + MAX_LEN - 1;
    len = 0;
    do {
        c = (base <= 10)? val % base + '0' : ((val % base) < 10)? val % base + '0'
                                                                  : (val % base) - 10 + 'a';
        *q-- = c;
        len++;
        val /= base;
    } while (val);

    do {
        *p++ = *++q;
    } while (q < buf + len - 1);
    *p = '\0';

    switch (base) {
    case 16:
        str = Hex;
        break;
    default:
        str = hex;
        break;
    }

    do {
        *q++ = *str++;
    } while (q < buf + len);

    return len;
}