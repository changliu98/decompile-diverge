int func0(int *list1, int size)
{
    int i;
    int min = list1[0];

    for (i = 0; i < size; i++)
    {
        if (list1[i] < min)
        {
            min = list1[i];
        }
    }

    return min;
}