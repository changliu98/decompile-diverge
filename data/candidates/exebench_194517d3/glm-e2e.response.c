void geom_matvec3f(float *mat, float *vec, float *res) {
    // Row 0
    res[0] = mat[0] * vec[0] + mat[3] * vec[1] + mat[6] * vec[2];
    
    // Row 1
    res[1] = mat[1] * vec[0] + mat[4] * vec[1] + mat[7] * vec[2];
    
    // Row 2
    res[2] = mat[2] * vec[0] + mat[5] * vec[1] + mat[8] * vec[2];
}