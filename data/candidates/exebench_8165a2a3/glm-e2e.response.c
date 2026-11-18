void geom_matmat2f(float *out, const float *a, const float *b) {
    // Matrix layout (row-major):
    // a[0] a[1]     b[0] b[1]     out[0] out[1]
    // a[2] a[3]  *  b[2] b[3]  =  out[2] out[3]

    out[0] = a[0] * b[0] + a[1] * b[2];
    out[1] = a[0] * b[1] + a[1] * b[3];
    out[2] = a[2] * b[0] + a[3] * b[2];
    out[3] = a[2] * b[1] + a[3] * b[3];
}