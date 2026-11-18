char* skip(char* str, char c) {
    // Skip all characters that match 'c' or are not the null terminator
    while (*str != '\0' && *str != c) {
        str++;
    }
    
    // If the current character is not the null terminator, 
    // split the string by replacing it with a null terminator and move to the next character
    if (*str != '\0') {
        *str = '\0';
        str++;
    }
    
    return str;
}