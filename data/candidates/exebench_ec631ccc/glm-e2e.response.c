void lamda2x(double *x, double *out, double *c, double *m) {
    // First component (offset 0)
    out[0] = m[0] * x[0] + m[5] * x[1] + m[4] * x[2] + c[0];

    // Second component (offset 8)
    out[1] = m[1] * x[1] + m[3] * x[2] + c[1];

    // Third component (offset 16)
    out[2] = m[2] * x[2] + c[2];
}