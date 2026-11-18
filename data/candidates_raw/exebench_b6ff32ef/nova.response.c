void func0(float *a, float *b) {
    float a11 = a[0] * b[0] + a[1] * b[2];
    float a12 = a[0] * b[1] + a[1] * b[3];
    float a21 = a[2] * b[0] + a[3] * b[2];
    float a22 = a[2] * b[1] + a[3] * b[3];
    a[0] = a11;
    a[1] = a12;
    a[2] = a21;
    a[3] = a22 + b[4];
}