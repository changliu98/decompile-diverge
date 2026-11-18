int checkdist(float *d, int n)
{
    int i;

    if ((d[0] > 0) ^ (d[1] > 0))
        i = n;
    else
        i = 0;

    return (i);
}