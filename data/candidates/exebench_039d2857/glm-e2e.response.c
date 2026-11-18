void dual_mul(double a1, double a2, double b1, double b2, double *c1, double *c2) {
    *c1 = a1 * b1;
    *c2 = a1 * b2 + a2 * b1;
}