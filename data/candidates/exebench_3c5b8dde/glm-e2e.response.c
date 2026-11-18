void mat3d_from_mat3f(double *out, const float *in) {
    for (int i = 0; i < 9; i++) {
        out[i] = (double)in[i];
    }
}