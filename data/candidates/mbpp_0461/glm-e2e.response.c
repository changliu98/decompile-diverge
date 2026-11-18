int func0(const char *str) {
    int count = 0;
    int i = 0;
    int result = 0;

    while (i < strlen(str)) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            count++;
        }
        result = count;
        i++;
    }
    
    return result;
}