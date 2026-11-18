double __cdecl lagrange4(double *x, float *y, double t)
{
    // Unrolled x (temp) and y (q) array accesses for readability
    double x0 = x[0], x1 = x[1], x2 = x[2], x3 = x[3];
    double y0 = y[0], y1 = y[1], y2 = y[2], y3 = y[3];

    // Precompute the differences between the evaluation point t and the nodes
    double t_x0 = t - x0;
    double t_x1 = t - x1;
    double t_x2 = t - x2;
    double t_x3 = t - x3;

    // Precompute the denominators (Lagrange basis polynomial evaluations at nodes)
    double d0 = (x0 - x1) * (x0 - x2) * (x0 - x3);
    double d1 = (x1 - x0) * (x1 - x2) * (x1 - x3);
    double d2 = (x2 - x0) * (x2 - x1) * (x2 - x3);
    double d3 = (x3 - x0) * (x3 - x1) * (x3 - x2);

    // Compute the 4th-order Lagrange interpolation
    return (y0 * t_x1 * t_x2 * t_x3 / d0)
         + (y1 * t_x0 * t_x2 * t_x3 / d1)
         + (y2 * t_x0 * t_x1 * t_x3 / d2)
         + (y3 * t_x0 * t_x1 * t_x2 / d3);
}