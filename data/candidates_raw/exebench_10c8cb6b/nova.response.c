char *func0(char *dest, const char *src) {
    do {
        *dest = *src;
        if (*dest!= '\0') {
            dest++;
            src++;
        }
    } while (*dest!= '\0');
    return dest;
}