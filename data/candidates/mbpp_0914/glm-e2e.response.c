int func0(const char *str) {
    int len = strlen(str);
    int i = 0;
    
    while (i < len - 2) {
        if (str[i] == str[i + 2]) {
            return 0;
        }
        i++;
    }
    
    if (str[0] == str[1]) {
        return 0;
    }
    
    return 1;
}