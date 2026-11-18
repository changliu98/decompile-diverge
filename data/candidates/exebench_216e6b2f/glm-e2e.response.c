char* my_strcpy(char* dest, const char* src) {
    int i = 0;
    
    // Loop until the null terminator is encountered
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    
    // Append the null terminator to the destination string
    dest[i] = '\0';
    
    return dest;
}