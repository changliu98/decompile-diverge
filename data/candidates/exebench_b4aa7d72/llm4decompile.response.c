void grad1(int hash, float *gx)
{
    int h = hash & 15;
    *gx = (h & 7) + 0.5f;
    if ((h & 8) != 0)
        *gx = -*gx;
}