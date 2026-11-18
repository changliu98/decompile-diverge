void drwav_alaw_to_f32(float* dst, const uint8_t* src, size_t count) {
    if (dst == NULL || src == NULL) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        uint8_t a = src[i];
        float sample = (float)g_drwavAlawTable[a] / 32768.0f;
        *dst = sample;
        dst++;
    }
}