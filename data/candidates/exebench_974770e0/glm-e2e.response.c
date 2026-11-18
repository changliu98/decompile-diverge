char *envstring(char *str) {
    char *p = str;
    
    while (*p != '\0') {
        if (*p == '-') {
            *p = '_';
        } else if (*p >= 'a' && *p <= 'z') {
            *p = *p - 32; // Convert to uppercase
        } else if (!(*p >= 'A' && *p <= 'Z')) {
            *str = '\0';
            break;
        }
        p++;
    }
    
    return str;
}