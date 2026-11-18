int sdsll2str(char *s, long long value) {
    char *p, aux;
    int len;

    p = s;
    if (value < 0) {
        if (value == (long long)0x8000000000000000ull) {
            value = 0x8000000000000000ull;
        } else {
            value = -value;
        }
    }
    do {
        *p++ = '0'+(value%10);
        value /= 10;
    } while(value);
    if (value < 0) *p++ = '-';
    *p-- = '\0';
    len = p-s;
    do {
        aux = *s;
        *s++ = *p;
        *p-- = aux;
    } while(s<p);
    return len;
}