void cross3(double Q[3], double A[3], double B[3]) {
    Q[0] = A[1] * B[2] - A[2] * B[1];
    Q[1] = A[2] * B[0] - A[0] * B[2];
    Q[2] = A[0] * B[1] - A[1] * B[0];
}