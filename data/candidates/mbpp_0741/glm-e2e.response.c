bool func0(const char *str) {
    int len = strlen(str);
    int i = 1;
    
    while (i < len) {
        if (str[i] != str[0]) {
            return false;
        }
        i++;
    }
    
    return true;
}