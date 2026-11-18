int get_max_int(int n)
{
    if (n == 0)
        return 0;
    int i = n / 2;
    int j = 0;
    while (i > 0)
    {
        i = i / 2;
        j++;
    }
    return 1 << j;
}