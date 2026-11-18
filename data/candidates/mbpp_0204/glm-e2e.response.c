int func0(const char *str, char c) {
    int count = 0;
    int i = 0;
    
    while (i < strlen(str)) {
        if (str[i] == c) {
            count++;
        }
        i++;
    }
    
    return count;
}