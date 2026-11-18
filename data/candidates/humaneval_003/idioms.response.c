int func0(int *operations, int size)
{
    int sum = 0;
    int i = 0;
    for (i = 0; i < size; i++)
    {
        sum += operations[i];
        if (sum < 0)
            return 1;
    }
    return 0;
}