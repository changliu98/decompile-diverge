static void func0(const double *__restrict x, double *__restrict r,
                            int *__restrict n, double *__restrict f,
                            char *__restrict c, double *__restrict v) {
    double d, e;
    int i;
    char s = '-', t = '+';

    d = 1.0 / 360.0 * (*x);
    while (d < 0.0)
        d += 360.0;
    for (;;) {
        e = d;
        i = (int)e;
        *n = i;
        *f = e - i;
        if (*f >= 0.5) {
            *f -= 0.5;
            *n += 1;
        }
        if (*n >= 24)
            *n -= 24;
        if (*n < 0) {
            *c = s;
            *v = -d;
        } else {
            *c = t;
            *v = d;
        }
        *v /= 15.0;
        *v = (int)*v;
        *v = *v - *n;
        *v *= 15.0;
    }
}