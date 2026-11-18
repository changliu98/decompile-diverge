long vpf_str_to_num(const char *str, int *num) {
    int result = 0;
    const char *p = str;
    
    while (*p != '\0') {
        if (*p < '0' || *p > '9') {
            break;
        }
        
        int digit = *p - '0';
        result = result * 10 + digit;
        p++;
    }
    
    *num = result;
    return p - str;
}