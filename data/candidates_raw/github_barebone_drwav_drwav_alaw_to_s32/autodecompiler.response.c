void drwav_alaw_to_s32(drwav_int32* pOut, const char* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = ((drwav_int32)g_drwavAlawTable[(unsigned char)pIn[i]]) << 16;
    }
}