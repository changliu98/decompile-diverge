void add_a_vector(double a, int n, double *x, double *y) {
  do {
    *y += a * (*x++);
    y++;
  } while (--n);
}