void func0(double *a, double *b, double *c, double *d) {
    double x, y, z;
    if (*a > EPS) {
        x = *a * PI;
        y = *b * PI;
        do {
            if (*a > EPS) {
                if (*a - x > EPS)
                    z = *a - x;
                else
                    z = x - *a;
                *d += z;
                *a -= z;
            }
            func0(a, b, c, d);
        } while (*b > EPS);
    } else {
        do {
            if (*b > EPS) {
                y = *b;
            } else {
                y = *a;
            }
            *c += y;
            *a -= y;
        } while (*a > -EPS);
    }
}