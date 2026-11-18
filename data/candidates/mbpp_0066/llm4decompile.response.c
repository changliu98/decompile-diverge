int func0(int *list, int list_size)
{
    int i;
    int count = 0;
    for (i = 0; i < list_size; i++)
    {
        if (list[i] >= 0)
        {
            count++;
        }
    }
    return count;
}