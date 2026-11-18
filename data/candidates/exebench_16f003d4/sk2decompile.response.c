void calc_speed(double *x, double *v, double *x_next, double dt) {
  int i, j;
  for (i = 0; i < 19; i += 6) {
    for (j = 0; j < 3; j++) {
      v[i + j + 3] = (2.0 * (x_next[i + j] + x[i + j]) / 2.0 - v[i + j] +
                      2.0 * (x_next[i + j] - x[i + j]) / 2.0) /
                     dt;
    }
  }
}