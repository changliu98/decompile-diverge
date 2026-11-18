char** func0(char** lst, int lst_size, int* return_size)
{
    *return_size = 0;
    for (int i = 0; i < lst_size; i++)
        if (strlen(lst[i]) % 2 == 0)
            lst[(*return_size)++] = lst[i];

    for (int i = 0; i < *return_size - 1; i++)
        for (int j = 0; j < *return_size - i - 1; j++)
            if (strlen(lst[j]) > strlen(lst[j + 1]) || (strlen(lst[j]) == strlen(lst[j + 1]) && strcmp(lst[j], lst[j + 1]) > 0))
            {
                char* tmp = lst[j];
                lst[j] = lst[j + 1];
                lst[j + 1] = tmp;
            }

    char** result = (char**)malloc((long long)*return_size * sizeof(char*));
    for (int i = 0; i < *return_size; i++)
        result[i] = lst[i];

    return result;
}