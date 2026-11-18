void func0(double x, double y, double xscale, double yscale,
                            double *rx, double *ry) {
    *rx = xscale * x + yscale * y;
    *ry = xscale * y - yscale * x;
}