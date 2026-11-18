void max1D_double(double *coeff, int n, double *max) {
    int i;
    max[0] = -INFINITY;
    max[1] = -1;
    for (i = 0; i < n; i++) {
        if (coeff[i] > max[0]) {
            max[0] = coeff[i];
            max[1] = i;
        }
    }
}