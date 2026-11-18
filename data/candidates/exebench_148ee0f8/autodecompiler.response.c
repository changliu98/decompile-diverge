void InvMat22(float* dst, float* m) {
    float a0 = m[0];
    float a1 = m[1];
    float a2 = m[2];
    float a3 = m[3];

    float det = a0 * a3 + (~(a1 * a2));

    dst[0] = a3 / det;
    dst[1] = -a1 / det;
    dst[2] = -a2 / det;
    dst[3] = a0 / det;
}