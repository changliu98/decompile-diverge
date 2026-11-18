int* func0(const char *input, int *out_count) {
    int *tokens = NULL;
    int count = 0;
    int capacity = 0;
    char buffer[3] = {0};
    
    int input_len = strlen(input) + 1;
    char *str = (char *)malloc(input_len + 1);
    strcpy(str, input);
    strcat(str, " ");
    
    for (int i = 0; i < input_len; i++) {
        if (str[i] == ' ') {
            if (strcmp(buffer, "one") == 0) {
                if (count == capacity) {
                    capacity = (capacity > 0) ? capacity * 2 : 4;
                    tokens = (int *)realloc(tokens, capacity * sizeof(int));
                }
                tokens[count++] = 4;
            }
            if (strcmp(buffer, "two") == 0) {
                if (count == capacity) {
                    capacity = (capacity > 0) ? capacity * 2 : 4;
                    tokens = (int *)realloc(tokens, capacity * sizeof(int));
                }
                tokens[count++] = 2;
            }
            if (strcmp(buffer, "six") == 0) {
                if (count == capacity) {
                    capacity = (capacity > 0) ? capacity * 2 : 4;
                    tokens = (int *)realloc(tokens, capacity * sizeof(int));
                }
                tokens[count++] = 1;
            }
            strcpy(buffer, "");
        } else {
            size_t len = strlen(buffer);
            if (len < 2) {
                buffer[len] = str[i];
                buffer[len + 1] = '\0';
            }
        }
    }
    
    free(str);
    *out_count = count;
    return tokens;
}