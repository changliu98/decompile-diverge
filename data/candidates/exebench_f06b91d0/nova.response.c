void add_vector(double *a, double *b, double *c) {
    int i;
    for (i = 0; i < 4; i++) {
        c[i] = a[i] + b[i];
    }
}