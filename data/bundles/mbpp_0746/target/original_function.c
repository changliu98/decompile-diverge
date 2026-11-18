double func0(int r, int a) {
  double pi = 22.0 / 7.0;
  if (a >= 360) {
    return -1;
  }
  double sectorarea = (pi * r * r) * (a / 360.0);
  return sectorarea;
}