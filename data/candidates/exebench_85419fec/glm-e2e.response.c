char *strcpyend(char *dest, const char *src) {
    char *d = dest;
    char *s = src;
    char c;

    do {
        c = *s++;
        *d++ = c;
    } while (c != '\0');

    return d - 1;
}