void drwav_s16_to_f32(float* pOut, const int16_t* pIn, size_t sampleCount) {
    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (size_t i = 0; i < sampleCount; ++i) {
        // movswl sign-extends the 16-bit integer to 32-bit before conversion
        int32_t sample = (int32_t)pIn[i];
        
        // cvtsi2ss converts the 32-bit integer to float
        // mulss multiplies by the constant (1.0f / 32768.0f)
        *pOut++ = (float)sample * (1.0f / 32768.0f);
    }
}