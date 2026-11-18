void geom_matvec4d(double *mat, double *vec, double *res) {
    res[0] = mat[0] * vec[0] + mat[4] * vec[1] + mat[8]  * vec[2] + mat[12] * vec[3];
    res[1] = mat[1] * vec[0] + mat[5] * vec[1] + mat[9]  * vec[2] + mat[13] * vec[3];
    res[2] = mat[2] * vec[0] + mat[6] * vec[1] + mat[10] * vec[2] + mat[14] * vec[3];
    res[3] = mat[3] * vec[0] + mat[7] * vec[1] + mat[11] * vec[2] + mat[15] * vec[3];
}