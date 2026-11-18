double _calc_radius(int n, double d) {
  double r;
  r = d * d * n / (4.0 * tan(3.14159265358979323846 / n));
  return r;
}