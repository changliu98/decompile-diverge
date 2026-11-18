void drwav_f32_to_s16(int16_t* dst, const float* src, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        float sample = src[i];
        float clamped;

        // Clamp upper bound to 1.0f
        if (1.0f < sample) {
            clamped = 1.0f;
        } else {
            // Clamp lower bound to -1.0f
            if (sample > -1.0f) {
                clamped = sample;
            } else {
                clamped = -1.0f;
            }
        }

        // Convert to signed 16-bit integer
        // The float is offset by 1.0f, scaled by 32768.0f, and then shifted down by 0x8000
        int32_t converted = (int32_t)((clamped + 1.0f) * 32768.0f);
        converted -= 0x8000;

        dst[i] = (int16_t)converted;
    }
}