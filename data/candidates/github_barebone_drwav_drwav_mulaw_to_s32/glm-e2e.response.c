void drwav_mulaw_to_s32(int32_t *dst, const uint8_t *src, size_t count) {
    if (dst == NULL || src == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        uint8_t sample = src[i];
        int32_t expanded = (int32_t)g_drwavMulawTable[sample] << 16;
        *dst++ = expanded;
    }
}