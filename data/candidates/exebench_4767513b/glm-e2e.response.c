char *my_strncpy(char *dest, const char *src, int n) {
    int i = 0;
    
    // Copy up to n characters from src to dest
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    
    // Pad the remaining space with null bytes
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    
    return dest;
}