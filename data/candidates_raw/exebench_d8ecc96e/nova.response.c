char *func0(char *dest, const char *src) {
    size_t i = 0;
    do {
        dest[i] = src[i];
    } while (src[i++]!= '\0');
    return dest;
}