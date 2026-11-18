char **func0(const char *str, int *count) {
    int len = strlen(str);
    char **tokens = malloc(len * sizeof(char *));
    *count = 0;
    int start = 0;
    
    for (int i = 1; i <= len; i++) {
        if (i == len || (isspace(str[i]) && !isspace(str[i - 1]))) {
            int token_len = i - start;
            tokens[*count] = malloc(token_len + 1);
            strncpy(tokens[*count], str + start, token_len);
            tokens[*count][token_len] = '\0';
            (*count)++;
            start = i;
        }
    }
    
    return tokens;
}