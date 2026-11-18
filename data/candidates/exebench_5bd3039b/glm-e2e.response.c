void mul_mat_vec_2(float *mat, float *vec, float *res) {
    // First row of matrix multiplied by the vector
    res[0] = mat[0] * vec[0] + mat[1] * vec[1];
    
    // Second row of matrix multiplied by the vector
    res[1] = mat[2] * vec[0] + mat[3] * vec[1];
}