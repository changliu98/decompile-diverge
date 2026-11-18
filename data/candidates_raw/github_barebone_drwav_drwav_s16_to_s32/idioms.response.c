void drwav_convert_s16_to_s32(void *outBuffer, void *inBuffer, unsigned long sampleCount)
{
    int *out = (int *)outBuffer;
    short *in = (short *)inBuffer;
    if (out && in)
    {
        for (unsigned long i = 0; i < sampleCount; i++)
        {
            *out++ = in[i] << 16;
        }
    }
}