int getPossibleCount(int *array, int *num)
{
    int i;
    int count = 0;

    for (i = 0; i < 9; i++)
    {
        if (array[i] != 0)
        {
            *num = array[i];
            count++;
        }
    }

    return count;
}