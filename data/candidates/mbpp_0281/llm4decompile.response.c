int func0(int *test_list, int length)
{
    int i,j;
    for (i = 0; i < length - 1; i++)
    {
        for (j = i + 1; j < length; j++)
        {
            if (test_list[i] == test_list[j])
            {
                return 0;
            }
        }
    }
    return 1;
}