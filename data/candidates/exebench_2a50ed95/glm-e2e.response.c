void ZVdotC21(int n, double complex *A, double complex *B, double complex *C) {
    double complex dot1 = 0.0;
    double complex dot2 = 0.0;

    for (int i = 0, j = 1; i < n; i += 2, j += 2) {
        double complex a1 = A[i];
        double complex a2 = A[j];
        double complex b1 = B[i];
        double complex b2 = B[j];

        dot1 += a1 * conj(b1) + a2 * conj(b2);
        dot2 += a1 * conj(b2) + a2 * conj(b1);
    }

    C[0] = dot1;
    C[1] = dot2;
}