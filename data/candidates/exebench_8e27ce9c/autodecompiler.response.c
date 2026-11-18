static void DFT2(float *ioptr, float *cosptr)
{
    float f0;
    f0 = ioptr[0] + ioptr[1];
    ioptr[1] = ioptr[0] - ioptr[1];
    ioptr[0] = f0;
}