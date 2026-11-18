double GO_frexp(double x, int *exp) {
  double y = x;
  int e = 0;
  double sign = 1.0;
  if (y < 0.0) {
    y = -y;
    sign = -1.0;
  }
  if (y != 0.0) {
    while (y >= 1.0) {
      y /= 2.0;
      e++;
    }
    while (y < 0.5) {
      y *= 2.0;
      e--;
    }
  }
  *exp = e;
  return y * sign;
}