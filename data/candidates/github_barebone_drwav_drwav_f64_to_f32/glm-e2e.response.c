void drwav_f64_to_f32(float* dst, const double* src, size_t count) {
    if (dst == NULL || src == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        dst[i] = (float)src[i];
    }
}