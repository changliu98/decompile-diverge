char* func0(char* str, char ch)
{
    char *new_str;
    int len = strlen(str);
    int first = -1;
    int last = -1;
    int index;
    int new_index = 0;
    for (index = 0; index < len; index++)
    {
        if (str[index] == ch)
        {
            if (first == -1)
            {
                first = index;
            }
            last = index;
        }
    }
    if (first == -1 || last == -1 || first == last)
    {
        new_str = (char*)malloc(len + 1);
        strcpy(new_str, str);
    }
    else
    {
        new_str = (char*)malloc(len - 1);
        for (index = 0; index < first; index++)
        {
            new_str[new_index] = str[index];
            new_index++;
        }
        for (index = first + 1; index < last; index++)
        {
            new_str[new_index] = str[index];
            new_index++;
        }
        for (index = last + 1; index < len; index++)
        {
            new_str[new_index] = str[index];
            new_index++;
        }
        new_str[new_index] = '\0';
    }
    return new_str;
}