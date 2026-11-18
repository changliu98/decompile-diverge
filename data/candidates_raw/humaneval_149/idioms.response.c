char **get_even_sorted(char **list, int list_size, int *return_size)
{
    int i; int j;
    char *temp;
    unsigned long len1; unsigned long len2;
    char **sorted;
    *return_size = 0;
    for (i = 0; i < list_size; i++)
    {
        if (strlen(list[i]) % 2 == 0)
        {
            list[*return_size] = list[i];
            (*return_size)++;
        }
    }
    for (i = 0; i < *return_size - 1; i++)
    {
        for (j = 0; j < *return_size - i - 1; j++)
        {
            len1 = strlen(list[j]);
            len2 = strlen(list[j + 1]);
            if (len1 > len2 || (len1 == len2 && strcmp(list[j], list[j + 1]) > 0))
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
    sorted = (char **)malloc(*return_size * sizeof(char *));
    for (i = 0; i < *return_size; i++)
    {
        sorted[i] = list[i];
    }
    return sorted;
}