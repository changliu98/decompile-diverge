char **func0(const char *str, int *count) {
    int capacity = 10;
    char **tokens = malloc(capacity * sizeof(char *));
    
    int cnt = 0;
    int len = 0;
    char *current_token = malloc(strlen(str) + 1);
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',') {
            if (len > 0) {
                current_token[len] = '\0';
                tokens[cnt] = strdup(current_token);
                cnt++;
                len = 0;
                
                if (cnt >= capacity) {
                    capacity *= 2;
                    tokens = realloc(tokens, capacity * sizeof(char *));
                }
            }
        } else {
            current_token[len] = str[i];
            len++;
        }
    }
    
    if (len > 0) {
        current_token[len] = '\0';
        tokens[cnt] = strdup(current_token);
        cnt++;
    }
    
    free(current_token);
    *count = cnt;
    
    return tokens;
}