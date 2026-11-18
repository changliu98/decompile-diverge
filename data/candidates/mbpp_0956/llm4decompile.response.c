char **func0(char *text, int *count)
{
    char **words;
    int length;
    int word_start;
    int i;
    int word_length;

    length = strlen(text);
    words = malloc((size_t)length * sizeof(char *));
    *count = 0;
    word_start = 0;
    for (i = 1; i <= length; i++) {
        if (i == length || (isspace(text[i]) && !isspace(text[i - 1]))) {
            word_length = i - word_start;
            words[*count] = malloc((size_t)(word_length + 1) * sizeof(char));
            strncpy(words[*count], text + word_start, (size_t)word_length);
            words[*count][word_length] = '\0';
            *count = *count + 1;
            word_start = i;
        }
    }

    return words;
}