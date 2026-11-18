int itostr(char *str, int size, int num) {
    int len = 0;
    
    if (size <= 0) {
        return len;
    }
    
    if (num < 0) {
        str[0] = '-';
        str++;
        size--;
        len++;
        num = -num;
    }
    
    if (size <= 0) {
        return len;
    }
    
    char *start = str;
    
    // Extract digits in reverse order
    do {
        str[0] = (num % 10) + '0';
        str++;
        len++;
        size--;
        
        if (size <= 0) {
            return len;
        }
        
        num /= 10;
    } while (num > 0);
    
    // Null-terminate if there's space
    if (size > 0) {
        str[0] = '\0';
    }
    
    // Reverse the string in-place
    str--;
    while (start < str) {
        char temp = *start;
        *start = *str;
        *str = temp;
        start++;
        str--;
    }
    
    return len;
}