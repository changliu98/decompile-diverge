void swapfloat(float *flt)
{
    int *intfloat;
    intfloat = (int *)flt;
    *intfloat = (*intfloat << 24) |
                ((*intfloat & 0x0000ff00) << 8) |
                ((*intfloat & 0x00ff0000) >> 8) |
                (*intfloat >> 24);
}