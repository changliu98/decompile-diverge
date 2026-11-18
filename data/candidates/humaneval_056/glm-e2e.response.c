bool func0(const char *str) {
    int balance = 0;
    int i = 0;
    
    while (str[i] != '\0') {
        if (str[i] == '<') {
            balance++;
        }
        if (str[i] == '>') {
            balance--;
        }
        if (balance < 0) {
            return false;
        }
        i++;
    }
    
    if (balance != 0) {
        return false;
    }
    
    return true;
}