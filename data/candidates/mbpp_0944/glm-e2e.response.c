int func0(const char *str) {
    int i = 0;
    int result;

    while (str[i] != '\0') {
        if (isalpha(str[i])) {
            result = i;
            return result;
        }
        i++;
    }
    
    result = -1;
    return result;
}