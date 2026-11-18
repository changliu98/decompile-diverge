void func0(double *x, double *y, double a) {
    double temp = *x;
    *x = a * (*x) + (*y) * a;
    *y = a * temp + (*y) * a;
}