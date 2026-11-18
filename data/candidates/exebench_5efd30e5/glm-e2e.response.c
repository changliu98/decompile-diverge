int stringToInt(int *result, const char *str) {
    *result = 0;
    
    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            return -1;
        }
        
        *result = (*result * 10) + (*str - '0');
        str++;
    }
    
    return 0;
}