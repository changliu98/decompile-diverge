int func0(int *xs, int size)
{
    int i;
    int min_val = 2147483647;

    for (i = 0; i < size; i++)
    {
        if (xs[i] < min_val)
        {
            min_val = xs[i];
        }
    }

    return min_val;
}