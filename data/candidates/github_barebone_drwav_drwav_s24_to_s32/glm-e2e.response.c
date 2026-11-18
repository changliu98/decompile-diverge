void drwav_s24_to_s32(int32_t *dst, const uint8_t *src, uint64_t count) {
    if (dst == NULL || src == NULL) {
        return;
    }

    for (uint64_t i = 0; i < count; i++) {
        uint32_t b0 = src[i * 3];
        uint32_t b1 = src[i * 3 + 1];
        uint32_t b2 = src[i * 3 + 2];

        // Combine the 3 bytes into a 32-bit integer.
        // The bytes are shifted to the most significant 24 bits.
        uint32_t combined = (b0 << 8) | (b1 << 16) | (b2 << 24);

        // Store the result into the destination array
        *dst = (int32_t)combined;
        dst++;
    }
}