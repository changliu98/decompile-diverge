char** func0(char** lst, int size)
{
    int i = 0;
    int j = 0;
    int count = 0;
    char** output = (char**)malloc(size * sizeof(char*));
    for (i = 0; i < size; i++)
    {
        count = 0;
        for (j = 0; lst[i][j] != '\0'; j++)
        {
            if (lst[i][j] >= '0' && lst[i][j] <= '9')
            {
                if ((lst[i][j] - '0') % 2 == 1)
                {
                    count++;
                }
            }
        }
        output[i] = (char*)malloc(100 * sizeof(char));
        sprintf(output[i], "the number of odd elements %d in the string %d of the %d input.", count, count, count);
    }
    return output;
}