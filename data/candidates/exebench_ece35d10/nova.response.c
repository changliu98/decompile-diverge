char *itoa(int n, char *s, int b) {
    char buf[37], *p, *sp;
    static char digs[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    memcpy(buf, digs, 37);
    p = s;
    sp = s;
    if (p == NULL || b < 3 || b > 36) {
        p = sp;
        goto done;
    }
    if (b == 10 && n >= 0) {
        do {
            *p++ = n % b + '0';
        } while (n /= b);
    } else if (n < 0) {
        *p++ = '-';
        n = -n;
    } else if (n == 0) {
        *p++ = '0';
        *p = '\0';
    } else {
        while (n > 0) {
            *p++ = buf[n % b];
            n /= b;
        }
    }

done:
    *p-- = '\0';
    while (sp <= p) {
        char tmp = *sp;
        *sp = *p;
        *p = tmp;
        sp++;
        p--;
    }
    return s;
}