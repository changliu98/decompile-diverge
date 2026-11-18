static int byte_col_big5(int c) {
  if (c >= 0x40 && c < 0x7f) return c - 0x40;
  if (c >= 0xa1 && c < 0xff) return c - 0x62;
  return -1;
}