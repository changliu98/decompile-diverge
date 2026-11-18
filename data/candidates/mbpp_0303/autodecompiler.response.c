int func0(int *y, int n)
{
    int i;
    int isMonotonic = 1;
    int last_y = -1e32;
    for (i = 1; ; i++)
    {
        if (i >= n)
            break;

        if (y[i] < last_y)
        {
            isMonotonic = 0;
            break;
        }
        else if (y[i-1] > last_y)
        {
            last_y = y[i-1];
        }
    }

    return isMonotonic;
}