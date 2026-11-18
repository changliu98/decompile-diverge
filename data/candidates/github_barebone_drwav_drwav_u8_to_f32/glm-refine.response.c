void __cdecl drwav_u8_to_f32(float *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
    if (pOut && pIn)
    {
        for (size_t i = 0; i < sampleCount; ++i)
        {
            pOut[i] = (0.0078431377f * (float)pIn[i]) - 1.0f;
        }
    }
}