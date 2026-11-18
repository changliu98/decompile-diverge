double func0(double *coeffs, int n) {
    double sum;
    double x;
    double ret;
    int i;

    if (n < 2)
        return 0.0;

    x = roots(coeffs, n);
    sum = 0.0;
    for (i = 0; i < n; i++)
        sum += coeffs[i] * (coeffs[i] - x);

    ret = sqrt(sum / (n - 1));
    return ret;
}