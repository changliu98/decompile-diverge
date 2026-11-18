int zmlt_(const double *p1, const double *p2, const double *p3,
              const double *p4, double *d1, double *d2) {
    double x1 = p1[0], y1 = p1[1];
    double x2 = p2[0], y2 = p2[1];
    double x3 = p3[0], y3 = p3[1];
    double x4 = p4[0], y4 = p4[1];

    double a1 = y2 - y1;
    double b1 = x1 - x2;
    double c1 = x2 * y1 - x1 * y2;

    double a2 = y4 - y3;
    double b2 = x3 - x4;
    double c2 = x4 * y3 - x3 * y4;

    *d1 = a1 * b2 - a2 * b1;
    *d2 = b1 * c2 - b2 * c1;

    return 0;
}