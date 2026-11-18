void drwav_s24_to_f32(float* dst, const uint8_t* src, uint64_t count) {
    if (dst == 0 || src == 0) {
        return;
    }

    for (uint64_t i = 0; i < count; i++) {
        // Extract the 3 bytes of the 24-bit signed integer
        uint32_t b0 = (uint32_t)src[i * 3] << 8;
        uint32_t b1 = (uint32_t)src[i * 3 + 1] << 16;
        uint32_t b2 = (uint32_t)src[i * 3 + 2] << 24;

        // Combine them and perform an arithmetic right shift to sign-extend to 32-bit
        int32_t s32 = (int32_t)((b0 | b1 | b2) >> 8);

        // Convert to double, scale, and then downcast to float
        double d = (double)s32;
        float f = (float)(d * 2.3283064365386963e-10); // 2.3283064365386963e-10 is 1 / 2^32

        *dst = f;
        dst++;
    }
}