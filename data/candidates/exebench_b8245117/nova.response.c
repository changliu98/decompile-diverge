char *mystrcpy(char *dst, const char *src) {
    char *ret = dst;
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
    return ret;
}