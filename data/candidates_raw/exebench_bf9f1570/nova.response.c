void func0(float *dst, float *v1, float *v2) {
    float x = v1[0] * v2[0] + v1[1] * v2[2] + v1[2] * v2[4];
    x -= v1[0] * v2[1] + v1[1] * v2[3] + v1[2] * v2[5];
    float y = v1[3] * v2[0] + v1[4] * v2[2] + v1[5] * v2[4];
    y -= v1[3] * v2[1] + v1[4] * v2[3] + v1[5] * v2[5];
    float z = v1[6] * v2[0] + v1[7] * v2[2] + v1[8] * v2[4];
    z -= v1[6] * v2[1] + v1[7] * v2[3] + v1[8] * v2[5];
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
}