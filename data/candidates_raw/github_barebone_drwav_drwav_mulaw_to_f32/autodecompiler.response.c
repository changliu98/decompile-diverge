void drwav_mulaw_to_f32(float* pOut, const char* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        unsigned char uc = pIn[i];
        *pOut++ = ((float)g_drwavMulawTable[uc]) / 32768.0f;
    }
}