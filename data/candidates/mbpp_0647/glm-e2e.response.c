char **func0(const char *str, int *count) {
    int len = strlen(str);
    char **tokens = malloc(len * sizeof(char *));
    if (tokens == NULL) {
        perror("malloc");
        exit(1);
    }

    int token_count = 0;
    int start = 0;
    int i = 1;
    
    while (i <= len) {
        if (isspace(str[i]) || str[i] == '\0') {
            int token_len = i - start;
            tokens[token_count] = malloc(token_len + 1);
            if (tokens[token_count] == NULL) {
                perror("malloc");
                exit(1);
            }
            memcpy(tokens[token_count], str + start, token_len);
            tokens[token_count][token_len] = '\0';
            start = i;
            token_count++;
        }
        i++;
    }

    *count = token_count;
    return tokens;
}