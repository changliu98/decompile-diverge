char *func0(char *str) {
    int i = 0;
    int j = 0;
    
    while (str[i] != '\0') {
        if (!isspace(str[i])) {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    
    str[j] = '\0';
    return str;
}