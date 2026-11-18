char *strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    
    while ((*dest++ = *src++) != '\0') {
        // The loop body is empty; the copy and pointer increment 
        // happen directly in the loop condition.
    }
    
    return original_dest;
}