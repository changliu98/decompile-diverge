void zywrleCalcSize(int *width, int *height, int bits) {
  int mask;
  mask = (1 << bits) - 1;
  *width &= ~mask;
  *height &= ~mask;
}