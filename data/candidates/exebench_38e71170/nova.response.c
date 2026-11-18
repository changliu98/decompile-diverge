void scal3(double x, double *f, double *f_p, int n) {
    int i;
    f[0] *= x;
    f_p[0] *= x;
    for (i = 1; i < n; i++) {
        f[i] *= x;
        f_p[i] *= x;
    }
}