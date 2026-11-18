char *my_strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    
    while (1) {
        char c = *src;
        src++;
        
        *dest = c;
        dest++;
        
        if (c == '\0') {
            break;
        }
    }
    
    return original_dest;
}