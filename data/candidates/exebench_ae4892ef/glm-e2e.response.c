char* my_strcpy(char* dest, const char* src) {
    char* original_dest = dest;
    
    while (*src != '\0') {
        *dest = *src;
        src++;
        dest++;
    }
    
    *dest = '\0';
    
    return original_dest;
}