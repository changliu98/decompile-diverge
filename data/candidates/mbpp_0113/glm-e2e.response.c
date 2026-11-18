int func0(const char *s) {
    int len = strlen(s);
    
    // Skip leading spaces
    while (*s == ' ') {
        s++;
        len--;
    }
    
    // Empty string after skipping spaces
    if (len < 1) {
        return -1;
    }
    
    int i;
    if (*s == '+' || *s == '-') {
        // Optional sign present, check rest are digits
        for (i = 1; i < len; i++) {
            if (s[i] < '0' || s[i] > '9') {
                return 0;
            }
        }
    } else {
        // No sign, check all are digits
        for (i = 0; i < len; i++) {
            if (s[i] < '0' || s[i] > '9') {
                return 0;
            }
        }
    }
    
    return 1;
}