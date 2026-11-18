void __cdecl drwav_alaw_to_s32(drwav_int32 *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
    if (pOut && pIn)
    {
        for (size_t i = 0; i < sampleCount; ++i)
        {
            pOut[i] = (drwav_int32)g_drwavAlawTable[pIn[i]] << 16;
        }
    }
}