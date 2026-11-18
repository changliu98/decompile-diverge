int ExtractRnick(char *dest, const char *src) {
    int i = 0;
    
    if (*src == ':') {
        src++;
    }
    
    while (*src != '!' && *src != '\0') {
        dest[i] = *src;
        src++;
        i++;
    }
    
    dest[i] = '\0';
    
    if (*dest < '0') {
        return 0;
    }
    
    return 1;
}