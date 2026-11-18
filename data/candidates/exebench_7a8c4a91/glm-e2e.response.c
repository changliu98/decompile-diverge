void removeCharactersInPlace(char *str, const char *charsToRemove) {
    char *dest = str;
    
    while (*str != '\0') {
        bool shouldRemove = false;
        const char *ptr = charsToRemove;
        
        // Check if the current character matches any character in charsToRemove
        do {
            shouldRemove = (*str == *ptr);
            ptr++;
        } while (*ptr != '\0' && !shouldRemove);
        
        // If it should not be removed, copy it to the destination
        if (!shouldRemove) {
            *dest = *str;
            dest++;
        }
        
        str++;
    }
    
    // Null-terminate the modified string
    *dest = '\0';
}