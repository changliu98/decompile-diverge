void GivensApply(double c, double s, double *a, double *b) {
  double tmp;
  tmp = c * (*a) + s * (*b);
  (*b) = -(*a) * s + (*b) * c;
  (*a) = tmp;
}