void __cdecl geom_matTvec2d(const double *M, const double *x, double *y)
{
    // Extract vector components for readability
    double x0 = x[0];
    double x1 = x[1];

    // Compute the resulting vector components
    y[0] = M[0] * x0 + M[1] * x1;
    y[1] = M[2] * x0 + M[3] * x1;
}