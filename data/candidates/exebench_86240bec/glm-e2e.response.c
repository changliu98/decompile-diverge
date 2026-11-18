char *ft_strcpy(char *dest, const char *src) {
    char *ret = dest;
    
    while ((*dest++ = *src++) != '\0') {
        // The loop body is empty, as the copy and comparison 
        // are handled entirely within the loop condition.
    }
    
    return ret;
}