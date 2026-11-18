int CalcOffsetAndShift(int x, int y, unsigned int *offset, unsigned int *shift) {
  if (x < 0 || x >= 84 || y < 0 || y >= 48) return -1;
  if (offset == NULL || shift == NULL) return -1;
  *offset = x + (y / 8) * 84;
  *shift = y % 8;
  return 0;
}