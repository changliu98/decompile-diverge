char *func0(char *string) {
    char *string_copy = strdup(string);
    if (string_copy == NULL) {
        return NULL;
    }

    char *tokens[MAX_TOKENS];
    int token_count = 0;

    char *token = strtok(string_copy, " ");
    while (token!= NULL) {
        int found = 0;
        for (int i = 0; i < token_count; i++) {
            if (strcmp(token, tokens[i]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            tokens[token_count++] = token;
        }
        token = strtok(NULL, " ");
    }

    int len = 0;
    for (int i = 0; i < token_count; i++) {
        len += strlen(tokens[i]) + 1;
    }

    char *result = (char *)malloc(len);
    if (result == NULL) {
        free(string_copy);
        return NULL;
    }

    result[0] = '\0';
    for (int i = 0; i < token_count; i++) {
        strcat(result, tokens[i]);
        if (i < token_count - 1) {
            strcat(result, " ");
        }
    }

    free(string_copy);
    return result;
}