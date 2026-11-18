char *strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    
    // The assembly checks the first character before entering the loop
    char current_char = *src;
    *dest = current_char;
    
    while (current_char != '\0') {
        src++;
        dest++;
        
        current_char = *src;
        *dest = current_char;
    }
    
    return original_dest;
}