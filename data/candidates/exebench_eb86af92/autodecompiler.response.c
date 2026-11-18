void maxind( double a[], int n, double *val, double *index)
{
    int i = 0;

    *val = a[0];
    *index = 0;

    for (i = 1;i < n;i++)
    {
        if (a[i] > *val)
        {
            *val = a[i];
            *index = i;
        }
    }
}