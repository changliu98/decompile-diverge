char *reverse(char *str)
{
    char *word = str;
    char *token;
    char *words[10];
    int word_count = 0;
    int i;
    while ((token = strtok(word, " ")))
    {
        words[word_count++] = token;
    }
    static char func0_result[100];
    func0_result[0] = '\0';
    for (i = (word_count - 1); i >= 0; i--)
    {
        strcat(func0_result, words[i]);
        if (i > 0)
        {
            strcat(func0_result, " ");
        }
    }
    return func0_result;
}