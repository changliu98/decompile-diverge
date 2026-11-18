void func0(double *p, double *x, double *y, double *z) {
    int i;
    for (i = 0; i < 3; i++) {
        x[i] = p[3 * i + 0];
        y[i] = p[3 * i + 1];
        z[i] = p[3 * i + 2];
    }
}