long bytelen_and_check_utf8(const char *str) {
    const char *p = str;
    long len = -1; // Initialized to -1 (0xffffffffffffffff) as seen at 0x3f and 0x86

    while (*p != '\0') {
        long size = codepoint_size(*p);
        
        if (size == -1) {
            return -1;
        }
        
        p++;
        size--;
        
        while (size > 0) {
            // Check if the byte is a valid UTF-8 continuation byte (0b10xxxxxx)
            if ((*p & 0xC0) != 0x80) {
                return -1;
            }
            
            p++;
            size--;
        }
    }
    
    len = p - str;
    return len;
}