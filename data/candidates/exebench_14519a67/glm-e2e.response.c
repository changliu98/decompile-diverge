char *strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    
    // Loop until the null terminator is found
    while (*src != '\0') {
        *dest++ = *src++;
    }
    
    // Append the null terminator to the destination
    *dest = '\0';
    
    // Return the original destination pointer
    return original_dest;
}