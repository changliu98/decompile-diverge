void func0(double *x, double *y, double *z, double a, double b) {
    if (b > *y)
        *y = b;
    else
        *y = *y;
    if (a > *z)
        *z = a;
    else
        *z = *z;
}