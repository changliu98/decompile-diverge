char **split(char *str, int *len) {
    int capacity = 10;
    char **result = malloc(sizeof(char*) * capacity);
    char *word = malloc(strlen(str)+1);
    int word_len = 0;
    int words = 0;
    int i = 0;

    while(1) {
        if (str[i] == '\0') {
            break;
        }

        switch(str[i]) {
            case ' ':
            case ',':

                if (word_len > 0) {
                    word[word_len] = '\0';
                    result[words++] = strdup(word);

                    word_len = 0;

                    if (words >= capacity) {
                        capacity *= 2;
                        result = realloc(result, sizeof(char*) * capacity);
                    }
                }

                break;
            default:
                word[word_len++] = str[i];
        }

        i++;
    }

    if (word_len > 0) {
        word[word_len] = '\0';
        result[words++] = strdup(word);
    }

    free(word);
    *len = words;
    return result;
}