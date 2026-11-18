char *func0(char *str) {
    char *copy = strdup(str);
    if (copy == NULL) {
        return NULL;
    }

    char *tokens[100];
    int token_count = 0;
    char *token = strtok(copy, " ");
    
    while (token != NULL) {
        int is_duplicate = 0;
        for (int i = 0; i < token_count; i++) {
            if (strcmp(token, tokens[i]) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        
        if (!is_duplicate) {
            tokens[token_count++] = token;
        }
        
        token = strtok(NULL, " ");
    }
    
    int total_length = 0;
    for (int i = 0; i < token_count; i++) {
        total_length += strlen(tokens[i]) + 1;
    }
    
    char *result = malloc(total_length);
    if (result == NULL) {
        free(copy);
        return NULL;
    }
    
    result[0] = '\0';
    for (int i = 0; i < token_count; i++) {
        strcat(result, tokens[i]);
        if (i < token_count - 1) {
            strcat(result, " ");
        }
    }
    
    free(copy);
    return result;
}