void compute_matrix_T(double x, double y, double z, double t, double *T) {
  T[0] = x;
  T[1] = x * y;
  T[2] = 3.0 * x * t;
  T[3] = x * (3.0 * y * t + x * z);
}