void func0(int n, double *a, double *b, double *c, double *d, double *e) {
    int i, j, k;
    double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;

    for (i = 0, j = 1, k = 2; i < n; i++, j += 2, k += 2) {
        sum1 += a[i] * c[k];
        sum2 += a[i] * c[j];
        sum3 += b[i] * c[k];
        sum4 += b[i] * c[j];
    }
    *e = sum1;
    *(d + 1) = sum2;
    *(d + 2) = sum3;
    *(d + 3) = sum4;
}