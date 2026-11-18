void drwav_alaw_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (size_t i = 0; i < sampleCount; ++i) {
        *pOut++ = (drwav_int32)((short)g_drwavAlawTable[*pIn++] << 16);
    }
}