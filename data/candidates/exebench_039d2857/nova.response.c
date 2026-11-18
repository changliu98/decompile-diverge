void dual_mul(double x, double y, double a, double b, double *x1, double *y1) {
    *x1 = a * x;
    *y1 = a * x + b * y;
}