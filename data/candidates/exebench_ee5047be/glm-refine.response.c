void __cdecl geom_matvec2d(const double *m, const double *x, double *y)
{
    // 2x2 matrix multiplied by a 2D vector
    // m is treated as a 2x2 matrix in row-major order:
    // [ m[0]  m[1] ]
    // [ m[2]  m[3] ]
    y[0] = m[0] * x[0] + m[2] * x[1];
    y[1] = m[1] * x[0] + m[3] * x[1];
}