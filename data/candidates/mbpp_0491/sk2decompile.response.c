double func0(double x, int n, double r) {
  double y;
  y = x * (1.0 - pow(r, (double)n)) / (1.0 - r);
  return y;
}