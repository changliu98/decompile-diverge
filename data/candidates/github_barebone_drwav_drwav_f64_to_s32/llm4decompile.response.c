void drwav_f64_to_s32(drwav_int32* pOut, const drwav_float64* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        pOut[i] = (drwav_int32)(pIn[i] * 2147483647.0);
    }
}