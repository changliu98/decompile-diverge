void babl_matrix_to_float(double *src, float *dst) {
    for (int i = 0; i < 9; i++) {
        dst[i] = (float)src[i];
    }
}