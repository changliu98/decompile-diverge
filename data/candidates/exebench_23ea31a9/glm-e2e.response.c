char *jstrescapecpy(char *dst, const char *src) {
    int i = 0;
    int j = 0;
    char c;

    if (src == NULL) {
        dst[0] = '\0';
        return dst;
    }

    while ((c = src[i]) != '\0') {
        if (c == '\'') {
            dst[j++] = '\\';
            dst[j++] = src[i++];
        } else if (c == '\\') {
            dst[j++] = '\\';
            dst[j++] = src[i++];
        } else if (c == '%') {
            dst[j++] = '_';
            i++;
        } else {
            dst[j++] = src[i++];
        }
    }

    dst[j] = '\0';
    return dst;
}