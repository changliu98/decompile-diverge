void func0(const char *src, char *dst) {
    int len = strlen(src);
    for (int i = 0; i < len; i++) {
        char c = src[i];
        if (c >= 'a' && c <= 'z') {
            c -= 32;
        } else if (c >= 'A' && c <= 'Z') {
            c += 32;
        }
        dst[i] = c;
    }
    dst[len] = '\0';
}