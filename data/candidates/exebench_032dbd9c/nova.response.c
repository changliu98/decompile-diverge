void poly_mul1(double *a, double *b, int i, int j, double *c, int *n) {
    int k, l;
    *n = i + j;
    for (k = 0; k < 18; k++)
        c[k] = 0;
    for (k = 0; k <= i; k++)
        for (l = 0; l <= j; l++)
            c[k + l] += a[k] * b[l];
}