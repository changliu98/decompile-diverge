void matvec(double *A, double *x, double *y) {
    int i, j;
    int n = 5;

    j = 0;
    for (i=0; i<n; i++) {
        y[i] = A[j++] * x[0];
        y[i] += A[j++] * x[1];
        y[i] += A[j++] * x[2];
        y[i] += A[j++] * x[3];
    }
}