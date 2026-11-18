char **func0(int min_len, char *str, int *count) {
    int counter = 0;
    char *token = strtok(str, " ");
    while (token != NULL) {
        if (strlen(token) > min_len) {
            word_len[counter++] = token;
        }
        token = strtok(NULL, " ");
    }
    *count = counter;
    return word_len;
}