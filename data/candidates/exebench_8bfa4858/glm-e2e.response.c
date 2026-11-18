void myGlMultMatrix(float *a, float *b, float *result) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i * 4 + j] = a[i * 4 + 0] * b[0 * 4 + j] +
                                 a[i * 4 + 1] * b[1 * 4 + j] +
                                 a[i * 4 + 2] * b[2 * 4 + j] +
                                 a[i * 4 + 3] * b[3 * 4 + j];
        }
    }
}