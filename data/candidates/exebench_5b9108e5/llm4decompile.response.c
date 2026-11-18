void heaviside(double *first, double *last, double *res) {
  *res = 1.0;
  for (; first <= last; first++) {
    *res = *res && *first >= 0.0;
  }
}