int conv_hstring(const char *str, int *val) {
    int i = 0;
    *val = 0;
    
    while (1) {
        char c = str[i];
        int is_valid;
        
        if (c >= '0' && c <= '9') {
            is_valid = (i < 10);
        } else if (c >= 'a' && c <= 'f') {
            is_valid = (i < 10);
        } else {
            is_valid = 0;
        }
        
        if (!is_valid) {
            break;
        }
        
        if (c >= '0' && c <= '9') {
            *val = (*val << 4) + (c - '0');
        } else {
            *val = (*val << 4) + (c - 'a' + 10);
        }
        
        i++;
    }
    
    return i;
}