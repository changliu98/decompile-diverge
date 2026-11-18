double func0(double a, int digits) {
  double n = pow(10, -digits);
  return round(ceil(a / n) * n * pow(10, digits)) / pow(10, digits);
}