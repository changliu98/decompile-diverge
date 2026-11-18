void rotate_point(float *m) {
    float m00 = m[0], m01 = m[1], m02 = m[2], m10 = m[3], m11 = m[4], m12 = m[5],
          m20 = m[6], m21 = m[7], m22 = m[8];
    float t0 = m01 * m10 + m02 * m20, t1 = m11 * m20 + m12 * m00,
          t2 = m21 * m00 + m22 * m10;
    m[0] = m00;
    m[1] = t0;
    m[2] = t1;
    m[3] = m10;
    m[4] = m11;
    m[5] = t2;
    m[6] = m20;
    m[7] = m21;
    m[8] = m22;
}