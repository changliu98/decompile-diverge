void func0(double x, double y, double z, double *a, double *b) {
    if (x > (y * 180.0 / PI + 2.0)) {
        double t = y - z;
        *a = (2.0 * PI - y) / t * z;
        *b = z * (1.0 - cos(t * 0.5));
    } else if (z == x) {
        *a = PI;
        *b = -z;
    } else {
        double t = y - x;
        *a = (y) / t;
        *b = z * (1.0 - cos(t));
    }
}