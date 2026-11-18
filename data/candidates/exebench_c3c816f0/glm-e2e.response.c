int char2num(char c, char *out) {
    int ret = 0;
    
    if (c >= '0' && c <= '9') {
        *out = c - '0';
    } else if (c >= 'A' && c <= 'F') {
        *out = c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
        *out = c - 'a' + 10;
    } else {
        ret = -1;
    }
    
    return ret;
}