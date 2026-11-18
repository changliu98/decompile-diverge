int get_hex(const char *str, int *val) {
    int i = 0;
    int error = 0;
    
    *val = 0;
    
    while (error == 0) {
        if (i >= 8) {
            error = 1;
            break;
        }
        
        char c = str[i];
        if (c >= '0' && c <= '9') {
            *val = (*val << 4) + (c - '0');
        } else if (c >= 'A' && c <= 'F') {
            *val = (*val << 4) + (c - 'A' + 10);
        } else if (c >= 'a' && c <= 'f') {
            *val = (*val << 4) + (c - 'a' + 10);
        } else {
            error = 1;
        }
        
        if (error == 0) {
            i++;
        }
    }
    
    return i;
}