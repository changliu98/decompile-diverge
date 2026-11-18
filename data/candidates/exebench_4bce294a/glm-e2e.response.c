char *strichr(char *str, int c) {
    if (str != NULL) {
        char *p = str;
        
        // Find the end of the string
        while (*p != '\0') {
            p++;
        }
        
        // Shift characters to the right to make space for the new character
        while (p >= str) {
            *(p + 1) = *p;
            p--;
        }
        
        // Insert the character at the beginning
        *str = (char)c;
    }
    
    return str;
}