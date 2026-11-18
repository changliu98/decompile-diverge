int Q_islower(int c) {
    int result;
    
    if (c >= 0x61 && c <= 0x7a) {
        result = 1;
    } else {
        result = 0;
    }
    
    return result;
}