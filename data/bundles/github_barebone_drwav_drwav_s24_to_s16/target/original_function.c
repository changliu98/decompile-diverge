DRWAV_API void drwav_s24_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    int r;
    size_t i;
    for (i = 0; i < sampleCount; ++i) {
        int x = ((int)(((unsigned int)(((const drwav_uint8*)pIn)[i*3+0]) << 8) | ((unsigned int)(((const drwav_uint8*)pIn)[i*3+1]) << 16) | ((unsigned int)(((const drwav_uint8*)pIn)[i*3+2])) << 24)) >> 8;
        r = x >> 8;
        pOut[i] = (short)r;
    }
}