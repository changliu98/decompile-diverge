void __cdecl drwav_mulaw_to_f32(float *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
    if (pOut && pIn)
    {
        for (size_t i = 0; i < sampleCount; ++i)
        {
            pOut[i] = (float)g_drwavMulawTable[pIn[i]] / 32768.0f;
        }
    }
}