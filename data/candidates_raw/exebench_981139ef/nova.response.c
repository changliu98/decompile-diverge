void func0(float *dst, float *a, float *b) {
    float x = a[0] * b[0] + a[1] * b[2] + a[2] * b[4] + a[3];
    float y = a[0] * b[1] + a[1] * b[3] + a[2] * b[5] + a[3];
    float z = a[0] * b[2] + a[1] * b[4] + a[2] * b[6] + a[3];
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
}