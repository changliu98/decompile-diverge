double func0(int num) {
  double d = 0.0;
  d = num;
  d = pow(d, (1.0 / 3.0));
  d = d / (125.0 * sqrt(2.0));
  d = d * 1000.0;
  d = round(d);
  d = d / 1000.0;
  return d;
}