int ctr_intersect(double a, double b, double c, double *t) {
  if ((a - c) * (b - c) < 0.0) {
    *t = (c - a) / (b - a);
    return 1;
  } else {
    return 0;
  }
}