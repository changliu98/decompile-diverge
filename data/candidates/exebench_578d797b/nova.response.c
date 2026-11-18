void add_a_vector(double a, int n, double *c, double *d) {
    do {
        *d++ += *c++ * a;
    } while (--n);
}