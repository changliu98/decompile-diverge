void ZVdotC31(int n, double *x, double *y, double *z, double *u, double *v,
             double *w) {
    int i, j, k;
    double a, b, c, d, e, f;
    a = b = c = d = e = f = 0.0;
    for (i = 0, j = 1, k = 2; i < n; i++, j += 2, k += 2) {
        a += x[i] * u[k];
        b += x[i] * v[k];
        c += y[i] * u[j];
        d += y[i] * v[j];
        e += z[i] * u[k];
        f += z[i] * v[k];
    }
    w[0] = a;
    w[1] = b;
    w[2] = c;
    w[3] = d;
    w[4] = e;
    w[5] = f;
}