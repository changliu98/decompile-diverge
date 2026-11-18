int json_get_escape_len(const char *str, int len) {
    char c = str[0];
    
    switch (c) {
        case 'u':
            if (len < 6) {
                return -2;
            }
            if (isxdigit(str[1]) && 
                isxdigit(str[2]) && 
                isxdigit(str[3]) && 
                isxdigit(str[4])) {
                return 5;
            }
            return -1;
            
        case 'x':
            if (len < 2) {
                return -2;
            }
            return 1;
            
        default:
            return -1;
    }
}