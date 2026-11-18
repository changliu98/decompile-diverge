char *func0(char *word)
{
    int i;
    for (i = strlen(word) - 2; i > 0; i--) {
        if (strchr("AEIOUaeiou", word[i]) != NULL &&
            strchr("AEIOUaeiou", word[i + 1]) == NULL &&
            strchr("AEIOUaeiou", word[i - 1]) == NULL) {
            func0::out[0] = word[i];
            return func0::out;
        }
    }
    func0::out[0] = '\0';
    return func0::out;
}