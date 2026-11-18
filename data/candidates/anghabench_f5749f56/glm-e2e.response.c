int hex2int(int c) {
    int result;
    
    if (c >= 'a' && c <= 'f') {
        result = c + 10 - 'a';
    } else if (c >= 'A' && c <= 'F') {
        result = c + 10 - 'A';
    } else {
        result = c - '0';
    }
    
    return result;
}