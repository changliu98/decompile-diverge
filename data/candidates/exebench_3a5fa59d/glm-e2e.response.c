char *strichr(char *str, int c) {
    if (str != NULL) {
        char *p = str;
        
        // Find the end of the string
        while (*p != '\0') {
            p++;
        }
        
        // Shift characters to the right to make room for the new character
        while (p >= str) {
            *(p + 1) = *p;
            p--;
        }
        
        // Insert the character at the beginning of the string
        *str = (char)c;
    }
    
    return str;
}