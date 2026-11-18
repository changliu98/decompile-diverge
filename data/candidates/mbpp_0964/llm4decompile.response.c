int func0(char *str)
{
    int ret;
    char *word = strtok(str, " ");
    if (word == NULL)
        return 0;
    if (strlen(word) % 2 == 0)
        ret = 1;
    else
        ret = 0;
    return ret;
}