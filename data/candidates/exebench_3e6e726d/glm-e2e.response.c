void mat3f_from_mat3d(float *out, const double *in) {
    for (int i = 0; i < 9; i++) {
        out[i] = (float)in[i];
    }
}