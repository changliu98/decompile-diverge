void func0(double a, int n, double *c, double *d) {
    do {
        *d++ += *c++ * a;
    } while (--n);
}