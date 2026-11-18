void func0(float *m) {
    float m00 = m[0], m01 = m[1], m02 = m[2], m03 = m[3];
    float m10 = m[4], m11 = m[5], m12 = m[6], m13 = m[7];
    float m20 = m[8], m21 = m[9], m22 = m[10], m23 = m[11];
    float m30 = m[12], m31 = m[13], m32 = m[14], m33 = m[15];

    float t00 = m00 + m11;
    float t11 = m00 - m11;
    float t22 = m22 + m33;
    float t33 = m22 - m33;
    float t03 = m03 + m12 - m31 - m20;
    float t12 = m03 - m12 + m31 + m20;
    float t13 = m13 + m22 - m02 - m30;
    float t23 = m13 - m22 + m02 + m30;

    m[0] = t00;
    m[1] = t11;
    m[2] = t22;
    m[3] = t33;
    m[4] = t03;
    m[5] = t12;
    m[6] = t23;
    m[7] = t13;
}