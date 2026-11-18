void rsQuat_postMult(float *a, float *b) {
    float a11 = a[0], a12 = a[1], a13 = a[2], a21 = a[3], a22 = a[4], a23 = a[5],
          a31 = a[6], a32 = a[7], a33 = a[8];
    a[0] = a11 * b[0] + a12 * b[3] + a13 * b[6];
    a[1] = a21 * b[1] + a22 * b[4] + a23 * b[7];
    a[2] = a31 * b[2] + a32 * b[5] + a33 * b[8];
}