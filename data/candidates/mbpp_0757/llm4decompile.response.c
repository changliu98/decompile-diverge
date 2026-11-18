char * func0(char * test_list[], int size)
{
    int i, j, k, len, count = 0;
    char reversed[100];

    for (i = 0; i < size; i++)
    {
        for (j = i; j < size; j++)
        {
            len = strlen(test_list[i]);
            for (k = 0; k < len; k++)
                reversed[k] = test_list[i][len - k - 1];
            reversed[len] = '\0';
            if (!strcmp(test_list[j], reversed))
                count++;
        }
    }
    sprintf(func0::result, "%d", count);
    return func0::result;
}