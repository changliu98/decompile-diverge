int matM4toM3(double *src, double *dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];

    dst[3] = src[4];
    dst[4] = src[5];
    dst[5] = src[6];

    dst[6] = src[8];
    dst[7] = src[8];
    dst[8] = src[10];

    return 0;
}