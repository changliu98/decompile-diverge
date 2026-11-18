static int sdsll2str(char *s, long long value) {
    char *p, aux;
    unsigned long long v;
    size_t l;



    if (value < 0) {
        v = -value;
    } else {
        v = value;
    }

    p = s;
    do {
        *p++ = '0' + (v % 10);
        v /= 10;
    } while (v);
    if (value < 0) *p++ = '-';

    l = p - s;
    *p = '\0';

    p--;
    while (s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return l;
}