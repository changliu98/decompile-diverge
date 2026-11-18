char hex_char(unsigned char val) {
    char result;
    
    if (val < 10) {
        result = val + '0';
    } else if (val < 16) {
        result = val - 10 + 'a';
    } else {
        result = '?';
    }
    
    return result;
}