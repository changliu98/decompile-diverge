void drwav_u8_to_f32(float* dst, const uint8_t* src, size_t len) {
    if (dst == NULL || src == NULL) {
        return;
    }

    for (size_t i = 0; i < len; ++i) {
        float sample = (float)src[i];
        sample *= 1.0f / 127.5f; // 0x8fde(%rip) points to 1/127.5f
        sample -= 1.0f;          // 0x8fbf(%rip) points to 1.0f
        *dst++ = sample;
    }
}