int c_mul_(double* a, double* b, double* c, double* d, double* e, double* f) {
    double p = *a * *c + fabs(*b * *d);
    double q = *a * *d + *b * *c;
    *e = p;
    *f = q;
    return 0;
}