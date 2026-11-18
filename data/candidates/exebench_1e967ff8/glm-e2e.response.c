void right_shift_str(char *str, int n) {
    int len = 0;
    char *ptr = str;
    
    // Calculate the length of the string
    while (*ptr != '\0') {
        len++;
        ptr++;
    }
    
    // Perform right shift n times
    for (int i = 0; i < n; i++) {
        char last_char = str[len - 1];
        
        // Shift characters to the right by 1
        for (int j = len - 1; j > 0; j--) {
            str[j] = str[j - 1];
        }
        
        // Place the last character at the beginning
        str[0] = last_char;
    }
}