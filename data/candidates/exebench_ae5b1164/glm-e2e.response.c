int ctr_intersect(double a, double b, double c, double *out) {
    if ((c > a) == (c > b)) {
        return 0;
    }

    if (c == a || c == b) {
        return 0;
    }

    *out = (c - a) / (b - a);
    return 1;
}