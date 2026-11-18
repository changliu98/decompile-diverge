double func0(double *x, double *y) {
    double a = 3.0;
    double b = 0.1;
    long int c = 70368744177663;
    long int d = 765234123;
    long int q = (*x) * (*y);
    double z;
    q = q & c;
    z = b * (double)q;
    *x = q;
    return z;
}