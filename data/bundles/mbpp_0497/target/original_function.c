double func0(double r, double h) {
  double l = sqrt(r * r + h * h);
  double SA = M_PI * r * (r + l);
  return SA;
}