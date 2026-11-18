void max1D_double( double a[], int n, double *maxIndex)
{
    int i;

    *maxIndex = -1;
    for (i = 0; i < n; i++)
    {
        if (a[i] > *maxIndex)
        {
            *maxIndex = a[i];
            *maxIndex = i;
        }
    }
}