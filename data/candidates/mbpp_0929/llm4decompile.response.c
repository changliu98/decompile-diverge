int func0(int *tuplex, int size, int value)
{
    int i;
    int count = 0;
    for (i = 0; i < size; i++)
    {
        if (tuplex[i] == value)
        {
            count++;
        }
    }
    return count;
}