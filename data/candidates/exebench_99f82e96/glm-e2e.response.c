char* itoa(int value, char* str, int base) {
    char* ptr;
    char* start;
    char* end;
    char temp;
    
    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }
    
    ptr = str;
    start = str;
    
    if (value < 0) {
        *ptr++ = '-';
    }
    
    end = ptr;
    
    do {
        *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base + 35];
        value /= base;
    } while (value != 0);
    
    *ptr-- = '\0';
    
    while (end < ptr) {
        temp = *end;
        *end++ = *ptr;
        *ptr-- = temp;
    }
    
    return start;
}