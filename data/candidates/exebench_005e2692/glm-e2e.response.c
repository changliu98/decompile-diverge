void geom_matvec2f(float *mat, float *vec, float *res) {
    // Calculate the x component of the result
    res[0] = mat[0] * vec[0] + mat[1] * vec[1];
    
    // Calculate the y component of the result
    res[1] = mat[2] * vec[0] + mat[3] * vec[1];
}