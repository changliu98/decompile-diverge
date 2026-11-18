char *func0(const char *str) {
    int space_count = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }
    
    int new_len = len + 2 * space_count;
    
    if (new_len > 1000) {
        return "String too long";
    }
    
    char buffer[1024];
    buffer[new_len] = '\0';
    
    int j = new_len - 1;
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            buffer[j] = '0';
            buffer[j - 1] = '2';
            buffer[j - 2] = '%';
            j -= 3;
        } else {
            buffer[j] = str[i];
            j--;
        }
    }
    
    char *result = (char *)malloc(new_len + 1);
    strcpy(result, buffer);
    
    return result;
}