size_t i_to_str(int num, char *buf) {
    char *start = buf;
    
    // Handle negative numbers
    if (num < 0) {
        *buf++ = '-';
        num = -num;
    }
    
    char *ptr = buf;
    int quotient;
    
    // Convert number to string in reverse order
    do {
        quotient = num / 10;
        int remainder = num - (quotient * 10);
        *ptr++ = (char)(remainder + '0');
    } while (quotient != 0);
    
    *ptr = '\0';
    
    int len = ptr - buf;
    
    // Reverse the string in place
    for (int i = 0; i < len / 2; i++) {
        char temp = buf[i];
        buf[i] = buf[len - 1 - i];
        buf[len - 1 - i] = temp;
    }
    
    return ptr - start;
}