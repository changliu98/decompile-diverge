void drwav_s32_to_f32(float* dst, const int32_t* src, uint64_t count) {
    if (dst == NULL || src == NULL) {
        return;
    }

    for (uint64_t i = 0; i < count; ++i) {
        // The assembly uses double-precision floating-point arithmetic 
        // for the conversion before storing it as a single-precision float.
        // 2147483648.0 is 2^31.
        dst[i] = (float)((double)src[i] / 2147483648.0);
    }
}