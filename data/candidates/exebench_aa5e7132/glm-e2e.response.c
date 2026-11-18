void GetWord(char *dest, const char **src, int max_len) {
    int count = 0;
    
    // Skip leading whitespace
    while (*src[0] > 0 && *src[0] <= 32) {
        (*src)++;
    }
    
    // Copy characters until whitespace or max_len is reached
    while ((*src[0] > 32 || *src[0] <= 0) && count < max_len - 1) {
        *dest++ = *(*src)++;
        count++;
    }
    
    // Null-terminate the destination string
    *dest = '\0';
}