char *string_copy(char *dest, const char *src) {
    char *ret = NULL;
    
    if (src != NULL && dest != NULL) {
        char *p = src;
        char *q = dest;
        
        while (*p != '\0') {
            *q++ = *p++;
        }
        
        *q = '\0';
        ret = dest;
    }
    
    return ret;
}