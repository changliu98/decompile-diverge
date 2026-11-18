double func0(int r, int theta) {
  double theta_d;
  if (theta >= 360) {
    return -1;
  }
  theta_d = (double)theta / 360;
  return 3.142857142857143 * (double)r * (double)r * theta_d;
}