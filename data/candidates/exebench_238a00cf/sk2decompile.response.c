void quad_2_grad(double *g, double *a, double *b, double *c) {
  g[0] = a[0] + b[0] * c[0] + b[1] * c[1];
  g[1] = a[1] + b[1] * c[0] + b[2] * c[1];
}