void drwav_s24_to_s32(int *pOut, unsigned char *pIn, unsigned long sampleCount)
{
    int *pOutCur = pOut;
    unsigned long i;
    if (pOut && pIn)
    {
        for (i = 0; i < sampleCount; i++)
        {
            *pOutCur++ = (pIn[i * 3 + 0] << 8) | (pIn[i * 3 + 1] << 16) | (pIn[i * 3 + 2] << 24);
        }
    }
}