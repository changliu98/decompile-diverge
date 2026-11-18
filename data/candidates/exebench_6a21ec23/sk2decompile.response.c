void set_mask(int *mask, int width, int x, int y) {
  int i = 0;
  if (x > 0) {
    mask[i++] = -x;
  }
  mask[i++] = y;
  mask[i++] = y - (width - x);
  mask[i++] = 0;
}