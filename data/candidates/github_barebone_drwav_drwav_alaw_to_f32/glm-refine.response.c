void __cdecl drwav_alaw_to_f32(float *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
    if (pOut && pIn)
    {
        for (size_t i = 0; i < sampleCount; ++i)
        {
            pOut[i] = (float)g_drwavAlawTable[pIn[i]] / 32768.0f;
        }
    }
}