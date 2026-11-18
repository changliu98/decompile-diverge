int func0(const char *str) {
    int current_len = 0;
    int max_len = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        if (isalpha(str[i])) {
            current_len++;
        } else {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 0;
        }
    }
    
    // Check the last word if the string ends with an alphabetic character
    if (isalpha(str[len - 1])) {
        if (current_len > max_len) {
            max_len = current_len;
        }
    }
    
    return max_len;
}