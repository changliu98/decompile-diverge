int lowercase(int c) {
    int result;
    
    if (0x41 <= c && c <= 0x5a) {
        result = c - 0x41 + 0x61;
    } else {
        result = c;
    }
    
    return result;
}