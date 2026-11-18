void Mat4_Translate(float *mat, const float *vec) {
    // Column 0 * vec.x
    mat[12] += mat[0] * vec[0] + mat[4] * vec[1] + mat[8] * vec[2];
    
    // Column 1 * vec.y
    mat[13] += mat[1] * vec[0] + mat[5] * vec[1] + mat[9] * vec[2];
    
    // Column 2 * vec.z
    mat[14] += mat[2] * vec[0] + mat[6] * vec[1] + mat[10] * vec[2];
}