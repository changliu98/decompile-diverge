int func0(int *listval, int size)
{
    int i;
    int max_val;

    max_val = 0x80000000;
    for (i = 0; i < size; i++)
    {
        if (listval[i] > max_val)
        {
            max_val = listval[i];
        }
    }

    return max_val;
}