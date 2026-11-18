void func0(int n, double *a, double *b, double *c, double *d, double *e,
             double *f) {
    int i, j, k;
    double sum1, sum2, sum3, sum4, sum5, sum6, sum7, sum8, sum9, sum10, sum11,
        sum12;
    for (i = 0, j = 0, k = 1;; i++, j += 2, k += 2) {
        sum1 = a[i] * b[j];
        sum2 = a[i] * b[k];
        sum3 = c[i] * b[j];
        sum4 = c[i] * b[k];
        sum5 = a[i] * d[j];
        sum6 = a[i] * d[k];
        sum7 = c[i] * d[j];
        sum8 = c[i] * d[k];
        sum9 = a[i] * e[j];
        sum10 = a[i] * e[k];
        sum11 = c[i] * e[j];
        sum12 = c[i] * e[k];
        f[j] = sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum7 + sum8 + sum9 +
               sum10 + sum11 + sum12;
        f[k] = sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum7 + sum8 + sum9 +
               sum10 + sum11 + sum12;
    }
}