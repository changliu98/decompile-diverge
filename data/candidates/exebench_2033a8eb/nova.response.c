void complexMultiplicationRI(double x, double y, double xscale, double yscale,
                      double *xmin, double *ymin) {
    *xmin = (x * xscale) + (-y * yscale) + (-1 * xscale);
    *ymin = (y * xscale) + (-x * yscale) + (-1 * yscale);
}