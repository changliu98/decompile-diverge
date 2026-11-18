int ctr_intersect(double x1, double x2, double x, double *t) {
  if ((x1 == x) || (x2 == x) || (x1 < x) == (x2 < x)) return 0;
  *t = (x - x1) / (x2 - x1);
  return 1;
}