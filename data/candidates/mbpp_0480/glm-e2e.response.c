char func0(const char *str) {
    int count[256];
    memset(count, 0, 1024); // 256 * 4 bytes = 1024 bytes
    
    int min_count = -1;
    char min_char = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
    }
    
    for (int i = 0; i < len; i++) {
        if (min_count > count[(unsigned char)str[i]]) {
            min_count = count[(unsigned char)str[i]];
            min_char = str[i];
        }
    }
    
    return min_char;
}