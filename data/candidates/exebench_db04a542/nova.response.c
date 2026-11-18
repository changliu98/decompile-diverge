char *checkpath(char *dst, const char *src) {
    char *const d = dst;
    const char *s = src;

    if (dst == src) {
        while (*s!= '\0') {
            if (*s == '\\') {
                *d++ = '/';
            } else {
                *d++ = *s;
            }
            ++s;
        }
    } else {
        while (*s!= '\0') {
            if (*s == '\\') {
                *d++ = '/';
            } else {
                *d++ = *s;
            }
            ++s;
        }
    }
    *d = '\0';

    return dst;
}