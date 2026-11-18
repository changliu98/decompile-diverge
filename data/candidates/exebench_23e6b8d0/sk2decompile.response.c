void lincomb(double a, double *v1, double b, double *v2, double *v3) {
  v3[0] = a * v1[0] + b * v2[0];
  v3[1] = a * v1[1] + b * v2[1];
  v3[2] = a * v1[2] + b * v2[2];
}