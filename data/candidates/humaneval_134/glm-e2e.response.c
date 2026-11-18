int func0(const char *str) {
    int len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    char last_char = str[len - 1];
    if (!isalpha(last_char)) {
        return 0;
    }
    
    if (len == 1) {
        return 1;
    }
    
    char second_last_char = str[len - 2];
    if (isalpha(second_last_char)) {
        return 0;
    }
    
    return 1;
}