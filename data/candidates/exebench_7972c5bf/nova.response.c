void tagcpy(char *dest, const char *src, int n) {
    const char *p = src;
    const char *q = src + n - 1;

    while (*q == '\0' && *(q - 1)!= '\0')
        q--;

    while (p <= q) {
        if (*p!='')
            break;
        p++;
    }

    while (q > p) {
        if (*q!='')
            break;
        q--;
    }

    while (p <= q) {
        *dest++ = *p++;
    }

    *dest = '\0';
}