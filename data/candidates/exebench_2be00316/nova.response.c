void ZVdotU31(int n, double *a, double *b, double *c, double *d, double *e,
             double *f) {
    int i, j, k;
    double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0, sum6 = 0;
    for (i = 0, j = 1, k = 2; i < n; i++, j += 2, k += 2) {
        double a1 = a[i], a2 = a[j], a3 = a[k];
        double b1 = b[i], b2 = b[j], b3 = b[k];
        double c1 = c[i], c2 = c[j], c3 = c[k];
        double d1 = d[i], d2 = d[j], d3 = d[k];
        double e1 = e[i], e2 = e[j], e3 = e[k];
        sum1 += a1 * b1 + a2 * b2 + a3 * b3;
        sum2 += a1 * c1 + a2 * c2 + a3 * c3;
        sum3 += a1 * d1 + a2 * d2 + a3 * d3;
        sum4 += a1 * e1 + a2 * e2 + a3 * e3;
        sum5 += b1 * c1 + b2 * c2 + b3 * c3;
        sum6 += b1 * d1 + b2 * d2 + b3 * d3;
    }
    f[0] = sum1;
    f[1] = sum2;
    f[2] = sum3;
    f[3] = sum4;
    f[4] = sum5;
    f[5] = sum6;
}