void __cdecl drwav_s16_to_f32(float *pOut, const drwav_int16 *pIn, size_t sampleCount)
{
    if (pOut && pIn)
    {
        for (size_t i = 0; i < sampleCount; ++i)
        {
            pOut[i] = (float)pIn[i] * 0.000030517578f;
        }
    }
}