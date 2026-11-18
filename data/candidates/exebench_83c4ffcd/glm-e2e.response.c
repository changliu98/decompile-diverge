char* copy_line(char *dst, const char *src, int size) {
    int i = 0;
    
    // Loop until the buffer is full (leaving space for the null terminator),
    // or until we encounter a newline or carriage return.
    while (i < size - 1 && *src != '\0' && *src != '\n' && *src != '\r') {
        dst[i] = *src;
        src++;
        i++;
    }
    
    // Null-terminate the destination string
    dst[i] = '\0';
    
    // Skip the carriage return if present
    if (*src == '\r') {
        src++;
    }
    
    // Skip the newline character if present
    if (*src == '\n') {
        src++;
    }
    
    return (char*)src;
}