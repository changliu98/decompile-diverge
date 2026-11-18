void func0(const char *src, char *dst) {
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = tolower(src[i]);
        i++;
    }
    dst[i] = '\0';
}