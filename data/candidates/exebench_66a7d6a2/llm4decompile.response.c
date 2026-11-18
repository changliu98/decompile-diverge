void swapdouble(double *dbl)
{
    int i;
    int *j;
    j = (int *)dbl;
    i = *j;
    *j = ((i & 0xff000000) >> 24) | ((i & 0x00ff0000) >> 8) | ((i & 0x0000ff00) << 8) | ((i & 0x000000ff) << 24);
    i = *(j+1);
    *(j+1) = ((i & 0xff000000) >> 24) | ((i & 0x00ff0000) >> 8) | ((i & 0x0000ff00) << 8) | ((i & 0x000000ff) << 24);
}