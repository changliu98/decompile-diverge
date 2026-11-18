void mlMatrixTransposeTo(float *dst, const float *src) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dst[j * 4 + i] = src[i * 4 + j];
        }
    }
}