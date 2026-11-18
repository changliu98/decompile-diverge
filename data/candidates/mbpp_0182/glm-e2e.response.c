void func0(const char *str, char *upper, char *lower, char *digit, char *punct) {
    int u = 0, l = 0, d = 0, p = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        if (isupper(str[i])) {
            upper[u++] = str[i];
        } else if (islower(str[i])) {
            lower[l++] = str[i];
        } else if (isdigit(str[i])) {
            digit[d++] = str[i];
        } else if (str[i] == ',' || str[i] == '.' || 
                   str[i] == '!' || str[i] == '?') {
            punct[p++] = str[i];
        }
    }
    
    upper[u] = '\0';
    lower[l] = '\0';
    digit[d] = '\0';
    punct[p] = '\0';
}