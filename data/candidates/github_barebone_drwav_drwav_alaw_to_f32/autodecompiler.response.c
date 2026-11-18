void drwav_alaw_to_f32(float* pOut, const char* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = ((float)g_drwavAlawTable[(unsigned char)pIn[i]]) / 32768.0f;
    }
}