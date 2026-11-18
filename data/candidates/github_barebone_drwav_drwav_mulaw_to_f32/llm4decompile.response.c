void drwav_mulaw_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (size_t i = 0; i < sampleCount; ++i) {
        *pOut++ = (float)(short)g_drwavMulawTable[*pIn++] / 32768.0f;
    }
}