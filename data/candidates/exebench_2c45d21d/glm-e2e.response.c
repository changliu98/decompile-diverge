char last_char(char *str) {
    char ret;

    if (str == NULL || *str == '\0') {
        ret = '\0';
    } else {
        // Find the end of the string
        while (*str != '\0') {
            str++;
        }
        
        // Step back one character
        str--;
        
        // Extract the last character and truncate the string
        ret = *str;
        *str = '\0';
    }

    return ret;
}