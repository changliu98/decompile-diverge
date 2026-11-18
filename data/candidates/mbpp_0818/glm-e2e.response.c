int func0(const char *str) {
    int count = 0;
    int i = 0;
    int len = strlen(str);
    
    while (i < len) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            count++;
        }
        i++;
    }
    
    return count;
}