bool ctr_intersect(double a, double b, double c, double *out) {
    if ((a - c) * (b - c) > 0.0) {
        *out = (c - a) / (b - a);
        return true;
    }
    return false;
}