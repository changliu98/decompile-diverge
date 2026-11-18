void load_scl_mat(float *mat, float x, float y, float z) {
    // Assuming mat is a 4x4 matrix of floats
    // mat[0][0] = x
    mat[0] = x;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    // mat[1][1] = y
    mat[4] = 0.0f;
    mat[5] = y;
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    // mat[2][2] = z
    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = z;
    mat[11] = 0.0f;

    // mat[3][3] = 1.0f
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}