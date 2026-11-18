char *string_copy(char *dest, const char *src) {
    char *d = NULL;
    char *s = NULL;
    if (src && dest) {
        d = dest;
        s = (char *)src;
        while (*s) {
            *d++ = *s++;
        }
        *d = '\0';
        return dest;
    }
    return NULL;
}