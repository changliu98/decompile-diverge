void drwav_f32_to_s32(void *out, float *in, unsigned long sampleCount)
{
    int *out32 = (int *)out;
    if (out && in)
    {
        for (unsigned long i = 0; i < sampleCount; i++)
        {
            *out32++ = in[i] * (float)(0x7fffffff);
        }
    }
}