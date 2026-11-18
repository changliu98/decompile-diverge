char **func0(const char *str, int n, int *count) {
    const char *delim = " \t\n"; // Assuming the string at 0x2004 is " \t\n"
    char **result = NULL;
    int word_count = 0;
    int current_word_len = 0;
    int start = 0;
    size_t len = strlen(str);
    char *buffer = malloc(len + 1);
    
    for (size_t i = 0; i <= len; i++) {
        if (isspace(str[i]) || str[i] == '\0') {
            if (current_word_len == n) {
                buffer[i - start] = '\0';
                result = realloc(result, (word_count + 1) * sizeof(char *));
                result[word_count] = malloc(strlen(buffer) + 1);
                strcpy(result[word_count], buffer);
                word_count++;
            }
            start = i + 1;
            current_word_len = 0;
        } else {
            buffer[i - start] = str[i];
            if (strchr(delim, str[i]) == NULL && isxdigit(str[i])) {
                current_word_len++;
            }
        }
    }
    
    free(buffer);
    *count = word_count;
    return result;
}