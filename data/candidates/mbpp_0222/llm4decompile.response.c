int func0(int *test_array, int size)
{
    int i;
    for (i = 1; i < size; i++)
    {
        if (test_array[i] < test_array[i - 1])
        {
            return 0;
        }
    }
    return 1;
}