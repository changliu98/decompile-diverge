void htonf(float *x)
{
    int *y;
    y = (int*)x;
    *y = htonl(*y);
}