void dgrad(double *grad, double *g, double *H, double *r)
{
  grad[0] = g[0] + H[0]*r[0] + H[1]*r[1];
  grad[1] = g[1] + H[1]*r[0] + H[2]*r[1];
}