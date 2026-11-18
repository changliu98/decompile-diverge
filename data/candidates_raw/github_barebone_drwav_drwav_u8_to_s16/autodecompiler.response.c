void drwav_u8_to_s16(short* pOut, const unsigned char* pIn, size_t sampleCount)
{
    size_t i;
    for (i = 0; ; i++)
    {
        int x;
        if (i >= sampleCount)
            break;

        x = pIn[i];
        x <<= 8;
        x -= 32768;
        pOut[i] = (short)x;
    }
}