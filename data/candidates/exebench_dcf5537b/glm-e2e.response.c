void ZVdotU23(int n, double *A, double *B, double *C, double *D, double *E, double *out) {
    double s00 = 0.0, s01 = 0.0;
    double s10 = 0.0, s11 = 0.0;
    double s20 = 0.0, s21 = 0.0;
    double s30 = 0.0, s31 = 0.0;
    double s40 = 0.0, s41 = 0.0;
    double s50 = 0.0, s51 = 0.0;

    for (int i = 0, j = 0, k = 1; i < n; i += 1, j += 2, k += 2) {
        double a0 = A[j];
        double a1 = A[k];
        double b0 = B[j];
        double b1 = B[k];
        double c0 = C[j];
        double c1 = C[k];
        double d0 = D[j];
        double d1 = D[k];
        double e0 = E[j];
        double e1 = E[k];

        s00 += a0 * c0 - a1 * c1;
        s01 += a0 * c1 + a1 * c0;
        s10 += a0 * d0 - a1 * d1;
        s11 += a0 * d1 + a1 * d0;
        s20 += a0 * e0 - a1 * e1;
        s21 += a0 * e1 + a1 * e0;
        s30 += b0 * c0 - b1 * c1;
        s31 += b0 * c1 + b1 * c0;
        s40 += b0 * d0 - b1 * d1;
        s41 += b0 * d1 + b1 * d0;
        s50 += b0 * e0 - b1 * e1;
        s51 += b0 * e1 + b1 * e0;
    }

    out[0]  = s00;
    out[1]  = s01;
    out[2]  = s10;
    out[3]  = s11;
    out[4]  = s20;
    out[5]  = s21;
    out[6]  = s30;
    out[7]  = s31;
    out[8]  = s40;
    out[9]  = s41;
    out[10] = s50;
    out[11] = s51;
}