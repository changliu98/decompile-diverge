void Mat4_T(Mat4 *mat) {
    // Swap elements across the main diagonal
    float temp;

    // mat[0][1] <-> mat[1][0]
    temp = mat->m[0][1];
    mat->m[0][1] = mat->m[1][0];
    mat->m[1][0] = temp;

    // mat[0][2] <-> mat[2][0]
    temp = mat->m[0][2];
    mat->m[0][2] = mat->m[2][0];
    mat->m[2][0] = temp;

    // mat[0][3] <-> mat[3][0]
    temp = mat->m[0][3];
    mat->m[0][3] = mat->m[3][0];
    mat->m[3][0] = temp;

    // mat[1][2] <-> mat[2][1]
    temp = mat->m[1][2];
    mat->m[1][2] = mat->m[2][1];
    mat->m[2][1] = temp;

    // mat[1][3] <-> mat[3][1]
    temp = mat->m[1][3];
    mat->m[1][3] = mat->m[3][1];
    mat->m[3][1] = temp;

    // mat[2][3] <-> mat[3][2]
    temp = mat->m[2][3];
    mat->m[2][3] = mat->m[3][2];
    mat->m[3][2] = temp;
}