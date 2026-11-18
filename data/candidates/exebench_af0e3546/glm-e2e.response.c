void set_mac(char *dst, const char *src) {
    for (int i = 0; i < 6; i++) {
        dst[i] = src[i];
    }
}