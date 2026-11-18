int metric(double *x, double *u, double *par, double *g) {
  int i;
  for (i = 0; i < 9; i++) g[i] = 0.0;
  g[0] = 1.0;
  g[4] = 1.0;
  g[8] = 1.0;
  return 0;
}