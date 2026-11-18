int func0(int *lst, int size)
{
    int i;
    int total = 0;

    for (i = 0; i < size; i++)
        total += lst[i];

    return total;
}