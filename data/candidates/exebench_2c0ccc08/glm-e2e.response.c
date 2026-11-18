char *strcpy2(char *dest, const char *src) {
    char *original_dest = dest;
    
    while (*src != '\0') {
        *dest++ = *src++;
    }
    
    return original_dest;
}