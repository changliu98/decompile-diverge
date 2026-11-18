void mat3d_from_mat3f(double *out, float *x, int *length) {
    int i = 0;
    for (; i < 10; ++i) {
        out[i] = (double)x[i];
    }
}