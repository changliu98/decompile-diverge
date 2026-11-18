void point_computing(double *w, double *x, double *y, double *px, double *py) {
  double sum;
  sum = w[0] + w[1] + w[2] + w[3];
  *px = (w[0] * x[0] + w[1] * x[1] + w[2] * x[2] + w[3] * x[3]) / sum;
  *py = (w[0] * y[0] + w[1] * y[1] + w[2] * y[2] + w[3] * y[3]) / sum;
}