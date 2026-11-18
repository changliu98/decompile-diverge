char *smtp_stpcpy(char *dst, const char *src) {
    long i = 0;
    do {
        dst[i] = src[i];
        i++;
    } while (src[i - 1] != '\0');
    
    return &dst[i - 1];
}