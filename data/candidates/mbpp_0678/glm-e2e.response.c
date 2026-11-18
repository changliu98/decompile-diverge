char* func0(char* str) {
    int j = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        if (str[i] != ' ') {
            str[j] = str[i];
            j++;
        }
    }
    
    str[j] = '\0';
    return str;
}