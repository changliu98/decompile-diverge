void drwav_s32_to_s16(drwav_int16* pOut, const drwav_int32* pIn, size_t sampleCount)
{
    size_t i;

    for (i = 0; i < sampleCount; ++i) {
        pOut[i] = (drwav_int16)(pIn[i] >> 16);
    }
}