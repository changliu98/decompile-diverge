double func0(double x) {
  double y, z;
  if (x == 0) return 0;
  y = x / 2;
  z = y + 1;
  while (y != z) {
    z = y;
    y = (y + x / y) / 2;
  }
  return y;
}