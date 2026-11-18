bool func0(const char *str) {
    int balance = 0;
    int i = 0;
    bool result;

    while (i < strlen(str)) {
        if (str[i] == '(') {
            balance++;
        }
        if (str[i] == ')') {
            balance--;
        }
        if (balance < 0) {
            result = false;
            goto end;
        }
        i++;
    }
    
    result = (balance == 0);

end:
    return result;
}