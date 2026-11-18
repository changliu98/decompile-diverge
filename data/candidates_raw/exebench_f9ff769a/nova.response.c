char *func0(char *dest, const char *src) {
    int i = 0;
    while (1) {
        if (src[i] == '\0') {
            dest[i] = '\0';
            break;
        }
        dest[i] = src[i];
        i++;
    }
    return dest;
}