int get_second_min(int *list, int size)
{
    int first; int second;
    int i;
    if (size < 2)
        return -1;
    first = 0x7fffffff;
    second = 0x7fffffff;
    for (i = 0; i < size; i++)
    {
        if (list[i] < first)
        {
            second = first;
            first = list[i];
        }
        else if (list[i] < second && list[i] != first)
        {
            second = list[i];
        }
    }
    if (second == 0x7fffffff)
        return -1;
    return second;
}