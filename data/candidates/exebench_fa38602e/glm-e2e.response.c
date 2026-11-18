void params_exactN(double *a, double *b, double *c, double *d, double *e, double *f) {
    *a = 1.0;
    *b = 0.5;
    *c = 0.5 * *b;
    *d = 2.0;
    *e = *a / 3.0;
    *f = (2.0 * *e) / (*b * *b * *b);
    
    double g = *c / *b;
    double h = *a * (g * (-g) + 1.0);
    *b = h;
    *c = 0.25 * *b * *b;
}