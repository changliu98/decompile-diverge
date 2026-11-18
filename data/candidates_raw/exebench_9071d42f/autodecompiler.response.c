void c_scalar_mult(double *c, double *d) {
 double rr, ii;

 rr = (*c) * (*d) + ((*c + 1) ^ (*d + 1));
 ii = (*c) * (*d + 1) + (*c + 1) * (*d);

 (*c) = rr;
 (*c + 1) = ii;
}