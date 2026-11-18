char *func0(char *dest, char *src, int n) {
    int i = -1;
    char c;
    while (1) {
        i++;
        c = src[i];
        if (c == '\0') {
            break;
        }
        if (i < n) {
            dest[i] = src[i];
        }
    }
    dest[i] = '\0';
    return dest;
}