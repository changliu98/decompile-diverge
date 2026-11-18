void drwav_f64_to_f32(float* pOut, const double* pIn, drwav_uint64 sampleCount)
{
    drwav_uint64 i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = (float)*pIn++;
    }
}