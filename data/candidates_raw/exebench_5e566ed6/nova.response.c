int func0(double *a, double *b, int n, double *cov, double *var) {
    int i;
    double avga = 0.0, avgb = 0.0, covar = 0.0, vara = 0.0, varb = 0.0;
    for (i = 0; i < n; i++) {
        avga += a[i];
        avgb += b[i];
        covar += a[i] * b[i];
    }
    avga /= n;
    avgb /= n;
    covar = covar / n - avga * avgb;
    for (i = 0; i < n; i++) {
        vara += (a[i] - avga) * (a[i] - avga);
        varb += (b[i] - avgb) * (b[i] - avgb);
    }
    vara /= n;
    varb /= n;
    *cov = covar;
    *var = vara;
    return 0;
}