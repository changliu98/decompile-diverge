char *get_word(char *str, int *len) {
    int i = 0;
    
    if (str != NULL) {
        // Skip leading dashes
        while (*str == '-') {
            str++;
        }
        
        // Check if the string starts with a lowercase letter
        if (*str >= 'a' && *str <= 'z') {
            // Count the length of the word
            while (i < 64) {
                char c = str[i];
                if ((c >= '0' && c <= '9') || 
                    (c >= 'a' && c <= 'z') || 
                    c == '-' || 
                    c == '_') {
                    i++;
                } else {
                    break;
                }
            }
        }
    }
    
    // Dereference the length pointer and store the counted length
    *len = i;
    
    return str;
}