void func0(float *out, float *m) {
    int i, j;
    float det = 0;
    float a[3][3];
    int sign = 1;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            a[i][j] = m[i * 3 + j];
        }
    }
    det = a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2]) -
          a[1][0] * (a[0][1] * a[2][2] - a[2][1] * a[0][2]) +
          a[2][0] * (a[0][1] * a[1][2] - a[1][1] * a[0][2]);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            out[i * 3 + j] =
                (sign * (a[(i + j) % 3][(i + 1) % 3] * a[(i + 1) % 3][j])) / det;
            sign = -sign;
        }
    }
}