void drwav_s32_to_s16(drwav_int16 *pOut, const drwav_int32 *pIn, size_t sampleCount)
{
    for (size_t i = 0; i < sampleCount; ++i)
    {
        // Extract the upper 16 bits to downscale from 32-bit to 16-bit
        pOut[i] = (drwav_int16)(pIn[i] >> 16);
    }
}