void drwav_float_to_pcm(void *pOut, void *pIn, unsigned long sampleCount)
{
    float *out = (float *) pOut;
    float *in = (float *) pIn;
    if (out == ((void *)0) || in == ((void *)0))
        return;
    for (unsigned long i = 0; i < sampleCount; i++)
        *out++ = in[i] / (float) (0x7fffffff);
}