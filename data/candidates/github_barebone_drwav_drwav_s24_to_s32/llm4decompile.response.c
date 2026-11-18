void drwav_s24_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (size_t i = 0; i < sampleCount; ++i) {
        drwav_uint32 sample = pIn[i*3];
        sample = (sample << 8) | pIn[i*3 + 1];
        sample = (sample << 8) | pIn[i*3 + 2];


        sample = (sample << 8) >> 8;

        *pOut++ = (drwav_int32)sample;
    }
}