int func0(const char *str) {
    int count = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        for (int j = 1; j <= len - i; j++) {
            if (check_Equality(str, i, i + j - 1)) {
                count++;
            }
        }
    }
    
    return count;
}