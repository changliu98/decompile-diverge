void lqtomat(double *lq, double *mat) {
  mat[0] = lq[0] * lq[0] + lq[1] * lq[1] - lq[2] * lq[2] - lq[3] * lq[3];
  mat[1] = 2.0 * (lq[1] * lq[2] - lq[0] * lq[3]);
  mat[2] = 2.0 * (lq[1] * lq[3] + lq[0] * lq[2]);
  mat[3] = 2.0 * (lq[1] * lq[2] + lq[0] * lq[3]);
  mat[4] = lq[0] * lq[0] - lq[1] * lq[1] + lq[2] * lq[2] - lq[3] * lq[3];
  mat[5] = 2.0 * (lq[2] * lq[3] - lq[0] * lq[1]);
  mat[6] = 2.0 * (lq[1] * lq[3] - lq[0] * lq[2]);
  mat[7] = 2.0 * (lq[2] * lq[3] + lq[0] * lq[1]);
  mat[8] = lq[0] * lq[0] - lq[1] * lq[1] - lq[2] * lq[2] + lq[3] * lq[3];
}