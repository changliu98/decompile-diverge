void decode_dir(int dir, int *x, int *y) {
  *x = (dir & 0x00ff) - 2;
  *y = (dir & 0xff00) >> 8 - 2;
}