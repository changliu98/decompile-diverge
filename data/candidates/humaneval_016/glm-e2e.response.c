int func0(const char *str) {
    int count = 0;
    int seen[256] = {0}; // 0x400 bytes = 256 ints
    
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        
        if (seen[(unsigned char)c] == 0) {
            if (isalpha(c)) {
                seen[(unsigned char)c] = 1;
                count++;
            }
        }
    }
    
    return count;
}