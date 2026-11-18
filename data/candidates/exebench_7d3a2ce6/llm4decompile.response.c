void geom_matTvec2d(const double *m, const double *x, double *y)
{
    double x0 = m[0]*x[0] + m[1]*x[1];
    double x1 = m[2]*x[0] + m[3]*x[1];
    y[0] = x0;
    y[1] = x1;
}