void __cdecl drwav_f32_to_s32(drwav_int32 *pOut, const float *pIn, size_t sampleCount)
{
    if (pOut && pIn)
    {
        for (size_t i = 0; i < sampleCount; ++i)
        {
            pOut[i] = (drwav_int32)(2147483600.0f * pIn[i]);
        }
    }
}