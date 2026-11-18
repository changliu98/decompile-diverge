void geom_matvec2d(double x[2], double v[2], double F[2]) {
    F[0] = x[1] * v[0] + x[0] * v[1];
    F[1] = x[0] * v[0] + x[1] * v[1];
}