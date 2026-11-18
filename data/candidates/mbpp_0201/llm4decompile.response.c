int func0(char **lst, int size)
{
    int i;
    for (i = 1; i < size; i++)
        if (!strcmp(lst[0], lst[i]))
            return 0;
    return 1;
}