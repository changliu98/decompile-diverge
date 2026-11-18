char *checkpath(char *dst, char *src) {
    char *d = dst;
    
    if (dst == 0 || src == 0) {
        return dst;
    }
    
    while (*src != '\0') {
        if (*src == '\\') {
            *d = '/';
            d++;
            src++;
        } else {
            *d = *src;
            d++;
            src++;
        }
    }
    
    *d = *src; // Copy the null terminator
    
    return dst;
}