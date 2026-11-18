void drwav_mulaw_to_s32(drwav_int32* pOut, const char* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        unsigned char uc = pIn[i];
        *pOut++ = ((drwav_int32)g_drwavMulawTable[uc]) << 16;
    }
}