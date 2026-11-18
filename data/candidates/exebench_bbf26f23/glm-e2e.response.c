char *strcpy(char *dest, const char *src) {
    int i = 0;
    
    // Loop through the source string until the null terminator is found
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    
    // Append the null terminator to the destination string
    dest[i] = '\0';
    
    // Return the original destination pointer
    return dest;
}