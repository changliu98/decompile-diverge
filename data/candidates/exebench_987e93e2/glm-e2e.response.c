void geom_matmat3f(float *a, float *b, float *out) {
    // Row 0
    out[0]  = a[0] * b[0]  + a[3] * b[1]  + a[6] * b[2];
    out[1]  = a[1] * b[0]  + a[4] * b[1]  + a[7] * b[2];
    out[2]  = a[2] * b[0]  + a[5] * b[1]  + a[8] * b[2];

    // Row 1
    out[3]  = a[0] * b[3]  + a[3] * b[4]  + a[6] * b[5];
    out[4]  = a[1] * b[3]  + a[4] * b[4]  + a[7] * b[5];
    out[5]  = a[2] * b[3]  + a[5] * b[4]  + a[8] * b[5];

    // Row 2
    out[6]  = a[0] * b[6]  + a[3] * b[7]  + a[6] * b[8];
    out[7]  = a[1] * b[6]  + a[4] * b[7]  + a[7] * b[8];
    out[8]  = a[2] * b[6]  + a[5] * b[7]  + a[8] * b[8];
}