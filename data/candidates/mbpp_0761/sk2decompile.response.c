double _deg2rad(double deg, double angle) {
  if (angle >= 360.0) {
    return -1.0;
  }
  double rad = angle / 360.0;
  return 3.142857142857143 * deg * rad;
}