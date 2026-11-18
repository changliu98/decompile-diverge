void compute_matrix_T(double *T, double a, double b, double c, double d) {
    T[0] = a;
    T[1] = a * b;
    T[2] = a * d * 2.0;
    T[3] = a * (2.0 * b * d + a * c);
}