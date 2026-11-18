void geom_matmat2d(double *matrix_a, double *matrix_b, double *matrix_c)
{
    // c[0] = a[0]*b[0] + a[1]*b[2]
    *matrix_c = *matrix_a * *matrix_b + matrix_a[2] * matrix_b[1];
    // c[1] = a[2]*b[0] + a[3]*b[2]
    matrix_c[1] = matrix_a[1] * *matrix_b + matrix_a[3] * matrix_b[1];
    // c[2] = a[0]*b[1] + a[1]*b[3]
    matrix_c[2] = *matrix_a * matrix_b[2] + matrix_a[2] * matrix_b[3];
    // c[3] = a[2]*b[1] + a[3]*b[3]
    matrix_c[3] = matrix_a[1] * matrix_b[2] + matrix_a[3] * matrix_b[3];
}