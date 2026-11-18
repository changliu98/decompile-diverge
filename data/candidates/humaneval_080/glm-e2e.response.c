bool func0(const char *str) {
    if (strlen(str) < 3) {
        return false;
    }
    
    for (int i = 2; i < strlen(str); i++) {
        if (str[i] == str[i - 1] || str[i] == str[i - 2]) {
            return false;
        }
    }
    
    return true;
}