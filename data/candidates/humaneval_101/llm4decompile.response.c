char **func0(char *str, int *count)
{
    int i;
    int word_count = 0;
    int current_length = 0;
    int capacity = 10;
    char **out = (char **)malloc(capacity * sizeof(char *));
    char *word = (char *)malloc(strlen(str) + 1);

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',') {
            if (current_length > 0) {
                word[current_length] = '\0';
                out[word_count] = strdup(word);
                word_count++;
                current_length = 0;
                if (word_count >= capacity) {
                    capacity *= 2;
                    out = (char **)realloc(out, capacity * sizeof(char *));
                }
            }
        } else {
            word[current_length] = str[i];
            current_length++;
        }
    }

    if (current_length > 0) {
        word[current_length] = '\0';
        out[word_count] = strdup(word);
        word_count++;
    }

    free(word);
    *count = word_count;
    return out;
}