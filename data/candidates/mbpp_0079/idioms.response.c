int func0(char *str)
{
    char *token = strtok(str, " ");
    if (token == ((void *)0))
        return 0;
    int len = strlen(token);
    if (len % 2 == 0)
        return 0;
    return 1;
}