void drwav_f64_to_s32(void *out, void *in, unsigned long sampleCount)
{
    int *pOut = (int *)out;
    double *pIn = (double *)in;
    if (pOut == ((void *)0) || pIn == ((void *)0))
        return;
    for (unsigned long i = 0; i < sampleCount; i++)
    {
        *pOut++ = (int)(pIn[i] * (double)(0x80000000));
    }
}