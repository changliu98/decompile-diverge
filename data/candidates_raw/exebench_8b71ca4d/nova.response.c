char *func0(char *dest, char *src) {
    int i = 0;
    do {
        dest[i] = src[i];
    } while (src[i++]!= '\0');
    return dest;
}