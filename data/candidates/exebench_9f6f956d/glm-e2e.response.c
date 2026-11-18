int ckstrncpy(char *dst, const char *src, int size) {
    int i = 0;
    
    if (size >= 1 && src != NULL && dst != NULL) {
        i = 0;
        while (src[i] != '\0' && i < size - 1) {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    } else {
        if (dst != NULL) {
            dst[0] = '\0';
        }
        i = 0;
    }
    
    return i;
}