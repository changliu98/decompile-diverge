void ml_multiply_mat4_vec4(const float *mat, const float *vec, float *result) {
    // The assembly accesses the matrix and vector using raw byte offsets.
    // This implies they are passed as flat arrays or the compiler completely unrolled 
    // and flattened 2D array accesses. We use pointer arithmetic to reflect the assembly exactly.
    
    float r0 = mat[0]  * vec[0] + mat[1]  * vec[1] + mat[2]  * vec[2] + mat[3]  * vec[3];
    float r1 = mat[4]  * vec[0] + mat[5]  * vec[1] + mat[6]  * vec[2] + mat[7]  * vec[3];
    float r2 = mat[8]  * vec[0] + mat[9]  * vec[1] + mat[10] * vec[2] + mat[11] * vec[3];
    float r3 = mat[12] * vec[0] + mat[13] * vec[1] + mat[14] * vec[2] + mat[15] * vec[3];

    result[0] = r0;
    result[1] = r1;
    result[2] = r2;
    result[3] = r3;
}