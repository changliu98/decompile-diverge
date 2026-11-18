char *strncpy2(char *dest, const char *src, int n) {
    int i = n;
    char *d = dest;
    const char *s = src;
    
    while (i-- > 0 && *s != '\0') {
        *d++ = *s++;
    }
    
    *d = '\0';
    return dest;
}