void geom_matmat2d(double *a, double *b, double *c) {
    // Assuming matrices are stored as 1D arrays in row-major order:
    // a = [a00, a01, a10, a11]
    // b = [b00, b01, b10, b11]
    // c = [c00, c01, c10, c11]

    // c00 = a00 * b00 + a01 * b10
    c[0] = a[0] * b[0] + a[2] * b[1];

    // c01 = a10 * b00 + a11 * b10
    c[1] = a[1] * b[0] + a[3] * b[1];

    // c10 = a00 * b01 + a01 * b11
    c[2] = a[0] * b[2] + a[2] * b[3];

    // c11 = a10 * b01 + a11 * b11
    c[3] = a[1] * b[2] + a[3] * b[3];
}