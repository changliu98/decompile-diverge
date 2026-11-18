int unique(int *list, int length)
{
    int i;
    int j;
    for (i = 0; i < length - 1; i++)
    {
        for (j = i + 1; j < length; j++)
        {
            if (list[i] == list[j])
            {
                return 0;
            }
        }
    }
    return 1;
}