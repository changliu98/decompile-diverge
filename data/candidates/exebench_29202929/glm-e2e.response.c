char *mystpcpy(char *dst, const char *src) {
    while (1) {
        *dst = *src;
        if (*src == '\0') {
            break;
        }
        src++;
        dst++;
    }
    return dst;
}