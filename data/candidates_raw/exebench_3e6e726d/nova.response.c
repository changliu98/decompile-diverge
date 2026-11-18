void func0(float *out, const double *x) {
    int i;
    for (i = 0; i < 10; i++) {
        out[i] = (float)x[i];
    }
}