char **func0(char *string)
{
    int count = 1;
    char *ptr;
    char **list;
    char *str;
    char *token;
    int index;

    for (ptr = string; *ptr != '\0'; ptr++)
    {
        if (*ptr == ' ')
        {
            count++;
        }
    }

    list = malloc((size_t)(count + 1) * sizeof(char *));
    if (list == NULL)
    {
        return NULL;
    }

    str = strdup(string);
    if (str == NULL)
    {
        free(list);
        return NULL;
    }

    index = 0;
    token = strtok(str, " ");
    while (token != NULL)
    {
        list[index] = strdup(token);
        token = strtok(NULL, " ");
        index++;
    }
    list[index] = NULL;

    free(str);

    return list;
}