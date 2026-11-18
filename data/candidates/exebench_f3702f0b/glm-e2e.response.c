void escape(char *dst, char *src) {
    int j = 0;
    for (int i = 0; src[i] != 0; i++) {
        char c = src[i];
        if (c == '\t') {
            dst[j++] = '\\';
            dst[j++] = 't';
        } else if (c == '\n') {
            dst[j++] = '\\';
            dst[j++] = 'n';
        } else if (c == ' ') {
            dst[j++] = '\\';
            dst[j++] = 'b';
        } else {
            dst[j++] = c;
        }
    }
    dst[j] = '\0';
}