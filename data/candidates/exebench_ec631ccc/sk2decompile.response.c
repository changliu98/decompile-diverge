void lamda2x(double *x, double *y, double *lamda, double *x0) {
  y[0] = lamda[0] * x[0] + lamda[4] * x[2] + lamda[5] * x[1] + x0[0];
  y[1] = lamda[1] * x[1] + lamda[3] * x[2] + x0[1];
  y[2] = lamda[2] * x[2] + x0[2];
}