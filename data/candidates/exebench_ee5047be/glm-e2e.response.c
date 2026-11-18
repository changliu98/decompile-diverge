void geom_matvec2d(double *mat, double *vec, double *res) {
    res[0] = mat[0] * vec[0] + mat[2] * vec[1];
    res[1] = mat[1] * vec[0] + mat[3] * vec[1];
}