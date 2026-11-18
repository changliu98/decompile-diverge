void drwav_s24_to_s16(short *pOut, unsigned char *pIn, unsigned long sampleCount)
{
    unsigned long i;
    for (i = 0; i < sampleCount; i++)
    {
        unsigned int sample = pIn[i * 3 + 0] << 16 | pIn[i * 3 + 1] << 8 | pIn[i * 3 + 2];
        pOut[i] = (short)(sample >> 16);
    }
}