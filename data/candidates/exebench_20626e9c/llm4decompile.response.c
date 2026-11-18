void unscale(double *prob, unsigned int times)
{
    unsigned int i;
    for (i = 0; i < times; i++)
        *prob /= 2.0;
}