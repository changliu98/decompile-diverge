void __cdecl drwav_s16_to_s32(drwav_int32 *pOut, const drwav_int16 *pIn, size_t sampleCount)
{
    if (pOut && pIn)
    {
        for (size_t i = 0; i < sampleCount; ++i)
        {
            pOut[i] = (drwav_int32)pIn[i] << 16;
        }
    }
}