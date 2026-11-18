double func0(double d, double a) {
  double pi = 22.0 / 7.0;
  if (a >= 360) {
    return -1;
  }
  double arclength = (pi * d) * (a / 360);
  return arclength;
}