void drwav_f32_to_s32(int32_t* dst, const float* src, size_t count) {
    if (dst == NULL || src == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        *dst++ = (int32_t)(src[i] * 2147483648.0f);
    }
}