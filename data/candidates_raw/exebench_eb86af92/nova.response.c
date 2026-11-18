void func0(double *coeff, int degree, double *max, double *power) {
    int i = 0;
    *max = coeff[0];
    *power = 0;
    for (i = 1; i <= degree; i++) {
        if (coeff[i] > *max) {
            *max = coeff[i];
            *power = 1.0 * i;
        }
    }
}