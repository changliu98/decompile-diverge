void drwav_u8_to_f32(void *pOut, void *pIn, unsigned long sampleCount)
{
    float *out = (float *) pOut;
    char *in = (char *) pIn;
    if (out == ((void *)0) || in == ((void *)0))
        return;
    for (unsigned long i = 0; i < sampleCount; i++)
        *out++ = (float) in[i] * (1.0 / 128.0) - 1.0f;
}