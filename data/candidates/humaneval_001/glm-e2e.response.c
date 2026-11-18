char **func0(const char *str, int *count) {
    int len = strlen(str);
    int balance = 0;
    int capacity = 10;
    char **result = malloc(capacity * sizeof(char *));
    
    char *current = malloc(len + 1);
    int current_len = 0;
    *count = 0;
    
    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c == '(') {
            balance++;
            current[current_len++] = c;
        } else if (c == ')') {
            balance--;
            current[current_len++] = c;
            if (balance == 0) {
                current[current_len] = '\0';
                result[*count] = strdup(current);
                (*count)++;
                if (*count >= capacity) {
                    capacity *= 2;
                    result = realloc(result, capacity * sizeof(char *));
                }
                current_len = 0;
            }
        }
    }
    
    free(current);
    return result;
}