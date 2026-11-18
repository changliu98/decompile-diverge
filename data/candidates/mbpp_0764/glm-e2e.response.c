int func0(const char *str) {
    int count = 0;
    int i = 0;
    
    while (i < strlen(str)) {
        if (str[i] >= '0' && str[i] <= '9') {
            count++;
        }
        i++;
    }
    
    return count;
}