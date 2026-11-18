void func0(int n, double *a, double *b, double *c, double *d, double *e,
             double *f) {
    int i, j, k;
    double sum1, sum2, sum3, sum4, sum5, sum6, sum7, sum8;
    sum1 = sum2 = sum3 = sum4 = sum5 = sum6 = sum7 = sum8 = 0.0;
    for (i = 0; i < n; i++) {
        for (j = 1; j <= n; j++) {
            for (k = 1; k <= n; k++) {
                sum1 += a[i] * b[j] * c[k];
                sum2 += a[i] * b[k] * c[j];
                sum3 += a[i] * c[j] * b[k];
                sum4 += a[i] * c[k] * b[j];
                sum5 += b[i] * a[j] * c[k];
                sum6 += b[i] * a[k] * c[j];
                sum7 += b[i] * c[j] * a[k];
                sum8 += b[i] * c[k] * a[j];
            }
        }
    }
    f[0] = sum1;
    f[1] = sum2;
    f[2] = sum3;
    f[3] = sum4;
    f[4] = sum5;
    f[5] = sum6;
    f[6] = sum7;
    f[7] = sum8;
}