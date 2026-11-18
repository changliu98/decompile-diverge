void func0(float *mat, float s) {
    float m00 = mat[0 * 3 + 0];
    float m01 = mat[0 * 3 + 1];
    float m02 = mat[0 * 3 + 2];
    float m10 = mat[1 * 3 + 0];
    float m11 = mat[1 * 3 + 1];
    float m12 = mat[1 * 3 + 2];
    float m20 = mat[2 * 3 + 0];
    float m21 = mat[2 * 3 + 1];
    float m22 = mat[2 * 3 + 2];

    mat[0 * 3 + 0] = m00 * s;
    mat[0 * 3 + 1] = m01 * s;
    mat[0 * 3 + 2] = m02 * s;
    mat[1 * 3 + 0] = m10 * s;
    mat[1 * 3 + 1] = m11 * s;
    mat[1 * 3 + 2] = m12 * s;
    mat[2 * 3 + 0] = m20 * s;
    mat[2 * 3 + 1] = m21 * s;
    mat[2 * 3 + 2] = m22 * s;
}