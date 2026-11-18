int func0(double *p, double *q, double *r, double *s, double *t,
               double *u) {
    double v, w, x, y, z;
    int i;

    i = 0;
    while (i == 0) {
        v = (*p - *r) * (*s - *r);
        w = (*q - *r) * (*s - *r);
        x = (*r - *r) * (*s - *r);
        y = (*p - *q) * (*t - *q);
        z = (*q - *q) * (*t - *q);
        *u = v * z + w * y + x * y + x * z;
        if (*u > 0)
            i = 1;
    }
    return i;
}