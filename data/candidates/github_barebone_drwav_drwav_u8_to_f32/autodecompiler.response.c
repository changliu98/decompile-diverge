void drwav_u8_to_f32(float* pOut, const drwav_int8* pIn, size_t sampleCount)
{
    size_t i;

    if (to == NULL || from == NULL) {
        return;
    }

    for (i = 0; i < sample_count; ++i) {
        float x = ((float)pIn[i]);
        x = x - 1.0f;
        *pOut++ = x;
    }
}