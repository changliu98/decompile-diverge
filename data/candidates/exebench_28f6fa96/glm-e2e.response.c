int arikkei_ucs2_strncpy(unsigned short *dest, const unsigned short *src, unsigned int n) {
    unsigned int i = 0;
    const unsigned short *p = src;

    if (n == 0) {
        return i;
    }

    while (*p != 0) {
        dest[i] = *p;
        p++;
        i++;
        if (i >= n) {
            break;
        }
    }

    while (i < n) {
        dest[i] = 0;
        i++;
    }

    return i;
}