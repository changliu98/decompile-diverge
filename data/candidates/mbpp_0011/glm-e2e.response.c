char* func0(char* str, char c) {
    int len = strlen(str);
    int first = -1;
    int last = -1;
    
    for (int i = 0; i < len; i++) {
        if (str[i] == c) {
            if (first == -1) {
                first = i;
            }
            last = i;
        }
    }
    
    if (first == -1 || last == -1 || first == last) {
        char* result = malloc(len + 1);
        strcpy(result, str);
        return result;
    }
    
    char* result = malloc(len - 1);
    int j = 0;
    
    for (int i = 0; i < first; i++) {
        result[j++] = str[i];
    }
    for (int i = first + 1; i < last; i++) {
        result[j++] = str[i];
    }
    for (int i = last + 1; i < len; i++) {
        result[j++] = str[i];
    }
    result[j] = '\0';
    
    return result;
}