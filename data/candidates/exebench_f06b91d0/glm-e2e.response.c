void add_vector(double *a, double *b, double *c) {
    for (int i = 0; i < 3; i++) {
        c[i] = a[i] + b[i];
    }
}