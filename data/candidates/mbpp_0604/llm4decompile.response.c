char *func0(char *s)
{
    char *words[10];
    int word_count = 0;
    char *token = strtok(s, " ");
    while (token != NULL) {
        words[word_count] = token;
        token = strtok(NULL, " ");
        word_count++;
    }
    func0::result[0] = '\0';
    for (int i = word_count - 1; i >= 0; i--) {
        strcat(func0::result, words[i]);
        if (i > 0)
            strcat(func0::result, " ");
    }
    return func0::result;
}