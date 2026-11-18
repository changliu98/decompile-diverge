void mtx3x3Transpose(float *dst, const float *src) {
    // Transpose the 3x3 matrix
    // The diagonal elements remain in the same position
    dst[0] = src[0];
    dst[4] = src[4];
    dst[8] = src[8];

    // Swap the off-diagonal elements
    float temp;

    // Swap src[1] and src[3]
    temp = src[1];
    dst[1] = src[3];
    dst[3] = temp;

    // Swap src[2] and src[6]
    temp = src[2];
    dst[2] = src[6];
    dst[6] = temp;

    // Swap src[5] and src[7]
    temp = src[5];
    dst[5] = src[7];
    dst[7] = temp;
}