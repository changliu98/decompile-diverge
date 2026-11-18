int func0(const char *s) {
    int count = 0;
    int len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        for (int j = 1; j <= len - i; j++) {
            if (check_Equality(s, i, j)) {
                count++;
            }
        }
    }
    
    return count;
}