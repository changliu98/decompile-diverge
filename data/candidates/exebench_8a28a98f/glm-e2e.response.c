char* itoa(int value, char* str, int base) {
    char* ret = str;
    
    // Check if base is valid (between 2 and 36)
    if (base < 2 || base > 36) {
        str[0] = '\0';
        return str;
    }
    
    char* ptr = str;
    char* low = str;
    
    // Convert the integer to a string in reverse order
    do {
        int remainder = value % base;
        char c = "0123456789abcdefghijklmnopqrstuvwxyz"[remainder + 35];
        *ptr++ = c;
        value /= base;
    } while (value != 0);
    
    // Null-terminate the string
    *ptr = '\0';
    
    // Reverse the string
    ptr--;
    while (low < ptr) {
        char temp = *low;
        *low++ = *ptr;
        *ptr-- = temp;
    }
    
    return ret;
}