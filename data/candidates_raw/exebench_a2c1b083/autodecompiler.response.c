void update(double *g, double *d, double *h, double alpha, double beta) {
  h[0] = alpha*(g[0]*d[0] + g[1]*d[3] + g[2]*d[6]) + beta*h[0];
  h[1] = alpha*(g[0]*d[1] + g[1]*d[4] + g[2]*d[7]) + beta*h[1];
  h[2] = alpha*(g[0]*d[2] + g[1]*d[5] + g[2]*d[8]) + beta*h[2];

  h[3] = alpha*(g[3]*d[0] + g[4]*d[3] + g[5]*d[6]) + beta*h[3];
  h[4] = alpha*(g[3]*d[1] + g[4]*d[4] + g[5]*d[7]) + beta*h[4];
  h[5] = alpha*(g[3]*d[2] + g[4]*d[5] + g[5]*d[8]) + beta*h[5];

  h[6] = alpha*(g[6]*d[0] + g[7]*d[3] + g[8]*d[6]) + beta*h[6];
  h[7] = alpha*(g[6]*d[1] + g[7]*d[4] + g[8]*d[7]) + beta*h[7];
  h[8] = alpha*(g[6]*d[2] + g[7]*d[5] + g[8]*d[8]) + beta*h[8];
}