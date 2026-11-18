void func0(double *a, double *b) {
    double a_x = a[0] * b[0] - (INT_MAX & (a[0] * b[1]));
    double a_y = a[1] * b[0] - (INT_MAX & (a[1] * b[1]));
    a[0] = a_x;
    a[1] = a_y;
}