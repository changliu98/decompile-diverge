void geom_matTvec2d(const double *A, const double *v, double *w) {
  w[0] = A[0] * v[0] + A[1] * v[1];
  w[1] = A[2] * v[0] + A[3] * v[1];
}