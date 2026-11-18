void copy(char *dst, const char *src) {
    int i = 0;
    while (1) {
        char c = src[i];
        dst[i] = c;
        if (c == 0) {
            break;
        }
        i++;
    }
}