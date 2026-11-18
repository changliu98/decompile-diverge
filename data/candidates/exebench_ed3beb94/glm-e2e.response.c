void math_matrix_copy(float *dst, const float *src) {
    for (int i = 0; i < 16; i++) {
        dst[i] = src[i];
    }
}