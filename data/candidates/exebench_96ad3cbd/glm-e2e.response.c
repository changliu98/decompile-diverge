char* maybeint(char* str, int* out_val) {
    // Check if the first character is a digit
    if (*str >= '0' && *str <= '9') {
        int val = 0;
        
        // Parse consecutive digits
        while (*str >= '0' && *str <= '9') {
            val = val * 10 + (*str - '0');
            str++;
        }
        
        *out_val = val;
    } else {
        // First character is not a digit
        *out_val = 0;
    }
    
    return str;
}