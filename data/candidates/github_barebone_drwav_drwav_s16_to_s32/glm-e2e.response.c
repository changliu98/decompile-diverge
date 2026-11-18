void drwav_s16_to_s32(int32_t* dst, const int16_t* src, uint64_t count) {
    if (dst == NULL || src == NULL) {
        return;
    }

    for (uint64_t i = 0; i < count; i++) {
        // Sign-extend the 16-bit sample to 32-bit, then shift left by 16 bits
        dst[i] = ((int32_t)src[i]) << 16;
    }
}