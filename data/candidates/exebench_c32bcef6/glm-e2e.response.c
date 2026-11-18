void copy(char *dst, const char *src) {
    int i = 0;
    do {
        dst[i] = src[i];
        i++;
    } while (src[i - 1] != '\0');
}