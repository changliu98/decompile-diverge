char* myStrcpy1(char* dest, const char* src) {
    while (1) {
        char c = *src;
        src++;
        *dest = c;
        dest++;
        
        if (c == '\0') {
            break;
        }
    }
    
    return dest;
}