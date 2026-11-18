int func0(char *str)
{
    int count = 0;
    int len = strlen(str);
    int i = 0;
    int j = 0;
    for (i = 0; i < len; i++)
    {
        for (j = 1; j <= (len - i); j++)
        {
            if (check_Equality(str, i, j))
            {
                count++;
            }
        }
    }
    return (count);
}