void drwav_u8_to_s32(int32_t* dst, const uint8_t* src, uint64_t count) {
    if (dst == NULL || src == NULL) {
        return;
    }

    for (uint64_t i = 0; i < count; i++) {
        // Convert unsigned 8-bit to signed 8-bit, then shift to 32-bit range
        int32_t sample = ((int32_t)src[i] - 0x80) << 24;
        *dst++ = sample;
    }
}