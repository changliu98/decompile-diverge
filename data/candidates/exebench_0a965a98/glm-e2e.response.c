char* new_strcpy(char *dest, const char *src, int n) {
    int i = 0;
    
    // Loop until the null terminator is reached or the index reaches the limit n
    while (src[i] != '\0' && i < n) {
        dest[i] = src[i];
        i++;
    }
    
    // Null-terminate the destination string
    dest[i] = '\0';
    
    return dest;
}