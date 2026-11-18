void drwav_mulaw_to_f32(float* dst, const uint8_t* src, size_t len) {
    if (dst == NULL || src == NULL) {
        return;
    }
    
    for (size_t i = 0; i < len; ++i) {
        uint8_t mulaw = src[i];
        float sample = (float)g_drwavMulawTable[mulaw] / 32768.0f;
        *dst = sample;
        dst++;
    }
}