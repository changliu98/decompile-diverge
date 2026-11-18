char func0(const char *str) {
    int count[256] = {0};
    int max_count = 0;
    char max_char = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
        if (count[(unsigned char)str[i]] > max_count) {
            max_count = count[(unsigned char)str[i]];
            max_char = str[i];
        }
    }
    
    return max_char;
}