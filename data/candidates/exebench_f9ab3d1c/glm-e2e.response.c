int str_to_int(const char *str, int *result) {
    int i = 0;
    int base = 10;
    int digit = 0;
    
    *result = 0;
    
    // Check for "0x" or "0X" prefix
    if (str[0] == '0' && str[1] == 'x') {
        i = 2;
        base = 16;
    }
    
    // If the string is empty or just "0x", return -1 (error)
    if (str[i] == '\0') {
        return -1;
    }
    
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            digit = str[i] - '0';
        } else if (base == 16 && str[i] >= 'A' && str[i] <= 'F') {
            digit = str[i] - 'A' + 10;
        } else if (base == 16 && str[i] >= 'a' && str[i] <= 'f') {
            digit = str[i] - 'a' + 10;
        } else {
            return -1;
        }
        
        *result = *result * base + digit;
        i++;
    }
    
    return 0;
}