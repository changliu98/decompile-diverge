void rfft1pt(float *ioptr)
{
    float t0r, t0i;

    t0r = ioptr[0];
    t0i = ioptr[1];
    ioptr[0] = t0r + t0i;
    ioptr[1] = t0r - t0i;
}