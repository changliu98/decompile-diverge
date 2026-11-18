void drwav_f32_to_s16(drwav_int16* pOut, const float* pIn, size_t sampleCount)
{
    size_t i;
    for (i = 0; i < sampleCount; ++i) {
        float f = pIn[i];
        if (f < -1.0f) {
            f = -1.0f;
        } else if (f > 1.0f) {
            f = 1.0f;
        }

        pOut[i] = (drwav_int16)((f * 32767.0f) - 32768);
    }
}