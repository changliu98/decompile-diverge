void drwav_alaw_to_float(float *pOut, unsigned char *pIn, unsigned long sampleCount)
{
    if (pOut == ((void *)0) || pIn == ((void *)0))
        return;
    for (unsigned long i = 0; i < sampleCount; i++)
        *pOut++ = g_drwavAlawTable[pIn[i]] * (1.0f / (float)0x8000);
}