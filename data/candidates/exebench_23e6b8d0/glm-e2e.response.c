void lincomb(double a, double *x, double b, double *y, double *out) {
    out[0] = a * x[0] + b * y[0];
    out[1] = a * x[1] + b * y[1];
    out[2] = a * x[2] + b * y[2];
}