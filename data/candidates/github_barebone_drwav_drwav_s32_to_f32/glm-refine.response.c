void __cdecl drwav_s32_to_f32(float *pOut, const drwav_int32 *pIn, size_t sampleCount)
{
    if (pOut && pIn)
    {
        for (size_t i = 0; i < sampleCount; ++i)
        {
            // Cast to double to preserve precision before dividing by 2^31
            pOut[i] = (double)pIn[i] / 2147483648.0;
        }
    }
}