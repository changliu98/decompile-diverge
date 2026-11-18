address 0x40a0

char* func0(const char* s) {
    int len = strlen(s);
    int pos = 0;
    
    // First loop: from 1 to len
    for (int i = 1; i <= len; i++) {
        pos += sprintf(&res[pos], "%d", i);
    }
    
    // Second loop: from len-1 down to 1
    for (int i = len - 1; i > 0; i--) {
        pos += sprintf(&res[pos], "%d", i);
    }
    
    res[pos] = '\0';
    return res;
}