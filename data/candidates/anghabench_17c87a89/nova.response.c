double KernelBessel_Q1(double E) {
    double a = A[0], b = A[1];
    for (int i = 0; i < N; i++) {
        a = a + B[i] / E * A[i + 2];
        b = b + C[i] / E * A[i + 2];
    }
    return a / b;
}