char *func0(char *word, char *result)
{
    int i=0;
    int length = strlen(word);
    for(i=0; i<length; i++)
    {
        result[i] = word[i];
    }
    result[length] = '\0';
    return result;
}