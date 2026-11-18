int func0(int *list1, int size)
{
    int i;
    int max = list1[0];

    for (i = 0; i < size; i++)
    {
        if (list1[i] > max)
        {
            max = list1[i];
        }
    }

    return max;
}