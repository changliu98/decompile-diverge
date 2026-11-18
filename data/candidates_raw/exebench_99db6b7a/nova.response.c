void func0(float *m, float s) {
    float m00 = m[0], m01 = m[1], m02 = m[2], m03 = m[3];
    float m10 = m[4], m11 = m[5], m12 = m[6], m13 = m[7];
    float m20 = m[8], m21 = m[9], m22 = m[10], m23 = m[11];
    float m30 = m[12], m31 = m[13], m32 = m[14], m33 = m[15];
    m[0] = m00 * s;
    m[1] = m01 * s;
    m[2] = m02 * s;
    m[3] = m03 * s;
    m[4] = m10 * s;
    m[5] = m11 * s;
    m[6] = m12 * s;
    m[7] = m13 * s;
    m[8] = m20 * s;
    m[9] = m21 * s;
    m[10] = m22 * s;
    m[11] = m23 * s;
    m[12] = m30 * s;
    m[13] = m31 * s;
    m[14] = m32 * s;
    m[15] = m33 * s;
}