int func0(char *str)
{
    int ret;
    char *token = strtok(str, " ");
    if (token == NULL)
        return 0;
    if (strlen(token) % 2 == 0)
        ret = 0;
    else
        ret = 1;
    return ret;
}