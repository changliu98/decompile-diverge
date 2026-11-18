char* mystrncpy(char* dest, const char* src, int n) {
    char* original_dest = dest;
    int i = 0;
    
    while (i < n && *src != '\0') {
        *dest++ = *src++;
        i++;
    }
    
    *dest = '\0';
    return original_dest;
}