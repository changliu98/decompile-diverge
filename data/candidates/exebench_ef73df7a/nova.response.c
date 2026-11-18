void ZVdotC13(int n, double *x, double *y, double *z, double *t, double *u,
             double *v) {
    int i, j;
    double a, b, c, d, e, f;
    a = b = c = d = e = f = 0;
    for (i = 0, j = 1; i < n; i++, j += 2) {
        a += x[i] * y[j];
        b += x[i] * y[j + 1];
        c += x[j] * y[i];
        d += x[j] * y[j + 1];
        e += x[j + 1] * y[i];
        f += x[j + 1] * y[j + 1];
    }
    *v = a;
    *u = b;
    *t = c;
    *z = d;
    *y = e;
    *x = f;
}