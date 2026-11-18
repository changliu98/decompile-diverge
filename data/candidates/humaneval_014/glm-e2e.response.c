char** func0(const char* str, int* out_len) {
    int len = strlen(str);
    char** result = malloc(len * sizeof(char*));
    char* current_str = malloc(len + 1);
    current_str[0] = '\0';
    
    for (int i = 0; i < len; i++) {
        int current_len = strlen(current_str);
        current_str = realloc(current_str, current_len + 2);
        current_str[current_len] = str[i];
        current_str[current_len + 1] = '\0';
        
        result[i] = malloc(strlen(current_str) + 1);
        strcpy(result[i], current_str);
    }
    
    free(current_str);
    *out_len = len;
    return result;
}