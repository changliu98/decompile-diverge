void func0(double *a, double *b, double *c, double *d) {
    int i = 0;
    for (i = 0; i < N; i++) {
        c[i] = a[i] * b[i];
    }
    for (i = 0; i < N; i++) {
        d[i] = a[i] * b[i];
    }
}