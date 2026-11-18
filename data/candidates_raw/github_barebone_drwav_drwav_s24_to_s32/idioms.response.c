void drwav_int32_from_drwav_uint8_rgb(int *pOut, unsigned char *pIn, unsigned long sampleCount)
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