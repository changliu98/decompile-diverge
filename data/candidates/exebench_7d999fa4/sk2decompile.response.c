static int bkm_scale(long *x, int scale) {
  long y;
  y = *x * scale;
  if (y / scale != *x) return 1;
  *x = y;
  return 0;
}