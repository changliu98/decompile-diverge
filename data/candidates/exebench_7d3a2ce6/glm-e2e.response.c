void geom_matTvec2d(double *mat, double *vec, double *result) {
    // First component: result[0] = mat[0] * vec[0] + mat[1] * vec[1]
    result[0] = mat[0] * vec[0] + mat[1] * vec[1];
    
    // Second component: result[1] = mat[2] * vec[0] + mat[3] * vec[1]
    result[1] = mat[2] * vec[0] + mat[3] * vec[1];
}