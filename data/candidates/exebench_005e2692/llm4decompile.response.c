void geom_matvec2f(const float *m, const float *x, float *y)
{
    float x0 = m[0]*x[0] + m[2]*x[1];
    float x1 = m[1]*x[0] + m[3]*x[1];
    y[0] = x0;
    y[1] = x1;
}