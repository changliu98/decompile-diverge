void drwav_mulaw_to_f32(float *pOut, unsigned char *pIn, unsigned long sampleCount)
{
    if (pOut && pIn)
    {
        for (unsigned long i = 0; i < sampleCount; i++)
        {
            *pOut++ = g_drwavMulawTable[pIn[i]] / (float)32768;
        }
    }
}