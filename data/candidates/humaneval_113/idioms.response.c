char **func0(char **input, int size)
{
    int i;
    int j;
    int sum;
    char **result = (char **)malloc(size * sizeof(char *));
    for (i = 0; i < size; i++)
    {
        sum = 0;
        for (j = 0; input[i][j] != '\0'; j++)
        {
            if (input[i][j] >= '0' && input[i][j] <= '9')
            {
                if ((input[i][j] - '0') % 2 == 1)
                {
                    sum++;
                }
            }
        }
        result[i] = (char *)malloc(100 * sizeof(char));
        sprintf(result[i], "the number of odd elements %d in the string %d of the %d input.", sum, sum, sum);
    }
    return result;
}