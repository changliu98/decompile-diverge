double func0(double x, int n) {
  double m = pow(10.0, -n);
  double y = ceil(x / m) * m;
  y = round(y * pow(10.0, n));
  y /= pow(10.0, n);
  return y;
}