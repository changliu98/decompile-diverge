char** func0(char** str, int n, int l, int *size)
{
    int i, count = 0;
    for (i = 0; i < n; i++)
        if (strlen(str[i]) == (size_t)l)
            func0::result[count++] = str[i];
    *size = count;
    return func0::result;
}