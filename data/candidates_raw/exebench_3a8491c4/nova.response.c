void func0(double *coeff, double *coeff1, double *coeff2) {
    int i;
    *coeff2 = 0;
    for (i = 0; i < 101; i++) {
        *coeff2 = *coeff2 + coeff[i];
    }
    *coeff2 = *coeff2 / 100;
}