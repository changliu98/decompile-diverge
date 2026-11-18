void poly_mul1(double *a, double *b, int na, int nb, double *c, int *nc) {
  int i, j;
  double t;
  *nc = na + nb;
  for (j = 0; j < 17; j++) c[j] = 0.0;
  for (i = 0; i <= na; i++) {
    t = a[i];
    for (j = 0; j <= nb; j++) c[i + j] += t * b[j];
  }
}